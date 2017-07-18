#include <gtest/gtest.h>
#include <mcnla/isvd/former/gramian_former.hpp>
#include <mcnla/isvd/converter.hpp>
#include <mcnla/core/io/matrix_market.hpp>

#define MATRIX_A_PATH MCNLA_DATA_PATH "/a.mtx"
#define MATRIX_Q_PATH MCNLA_DATA_PATH "/q.mtx"
#define MATRIX_U_PATH MCNLA_DATA_PATH "/u.mtx"

TEST(GramianFormerTest, Test) {
  using ValType = double;
  const auto mpi_comm = MPI_COMM_WORLD;
  const auto mpi_rank = mcnla::mpi::commRank(mpi_comm);
  const auto mpi_root = 0;

  // Reads data
  mcnla::matrix::DenseMatrixRowMajor<ValType> a;
  mcnla::matrix::DenseMatrixRowMajor<ValType> q;
  mcnla::matrix::DenseMatrixColMajor<ValType> u_true;
  mcnla::io::loadMatrixMarket(a, MATRIX_A_PATH);
  mcnla::io::loadMatrixMarket(q, MATRIX_Q_PATH);
  mcnla::io::loadMatrixMarket(u_true, MATRIX_U_PATH);

  // Checks size
  ASSERT_EQ(a.nrow(), q.nrow());
  ASSERT_EQ(q.sizes(), u_true.sizes());

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
  mcnla::isvd::GramianFormer<ValType, true> former(parameters);
  former.initialize();

  // Creates matrices
  auto u_true_cut = u_true(""_, {0_i, k});

  // Forms
  former(a, q);

  // Gets results
  auto u = former.matrixU();

  // Checks result
  if ( mpi_rank == mpi_root ) {
    ASSERT_EQ(u.sizes(), u_true_cut.sizes());
    mcnla::matrix::DenseSymmetricMatrixRowMajor<ValType> uut(m);
    mcnla::matrix::DenseSymmetricMatrixRowMajor<ValType> uut_true(m);
    mcnla::la::rk(u, uut);
    mcnla::la::rk(u_true_cut, uut_true);
    for ( auto ir = 0; ir < m; ++ir ) {
      for ( auto ic = 0; ic <= ir; ++ic ) {
        ASSERT_NEAR(uut(ir, ic), uut_true(ir, ic), 1e-8) << "(ir, ic) =  (" << ir << ", " << ic << ")";
      }
    }
  }
}
