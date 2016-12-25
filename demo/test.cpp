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

  mcnla::matrix::DenseMatrix<double> mat(3, 3);

  std::cout << mat << std::endl;

  auto i = 0;
  for ( auto &v : mat ) {
    v = ++i;
  }

  std::cout << mat << std::endl;

  std::cout << "Symmetric" << std::endl;
  std::cout << mat.viewSymmetric() << std::endl;
  std::cout << mat.viewSymmetric<mcnla::Uplo::UPPER>() << std::endl;
  std::cout << mat.viewSymmetric<mcnla::Uplo::LOWER>() << std::endl;

  std::cout << "Triangular" << std::endl;
  std::cout << mat.viewTriangular() << std::endl;
  std::cout << mat.viewTriangular<mcnla::Uplo::UPPER>() << std::endl;
  std::cout << mat.viewTriangular<mcnla::Uplo::LOWER>() << std::endl;
  std::cout << mat.viewTriangular<mcnla::Uplo::UNITUPPER>() << std::endl;
  std::cout << mat.viewTriangular<mcnla::Uplo::UNITLOWER>() << std::endl;

  std::cout << "Diagonal" << std::endl;
  std::cout << mat.viewDiagonal() << std::endl;

  std::cout << "Vector" << std::endl;
  auto vec = mat(1, "");
  std::cout << vec << std::endl;
  std::cout << vec.viewDiagonal() << std::endl;

  return 0;
}
