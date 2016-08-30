////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    main/test.cpp
/// @brief   The test code
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#include <cstdio>
#include <iostream>
#include <iomanip>
#include <isvd.hpp>

template class isvd::DenseVector<double>;
template class isvd::DenseMatrix<double>;
template class isvd::DenseCube<double>;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Main function
///
int main() {
  std::cout << "iSVD "
            << ISVD_VERSION_MAJOR << "."
            << ISVD_VERSION_MINOR << "."
            << ISVD_VERSION_PATCH << " test" << std::endl << std::endl;

  isvd::index_t m = 6, n = 5, k = 3, lda = 7, lwork = 64*n, info;

  isvd::DenseMatrix<double> matA(m, n, lda), matA2(m, n, lda), matA3(m, n, lda);
  isvd::DenseVector<double> vecTau(n), vecTau2(n), vecTau3(n), vecWork(lwork);

  for ( auto i = 0; i < matA.getNrow(); ++i ) {
    for ( auto j = 0; j < matA.getNcol(); ++j ) {
      matA(i, j) = double(rand()) / RAND_MAX;
    }
  }

  isvd::blas::copy(matA.vectorize(), matA2.vectorize());
  isvd::blas::copy(matA.vectorize(), matA3.vectorize());

  std::cout << "A" << std::endl;
  std::cout << matA << std::endl;
  std::cout << matA2 << std::endl;
  std::cout << matA3 << std::endl;
  std::cout << std::endl;

  isvd::lapack::geqrf(matA, vecTau, vecWork);
  assert(isvd::lapack::internal::geqrf(m, n, matA2.getValue(), lda, vecTau2.getValue(), vecWork.getValue(), lwork) == 0);
  dgeqrf_(&m, &n, matA3.getValue(), &lda, vecTau3.getValue(), vecWork.getValue(), &lwork, &info); assert(info == 0);

  std::cout << "geqrf" << std::endl;
  std::cout << matA << std::endl;
  std::cout << matA2 << std::endl;
  std::cout << matA3 << std::endl;
  std::cout << std::endl;

  isvd::lapack::orgqr(matA, vecTau, vecWork, n, k);
  assert(isvd::lapack::internal::orgqr(m, n, k, matA2.getValue(), lda, vecTau2.getValue(), vecWork.getValue(), lwork) == 0);
  dorgqr_(&m, &n, &k, matA3.getValue(), &lda, vecTau3.getValue(), vecWork.getValue(), &lwork, &info); assert(info == 0);

  std::cout << "orgqr" << std::endl;
  std::cout << matA << std::endl;
  std::cout << matA2 << std::endl;
  std::cout << matA3 << std::endl;
}
