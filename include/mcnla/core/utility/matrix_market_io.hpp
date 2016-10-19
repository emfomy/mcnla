////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/utility/matrix_matlet_io.hpp
/// @brief   The Matrix Market IO utilities.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_UTILITY_MATRIX_MARKET_IO_HPP_
#define MCNLA_CORE_MATRIX_UTILITY_MATRIX_MARKET_IO_HPP_

#include <mcnla/def.hpp>
#include <mcnla/core/def.hpp>
#include <fstream>
#include <mcnla/core/matrix.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The utility namespace.
//
namespace utility {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  utility_module
/// Load a dense vector from a matrix market file.
///
/// @note  If @a vector is empty, the memory will be allocated.
///
/// @todo  Read banner
///
template <typename _Scalar>
void loadMatrixMarket(
    matrix::DenseVector<_Scalar> &vector,
    const char *file
) noexcept {
  // Open file
  std::ifstream fin(file);
  mcnla_assert_false(fin.fail());

  // Skip comment
  char c;
  fin >> c;
  while ( c == '%' ) {
    fin.ignore(4096, '\n');
    fin >> c;
  }
  fin.unget();

  // Get size
  index_t m;
  fin >> m;
  if ( vector.isEmpty() ) {
    vector = matrix::DenseVector<_Scalar>(m);
  } else {
    vector.resize(m, vector.getStride());
  }

  // Read values
  for ( auto &value : vector ) {
    fin >> value;
  }

  // Close file
  fin.close();
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Scalar>
inline void loadMatrixMarket(
    matrix::DenseVector<_Scalar> &&vector,
    const char *file
) noexcept {
  loadMatrixMarket(vector, file);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  utility_module
/// Load a dense matrix from a matrix market file.
///
/// @note  If @a matrix is empty, the memory will be allocated.
///
/// @todo  Read banner
///
template <typename _Scalar, Layout _layout>
void loadMatrixMarket(
    matrix::DenseMatrix<_Scalar, _layout> &matrix,
    const char *file
) noexcept {
  // Open file
  std::ifstream fin(file);
  mcnla_assert_false(fin.fail());

  // Skip comment
  char c;
  fin >> c;
  while ( c == '%' ) {
    fin.ignore(4096, '\n');
    fin >> c;
  }
  fin.unget();

  // Get size
  index_t m, n;
  fin >> m >> n;
  if ( matrix.isEmpty() ) {
    matrix = matrix::DenseMatrix<_Scalar, _layout>(m, n);
  } else {
    matrix.resize(m, n);
  }

  // Read values
  for ( auto &value : matrix ) {
    fin >> value;
  }

  // Close file
  fin.close();
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Scalar, Layout _layout>
inline void loadMatrixMarket(
    matrix::DenseMatrix<_Scalar> &&matrix,
    const char *file
) noexcept {
  loadMatrixMarket(matrix, file);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  utility_module
/// Load a dense cube from a matrix market file.
///
/// @note  If @a cube is empty, the memory will be allocated.
///
/// @todo  Read banner
///
template <typename _Scalar, Layout _layout>
void loadMatrixMarket(
    matrix::DenseCube<_Scalar, _layout> &cube,
    const char *file
) noexcept {
  // Open file
  std::ifstream fin(file);
  mcnla_assert_false(fin.fail());

  // Skip comment
  char c;
  fin >> c;
  while ( c == '%' ) {
    fin.ignore(4096, '\n');
    fin >> c;
  }
  fin.unget();

  // Get size
  index_t m, n, k;
  fin >> m >> n >> k;
  if ( cube.isEmpty() ) {
    cube = matrix::DenseCube<_Scalar, _layout>(m, n, k);
  } else {
    cube.resize(m, n, k);
  }

  // Read values
  for ( auto &value : cube ) {
    fin >> value;
  }

  // Close file
  fin.close();
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Scalar, Layout _layout>
inline void loadMatrixMarket(
    matrix::DenseCube<_Scalar> &&cube,
    const char *file
) noexcept {
  loadMatrixMarket(cube, file);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_UTILITY_MATRIX_MARKET_IO_HPP_
