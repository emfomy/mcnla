#include <gtest/gtest.h>
#include <mcnla/isvd/integrator/row_block_extrinsic_mean_integrator.hpp>
#include <mcnla/isvd/converter.hpp>
#include <mcnla/core/io/matrix_market.hpp>

#define COLLECTION_Q_PATH MCNLA_DATA_PATH "/qi.mtx"
#define MATRIX_Q_PATH MCNLA_DATA_PATH "/qb_em.mtx"

TEST(RowBlockExtrinsicMeanIntegratorTest, Test) {
  using ValType = double;
  const auto mpi_comm = MPI_COMM_WORLD;
  const auto mpi_rank = mcnla::mpi::commRank(mpi_comm);
  const auto mpi_size = mcnla::mpi::commSize(mpi_comm);
  const auto mpi_root = 0;

  // Reads data
  mcnla::matrix::DenseMatrixCollectionColBlockRowMajor<ValType> qi_true;
  mcnla::matrix::DenseMatrixRowMajor<ValType> qbar_true;
  mcnla::io::loadMatrixMarket(qi_true, COLLECTION_Q_PATH);
  mcnla::io::loadMatrixMarket(qbar_true, MATRIX_Q_PATH);

  // Checks size
  ASSERT_EQ(qi_true.nrow(), qbar_true.nrow());
  ASSERT_EQ(qi_true.ncol(), qbar_true.ncol());

  // Gets size
  const mcnla::index_t m  = qi_true.nrow();
  const mcnla::index_t k  = qi_true.ncol();
  const mcnla::index_t p  = 0;
  const mcnla::index_t N  = qi_true.nmat();
  const mcnla::index_t K  = mpi_size;
  const mcnla::index_t Nj = N / K;
  ASSERT_EQ(N % K, 0);

  // Sets parameters
  mcnla::isvd::Parameters<ValType> parameters(mpi_root, mpi_comm);
  parameters.setSize(m, k+p).setRank(k).setOverRank(p).setNumSketchEach(Nj);
  parameters.sync();

  // Initializes integrator
  mcnla::isvd::RowBlockExtrinsicMeanIntegrator<ValType> integrator(parameters);
  integrator.initialize();

  // Initializes converter
  mcnla::isvd::CollectionToRowBlockConverter<double> pre_converter(parameters);
  pre_converter.initialize();

  // Creates matrices
  auto qi    = parameters.createCollectionQ();
  auto qij   = parameters.createCollectionQj();
  auto qbar  = parameters.createMatrixQbar();

  // Copies data
  for ( auto i = 0; i < Nj; i++ ) {
    mcnla::la::copy(qi_true(mpi_rank*Nj + i), qi(i));
  }

  // Integrates
  pre_converter(qi.copy(), qij);
  integrator(qij, qi, qbar);

  // Checks result
  if ( mpi_rank == mpi_root ) {
    ASSERT_EQ(qbar.sizes(), qbar_true.sizes());
    mcnla::matrix::DenseSymmetricMatrixRowMajor<ValType> qq(m);
    mcnla::matrix::DenseSymmetricMatrixRowMajor<ValType> qq_true(m);
    mcnla::la::rk(qbar, qq);
    mcnla::la::rk(qbar_true, qq_true);
    for ( auto ir = 0; ir < m; ++ir ) {
      for ( auto ic = 0; ic <= ir; ++ic ) {
        ASSERT_NEAR(qq(ir, ic), qq_true(ir, ic), 1e-8) << "(ir, ic) =  (" << ir << ", " << ic << ")";
      }
    }
  }
}
