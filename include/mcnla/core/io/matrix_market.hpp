////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/io/matrix_market.hpp
/// @brief   The Matrix Market IO utilities.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_IO_MATRIX_MARKET_HPP_
#define MCNLA_CORE_IO_MATRIX_MARKET_HPP_

#include <mcnla/def.hpp>
#include <mcnla/core/def.hpp>
#include <mcnla/core/io/def.hpp>
#include <fstream>
#include <mcnla/core/matrix.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The I/O namespace.
//
namespace io {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  io_module
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
    mcnla_assert_eq(vector.getSizes(), m);
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
/// @ingroup  io_module
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
    if ( isColMajor(_layout) ) {
      matrix = matrix::DenseMatrix<_Scalar, _layout>(m, n);
    } else {
      matrix = matrix::DenseMatrix<_Scalar, _layout>(n, m);
    }
  } else {
    if ( isColMajor(_layout) ) {
      mcnla_assert_eq(matrix.getSizes(), std::make_pair(m, n));
    } else {
      mcnla_assert_eq(matrix.getSizes(), std::make_pair(n, m));
    }
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
/// @ingroup  io_module
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
    if ( isColMajor(_layout) ) {
      cube = matrix::DenseCube<_Scalar, _layout>(m, n, k);
    } else {
      cube = matrix::DenseCube<_Scalar, _layout>(n, m, k);
    }
  } else {
    if ( isColMajor(_layout) ) {
      mcnla_assert_eq(cube.getSizes(), std::make_tuple(m, n, k));
    } else {
      mcnla_assert_eq(cube.getSizes(), std::make_tuple(n, m, k));
    }
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

#endif  // MCNLA_CORE_IO_MATRIX_MARKET_HPP_
