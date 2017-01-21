////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    demo/test.cpp
/// @brief   The test code
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#define MCNLA_TEST

#include <cstdio>
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

  int m = 5, n = 4, k = 3, nnz = m*k, i;

  mcnla::matrix::CooMatrixColMajor<double> a(m, k, nnz);
  mcnla::matrix::DenseMatrixRowMajor<double> b(k, n);
  mcnla::matrix::DenseMatrixRowMajor<double> c(m, n);


  for ( auto j = 0; j < k; ++j ) {
    for ( auto i = 0; i < m; ++i ) {
      a.val().valarray()[i+j*m] = i+j*m;
      a.rowidx().valarray()[i+j*m] = i;
      a.colidx().valarray()[i+j*m] = j;
    }
  }

  i = 0;
  for ( auto &v : b ) {
    v = ++i;
  }

  std::cout << "a:\n" << a << std::endl;
  std::cout << "b:\n" << b << std::endl;

  double done = 1.0, dzero = 0.0;
  int ldb = b.pitch(), ldc = c.pitch();
  mkl_dcoomm("N", &m, &n, &k, &done, "G  C", a.valPtr(), a.rowidxPtr(), a.colidxPtr(), &nnz,
             b.valPtr(), &ldb, &dzero, c.valPtr(), &ldc);

  std::cout << "c:\n" << c << std::endl;

  mcnla::la::memset0(c);

  mcnla::la::mm(a, b, c);

  std::cout << "c:\n" << c << std::endl;

  return 0;
}
