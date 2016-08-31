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
  isvd::index_t m = 4, n = 6, ld = 8, lwork, lwork2, info;
  double dlwork2;

  // Generate A
  isvd::DenseMatrix<double, isvd::Layout::COLMAJOR> matA(m, n, ld),  matA2(m, n, ld),
                                                    matU(m, m, ld),  matU2(m, m, ld),
                                                    matVt(n, n, ld), matVt2(n, n, ld);
  isvd::lapack::larnv<3>(matA.vectorize(), iseed);
  isvd::blas::copy(matA.vectorize(), matA2.vectorize());

  std::cout << "A" << std::endl;
  std::cout << matA << std::endl;
  std::cout << matA2 << std::endl;
  std::cout << std::endl;

  // Query
  lwork = isvd::lapack::gesvdQuery<'A', 'A'>(matA);
  lwork2 = -1;
  dgesvd_("A", "A", &m, &n, nullptr, &ld, nullptr, nullptr, &ld, nullptr, &ld, &dlwork2, &lwork2, &info); assert(info == 0);
  lwork2 = dlwork2;

  std::cout << "lwork" << std::endl;
  std::cout << lwork << std::endl;
  std::cout << lwork2 << std::endl;
  std::cout << std::endl;

  isvd::DenseVector<double> vecS(m), vecS2(m), vecWork(lwork), vecRwork(5*m);

  // GESVD
  isvd::lapack::gesvd<'A', 'A'>(matA, vecS, matU, matVt, vecWork, vecRwork);
  dgesvd_("A", "A", &m, &n, matA2.getValue(), &ld, vecS2.getValue(),
          matU2.getValue(), &ld, matVt2.getValue(), &ld, vecWork.getValue(), &lwork2, &info); assert(info == 0);

  std::cout << "S" << std::endl;
  std::cout << vecS << std::endl;
  std::cout << vecS2 << std::endl;
  std::cout << std::endl;

  std::cout << "U" << std::endl;
  std::cout << matU << std::endl;
  std::cout << matU2 << std::endl;
  std::cout << std::endl;

  std::cout << "Vt" << std::endl;
  std::cout << matVt << std::endl;
  std::cout << matVt2 << std::endl;
  std::cout << std::endl;

  std::cout << "A" << std::endl;
  std::cout << matA << std::endl;
  std::cout << matA2 << std::endl;
  std::cout << std::endl;
}
