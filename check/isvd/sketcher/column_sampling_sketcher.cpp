#include <gtest/gtest.h>
#include <mcnla/isvd/sketcher/column_sampling_sketcher.hpp>
#include <mcnla/isvd/converter.hpp>
#include <mcnla/core/io/matrix_market.hpp>

#define MATRIX_A_PATH MCNLA_DATA_PATH "/a.mtx"

TEST(ColumnSamplingSketcherTest, Test) {
  using ValType = double;
  const auto mpi_comm = MPI_COMM_WORLD;
  const auto mpi_root = 0;

  // Reads data
  mcnla::matrix::DenseMatrixRowMajor<ValType> a;
  mcnla::io::loadMatrixMarket(a, MATRIX_A_PATH);

  // Gets size
  const mcnla::index_t m  = a.nrow();
  const mcnla::index_t n  = a.ncol();
  const mcnla::index_t k  = 6;
  const mcnla::index_t p  = 5;
  const mcnla::index_t Nj = 1;

  // Sets parameters
  mcnla::isvd::Parameters<ValType> parameters(mpi_root, mpi_comm);
  parameters.setSize(m, n).setRank(k).setOverRank(p).setNumSketchEach(Nj);
  parameters.sync();

  // Initializes sketcher
  mcnla::isvd::ColumnSamplingSketcher<ValType> sketcher(parameters);
  sketcher.initialize();

  // Creates matrices
  auto qi = parameters.createCollectionQ();

  // Sketches
  sketcher(a, qi);
}
