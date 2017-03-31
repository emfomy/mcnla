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
  mcnla::random::Streams streams(seed);
  mcnla::random::gaussian(streams, a.vectorize());

  mcnla::isvd::sketcherColumnSampling<double>(parameters, a, qs, seed);

  disp(a);
  disp(qs(0));

  MPI_Finalize();

  return 0;
}
