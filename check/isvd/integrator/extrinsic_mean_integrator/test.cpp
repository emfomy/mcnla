#include <gtest/gtest.h>
#include <mcnla.hpp>

#define CUBE_Q_PATH MCNLA_DATA_PATH "/qit.mtx"
#define MATRIX_QBAR_PATH MCNLA_DATA_PATH "/qbt_em.mtx"

TEST(EntrinsicMeanIntegratorTest, Test) {
  using ScalarType = double;
  auto mpi_size = mcnla::mpi::commSize(MPI_COMM_WORLD);
  auto mpi_rank = mcnla::mpi::commRank(MPI_COMM_WORLD);

  // Reads data
  mcnla::matrix::DenseMatrixSet120<ScalarType> set_q_true;
  mcnla::matrix::DenseMatrix<ScalarType, mcnla::Layout::ROWMAJOR> matrix_qbar_true;
  mcnla::io::loadMatrixMarket(set_q_true, CUBE_Q_PATH);
  mcnla::io::loadMatrixMarket(matrix_qbar_true, MATRIX_QBAR_PATH);

  // Checks size
  ASSERT_EQ(set_q_true.nrow(), matrix_qbar_true.nrow());
  ASSERT_EQ(set_q_true.ncol(), matrix_qbar_true.ncol());

  // Gets size
  const mcnla::index_t m  = set_q_true.nrow();
  const mcnla::index_t k  = set_q_true.ncol();
  const mcnla::index_t p  = 0;
  const mcnla::index_t N  = set_q_true.nmat();
  const mcnla::index_t K  = mpi_size;
  const mcnla::index_t Nj = N / K;
  ASSERT_EQ(N % K, 0);

  // Sets parameters
  mcnla::isvd::Parameters<ScalarType> parameters(MPI_COMM_WORLD, 0);
  parameters.nrow_ = m;
  parameters.rank_ = k;
  parameters.over_rank_ = p;
  parameters.num_sketch_each_ = Nj;
  parameters.tolerance_ = 1e-4;
  parameters.max_iteration_ = 256;

  // Initializes
  mcnla::isvd::ExtrinsicMeanIntegrator<mcnla::matrix::DenseMatrix<ScalarType>> integrator(parameters);
  integrator.initialize();
  parameters.initialized_ = true;

  // Copies data
  for ( auto i = 0; i < Nj; i++ ) {
    mcnla::blas::omatcopy(1.0, set_q_true(mpi_rank*Nj + i), integrator.getSetQ().getMatrix(i));
  }

  // Integrates
  integrator.integrate();

  // Checks result
  auto matrix_qbar = integrator.getMatrixQbar();
  if ( mcnla::mpi::isCommRoot(0, MPI_COMM_WORLD) ) {
    ASSERT_EQ(matrix_qbar.sizes(), matrix_qbar_true.sizes());
    for ( auto i = 0; i < m; ++i ) {
      for ( auto j = 0; j < k; ++j ) {
        ASSERT_NEAR(matrix_qbar(i, j), matrix_qbar_true(i, j), 1e-8) << "(i, j) = (" << i << ", " << j << ")";
      }
    }
  }
}
