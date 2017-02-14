////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    demo/demo_kn.cpp
/// @brief   The demo code of Kolmogorov-Nagumo-type integrator
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#include <iostream>
#include <mcnla.hpp>
#include "statistics_set.hpp"

using ScalarType = double;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Main function
///
int main( int argc, char **argv ) {

  // ====================================================================================================================== //
  // Initialize MPI
  MPI_Init(&argc, &argv);
  mcnla::mpi_int_t mpi_root = 0;
  mcnla::mpi_int_t mpi_size = mcnla::mpi::commSize(MPI_COMM_WORLD);
  mcnla::mpi_int_t mpi_rank = mcnla::mpi::commRank(MPI_COMM_WORLD);

  // ====================================================================================================================== //
  // Display program information
  if ( mpi_rank == mpi_root ) {
    std::cout << "MCNLA "
              << MCNLA_MAJOR_VERSION << "."
              << MCNLA_MINOR_VERSION << "."
              << MCNLA_PATCH_VERSION << " KN demo" << std::endl << std::endl;
  }

  // ====================================================================================================================== //
  // Initialize random seed
  srand(time(NULL) ^ mpi_rank);

  // ====================================================================================================================== //
  // Set parameters
  int argi = 0;
  mcnla::index_t Nj        = ( argc > ++argi ) ? atoi(argv[argi]) : 4;
  mcnla::index_t m         = ( argc > ++argi ) ? atoi(argv[argi]) : 1000;
  mcnla::index_t l         = ( argc > ++argi ) ? atoi(argv[argi]) : 100;
  mcnla::index_t num_test  = ( argc > ++argi ) ? atoi(argv[argi]) : 10;
  mcnla::index_t skip_test = ( argc > ++argi ) ? atoi(argv[argi]) : 5;
  ScalarType     tol       = ( argc > ++argi ) ? atof(argv[argi]) : -1;
  mcnla::index_t maxiter   = ( argc > ++argi ) ? atoi(argv[argi]) : 256;
  assert(l <= m);
  if ( mpi_rank == mpi_root ) {
    std::cout << "m = " << m
            << ", l = " << l
            << ", N = " << Nj*mpi_size
            << ", K = " << mpi_size
            << ", tol = " << tol
            << ", maxiter = " << maxiter << std::endl << std::endl;
  }

  // ====================================================================================================================== //
  // Create statistics collector
  StatisticsSet set_time(num_test), set_time1(num_test), set_time2(num_test), set_time3(num_test);

  // ====================================================================================================================== //
  // Initialize driver
  mcnla::isvd::Solver<ScalarType,
                      mcnla::isvd::GaussianProjectionSketcherTag<0>,
                      mcnla::isvd::SvdOrthogonalizerTag,
                      mcnla::isvd::KolmogorovNagumoIntegratorTag,
                      mcnla::isvd::DummyFormerTag> driver(MPI_COMM_WORLD);
  driver.setSize(m, m).setRank(l).setOverRank(0).setNumSketchEach(Nj);
  driver.setTolerance(tol).setMaxIteration(maxiter).setSeeds(rand());
  driver.initialize();
  auto sketcher = driver.sketcher();
  auto orthogonalizer = driver.orthogonalizer();
  auto integrator = driver.integrator();
  if ( mpi_rank == mpi_root ) {
    std::cout << "Uses " << integrator << "." << std::endl;
  }

  // ====================================================================================================================== //
  // Generate matrix
  mcnla::matrix::DenseDiagonalMatrix<ScalarType> matrix_a(m);
  auto integrator_qs = integrator.collectionQ();
  decltype(integrator_qs) collection_q(integrator_qs.sizes());
  for ( auto &v : matrix_a.viewVector() ) {
    v = 1.0;
  }
  sketcher.sketch(matrix_a, collection_q);
  orthogonalizer.orthogonalize(collection_q);

  // ====================================================================================================================== //
  // Run MCNLA
  if ( mpi_rank == mpi_root ) {
    std::cout << "Start KN." << std::endl << std::endl;
    std::cout << std::fixed << std::setprecision(6);
  }

  for ( int t = -skip_test; t < num_test; ++t ) {

    // Copy data
    mcnla::la::copy(collection_q.unfold(), integrator_qs.unfold());

    // Run driver
    MPI_Barrier(MPI_COMM_WORLD);
    integrator.integrate();
    MPI_Barrier(MPI_COMM_WORLD);

    // Check result
    if ( mpi_rank == mpi_root  ) {
      auto time = integrator.time();
      auto time1 = integrator.time1();
      auto time2 = integrator.time2();
      auto time3 = integrator.time3();
      std::cout << std::setw(log10(num_test)+1) << t
                << " | time: " << time << " (" << time1 << " / " << time2 << " / " << time3 << ")" << std::endl;
      if ( t >= 0 ) {
        set_time(time); set_time1(time1); set_time2(time2); set_time3(time3);
      }
    }
  }

  // Display statistics results
  if ( mpi_rank == mpi_root ) {
    std::cout << std::endl;
    std::cout << "Average total integrating time: " << set_time.mean()  << " seconds." << std::endl;
    std::cout << "Average time of rearrangeing Q: " << set_time1.mean() << " seconds." << std::endl;
    std::cout << "Average time of integrating Q:  " << set_time2.mean() << " seconds." << std::endl;
    std::cout << "Average time of gathering Qc:   " << set_time3.mean() << " seconds." << std::endl;
    std::cout << std::endl;
  }

  MPI_Finalize();
}
