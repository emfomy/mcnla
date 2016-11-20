////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    demo/demo1.cpp
/// @brief   The demo code (generate A using normal random)
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#include <iostream>
#include <iomanip>
#include <valarray>
#include <mcnla.hpp>

using ScalarType = double;

ScalarType tolerance = 1e-4;
mcnla::index_t maxiter = 256;

class StatisticsSet {
 private:
  std::valarray<double> set_;
  std::valarray<double> diff_;
  size_t size_;

 public:
  StatisticsSet( const int capacity ) : set_(capacity), diff_(capacity), size_(0) {};
  void operator()( const double value ) { assert(size_ < set_.size()); set_[size_++] = value; }
  double mean() { return set_.sum() / set_.size(); }
  double var() { diff_ = set_ - mean(); diff_ *= diff_; return diff_.sum() / diff_.size(); };
  double sd() { return std::sqrt(var()); };
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Main function
///
int main( int argc, char **argv ) {

  // ====================================================================================================================== //
  // Initialize MPI
  MPI_Init(&argc, &argv);
  mcnla::mpi_int_t mpi_root = 0;
  mcnla::mpi_int_t mpi_size = mcnla::mpi::getCommSize(MPI_COMM_WORLD);
  mcnla::mpi_int_t mpi_rank = mcnla::mpi::getCommRank(MPI_COMM_WORLD);

  // ====================================================================================================================== //
  // Display program information
  if ( mpi_rank == mpi_root ) {
    std::cout << "MCNLA "
              << MCNLA_MAJOR_VERSION << "."
              << MCNLA_MINOR_VERSION << "."
              << MCNLA_PATCH_VERSION << " demo" << std::endl << std::endl;
  }

  // ====================================================================================================================== //
  // Initialize random seed
  srand(time(NULL) ^ mpi_rank);
  srand(rand());
  mcnla::index_t seed[4] = {rand()%4096, rand()%4096, rand()%4096, (rand()%2048)*2+1};

  // ====================================================================================================================== //
  // Set parameters
  int argi = 0;
  mcnla::index_t Nj       = ( argc > ++argi ) ? atoi(argv[argi]) : 4;
  mcnla::index_t m        = ( argc > ++argi ) ? atoi(argv[argi]) : 1000;
  mcnla::index_t n        = ( argc > ++argi ) ? atoi(argv[argi]) : 10000;
  mcnla::index_t k        = ( argc > ++argi ) ? atoi(argv[argi]) : 10;
  mcnla::index_t p        = ( argc > ++argi ) ? atoi(argv[argi]) : 0;
  mcnla::index_t num_test = ( argc > ++argi ) ? atoi(argv[argi]) : 100;
  assert(k <= m && m <= n);
  if ( mpi_rank == mpi_root ) {
    std::cout << "m = " << m
            << ", n = " << n
            << ", k = " << k
            << ", p = " << p
            << ", N = " << Nj*mpi_size
            << ", K = " << mpi_size << std::endl << std::endl;
  }

  // ====================================================================================================================== //
  // Create statistics collector
  StatisticsSet set_time(num_test), set_time_s(num_test), set_time_i(num_test), set_time_r(num_test), set_iter(num_test);

  // ====================================================================================================================== //
  // Initialize solver
  mcnla::matrix::DenseMatrix<ScalarType> matrix_a(m, n), matrix_u_true;
  mcnla::isvd::Solver<mcnla::matrix::DenseMatrix<ScalarType>,
                      mcnla::isvd::GaussianProjectionSketcher<mcnla::matrix::DenseMatrix<ScalarType>>,
                      mcnla::isvd::KolmogorovNagumoIntegrator<mcnla::matrix::DenseMatrix<ScalarType>>,
                      mcnla::isvd::StandardReconstructor<mcnla::matrix::DenseMatrix<ScalarType>>> solver(MPI_COMM_WORLD);
  solver.setSize(matrix_a).setRank(k).setOverRank(p).setNumSketchEach(Nj).setSeed(seed);
  solver.setTolerance(tolerance).setMaxIteration(maxiter);
  solver.initialize();
  if ( mpi_rank == mpi_root ) {
    std::cout << "Uses " << solver.getSketcherName() << "." << std::endl;
    std::cout << "Uses " << solver.getIntegratorName() << "." << std::endl;
    std::cout << "Uses " << solver.getReconstructorName() << "." << std::endl << std::endl;
  }

  // ====================================================================================================================== //
  // Generate matrix
  if ( mpi_rank == mpi_root ) {
    std::cout << "Generate A using normal random." << std::endl << std::endl;
    mcnla::lapack::larnv<3>(matrix_a.vectorize(), seed);
  }
  mcnla::mpi::bcast(matrix_a, mpi_root, MPI_COMM_WORLD);

  // ====================================================================================================================== //
  // Run MCNLA
  if ( mpi_rank == mpi_root ) {
    std::cout << "Start iSVD." << std::endl << std::endl;
    std::cout << std::fixed << std::setprecision(6);
  }

  for ( mcnla::index_t t = 0; t < num_test; ++t ) {

    // Run solver
    MPI_Barrier(MPI_COMM_WORLD);
    solver.compute(matrix_a);
    MPI_Barrier(MPI_COMM_WORLD);

    // Check result
    if ( mpi_rank == mpi_root ) {
      auto iter    = solver.getIntegratorIter();
      auto maxiter = solver.getParameters().getMaxIteration();
      auto time_s = solver.getSketcherTime();
      auto time_i = solver.getIntegratorTime();
      auto time_r = solver.getReconstructorTime();
      auto time = time_s + time_i + time_r;
      std::cout << std::setw(log10(num_test)+1) << t
                << " | time: " << time << " (" << time_s << " / " << time_i << " / " << time_r << ")"
                << " | iter: " << std::setw(log10(maxiter)+1) << iter << std::endl;
      set_time(time); set_time_s(time_s); set_time_r(time_r); set_time_i(time_i); set_iter(iter);
    }
  }

  // Display statistics results
  if ( mpi_rank == mpi_root ) {
    std::cout << std::endl;
    std::cout << "Average total computing time: " << set_time.mean() << " seconds." << std::endl;
    std::cout << "Average sketching time:       " << set_time_s.mean() << " seconds." << std::endl;
    std::cout << "Average integrating time:     " << set_time_i.mean() << " seconds." << std::endl;
    std::cout << "Average reconstructing time:  " << set_time_r.mean() << " seconds." << std::endl;
    std::cout << "mean(iter) = " << set_iter.mean() << std::endl;
    std::cout << "sd(iter)   = " << set_iter.sd() << std::endl;
  }

  MPI_Finalize();
}