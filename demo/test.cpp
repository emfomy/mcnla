////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    demo/test.cpp
/// @brief   The test code
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#include <iostream>
#include <mcnla.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Main function
///
int main( int argc, char **argv ) {
  std::cout << "MCNLA "
            << MCNLA_MAJOR_VERSION << "."
            << MCNLA_MINOR_VERSION << "."
            << MCNLA_PATCH_VERSION << " test" << std::endl << std::endl;

  MPI_Init(&argc, &argv);

  mcnla::index_t m = 10, n = 10, k = 5, p = 1, l = k+p, Nj = 2, seed = 1;
  mcnla::mpi_int_t mpi_root = 0;

  mcnla::isvd::Parameters parameters(MPI_COMM_WORLD, mpi_root);
  parameters.setSize(m, n).setRank(k).setOverRank(p).setNumSketchEach(Nj);
  parameters.sync();

  mcnla::matrix::DenseMatrixColMajor<double> a(m, n);
  mcnla::matrix::DenseMatrixCollection120<double> qs(m, l, Nj);
  mcnla::matrix::DenseMatrixRowMajor<double> qbar(m, l);
  mcnla::matrix::DenseVector<double> s(l);
  mcnla::matrix::DenseMatrixColMajor<double> u(m, l);
  mcnla::matrix::DenseMatrixColMajor<double> vt(l, n);
  mcnla::random::Streams streams(0);
  mcnla::random::gaussian(streams, a.vectorize());
  mcnla::mpi::bcast(a, mpi_root, MPI_COMM_WORLD);

  mcnla::isvd::gaussianProjectionSketcher<double>(parameters, a, qs, 2);
  // mcnla::isvd::columnSamplingSketcher<double>(parameters, a, qs);

  mcnla::isvd::svdOrthogonalizer<double>(parameters, qs);

  mcnla::index_t iteration;
  double time2c;
  mcnla::isvd::kolmogorovNagumoIntegrator<double>(parameters, qs, qbar, iteration, time2c);

  mcnla::isvd::svdFormer<double>(parameters, a, qbar, s, u, vt);

  disp(a);
  disp(qbar);

  mcnla::matrix::DenseMatrixColMajor<double> qq(l, l);
  mcnla::la::mm(qbar.t(), qbar, qq);

  disp(qq);

  MPI_Finalize();

  return 0;
}
