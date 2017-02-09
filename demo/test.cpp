////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    demo/test.cpp
/// @brief   The test code
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#define MCNLA_TEST

#include <iostream>
#include <mcnla.hpp>

#define MTX_PATH MCNLA_DATA_PATH "/../demo/test.mtx"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Main function
///
int main( int argc, char **argv ) {
  std::cout << "MCNLA "
            << MCNLA_MAJOR_VERSION << "."
            << MCNLA_MINOR_VERSION << "."
            << MCNLA_PATCH_VERSION << " test" << std::endl << std::endl;

  mcnla::index_t m = 5, n = 4, k = 3, i;

  mcnla::matrix::DenseMatrixColMajor<double> a(m, k);
  // mcnla::matrix::DenseDiagonalMatrix<double> a(k);
  mcnla::matrix::DenseMatrixColMajor<double> b(k, n);
  mcnla::matrix::DenseMatrixColMajor<double> c(m, n);
  // mcnla::matrix::DenseVector<double> x(k);

  i = 0;
  for ( auto &v : a ) {
    v = ++i;
  }
  for ( auto &v : b ) {
    v = ++i;
  }

  disp(a);
  disp(b);
  disp(c);
  // disp(x);

  // mcnla::la::mm(a, b, c, 1.0, 0.0);

  mcnla::la::MmFunctor<decltype(a)> functor(a);
  functor(b, c);

  // disp(b);
  disp(c);
  // disp(x);

  return 0;
}
