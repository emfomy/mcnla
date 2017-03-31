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

  mcnla::isvd::Parameters parameters(MPI_COMM_WORLD, 0);
  parameters.nrow() = m;
  parameters.ncol() = n;
  parameters.rank() = k;
  parameters.overRank() = p;
  parameters.numSketchEach() = Nj;

  mcnla::matrix::DenseMatrixColMajor<double> a(m, n);
  mcnla::matrix::DenseMatrixCollection120<double> qs(m, l, Nj);
  mcnla::matrix::DenseMatrixRowMajor<double> qbar(m, l);
  mcnla::random::MpiStreams mpi_streams(MPI_COMM_WORLD, 0, seed);
  mcnla::random::gaussian(mpi_streams, a.vectorize());

  // mcnla::isvd::gaussianProjectionSketcher<double>(parameters, a, qs, mpi_streams, 2);
  mcnla::isvd::columnSamplingSketcher<double>(parameters, a, qs, mpi_streams);

  mcnla::isvd::svdOrthogonalizer<double>(parameters, qs);

  mcnla::index_t iteration;
  double time2c;
  mcnla::isvd::kolmogorovNagumoIntegrator<double>(parameters, qs, qbar, iteration, time2c);

  disp(a);
  disp(qbar);

  mcnla::matrix::DenseMatrixColMajor<double> qq(l, l);
  mcnla::la::mm(qbar.t(), qbar, qq);

  disp(qq);

  MPI_Finalize();

  return 0;
}
