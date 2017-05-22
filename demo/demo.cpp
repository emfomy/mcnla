////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    demo/demo.cpp
/// @brief   The demo code
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#include <iostream>
#include <mcnla.hpp>
#include <omp.h>
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
  // Initialize MCNLA
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
              << MCNLA_PATCH_VERSION << " demo" << std::endl << std::endl;
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
  mcnla::index_t k         = ( argc > ++argi ) ? atof(argv[argi]) : 10;
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
#ifdef MCNLA_USE_OMP
              << omp_get_max_threads()
#else  //MCNLA_USE_OMP
              << 1
#endif  // MCNLA_USE_OMP
              << " threads per node" << std::endl << std::endl;
  }
  assert((k+p) <= m && m <= n);

  // ====================================================================================================================== //
  // Generate matrix
  mcnla::matrix::DenseMatrixColMajor<ValType> matrix_a(m, n), matrix_u_true;
  ValType error0;
  if ( mpi_rank == mpi_root ) {
    std::cout << "A = U0 S0 V0', s0 = 1, 1/2, 1/3, ...1/k, 0.01/(k+1), ..., 0.01/" << k_scale << "k, 0, ..."
              << std::endl << std::endl;
    create(matrix_a, matrix_u_true, error0, k, k_scale);
  }
  mcnla::mpi::bcast(matrix_a, mpi_root, mpi_comm);

  // ====================================================================================================================== //
  // Create statistics collector
  StatisticsSet set_smax(num_test), set_smean(num_test),   set_smin(num_test),    set_frerr(num_test),
                set_time(num_test), set_time_s(num_test),  set_time_o(num_test),  set_time_i(num_test),  set_time_f(num_test),
                set_iter(num_test), set_time_so(num_test), set_time_oi(num_test), set_time_if(num_test);

  // ====================================================================================================================== //
  // Allocate stages
  mcnla::isvd::Parameters<ValType> parameters(mpi_root, mpi_comm);

  mcnla::isvd::RowBlockColumnSamplingSketcher<double> sketcher(parameters);
  mcnla::isvd::RowBlockGramianOrthogonalizer<double> orthogonalizer(parameters);
  mcnla::isvd::RowBlockKolmogorovNagumoIntegrator<double> integrator(parameters);
  mcnla::isvd::SvdFormer<double> former(parameters);
  mcnla::isvd::DummyConverter<double> so_converter(parameters);
  mcnla::isvd::DummyConverter<double> oi_converter(parameters);
  mcnla::isvd::MatrixFromRowBlockConverter<double> if_converter(parameters);

  // mcnla::isvd::GaussianProjectionSketcher<double> sketcher(parameters);
  // mcnla::isvd::SvdOrthogonalizer<double> orthogonalizer(parameters);
  // mcnla::isvd::KolmogorovNagumoIntegrator<double> integrator(parameters);
  // mcnla::isvd::SvdFormer<double> former(parameters);
  // mcnla::isvd::DummyConverter<double> so_converter(parameters);
  // mcnla::isvd::DummyConverter<double> oi_converter(parameters);
  // mcnla::isvd::DummyConverter<double> if_converter(parameters);

  // ====================================================================================================================== //
  // Initialize parameters
  parameters.setSize(matrix_a).setRank(k).setOverRank(p).setNumSketchEach(Nj);
  integrator.setMaxIteration(maxiter).setTolerance(tol);
  parameters.sync();
  sketcher.initialize();
  orthogonalizer.initialize();
  integrator.initialize();
  former.initialize();
  so_converter.initialize();
  oi_converter.initialize();
  if_converter.initialize();

  // ====================================================================================================================== //
  // Allocate matrices
  auto matrix_aj     = matrix_a(parameters.rowrange(), ""_);
  auto collection_q  = parameters.createCollectionQ();
  auto collection_qj = parameters.createCollectionQj();
  auto matrix_q      = parameters.createMatrixQ();
  auto matrix_qj     = parameters.createMatrixQj();

  // ====================================================================================================================== //
  // Display driver
  if ( mpi_rank == mpi_root ) {
    std::cout << "Uses " << sketcher << "." << std::endl;
    std::cout << "Uses " << orthogonalizer << "." << std::endl;
    std::cout << "Uses " << integrator << "." << std::endl;
    std::cout << "Uses " << former << "." << std::endl << std::endl;
  }

  // ====================================================================================================================== //
  // Run MCNLA
  if ( mpi_rank == mpi_root ) {
    std::cout << "Start iSVD." << std::endl << std::endl;
    std::cout << std::fixed << std::setprecision(6);
  }

  for ( int t = -skip_test; t < num_test; ++t ) {

    sketcher.setSeed(rand());

    // Run iSVD
    MPI_Barrier(mpi_comm);

    sketcher(matrix_aj, collection_qj);
    orthogonalizer(collection_qj);
    integrator(collection_qj, matrix_qj);
    if_converter(matrix_qj, matrix_q);
    former(matrix_a, matrix_q);

    // sketcher(matrix_a, collection_q);
    // orthogonalizer(collection_q);
    // integrator(collection_q, matrix_q);
    // former(matrix_a, matrix_q);

    MPI_Barrier(mpi_comm);

    // Check result
    if ( mpi_rank == mpi_root  ) {
      ValType smax, smin, smean, frerr;
      check_u(former.matrixU(), matrix_u_true, smax, smin, smean);
      check(matrix_a, former.matrixU(), former.matrixVt(), former.vectorS(), frerr);
      auto iter    = integrator.iteration();
      auto time_s  = sketcher.time();
      auto time_o  = orthogonalizer.time();
      auto time_i  = integrator.time();
      auto time_f  = former.time();
      auto time_so = so_converter.time();
      auto time_oi = oi_converter.time();
      auto time_if = if_converter.time();
      auto time    = time_s + time_o + time_i + time_f;
      std::cout << std::setw(log10(num_test)+1) << t
                << " | validity: " << smax << " / " << smean << " / " << smin
                << " | error: " << frerr
                << " | iter: " << std::setw(log10(maxiter)+1) << iter
                << " | time: " << time << " (" << time_s << " / " << time_o << " / "
                                               << time_i << " / " << time_f << ")"
                << " | converting time: " << time_so << " / " << time_oi << " / " << time_if << ")" << std::endl;
      if ( t >= 0 ) {
        set_smax(smax); set_smean(smean);     set_smin(smin);       set_frerr(frerr);
        set_time(time); set_time_s(time_s);   set_time_o(time_o);   set_time_i(time_i);   set_time_f(time_f);
        set_iter(iter); set_time_so(time_so); set_time_oi(time_oi); set_time_if(time_if);
      }
    }
  }

  // Display statistics results
  if ( mpi_rank == mpi_root ) {
    std::cout << std::endl;
    std::cout << "Average total computing time:   " << set_time.mean()   << " seconds." << std::endl;
    std::cout << "Average sketching time:         " << set_time_s.mean() << " seconds." << std::endl;
    std::cout << "Average orthogonaling time:     " << set_time_o.mean() << " seconds." << std::endl;
    std::cout << "Average integrating time:       " << set_time_i.mean() << " seconds." << std::endl;
    std::cout << "Average forming time:           " << set_time_f.mean() << " seconds." << std::endl;
    std::cout << "Average converting time (S->O): " << set_time_so.mean() << " seconds." << std::endl;
    std::cout << "Average converting time (O->I): " << set_time_oi.mean() << " seconds." << std::endl;
    std::cout << "Average converting time (I->F): " << set_time_if.mean() << " seconds." << std::endl;
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

  mcnla::finalize();
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
  mcnla::random::Streams streams(rand());
  mcnla::random::gaussian(streams, matrix_u.vectorize());
  mcnla::random::gaussian(streams, matrix_v.vectorize());

  // Orthogonalize U & V
  mcnla::la::gesvd<'O', 'N'>(matrix_u, vector_s, matrix_empty, matrix_empty);
  mcnla::la::gesvd<'O', 'N'>(matrix_v, vector_s, matrix_empty, matrix_empty);

  // Copy U
  mcnla::la::copy(matrix_u(""_, {0_i, rank}), matrix_u_true);

  // Generate S
  for ( mcnla::index_t i = 0; i < rank; ++i ) {
    vector_s(i) = 1.0/(i+1);
  }
  for ( mcnla::index_t i = rank; i < totalrank; ++i ) {
    vector_s(i) = 1e-2/(i+1);
  }

  // A := U * S * V'
  mcnla::la::mm(""_, vector_s.viewDiagonal(), matrix_u);
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
  mcnla::la::mm(""_, vector_s.viewDiagonal(), matrix_u_tmp);
  mcnla::la::mm(matrix_u_tmp, matrix_vt, matrix_a_tmp, -1.0, 1.0);

  // frerr := norm(A_tmp)_F / norm(A)_F
  frerr = mcnla::la::nrmf(matrix_a_tmp) / mcnla::la::nrmf(matrix_a);
}
