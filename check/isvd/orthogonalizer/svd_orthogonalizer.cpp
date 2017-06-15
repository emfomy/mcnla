#include <gtest/gtest.h>
#include <mcnla/isvd/orthogonalizer/svd_orthogonalizer.hpp>
#include <mcnla/isvd/converter.hpp>
#include <mcnla/core/io/matrix_market.hpp>

#define COLLECTION_Y_PATH MCNLA_DATA_PATH "/yi.mtx"
#define COLLECTION_Q_PATH MCNLA_DATA_PATH "/qi.mtx"

TEST(SvdOrthogonalizerTest, Test) {
  using ValType = double;
  const auto mpi_comm = MPI_COMM_WORLD;
  const auto mpi_rank = mcnla::mpi::commRank(mpi_comm);
  const auto mpi_size = mcnla::mpi::commSize(mpi_comm);
  const auto mpi_root = 0;

  // Reads data
  mcnla::matrix::DenseMatrixCollectionColBlockRowMajor<ValType> yi_true;
  mcnla::matrix::DenseMatrixCollectionColBlockRowMajor<ValType> qi_true;
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

  // Gather result
  mcnla::matrix::DenseMatrixCollectionColBlockColMajor<ValType> qi0(qi.sizes());
  mcnla::matrix::DenseMatrixCollectionColBlockColMajor<ValType> qis(qi.nrow(), qi.ncol(), N);
  mcnla::la::copy(qi.unfold(), qi0.unfold());
  mcnla::mpi::gather(qi0.unfold(), qis.unfold(), mpi_root, mpi_comm);

  // Checks result
  if ( mpi_rank == mpi_root ) {
    for ( auto i = 0; i < N; ++i ) {
      mcnla::matrix::DenseSymmetricMatrixRowMajor<ValType> qqt(m);
      mcnla::matrix::DenseSymmetricMatrixRowMajor<ValType> qqt_true(m);
      mcnla::la::rk(qis(i), qqt);
      mcnla::la::rk(qi_true(i), qqt_true);
      for ( auto ir = 0; ir < m; ++ir ) {
        for ( auto ic = 0; ic <= ir; ++ic ) {
          ASSERT_NEAR(qqt(ir, ic), qqt_true(ir, ic), 1e-8) << "(ir, ic) =  (" << ir << ", " << ic << ")" << ", i = " << i;
        }
      }
    }
  }
}
