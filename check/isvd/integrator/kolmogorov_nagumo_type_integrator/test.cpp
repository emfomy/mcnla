#include <gtest/gtest.h>
#include <mcnla.hpp>

TEST(KolmogorovNagumoTypeIntegratorTest, Test) {
  using ScalarType = double;

  const mcnla::index_t m  = 100;
  const mcnla::index_t k  = 10;
  const mcnla::index_t p  = 0;
  const mcnla::index_t N  = 8;
  const mcnla::index_t K  = mcnla::mpi::getCommSize(MPI_COMM_WORLD);
  const mcnla::index_t Nj = N / K;

  mcnla::isvd::Parameters<ScalarType> parameters(MPI_COMM_WORLD, 0);
  parameters.nrow_ = m;
  parameters.rank_ = k;
  parameters.over_rank_ = p;
  parameters.num_sketch_each_ = Nj;

  mcnla::isvd::KolmogorovNagumoTypeIntegrator<mcnla::matrix::DenseMatrix<ScalarType>> integrator(parameters);
}
