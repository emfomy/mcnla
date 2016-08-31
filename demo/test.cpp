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
  isvd::index_t m = 6, n = 6, ld = 8, info;

  // Generate A
  isvd::DenseMatrix<double> matA(m, n, ld),  matA2(m, n, ld);
  isvd::lapack::larnv<3>(matA.vectorize(), iseed);
  isvd::blas::copy(matA.vectorize(), matA2.vectorize());

  std::cout << "A" << std::endl;
  std::cout << matA << std::endl;
  std::cout << matA2 << std::endl;
  std::cout << std::endl;

  // SYEV Solver
  isvd::lapack::SyevSolver<isvd::DenseMatrix<double>, 'V'> syev_solver(matA);

  isvd::DenseVector<double> vecW(m), vecW2(m), vecWork(204);

  // compute
  syev_solver.compute(matA, vecW);
  isvd::index_t lwork = vecWork.getLength();
  std::cout << "lwork = " << lwork << std::endl << std::endl;
  dsyev_("V", "L", &m, matA2.getValue(), &ld, vecW2.getValue(), vecWork.getValue(), &lwork, &info); assert(info == 0);

  std::cout << "V" << std::endl;
  std::cout << matA << std::endl;
  std::cout << matA2 << std::endl;
  std::cout << std::endl;

  std::cout << "W" << std::endl;
  std::cout << vecW << std::endl;
  std::cout << vecW2 << std::endl;
  std::cout << std::endl;
}
