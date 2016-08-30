////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    main/test.cpp
/// @brief   The test code
///
/// @author  Mu Yang <emfomy@gmail.com>
///

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

  isvd::index_t iseed[4] = {rand()%4096, rand()%4096, rand()%4096, (rand()%2048)*2+1};
  isvd::index_t n = 6, lda = 8, lwork, lwork2, info;
  double dlwork2;

  // Generate A
  isvd::DenseMatrix<double, isvd::Layout::ROWMAJOR> matA(n, n, lda), matA2(n, n, lda);
  isvd::lapack::larnv<3>(matA.vectorize(), iseed);
  isvd::blas::copy(matA.vectorize(), matA2.vectorize());

  std::cout << "A" << std::endl;
  std::cout << matA << std::endl;
  std::cout << matA2 << std::endl;
  std::cout << std::endl;

  // Query
  lwork = isvd::lapack::syevQuery<'V', isvd::UploOption::UPPER>(matA);
  lwork2 = -1;
  dsyev_("V", "U", &n, nullptr, &lda, nullptr, &dlwork2, &lwork2, &info); assert(info == 0);
  lwork2 = dlwork2;

  std::cout << "lwork" << std::endl;
  std::cout << lwork << std::endl;
  std::cout << lwork2 << std::endl;

  isvd::DenseVector<double> vecW(n), vecW2(n), vecWork(lwork), vecRwork(3*n);

  // SYEV
  isvd::lapack::syev<'V', isvd::UploOption::UPPER>(matA, vecW, vecWork, vecRwork);
  dsyev_("V", "U", &n, matA2.getValue(), &lda, vecW2.getValue(), vecWork.getValue(), &lwork2, &info); assert(info == 0);

  std::cout << "V" << std::endl;
  std::cout << matA << std::endl;
  std::cout << matA2 << std::endl;
  std::cout << std::endl;

  std::cout << "W" << std::endl;
  std::cout << vecW << std::endl;
  std::cout << vecW2 << std::endl;
  std::cout << std::endl;
}
