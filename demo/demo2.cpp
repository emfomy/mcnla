////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    demo/demo2.cpp
/// @brief   The demo code kind 2
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#include <iostream>
#include <mcnla.hpp>
#include "statistics_set.hpp"

using ValType = double;

void create( mcnla::matrix::DenseMatrixColMajor<ValType> &matrix_a,
             mcnla::matrix::DenseMatrixColMajor<ValType> &matrix_u_true,
             ValType &error0,
             const mcnla::index_t rank,
             const double k_scale ) noexcept;

void check_u( const mcnla::matrix::DenseMatrixColMajor<ValType> &matrix_u,
              const mcnla::matrix::DenseMatrixColMajor<ValType> &matrix_u_true,
              ValType &smax, ValType &smin, ValType &smean ) noexcept;

void check( const mcnla::matrix::DenseMatrixColMajor<ValType> &matrix_a,
            const mcnla::matrix::DenseMatrixColMajor<ValType> &matrix_u,
            const mcnla::matrix::DenseMatrixColMajor<ValType> &matrix_vt,
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
              << MCNLA_PATCH_VERSION << " demo kind 2" << std::endl << std::endl;
  }

  // ====================================================================================================================== //
  // Initialize random seed
  srand(time(NULL) ^ mpi_rank);

  // ====================================================================================================================== //
  // Set parameters
  int argi = 0;
  mcnla::index_t Nj        = ( argc > ++argi ) ? atof(argv[argi]) : 4;
  mcnla::index_t m         = ( argc > ++argi ) ? atof(argv[argi]) : 1000;
  mcnla::index_t n         = ( argc > ++argi ) ? atof(argv[argi]) : 10000;
  mcnla::index_t k         = ( argc > ++argi ) ? atof(argv[argi]) : 100;
  mcnla::index_t p         = ( argc > ++argi ) ? atof(argv[argi]) : 12;
  mcnla::index_t num_test  = ( argc > ++argi ) ? atof(argv[argi]) : 10;
  mcnla::index_t skip_test = ( argc > ++argi ) ? atof(argv[argi]) : 5;
  ValType        tol       = ( argc > ++argi ) ? atof(argv[argi]) : 1e-4;
  mcnla::index_t maxiter   = ( argc > ++argi ) ? atof(argv[argi]) : 256;
  double         k_scale   = ( argc > ++argi ) ? atof(argv[argi]) : 2.0;
  if ( mpi_rank == mpi_root ) {
    std::cout << "m = " << m
            << ", n = " << n
            << ", k = " << k
            << ", p = " << p
            << ", N = " << Nj*mpi_size
            << ", tol = " << tol
            << ", maxiter = " << maxiter << std::endl;
    std::cout << mpi_size << " nodes / "
              << omp_get_max_threads() << " threads per node" << std::endl << std::endl;
  }
  assert((k+p) <= m && m <= n);

  // ====================================================================================================================== //
  // Create statistics collector
  StatisticsSet set_smax(num_test), set_smean(num_test),  set_smin(num_test),   set_frerr(num_test),
                set_time(num_test), set_time_s(num_test), set_time_o(num_test), set_time_i(num_test), set_time_f(num_test),
                set_iter(num_test);

  // ====================================================================================================================== //
  // Initialize driver
  mcnla::matrix::DenseMatrixColMajor<ValType> matrix_a(m, n), matrix_u_true;
  mcnla::isvd::Driver<ValType,
                      mcnla::isvd::GaussianProjectionSketcherTag<0>,
                      mcnla::isvd::SvdOrthogonalizerTag,
                      mcnla::isvd::KolmogorovNagumoIntegratorTag,
                      mcnla::isvd::SvdFormerTag> driver(MPI_COMM_WORLD);
  driver.setSize(matrix_a).setRank(k).setOverRank(p).setNumSketchEach(Nj);
  driver.setTolerance(tol).setMaxIteration(maxiter).setSeeds(rand());
  driver.initialize();
  if ( mpi_rank == mpi_root ) {
    std::cout << "Uses " << driver.sketcher() << "." << std::endl;
    std::cout << "Uses " << driver.orthogonalizer() << "." << std::endl;
    std::cout << "Uses " << driver.integrator() << "." << std::endl;
    std::cout << "Uses " << driver.former() << "." << std::endl << std::endl;
  }

  // ====================================================================================================================== //
  // Generate matrix
  ValType error0;
  if ( mpi_rank == mpi_root ) {
    std::cout << "A = U0 S0 V0', s0 = 1, 1/2, 1/3, ...1/k, 0.01/(k+1), ..., 0.01/" << k_scale << "k, 0, ..."
              << std::endl << std::endl;
    create(matrix_a, matrix_u_true, error0, k, k_scale);
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
      ValType smax, smin, smean, frerr;
      check_u(driver.leftSingularVectors(), matrix_u_true, smax, smin, smean);
      check(matrix_a, driver.leftSingularVectors(), driver.rightSingularVectors(), driver.singularValues(), frerr);
      auto iter    = driver.integratorIteration();
      auto maxiter = driver.parameters().maxIteration();
      auto time_s = driver.sketcherTime();
      auto time_o = driver.orthogonalizerTime();
      auto time_i = driver.integratorTime();
      auto time_f = driver.formerTime();
      auto time = time_s + time_o + time_i + time_f;
      std::cout << std::setw(log10(num_test)+1) << t
                << " | validity: " << smax << " / " << smean << " / " << smin
                << " | error: " << frerr
                << " | iter: " << std::setw(log10(maxiter)+1) << iter
                << " | time: " << time << " (" << time_s << " / " << time_o << " / "
                                               << time_i << " / " << time_f << ")" << std::endl;
      if ( t >= 0 ) {
        set_smax(smax); set_smean(smean);   set_smin(smin);     set_frerr(frerr);
        set_time(time); set_time_s(time_s); set_time_o(time_o); set_time_i(time_i); set_time_f(time_f); set_iter(iter);
      }
    }
  }

  // Display statistics results
  if ( mpi_rank == mpi_root ) {
    std::cout << std::endl;
    std::cout << "Average total computing time: " << set_time.mean()   << " seconds." << std::endl;
    std::cout << "Average sketching time:       " << set_time_s.mean() << " seconds." << std::endl;
    std::cout << "Average orthogonaling time:   " << set_time_o.mean() << " seconds." << std::endl;
    std::cout << "Average integrating time:     " << set_time_i.mean() << " seconds." << std::endl;
    std::cout << "Average forming time:         " << set_time_f.mean() << " seconds." << std::endl;
    std::cout << "mean(validity): max = " << set_smax.mean()
                           << ", mean = " << set_smean.mean()
                            << ", min = " << set_smin.mean() << std::endl;
    std::cout << "sd(validity):   max = " << set_smax.sd()
                           << ", mean = " << set_smean.sd()
                            << ", min = " << set_smin.sd() << std::endl;
    std::cout << "mean(error)         = " << set_frerr.mean() << std::endl;
    std::cout << "sd(error)           = " << set_frerr.sd() << std::endl;
    std::cout << "mean(iter)          = " << set_iter.mean() << std::endl;
    std::cout << "sd(iter)            = " << set_iter.sd() << std::endl;
    std::cout << std::endl;
    std::cout << "excepted validity   = 1" << std::endl;
    std::cout << "excepted error      = " << error0 << std::endl;
    std::cout << std::endl;
    std::cout << "validity := svd(U_true' U)_2" << std::endl;
    std::cout << "error    := norm(A-USV')_F/norm(A)_F" << std::endl;
    std::cout << std::endl;
  }

  MPI_Finalize();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Create matrix A
///
void create(
          mcnla::matrix::DenseMatrixColMajor<ValType> &matrix_a,
          mcnla::matrix::DenseMatrixColMajor<ValType> &matrix_u_true,
          ValType &error0,
    const mcnla::index_t rank,
    const double k_scale
) noexcept {
  assert(k_scale >= 1.0);

  matrix_u_true = mcnla::matrix::DenseMatrixColMajor<ValType>(matrix_a.nrow(), rank);

  mcnla::index_t totalrank = k_scale * rank;
  mcnla::matrix::DenseMatrixColMajor<ValType> matrix_u(matrix_a.nrow(), totalrank);
  mcnla::matrix::DenseMatrixColMajor<ValType> matrix_v(matrix_a.ncol(), totalrank);
  mcnla::matrix::DenseMatrixColMajor<ValType> matrix_empty;
  mcnla::matrix::DenseVector<ValType> vector_s(totalrank);

  // Generate E & U & V using normal random
  mcnla::random::gaussian(matrix_u.vectorize(), rand());
  mcnla::random::gaussian(matrix_v.vectorize(), rand());

  // Orthogonalize U & V
  mcnla::la::gesvd<'O', 'N'>(matrix_u, vector_s, matrix_empty, matrix_empty);
  mcnla::la::gesvd<'O', 'N'>(matrix_v, vector_s, matrix_empty, matrix_empty);

  // Copy U
  mcnla::la::copy(matrix_u("", {0, rank}), matrix_u_true);

  // Generate S
  for ( mcnla::index_t i = 0; i < rank; ++i ) {
    vector_s(i) = 1.0/(i+1);
  }
  for ( mcnla::index_t i = rank; i < totalrank; ++i ) {
    vector_s(i) = 1e-2/(i+1);
  }

  // A := U * S * V'
  mcnla::la::mm("", vector_s.viewDiagonal(), matrix_u);
  mcnla::la::mm(matrix_u, matrix_v.t(), matrix_a);

  // Compute excepted error
  error0 = mcnla::la::nrmf(vector_s({rank, totalrank})) / mcnla::la::nrmf(vector_s);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Check the result (U)
///
void check_u(
    const mcnla::matrix::DenseMatrixColMajor<ValType> &matrix_u,
    const mcnla::matrix::DenseMatrixColMajor<ValType> &matrix_u_true,
          ValType &smax,
          ValType &smin,
          ValType &smean
) noexcept {
  mcnla::matrix::DenseMatrixColMajor<ValType> matrix_u2(matrix_u.ncol(), matrix_u.ncol());
  mcnla::matrix::DenseVector<ValType> vector_s(matrix_u.ncol());
  mcnla::matrix::DenseMatrixColMajor<ValType> matrix_empty;

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
void check(
    const mcnla::matrix::DenseMatrixColMajor<ValType> &matrix_a,
    const mcnla::matrix::DenseMatrixColMajor<ValType> &matrix_u,
    const mcnla::matrix::DenseMatrixColMajor<ValType> &matrix_vt,
    const mcnla::matrix::DenseVector<ValType>         &vector_s,
          ValType &frerr
) noexcept {
  // A_tmp := A, U_tmp = U
  auto matrix_a_tmp = matrix_a.copy();
  auto matrix_u_tmp = matrix_u.copy();

  // A_tmp -= U * S * V'
  mcnla::la::mm("", vector_s.viewDiagonal(), matrix_u_tmp);
  mcnla::la::mm(matrix_u_tmp, matrix_vt, matrix_a_tmp, -1.0, 1.0);

  // frerr := norm(A_tmp)_F / norm(A)_F
  frerr = mcnla::la::nrmf(matrix_a_tmp) / mcnla::la::nrmf(matrix_a);
}
