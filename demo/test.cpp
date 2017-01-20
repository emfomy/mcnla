////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    demo/test.cpp
/// @brief   The test code
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#define MCNLA_TEST

#include <iostream>
#include <mcnla.hpp>
#include <cstdio>

#include <mcnla/core/la/raw/spblas/diamm.hpp>
#include <mcnla/core/la/raw/spblas/diasm.hpp>

#define MTX_PATH MCNLA_DATA_PATH "/../demo/test.mtx"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Main function
///
int main( int argc, char **argv ) {
  std::cout << "MCNLA "
            << MCNLA_MAJOR_VERSION << "."
            << MCNLA_MINOR_VERSION << "."
            << MCNLA_PATCH_VERSION << " test" << std::endl << std::endl;

  mcnla::index_t m = 5, n = 7;

  mcnla::matrix::DenseDiagonalMatrix<double> al(m);
  mcnla::matrix::DenseDiagonalMatrix<double> ar(n);
  mcnla::matrix::DenseMatrixColMajor<double> b(m, n);
  mcnla::matrix::DenseMatrixColMajor<double> c(m, n);

  // mcnla::random::gaussian(a.vectorize(), 0);
  // mcnla::random::gaussian(b.vectorize(), 1);
  // mcnla::random::gaussian(c.vectorize(), 2);

  int i = 0;
  for ( auto &v : al.viewVector() ) {
    v = ++i;
  }
  i = 0;
  for ( auto &v : ar.viewVector() ) {
    v = ++i;
  }
  i = 0;
  for ( auto &v : b ) {
    v = ++i;
  }

  std::cout << "Al\n" << al << std::endl;
  std::cout << "Ar\n"  << ar << std::endl;
  std::cout << "B\n"  << b << std::endl;

  std::cout << "================================" << std::endl;

  {

    mcnla::la::mm(al, b, c);

    std::cout << "C\n"  << c << std::endl;

    c.value().valarray() = 0;

    int izero = 0;
    // int izero = 0, ione = 1;
    // double done = 1.0, dzero = 0.0;
    // mkl_ddiamm("N", &m, &n, &m, &done, "D NC", al.valuePtr(), &m, &izero, &ione, b.valuePtr(), &m, &dzero, c.valuePtr(), &m);
    mcnla::la::detail::diamm('N', m, n, m, 1.0, "D NC", al.valuePtr(), m, &izero, 1, b.valuePtr(), m, 0.0, c.valuePtr(), m);

    std::cout << "C\n"  << c << std::endl;

  }

  std::cout << "================================" << std::endl;

  {

    mcnla::la::sm(al.inv(), b, c);

    std::cout << "C\n"  << c << std::endl;

    c.value().valarray() = 0;

    int izero = 0;
    int izero = 0, ione = 1;
    double done = 1.0;
    mkl_ddiasm("N", &m, &n, &done, "TLNC", al.valuePtr(), &m, &izero, &ione, b.valuePtr(), &m, c.valuePtr(), &m);

    std::cout << "C\n"  << c << std::endl;

  }

  std::cout << "================================" << std::endl;

  {

    i = 0;
    for ( auto &v : c ) {
      v = ++i;
    }

    mcnla::la::sm(al.inv(), "", c);

    std::cout << "C\n"  << c << std::endl;

    i = 0;
    for ( auto &v : c ) {
      v = ++i;
    }

    int izero = 0, ione = 1;
    double done = 1.0;
    mkl_ddiasm("N", &m, &n, &done, "TLNC", al.valuePtr(), &m, &izero, &ione, b.valuePtr(), &m, c.valuePtr(), &m);

    std::cout << "C\n"  << c << std::endl;

  }

  std::cout << "================================" << std::endl;

  return 0;
}
