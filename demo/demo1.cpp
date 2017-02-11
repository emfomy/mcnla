////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    demo/demo1.cpp
/// @brief   The demo code
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#include <iostream>
#include <mcnla.hpp>
#include "statistics_set.hpp"

using ValType = double;

ValType tolerance = 1e-4;
mcnla::index_t maxiter = 256;

void create( mcnla::matrix::DenseMatrix<ValType> &matrix_a,
             const mcnla::index_t rank ) noexcept;

template <mcnla::Trans _trans>
void check( const mcnla::matrix::DenseMatrix<ValType, _trans> &matrix_a,
            const mcnla::matrix::DenseMatrix<ValType, _trans> &matrix_u,
            const mcnla::matrix::DenseMatrix<ValType, _trans> &matrix_vt,
            const mcnla::matrix::DenseVector<ValType> &vector_s,
            ValType &frerr ) noexcept;

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
              << MCNLA_PATCH_VERSION << " demo v2" << std::endl << std::endl;
  }

  // ====================================================================================================================== //
  // Initialize random seed
  srand(time(NULL) ^ mpi_rank);

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
  StatisticsSet set_time(num_test), set_time_s(num_test), set_time_o(num_test), set_time_i(num_test), set_time_f(num_test),
                set_frerr(num_test),  set_iter(num_test);

  // ====================================================================================================================== //
  // Initialize driver
  mcnla::matrix::DenseMatrix<ValType> matrix_a(m, n);
  mcnla::isvd::Driver<ValType,
                      mcnla::isvd::GaussianProjectionSketcherTag<0>,
                      mcnla::isvd::SvdOrthogonalizerTag,
                      mcnla::isvd::KolmogorovNagumoIntegratorTag,
                      mcnla::isvd::SvdFormerTag> driver(MPI_COMM_WORLD);
  driver.setSize(matrix_a).setRank(k).setOverRank(p).setNumSketchEach(Nj);
  driver.setTolerance(tolerance).setMaxIteration(maxiter).setSeeds(rand());
  driver.initialize();
  if ( mpi_rank == mpi_root ) {
    std::cout << "Uses " << driver.sketcher() << "." << std::endl;
    std::cout << "Uses " << driver.orthogonalizer() << "." << std::endl;
    std::cout << "Uses " << driver.integrator() << "." << std::endl;
    std::cout << "Uses " << driver.former() << "." << std::endl << std::endl;
  }

  // ====================================================================================================================== //
  // Generate matrix
  if ( mpi_rank == mpi_root ) {
    std::cout << "A = Uk Sk Vk' + E; norm_F(E) = 1/(k+p)" << std::endl << std::endl;
    create(matrix_a, k);
  }
  mcnla::mpi::bcast(matrix_a, mpi_root, MPI_COMM_WORLD);

  // ====================================================================================================================== //
  // Run MCNLA
  if ( mpi_rank == mpi_root ) {
    std::cout << "Start iSVD." << std::endl << std::endl;
    std::cout << std::fixed << std::setprecision(6);
  }

  for ( int t = -skip_test; t < num_test; ++t ) {

    // Run driver
    MPI_Barrier(MPI_COMM_WORLD);
    driver.compute(matrix_a);
    MPI_Barrier(MPI_COMM_WORLD);

    // Check result
    if ( mpi_rank == mpi_root  ) {
      ValType frerr;
      check(matrix_a, driver.leftSingularVectors(), driver.rightSingularVectors(), driver.singularValues(), frerr);
      auto iter    = driver.integratorIteration();
      auto maxiter = driver.parameters().maxIteration();
      auto time_s = driver.sketcherTime();
      auto time_o = driver.orthogonalizerTime();
      auto time_i = driver.integratorTime();
      auto time_f = driver.formerTime();
      auto time = time_s + time_o + time_i + time_f;
      std::cout << std::setw(log10(num_test)+1) << t
                << " | error: " << frerr
                << " | iter: " << std::setw(log10(maxiter)+1) << iter
                << " | time: " << time << " (" << time_s << " / " << time_o << " / "
                                               << time_i << " / " << time_f << ")" << std::endl;
      if ( t >= 0 ) {
        set_time(time); set_time_s(time_s); set_time_o(time_o); set_time_i(time_i); set_time_f(time_f);
        set_frerr(frerr); set_iter(iter);
      }
    }
  }

  // Display statistics results
  if ( mpi_rank == mpi_root ) {
    std::cout << std::endl;
    std::cout << "Average total computing time: " << set_time.mean() << " seconds." << std::endl;
    std::cout << "Average sketching time:       " << set_time_s.mean() << " seconds." << std::endl;
    std::cout << "Average orthogonaling time:   " << set_time_o.mean() << " seconds." << std::endl;
    std::cout << "Average integrating time:     " << set_time_i.mean() << " seconds." << std::endl;
    std::cout << "Average forming time:         " << set_time_f.mean() << " seconds." << std::endl;
    std::cout << "mean(error) = " << set_frerr.mean() << std::endl;
    std::cout << "sd(error)   = " << set_frerr.sd() << std::endl;
    std::cout << "mean(iter)  = " << set_iter.mean() << std::endl;
    std::cout << "sd(iter)    = " << set_iter.sd() << std::endl;
    std::cout << std::endl;
    std::cout << "error = norm(A-USV')_F/norm(A)_F" << std::endl;
  }

  MPI_Finalize();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Create matrix A
///
void create(
          mcnla::matrix::DenseMatrix<ValType> &matrix_a,
    const mcnla::index_t rank
) noexcept {
  mcnla::matrix::DenseMatrix<ValType> matrix_u(matrix_a.nrow(), rank);
  mcnla::matrix::DenseMatrix<ValType> matrix_v(matrix_a.ncol(), rank);
  mcnla::matrix::DenseMatrix<ValType> matrix_empty;
  mcnla::matrix::DenseVector<ValType> vector_s(rank);

  // Generate E & U & V using normal random
  mcnla::random::gaussian(matrix_a.vectorize(), rand());
  mcnla::random::gaussian(matrix_u.vectorize(), rand());
  mcnla::random::gaussian(matrix_v.vectorize(), rand());

  // Orthogonalize U & V
  mcnla::la::gesvd<'O', 'N'>(matrix_u, vector_s, matrix_empty, matrix_empty);
  mcnla::la::gesvd<'O', 'N'>(matrix_v, vector_s, matrix_empty, matrix_empty);

  // A := U * S * V' + beta * E
  for ( mcnla::index_t i = 0; i < rank; ++i ) {
    mcnla::la::scal(matrix_u("", i), 1.0/(i+1));
  }
  ValType beta = 1.0 / rank / mcnla::la::nrmf(matrix_a);
  mcnla::la::mm(matrix_u, matrix_v.t(), matrix_a, 1.0, beta);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Check the result (A)
///
template <mcnla::Trans _trans>
void check(
    const mcnla::matrix::DenseMatrix<ValType, _trans> &matrix_a,
    const mcnla::matrix::DenseMatrix<ValType, _trans> &matrix_u,
    const mcnla::matrix::DenseMatrix<ValType, _trans> &matrix_vt,
    const mcnla::matrix::DenseVector<ValType>         &vector_s,
          ValType &frerr
) noexcept {
  mcnla::matrix::DenseMatrix<ValType, _trans> matrix_a_tmp(matrix_a.sizes());
  mcnla::matrix::DenseMatrix<ValType, _trans> matrix_u_tmp(matrix_u.sizes());

  // A_tmp := A, U_tmp = U
  mcnla::la::copy(matrix_a, matrix_a_tmp);
  mcnla::la::copy(matrix_u, matrix_u_tmp);

  // A_tmp -= U * S * V'
  mcnla::la::mm("", vector_s.viewDiagonal(), matrix_u_tmp);
  mcnla::la::mm(matrix_u_tmp, matrix_vt, matrix_a_tmp, -1.0, 1.0);

  // frerr := norm(A_tmp)_F / norm(A)_F
  frerr = mcnla::la::nrmf(matrix_a_tmp) / mcnla::la::nrmf(matrix_a);
}
