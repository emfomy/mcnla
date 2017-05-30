////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    report/stage.hpp
/// @brief   The report for a stage.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_REPORT_STAGE_HPP_
#define MCNLA_REPORT_STAGE_HPP_

#include <iostream>
#include <mcnla.hpp>
#include <omp.h>
#include "../demo/statistics_set.hpp"

#define STR_(x) #x
#define STR(y) STR_(y)

#ifndef Stage
#error  Stage is undefined!
#endif  // Stage

using StageType = mcnla::isvd::Stage<ValType>;

mcnla::index_t Nj, m, n, k, p, l, num_test, skip_test;

void setParam( mcnla::isvd::Parameters<ValType> &parameters, int &num_test, int &skip_test, int argc, char **argv ) noexcept;
void dispParam() noexcept;
void setStage( StageType &stage ) noexcept;
void runStage( StageType &stage, Data &data ) noexcept;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Main function
///
int main( int argc, char **argv ) {

  // ====================================================================================================================== //
  // Initialize MPI
  mcnla::init(argc, argv);
  auto mpi_comm = MPI_COMM_WORLD;
  auto mpi_size = mcnla::mpi::commSize(mpi_comm);
  auto mpi_rank = mcnla::mpi::commRank(mpi_comm);
  auto mpi_root = 0;

  // ====================================================================================================================== //
  // Display program information
  if ( mpi_rank == mpi_root ) {
    std::cout << "MCNLA "
              << MCNLA_MAJOR_VERSION << "."
              << MCNLA_MINOR_VERSION << "."
              << MCNLA_PATCH_VERSION << " report for " << STR(Stage) << std::endl << std::endl;
  }

  // ====================================================================================================================== //
  // Initializes
  int num_test, skip_test;

  mcnla::isvd::Parameters<ValType> parameters(mpi_root, mpi_comm);
  setParam(parameters, num_test, skip_test, argc, argv);
  parameters.sync();

  if ( mpi_rank == mpi_root ) {
    std::cout << "m = " << parameters.nrow()
            << ", n = " << parameters.ncol()
            << ", k = " << parameters.rank()
            << ", p = " << parameters.overRank()
            << ", N = " << parameters.numSketch() << std::endl;
    dispParam();
    std::cout << mpi_size << " nodes / "
#ifdef _OPENMP
              << omp_get_max_threads()
#else  // _OPENMP
              << 1
#endif  // _OPENMP
              << " threads per node" << std::endl << std::endl;
  }

  StageType stage(parameters);
  setStage(stage);
  stage.initialize();

  Data data(parameters);

  // ====================================================================================================================== //
  // Create statistics collector
  StatisticsSet set_time(num_test), set_comm_time(num_test);
  std::vector<StatisticsSet> set_times, set_comm_times;

  // ====================================================================================================================== //
  // Run stage
  if ( mpi_rank == mpi_root ) {
    std::cout << "Uses " << stage << "." << std::endl << std::endl;
    std::cout << std::setw(log10(num_test)+2) << "" << "   total time (" << stage.names() << ")" << std::endl << std::endl;
    std::cout << std::fixed << std::setprecision(6);
  }

  for ( int t = -skip_test; t < num_test; ++t ) {

    // Run stage
    MPI_Barrier(mpi_comm);
    runStage(stage, data);
    MPI_Barrier(mpi_comm);

    // Check result
    if ( mpi_rank == mpi_root ) {

      auto time       = stage.time();
      auto times      = stage.times();
      auto comm_time  = stage.commTime();
      auto comm_times = stage.commTimes();

      std::cout << std::setw(log10(num_test)+2) << t << " | time: " << time << " (";
      if ( t >= 0 ) {
        set_time(time);
      }

      for ( size_t i = 0; i < times.size(); ++i ) {
        if ( i > 0 ) {
          std::cout << " / ";
        }
        std::cout << times[i];

        if ( t == 0 ) {
          set_times.emplace_back(num_test);
        }

        if ( t >= 0 ) {
          set_times[i](times[i]);
        }
      }

      std::cout << ") | communication: " << comm_time << " (";
      if ( t >= 0 ) {
        set_comm_time(comm_time);
      }

      for ( size_t i = 0; i < comm_times.size(); ++i ) {
        if ( i > 0 ) {
          std::cout << " / ";
        }
        std::cout << comm_times[i];

        if ( t == 0 ) {
          set_comm_times.emplace_back(num_test);
        }

        if ( t >= 0 ) {
          set_comm_times[i](comm_times[i]);
        }
      }

      std::cout << ")" << std::endl;
    }
  }

  // Display statistics results
  if ( mpi_rank == mpi_root ) {
    std::cout << std::endl << std::setw(log10(num_test)+2) << "Avg" << " | time: " << set_time.mean() << " (";

    for ( size_t i = 0; i < set_times.size(); ++i ) {
      if ( i > 0 ) {
        std::cout << " / ";
      }
      std::cout << set_times[i].mean();
    }

    std::cout << ") | communication: " << set_comm_time.mean() << " (";

    for ( size_t i = 0; i < set_comm_times.size(); ++i ) {
      if ( i > 0 ) {
        std::cout << " / ";
      }
      std::cout << set_comm_times[i].mean();
    }

    std::cout << ")" << std::endl << std::endl;
  }

  mcnla::finalize();
}

#endif  // MCNLA_REPORT_STAGE_HPP_
