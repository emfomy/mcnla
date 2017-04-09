#include <gtest/gtest.h>
#include <mcnla/isvd/orthogonalizer/svd_orthogonalizer.hpp>
#include <mcnla/core/io/matrix_market.hpp>

#define COLLECTION_Y_PATH MCNLA_DATA_PATH "/yit.mtx"
#define COLLECTION_Q_PATH MCNLA_DATA_PATH "/qit.mtx"

TEST(SvdOrthogonalizerTest, Test) {
  using ValType = double;
  const auto mpi_comm = MPI_COMM_WORLD;
  const auto mpi_root = 0;
  const auto mpi_size = mcnla::mpi::commSize(mpi_comm);
  const auto mpi_rank = mcnla::mpi::commRank(mpi_comm);

  // Reads data
  mcnla::matrix::DenseMatrixCollection120<ValType> yi_true;
  mcnla::matrix::DenseMatrixCollection120<ValType> qi_true;
  mcnla::io::loadMatrixMarket(yi_true, COLLECTION_Y_PATH);
  mcnla::io::loadMatrixMarket(qi_true, COLLECTION_Q_PATH);

  // Checks size
  ASSERT_EQ(yi_true.sizes(), qi_true.sizes());

  // Gets size
  const mcnla::index_t m  = yi_true.nrow();
  const mcnla::index_t k  = yi_true.ncol();
  const mcnla::index_t p  = 0;
  const mcnla::index_t N  = yi_true.nmat();
  const mcnla::index_t K  = mpi_size;
  const mcnla::index_t Nj = N / K;
  ASSERT_EQ(N % K, 0);

  // Sets parameters
  mcnla::isvd::Parameters<ValType> parameters(mpi_root, mpi_comm);
  parameters.setSize(m, k+p).setRank(k).setOverRank(p).setNumSketchEach(Nj);
  parameters.sync();

  // Initializes orthogonalizer
  mcnla::isvd::SvdOrthogonalizer<ValType> orthogonalizer(parameters);
  orthogonalizer.initialize();

  // Creates matrices
  auto qi = parameters.createCollectionQ();

  // Copies data
  for ( auto i = 0; i < Nj; i++ ) {
    mcnla::la::copy(yi_true(mpi_rank*Nj + i), qi(i));
  }

  // Integrates
  orthogonalizer(qi);

  // Checks result
  if ( mpi_rank == mpi_root ) {
    for ( auto j = 0; j < K; ++j ) {
      if ( j != mpi_root ) {
        mcnla::mpi::recv(qi.unfold(), j, j, mpi_comm);
      }
      for ( auto i = 0; i < Nj; ++i ) {
        mcnla::matrix::DenseSymmetricMatrixRowMajor<ValType> qqt(m);
        mcnla::matrix::DenseSymmetricMatrixRowMajor<ValType> qqt_true(m);
        mcnla::la::rk(qi(i), qqt);
        mcnla::la::rk(qi_true(i+j*Nj), qqt_true);
        for ( auto ir = 0; ir < m; ++ir ) {
          for ( auto ic = 0; ic <= ir; ++ic ) {
            ASSERT_NEAR(qqt(ir, ic), qqt_true(ir, ic), 1e-8) << "(ir, ic) =  (" << ir << ", " << ic << ")"
                                                             << ", i = " << i << ", j = " << j;
          }
        }
      }
    }
  } else {
    mcnla::mpi::send(qi.unfold(), mpi_root, mpi_rank, mpi_comm);
  }
}
