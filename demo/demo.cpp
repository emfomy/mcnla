////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    demo/demo.cpp
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
             mcnla::matrix::DenseMatrix<ScalarType> &matrix_u_true,
             const mcnla::index_t rank, mcnla::index_t seed ) noexcept;

template <mcnla::Trans _trans>
void check_u( const mcnla::matrix::DenseMatrix<ScalarType, _trans> &matrix_u,
              const mcnla::matrix::DenseMatrix<ScalarType> &matrix_u_true,
              ScalarType &smax, ScalarType &smin, ScalarType &smean ) noexcept;

template <mcnla::Trans _trans>
void check( const mcnla::matrix::DenseMatrix<ScalarType, _trans> &matrix_a,
            const mcnla::matrix::DenseMatrix<ScalarType, _trans> &matrix_u,
            const mcnla::matrix::DenseMatrix<ScalarType, _trans> &matrix_vt,
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
  mcnla::index_t seed = rand();;

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
  StatisticsSet set_smax(num_test), set_smean(num_test),  set_smin(num_test),   set_frerr(num_test),
                set_time(num_test), set_time_s(num_test), set_time_i(num_test), set_time_f(num_test), set_iter(num_test);

  // ====================================================================================================================== //
  // Initialize solver
  mcnla::matrix::DenseMatrix<ScalarType> matrix_a(m, n), matrix_u_true;
  mcnla::isvd::Solver<ScalarType,
                      mcnla::isvd::GaussianProjectionSketcherTag<0>,
                      mcnla::isvd::SvdOrthogonalizerTag,
                      mcnla::isvd::KolmogorovNagumoIntegratorTag,
                      mcnla::isvd::SvdFormerTag> solver(MPI_COMM_WORLD);
  solver.setSize(matrix_a).setRank(k).setOverRank(p).setNumSketchEach(Nj);
  solver.setTolerance(tolerance).setMaxIteration(maxiter).setSeeds(seed);
  solver.initialize();
  if ( mpi_rank == mpi_root ) {
    std::cout << "Uses " << solver.sketcher() << "." << std::endl;
    std::cout << "Uses " << solver.integrator() << "." << std::endl;
    std::cout << "Uses " << solver.former() << "." << std::endl << std::endl;
  }

  // ====================================================================================================================== //
  // Generate matrix
  if ( mpi_rank == mpi_root ) {
    std::cout << "Generate A with given singular values." << std::endl << std::endl;
    create(matrix_a, matrix_u_true, k, seed);
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
    if ( mpi_rank == mpi_root  ) {
      ScalarType smax, smin, smean, frerr;
      check_u(solver.leftSingularVectors(), matrix_u_true, smax, smin, smean);
      check(matrix_a, solver.leftSingularVectors(), solver.rightSingularVectors(), solver.singularValues(), frerr);
      auto iter    = solver.integratorIteration();
      auto maxiter = solver.parameters().maxIteration();
      auto time_s = solver.sketcherTime();
      auto time_i = solver.integratorTime();
      auto time_f = solver.formerTime();
      auto time = time_s + time_i + time_f;
      std::cout << std::setw(log10(num_test)+1) << t
                << " | validity: " << smax << " / " << smean << " / " << smin
                << " | error: " << frerr
                << " | iter: " << std::setw(log10(maxiter)+1) << iter
                << " | time: " << time << " (" << time_s << " / " << time_i << " / " << time_f << ")" << std::endl;
      if ( t >= 0 ) {
        set_smax(smax); set_smean(smean);   set_smin(smin);     set_frerr(frerr);
        set_time(time); set_time_s(time_s); set_time_f(time_f); set_time_i(time_i); set_iter(iter);
      }
    }
  }

  // Display statistics results
  if ( mpi_rank == mpi_root ) {
    std::cout << std::endl;
    std::cout << "Average total computing time: " << set_time.mean() << " seconds." << std::endl;
    std::cout << "Average sketching time:       " << set_time_s.mean() << " seconds." << std::endl;
    std::cout << "Average integrating time:     " << set_time_i.mean() << " seconds." << std::endl;
    std::cout << "Average forming time:         " << set_time_f.mean() << " seconds." << std::endl;
    std::cout << "mean(validity): max = " << set_smax.mean()
                           << ", mean = " << set_smean.mean()
                            << ", min = " << set_smin.mean() << std::endl;
    std::cout << "sd(validity):   max = " << set_smax.sd()
                           << ", mean = " << set_smean.sd()
                            << ", min = " << set_smin.sd() << std::endl;
    std::cout << "mean(error) = " << set_frerr.mean() << std::endl;
    std::cout << "sd(error)   = " << set_frerr.sd() << std::endl;
    std::cout << "mean(iter) = " << set_iter.mean() << std::endl;
    std::cout << "sd(iter)   = " << set_iter.sd() << std::endl;
    std::cout << std::endl;
    std::cout << "validity = svd(U_true' U)_2" << std::endl;
    std::cout << "error = norm(A-USV')_F/norm(A)_F" << std::endl;
  }

  MPI_Finalize();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Create matrix A
///
void create(
          mcnla::matrix::DenseMatrix<ScalarType> &matrix_a,
          mcnla::matrix::DenseMatrix<ScalarType> &matrix_u_true,
    const mcnla::index_t rank,
          mcnla::index_t seed
) noexcept {
  matrix_u_true = mcnla::matrix::DenseMatrix<ScalarType>(matrix_a.nrow(), rank);

  mcnla::matrix::DenseMatrix<ScalarType> matrix_u(matrix_a.nrow(), matrix_a.nrow());
  mcnla::matrix::DenseMatrix<ScalarType> matrix_v(matrix_a.ncol(), matrix_a.nrow());
  mcnla::matrix::DenseMatrix<ScalarType> matrix_empty;
  mcnla::matrix::DenseVector<ScalarType> vector_s(matrix_a.nrow());

  // Generate U & V using normal random
  mcnla::random::gaussian(matrix_u.vectorize(), seed);
  mcnla::random::gaussian(matrix_v.vectorize(), seed);

  // Orthogonalize U & V
  mcnla::la::gesvd<'O', 'N'>(matrix_u, vector_s, matrix_empty, matrix_empty);
  mcnla::la::gesvd<'O', 'N'>(matrix_v, vector_s, matrix_empty, matrix_empty);

  // Copy U
  mcnla::la::copy(matrix_u("", {0, rank}), matrix_u_true);

  // A := U * S * V'
  for ( mcnla::index_t i = 0; i < rank; ++i ) {
    mcnla::la::scal(matrix_u("", i), 1.0/(i+1));
  }
  for ( mcnla::index_t i = rank; i < matrix_a.nrow(); ++i ) {
    mcnla::la::scal(matrix_u("", i), 1e-2/(i+1));
  }
  mcnla::la::mm(matrix_u, matrix_v.t(), matrix_a);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Check the result (U)
///
template <mcnla::Trans _trans>
void check_u(
    const mcnla::matrix::DenseMatrix<ScalarType, _trans> &matrix_u,
    const mcnla::matrix::DenseMatrix<ScalarType> &matrix_u_true,
          ScalarType &smax,
          ScalarType &smin,
          ScalarType &smean
) noexcept {
  mcnla::matrix::DenseMatrix<ScalarType> matrix_u2(matrix_u.ncol(), matrix_u.ncol());
  mcnla::matrix::DenseVector<ScalarType> vector_s(matrix_u.ncol());
  mcnla::matrix::DenseMatrix<ScalarType> matrix_empty;

  // U2 := Utrue' * U
  mcnla::la::mm(matrix_u_true.t(), matrix_u, matrix_u2);

  // Compute the SVD of U2
  mcnla::la::gesvd<'N', 'N'>(matrix_u2, vector_s, matrix_empty, matrix_empty);
  smax  = mcnla::la::amax(vector_s);
  smin  = mcnla::la::amin(vector_s);
  smean = mcnla::la::asum(vector_s) / vector_s.length();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Check the result (A)
///
template <mcnla::Trans _trans>
void check(
    const mcnla::matrix::DenseMatrix<ScalarType, _trans> &matrix_a,
    const mcnla::matrix::DenseMatrix<ScalarType, _trans> &matrix_u,
    const mcnla::matrix::DenseMatrix<ScalarType, _trans> &matrix_vt,
    const mcnla::matrix::DenseVector<ScalarType>          &vector_s,
          ScalarType &frerr
) noexcept {
  mcnla::matrix::DenseMatrix<ScalarType, _trans> matrix_a_tmp(matrix_a.sizes());
  mcnla::matrix::DenseMatrix<ScalarType, _trans> matrix_u_tmp(matrix_u.sizes());

  // A_tmp := A, U_tmp = U
  mcnla::la::copy(matrix_a, matrix_a_tmp);
  mcnla::la::copy(matrix_u, matrix_u_tmp);

  // A_tmp -= U * S * V'
  mcnla::la::mm("", vector_s.viewDiagonal(), matrix_u_tmp);
  mcnla::la::mm(matrix_u_tmp, matrix_vt, matrix_a_tmp, -1.0, 1.0);

  // frerr := norm(A_tmp)_F / norm(A)_F
  frerr = mcnla::la::nrmf(matrix_a_tmp) / mcnla::la::nrmf(matrix_a);
}
