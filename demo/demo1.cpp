////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    demo/demo1.cpp
/// @brief   The demo code
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#include <iostream>
#include <mcnla.hpp>
#include "statistics_set.hpp"

using ScalarType = double;

ScalarType tolerance = 1e-4;
mcnla::index_t maxiter = 256;

void create( mcnla::matrix::DenseMatrix<ScalarType> &matrix_a,
             const mcnla::index_t rank, mcnla::index_t seed[4] ) noexcept;

template <mcnla::Layout _layout>
void check( const mcnla::matrix::DenseMatrix<ScalarType, _layout> &matrix_a,
            const mcnla::matrix::DenseMatrix<ScalarType, _layout> &matrix_u,
            const mcnla::matrix::DenseMatrix<ScalarType, _layout> &matrix_vt,
            const mcnla::matrix::DenseVector<ScalarType> &vector_s,
            ScalarType &frerr ) noexcept;

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
  mcnla::index_t Nj        = ( argc > ++argi ) ? atoi(argv[argi]) : 4;
  mcnla::index_t m         = ( argc > ++argi ) ? atoi(argv[argi]) : 1000;
  mcnla::index_t n         = ( argc > ++argi ) ? atoi(argv[argi]) : 10000;
  mcnla::index_t k         = ( argc > ++argi ) ? atoi(argv[argi]) : 100;
  mcnla::index_t p         = ( argc > ++argi ) ? atoi(argv[argi]) : 0;
  mcnla::index_t num_test  = ( argc > ++argi ) ? atoi(argv[argi]) : 10;
  mcnla::index_t skip_test = ( argc > ++argi ) ? atoi(argv[argi]) : 5;
  assert(k <= m && m <= n);
  if ( mpi_rank == mpi_root ) {
    std::cout << "m = " << m
            << ", n = " << n
            << ", k = " << k
            << ", p = " << p
            << ", N = " << Nj*mpi_size
            << ", K = " << mpi_size << std::endl
            << "tolerance = " << tolerance
            << ", maxiter = " << maxiter << std::endl << std::endl;
  }

  // ====================================================================================================================== //
  // Create statistics collector
  StatisticsSet set_frerr(num_test),  set_iter(num_test),    set_time(num_test),
                set_time_s(num_test), set_time_s1(num_test), set_time_s2(num_test), set_time_s3(num_test),
                set_time_i(num_test), set_time_i1(num_test), set_time_i2(num_test), set_time_i3(num_test),
                set_time_f(num_test), set_time_f1(num_test), set_time_f2(num_test), set_time_f3(num_test);

  // ====================================================================================================================== //
  // Initialize solver
  mcnla::matrix::DenseMatrix<ScalarType> matrix_a(m, n);
  mcnla::isvd::Solver<mcnla::matrix::DenseMatrix<ScalarType>,
                      mcnla::isvd::GaussianProjectionSketcher<mcnla::matrix::DenseMatrix<ScalarType>>,
                      mcnla::isvd::KolmogorovNagumoIntegrator<mcnla::matrix::DenseMatrix<ScalarType>>,
                      mcnla::isvd::SvdFormer<mcnla::matrix::DenseMatrix<ScalarType>>> solver(MPI_COMM_WORLD);
  solver.setSize(matrix_a).setRank(k).setOverRank(p).setNumSketchEach(Nj).setSeed(seed);
  solver.setTolerance(tolerance).setMaxIteration(maxiter);
  solver.initialize();
  if ( mpi_rank == mpi_root ) {
    std::cout << "Uses " << solver.getSketcher() << "." << std::endl;
    std::cout << "Uses " << solver.getIntegrator() << "." << std::endl;
    std::cout << "Uses " << solver.getFormer() << "." << std::endl << std::endl;
  }

  // ====================================================================================================================== //
  // Generate matrix
  if ( mpi_rank == mpi_root ) {
    std::cout << "A = Uk Sk Vk' + E; E~N(0, 1/(k+p))." << std::endl << std::endl;
    create(matrix_a, k, seed);
  }
  mcnla::mpi::bcast(matrix_a, mpi_root, MPI_COMM_WORLD);

  // ====================================================================================================================== //
  // Run MCNLA
  if ( mpi_rank == mpi_root ) {
    std::cout << "Start iSVD." << std::endl << std::endl;
    std::cout << std::fixed << std::setprecision(6);
  }

  for ( int t = -skip_test; t < num_test; ++t ) {

    // Run solver
    MPI_Barrier(MPI_COMM_WORLD);
    solver.compute(matrix_a);
    MPI_Barrier(MPI_COMM_WORLD);

    // Check result
    if ( mpi_rank == mpi_root ) {
      ScalarType frerr;
      check(matrix_a, solver.getLeftSingularVectors(), solver.getRightSingularVectors(), solver.getSingularValues(), frerr);
      auto iter    = solver.getIntegratorIter();
      auto maxiter = solver.getParameters().getMaxIteration();
      auto time_s = solver.getSketcherTime();
      auto time_i = solver.getIntegratorTime();
      auto time_f = solver.getFormerTime();
      auto times_s = solver.getSketcherTimes();
      auto times_i = solver.getIntegratorTimes();
      auto times_r = solver.getFormerTimes();
      auto time = time_s + time_i + time_f;
      std::cout << std::setw(log10(num_test)+1) << t
                << " | error: " << frerr
                << " | iter: " << std::setw(log10(maxiter)+1) << iter
                << " | time: " << time << " (" << time_s << " / " << time_i << " / " << time_f << ")" << std::endl;
      if ( t >= 0 ) {
        set_frerr(frerr); set_iter(iter); set_time(time); set_time_s(time_s); set_time_f(time_f); set_time_i(time_i);
        set_time_s1(times_s.at(0)); set_time_s2(times_s.at(1)); set_time_s3(times_s.at(2));
        set_time_f1(times_r.at(0)); set_time_f2(times_r.at(1)); set_time_f3(times_r.at(2));
        set_time_i1(times_i.at(0)); set_time_i2(times_i.at(1)); set_time_i3(times_i.at(2));
      }
    }
  }

  // Display statistics results
  if ( mpi_rank == mpi_root ) {
    std::cout << std::endl;
    std::cout << "Average total computing time: " << set_time.mean()   << " seconds." << std::endl;
    std::cout << "Average sketching time:       " << set_time_s.mean() << " seconds: \t"
                                                  << set_time_s1.mean() << ", \t"
                                                  << set_time_s2.mean() << ", \t"
                                                  << set_time_s3.mean() << std::endl;
    std::cout << "Average integrating time:     " << set_time_i.mean() << " seconds: \t"
                                                  << set_time_i1.mean() << ", \t"
                                                  << set_time_i2.mean() << ", \t"
                                                  << set_time_i3.mean() << std::endl;
    std::cout << "Average forming time:         " << set_time_f.mean() << " seconds: \t"
                                                  << set_time_f1.mean() << ", \t"
                                                  << set_time_f2.mean() << ", \t"
                                                  << set_time_f3.mean() << std::endl;
    std::cout << "error: \tmean = " << set_frerr.mean() << ", \tsd = " << set_frerr.sd() << std::endl;
    std::cout << "iter:  \tmean = " << set_iter.mean()  << ", \tsd = " << set_iter.sd() << std::endl;
    std::cout << std::endl;
    std::cout << "error = norm(A-USV')_F/norm(A)_F" << std::endl;
  }

  MPI_Finalize();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Create matrix A
///
void create(
          mcnla::matrix::DenseMatrix<ScalarType> &matrix_a,
    const mcnla::index_t rank,
          mcnla::index_t seed[4]
) noexcept {
  mcnla::matrix::DenseMatrix<ScalarType> matrix_u(matrix_a.nrow(), rank);
  mcnla::matrix::DenseMatrix<ScalarType> matrix_v(matrix_a.ncol(), rank);
  mcnla::matrix::DenseMatrix<ScalarType> matrix_empty;
  mcnla::matrix::DenseVector<ScalarType> vector_s(rank);

  // Generate A & U & V using normal random
  mcnla::la::larnv<3>(matrix_a.vectorize(), seed);
  mcnla::la::larnv<3>(matrix_u.vectorize(), seed);
  mcnla::la::larnv<3>(matrix_v.vectorize(), seed);

  // Orthogonalize U & V
  mcnla::la::gesvd<'O', 'N'>(matrix_u, vector_s, matrix_empty, matrix_empty);
  mcnla::la::gesvd<'O', 'N'>(matrix_v, vector_s, matrix_empty, matrix_empty);

  // A := U * S * V'
  for ( mcnla::index_t i = 0; i < rank; ++i ) {
    mcnla::la::scal(1.0/(i+1), matrix_u.getCol(i));
  }
  ScalarType tmp = 1.0 / rank / mcnla::la::nrmf(matrix_a);
  mcnla::la::gemm<mcnla::Trans::NORMAL, mcnla::Trans::TRANS>(1.0, matrix_u, matrix_v, tmp, matrix_a);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Check the result
///
template <mcnla::Layout _layout>
void check(
    const mcnla::matrix::DenseMatrix<ScalarType, _layout> &matrix_a,
    const mcnla::matrix::DenseMatrix<ScalarType, _layout> &matrix_u,
    const mcnla::matrix::DenseMatrix<ScalarType, _layout> &matrix_vt,
    const mcnla::matrix::DenseVector<ScalarType>          &vector_s,
          ScalarType &frerr
) noexcept {
  mcnla::matrix::DenseMatrix<ScalarType, _layout> matrix_a_tmp(matrix_a.sizes());
  mcnla::matrix::DenseMatrix<ScalarType, _layout> matrix_u_tmp(matrix_u.sizes());

  // A_tmp := A, U_tmp = U
  mcnla::la::copy(matrix_a, matrix_a_tmp);
  mcnla::la::copy(matrix_u, matrix_u_tmp);

  // A_tmp -= U * S * V'
  for ( auto i = 0; i < vector_s.length(); ++i ) {
    mcnla::la::scal(vector_s(i), matrix_u_tmp.getCol(i));
  }
  mcnla::la::gemm<mcnla::Trans::NORMAL, mcnla::Trans::NORMAL>(-1.0, matrix_u_tmp, matrix_vt, 1.0, matrix_a_tmp);

  // frerr := norm(A_tmp)_F / norm(A)_F
  frerr = mcnla::la::nrmf(matrix_a_tmp) / mcnla::la::nrmf(matrix_a);
}
