#include <gtest/gtest.h>
#include <mcnla/isvd/former/row_block_polar_former.hpp>
#include <mcnla/isvd/converter.hpp>
#include <mcnla/core/io/matrix_market.hpp>

#define MATRIX_A_PATH MCNLA_DATA_PATH "/a.mtx"
#define MATRIX_Q_PATH MCNLA_DATA_PATH "/qb_kn.mtx"
#define MATRIX_U_PATH MCNLA_DATA_PATH "/u_kn.mtx"

TEST(RowBlockPolarFormerTest, Test) {
  using ValType = double;
  const auto mpi_comm = MPI_COMM_WORLD;
  const auto mpi_rank = mcnla::mpi::commRank(mpi_comm);
  const auto mpi_root = 0;

  // Reads data
  mcnla::matrix::DenseMatrixRowMajor<ValType> a;
  mcnla::matrix::DenseMatrixRowMajor<ValType> qbar_true;
  mcnla::matrix::DenseMatrixRowMajor<ValType> u_true_all;
  mcnla::io::loadMatrixMarket(a, MATRIX_A_PATH);
  mcnla::io::loadMatrixMarket(qbar_true, MATRIX_Q_PATH);
  mcnla::io::loadMatrixMarket(u_true_all, MATRIX_U_PATH);

  // Checks size
  ASSERT_EQ(a.nrow(), qbar_true.nrow());
  ASSERT_EQ(qbar_true.sizes(), u_true_all.sizes());

  // Gets size
  const mcnla::index_t m  = a.nrow();
  const mcnla::index_t n  = a.ncol();
  const mcnla::index_t k  = qbar_true.ncol() / 2;
  const mcnla::index_t p  = qbar_true.ncol() - k;
  const mcnla::index_t Nj = 1;

  // Sets parameters
  mcnla::isvd::Parameters<ValType> parameters(mpi_root, mpi_comm);
  parameters.setSize(m, n).setRank(k).setOverRank(p).setNumSketchEach(Nj);
  parameters.sync();

  // Initializes former
  mcnla::isvd::RowBlockPolarFormer<ValType> former(parameters);
  former.initialize();

  // Initializes converter
  mcnla::isvd::MatrixToRowBlockConverter<double> pre_converter(parameters);
  mcnla::isvd::MatrixFromRowBlockConverter<double> post_converter(parameters);
  pre_converter.initialize();
  post_converter.initialize();

  // Creates matrices
  auto qbar   = parameters.createMatrixQ();
  auto qbarj  = parameters.createMatrixQj();
  auto u      = parameters.createMatrixU();
  auto aj     = a(parameters.rowrange(), "");
  auto u_true = u_true_all("", {0, k});

  // Copies data
  mcnla::la::copy(qbar_true, qbar);

  // Integrates
  pre_converter(qbar, qbarj);
  former(aj, qbarj);

  // Gets result
  post_converter(former.matrixUj(), u);

  // Checks result
  if ( mpi_rank == mpi_root ) {
    ASSERT_EQ(u.sizes(), u_true.sizes());
    mcnla::matrix::DenseSymmetricMatrixRowMajor<ValType> uut(m);
    mcnla::matrix::DenseSymmetricMatrixRowMajor<ValType> uut_true(m);
    mcnla::la::rk(u, uut);
    mcnla::la::rk(u_true, uut_true);
    for ( auto ir = 0; ir < m; ++ir ) {
      for ( auto ic = 0; ic <= ir; ++ic ) {
        ASSERT_NEAR(uut(ir, ic), uut_true(ir, ic), 1e-8) << "(ir, ic) =  (" << ir << ", " << ic << ")";
      }
    }
  }
}
