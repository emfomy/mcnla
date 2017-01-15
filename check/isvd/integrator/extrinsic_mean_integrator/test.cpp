#include <gtest/gtest.h>
#include <mcnla/isvd/integrator/extrinsic_mean_integrator.hpp>
#include <mcnla/core/io.hpp>

#define CUBE_Q_PATH MCNLA_DATA_PATH "/qit.mtx"
#define MATRIX_Q_PATH MCNLA_DATA_PATH "/qbt_em.mtx"

TEST(KolmogorovNagumoIntegratorTest, Test) {
  using ScalarType = double;
  const auto mpi_size = mcnla::mpi::commSize(MPI_COMM_WORLD);
  const auto mpi_rank = mcnla::mpi::commRank(MPI_COMM_WORLD);
  const mcnla::index_t mpi_root = 0;

  // Reads data
  mcnla::container::DenseMatrixCollection120<ScalarType> collection_q_true;
  mcnla::container::DenseMatrixRowMajor<ScalarType> matrix_q_true;
  mcnla::io::loadMatrixMarket(collection_q_true, CUBE_Q_PATH);
  mcnla::io::loadMatrixMarket(matrix_q_true, MATRIX_Q_PATH);

  // Checks size
  ASSERT_EQ(collection_q_true.nrow(), matrix_q_true.nrow());
  ASSERT_EQ(collection_q_true.ncol(), matrix_q_true.ncol());

  // Gets size
  const mcnla::index_t m  = collection_q_true.nrow();
  const mcnla::index_t k  = collection_q_true.ncol();
  const mcnla::index_t p  = 0;
  const mcnla::index_t N  = collection_q_true.nmat();
  const mcnla::index_t K  = mpi_size;
  const mcnla::index_t Nj = N / K;
  ASSERT_EQ(N % K, 0);

  // Sets parameters
  mcnla::isvd::Parameters<ScalarType> parameters(MPI_COMM_WORLD);
  parameters.nrow_ = m;
  parameters.rank_ = k;
  parameters.over_rank_ = p;
  parameters.num_sketch_each_ = Nj;
  parameters.tolerance_ = 1e-4;
  parameters.max_iteration_ = 256;

  // Initializes
  mcnla::isvd::ExtrinsicMeanIntegrator<ScalarType> integrator(parameters, MPI_COMM_WORLD, mpi_root);
  integrator.initialize();
  parameters.initialized_ = true;

  // Copies data
  for ( auto i = 0; i < Nj; i++ ) {
    mcnla::blas::copy(collection_q_true(mpi_rank*Nj + i), integrator.collectionQ()(i));
  }

  // Integrates
  integrator.integrate();

  // Compute space
  mcnla::container::DenseSymmetricMatrixRowMajor<ScalarType> matrix_qq(m);
  mcnla::container::DenseSymmetricMatrixRowMajor<ScalarType> matrix_qq_true(m);
  auto matrix_q = integrator.matrixQ();
  mcnla::blas::rk(matrix_q, matrix_qq);
  mcnla::blas::rk(matrix_q_true, matrix_qq_true);

  // Checks result
  if ( mcnla::mpi::isCommRoot(0, MPI_COMM_WORLD) ) {
    ASSERT_EQ(matrix_q.sizes(), matrix_q_true.sizes());
    for ( auto i = 0; i < m; ++i ) {
      for ( auto j = 0; j < m; ++j ) {
        ASSERT_NEAR(matrix_qq(i, j), matrix_qq_true(i, j), 1e-8) << "(i, j) = (" << i << ", " << j << ")";
      }
    }
  }
}
