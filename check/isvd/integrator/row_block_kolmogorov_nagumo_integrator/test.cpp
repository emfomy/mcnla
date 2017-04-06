#include <gtest/gtest.h>
#include <mcnla/isvd/integrator/row_block_kolmogorov_nagumo_integrator.hpp>
#include <mcnla/isvd/converter.hpp>
#include <mcnla/core/io/matrix_market.hpp>

#define CUBE_Q_PATH MCNLA_DATA_PATH "/qit.mtx"
#define MATRIX_Q_PATH MCNLA_DATA_PATH "/qbt_kn.mtx"

TEST(RowBlockKolmogorovNagumoIntegratorTest, Test) {
  using ValType = double;
  const auto mpi_comm = MPI_COMM_WORLD;
  const auto mpi_root = 0;
  const auto mpi_size = mcnla::mpi::commSize(mpi_comm);
  const auto mpi_rank = mcnla::mpi::commRank(mpi_comm);

  // Reads data
  mcnla::matrix::DenseMatrixCollection120<ValType> qi_true;
  mcnla::matrix::DenseMatrixRowMajor<ValType> qbar_true;
  mcnla::io::loadMatrixMarket(qi_true, CUBE_Q_PATH);
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
  mcnla::isvd::Parameters<ValType> parameters(mpi_comm, mpi_root);
  parameters.setSize(m, k+p).setRank(k).setOverRank(p).setNumSketchEach(Nj);
  parameters.sync();

  // Initializes integrator
  mcnla::isvd::RowBlockKolmogorovNagumoIntegrator<ValType> integrator(parameters, 256, 1e-4);
  integrator.initialize();

  // Initializes converter
  mcnla::isvd::CollectionQToRowBlockConverter<double> oi_converter(parameters);
  mcnla::isvd::MatrixQFromRowBlockConverter<double> if_converter(parameters);
  oi_converter.initialize();
  if_converter.initialize();

  // Creates matrices
  auto qi    = parameters.createCollectionQ();
  auto qij   = parameters.createCollectionQj();
  auto qbar  = parameters.createMatrixQ();
  auto qbarj = parameters.createMatrixQj();

  // Copies data
  for ( auto i = 0; i < Nj; i++ ) {
    mcnla::la::copy(qi_true(mpi_rank*Nj + i), qi(i));
  }

  // Integrates
  oi_converter(qi, qij);
  integrator(qij, qbarj);
  if_converter(qbarj, qbar);

  // Checks result
  if ( mcnla::mpi::isCommRoot(0, mpi_comm) ) {
    ASSERT_EQ(qbar.sizes(), qbar_true.sizes());
    ASSERT_EQ(integrator.iteration(), 41);
    for ( auto i = 0; i < m; ++i ) {
      for ( auto j = 0; j < k; ++j ) {
        ASSERT_NEAR(qbar(i, j), qbar_true(i, j), 1e-8) << "(i, j) = (" << i << ", " << j << ")";
      }
    }
  }
}
