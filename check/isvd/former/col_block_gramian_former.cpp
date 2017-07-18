#include <gtest/gtest.h>
#include <mcnla/isvd/former/col_block_gramian_former.hpp>
#include <mcnla/isvd/converter.hpp>
#include <mcnla/core/io/matrix_market.hpp>

#define MATRIX_A_PATH MCNLA_DATA_PATH "/a.mtx"
#define MATRIX_Q_PATH MCNLA_DATA_PATH "/q.mtx"
#define MATRIX_U_PATH MCNLA_DATA_PATH "/u.mtx"

TEST(ColBlockGramianFormerTest, Test) {
  using ValType = double;
  const auto mpi_comm = MPI_COMM_WORLD;
  const auto mpi_rank = mcnla::mpi::commRank(mpi_comm);
  const auto mpi_root = 0;

  // Reads data
  mcnla::matrix::DenseMatrixColMajor<ValType> a;
  mcnla::matrix::DenseMatrixRowMajor<ValType> q;
  mcnla::matrix::DenseMatrixColMajor<ValType> u_true_all;
  mcnla::io::loadMatrixMarket(a, MATRIX_A_PATH);
  mcnla::io::loadMatrixMarket(q, MATRIX_Q_PATH);
  mcnla::io::loadMatrixMarket(u_true_all, MATRIX_U_PATH);

  // Checks size
  ASSERT_EQ(a.nrow(), q.nrow());
  ASSERT_EQ(q.sizes(), u_true_all.sizes());

  // Gets size
  const mcnla::index_t m  = a.nrow();
  const mcnla::index_t n  = a.ncol();
  const mcnla::index_t k  = q.ncol() / 2;
  const mcnla::index_t p  = q.ncol() - k;
  const mcnla::index_t Nj = 1;

  // Sets parameters
  mcnla::isvd::Parameters<ValType> parameters(mpi_root, mpi_comm);
  parameters.setSize(m, n).setRank(k).setOverRank(p).setNumSketchEach(Nj);
  parameters.sync();

  // Initializes former
  mcnla::isvd::ColBlockGramianFormer<ValType, true> former(parameters);
  former.initialize();

  // Creates matrices
  auto ajp    = a(""_, parameters.colrange());
  auto u_true = u_true_all(""_, {0_i, k});

  // Forms
  former(ajp, q);

  // Gets result
  auto u = former.matrixU();

  // Checks result
  if ( mpi_rank == mpi_root ) {
    ASSERT_EQ(u.sizes(), u_true.sizes());
    mcnla::matrix::DenseSymmetricMatrixColMajor<ValType> uut(m);
    mcnla::matrix::DenseSymmetricMatrixColMajor<ValType> uut_true(m);
    mcnla::la::rk(u, uut);
    mcnla::la::rk(u_true, uut_true);
    for ( auto ir = 0; ir < m; ++ir ) {
      for ( auto ic = 0; ic <= ir; ++ic ) {
        ASSERT_NEAR(uut(ir, ic), uut_true(ir, ic), 1e-8) << "(ir, ic) =  (" << ir << ", " << ic << ")";
      }
    }
  }
}
