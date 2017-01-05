////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    demo/test.cpp
/// @brief   The test code
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#include <iostream>
#include <mcnla.hpp>
#include <omp.h>
#include <mkl.h>

#define MTX_PATH MCNLA_DATA_PATH "/../demo/test.mtx"

template class mcnla::isvd::Sketcher<mcnla::matrix::DenseMatrixColMajor<double>,
                                     mcnla::matrix::DenseMatrixSet120<double>,
                                     mcnla::isvd::GaussianProjectionSketcherTag>;

#define N 10000

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Main function
///
int main( int argc, char **argv ) {
  std::cout << "MCNLA "
            << MCNLA_MAJOR_VERSION << "."
            << MCNLA_MINOR_VERSION << "."
            << MCNLA_PATCH_VERSION << " test" << std::endl << std::endl;

  // std::cout << omp_get_max_threads() << std::endl;

  // auto a = new double[N*N];
  // auto b = new double[N*N];
  // auto c = new double[N*N];
  // int n = N;
  // double d0 = 0.0, d1 = 1.0;
  // // dgemm("N", "N", &n, &n, &n, &d1, a, &n, b, &n, &d0, c, &n);
  // cblas_dgemm(CblasColMajor, CblasNoTrans, CblasNoTrans, n, n, n, d1, a, n, b, n, d0, c, n);

  mcnla::matrix::DenseMatrixColMajor<double> A(N, N), B(N, N), C(N, N);

  mcnla::blas::mm(A, B, C);

  std::cout << "!" << std::endl;
  int tmp;
  std::cin >> tmp;

  #pragma omp parallel for collapse(2)
  for ( auto i = 0; i < N; ++i ) {
    for ( auto j = 0; j < N; ++j ) {
      C(i, j) = A(i, j) + B(i, j);
    }
  }

  // delete[] a;
  // delete[] b;
  // delete[] c;

  return 0;
}
