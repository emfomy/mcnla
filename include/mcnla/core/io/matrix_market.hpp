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
    mcnla_assert_eq(vector.sizes(), m);
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
      mcnla_assert_eq(matrix.sizes(), std::make_pair(m, n));
    } else {
      mcnla_assert_eq(matrix.sizes(), std::make_pair(n, m));
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
/// Load a dense vector set from a matrix market file.
///
/// @note  If @a set is empty, the memory will be allocated.
///
/// @todo  Read banner
///
template <class _Derived>
void loadMatrixMarket(
    matrix::VectorSetWrapper<_Derived> &set,
    const char *file
) noexcept {

  static_assert(std::is_base_of<matrix::VectorBase<typename _Derived::VectorType>, typename _Derived::VectorType>::value,
                "'_Derived' is not a vector set!");
  static_assert(std::is_base_of<matrix::DenseBase<typename _Derived::VectorType>, typename _Derived::VectorType>::value,
                "'_Derived' is not a dense vector set!");

  auto &derived = set.derived();

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
  if ( derived.unfold().isEmpty() ) {
    derived = _Derived(m, n);
  } else {
    mcnla_assert_eq(derived.sizes(), std::make_pair(m, n));
  }

  // Read values
  for ( auto i = 0; i < n; ++i ) {
    auto vector = derived(i);
    for ( auto &value : vector ) {
      fin >> value;
    }
  }

  // Close file
  fin.close();
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <class _Derived>
inline void loadMatrixMarket(
    matrix::VectorSetWrapper<_Derived> &&set,
    const char *file
) noexcept {
  loadMatrixMarket(set, file);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  io_module
/// Load a dense matrix set from a matrix market file.
///
/// @note  If @a set is empty, the memory will be allocated.
///
/// @todo  Read banner
///
template <class _Derived>
void loadMatrixMarket(
    matrix::MatrixSetWrapper<_Derived> &set,
    const char *file
) noexcept {

  static_assert(std::is_base_of<matrix::MatrixBase<typename _Derived::MatrixType>, typename _Derived::MatrixType>::value,
                "'_Derived' is not a matrix set!");
  static_assert(std::is_base_of<matrix::DenseBase<typename _Derived::MatrixType>, typename _Derived::MatrixType>::value,
                "'_Derived' is not a dense matrix set!");

  constexpr auto layout = _Derived::MatrixType::layout;
  auto &derived = set.derived();

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
  if ( derived.unfold().isEmpty() ) {
    if ( !isTrans(trans) ) {
      derived = _Derived(m, n, k);
    } else {
      derived = _Derived(n, m, k);
    }
  } else {
    if ( !isTrans(trans) ) {
      mcnla_assert_eq(derived.sizes(), std::make_tuple(m, n, k));
    } else {
      mcnla_assert_eq(derived.sizes(), std::make_tuple(n, m, k));
    }
  }

  // Read values
  for ( auto i = 0; i < k; ++i ) {
    auto matrix = derived(i);
    for ( auto &value : matrix ) {
      fin >> value;
    }
  }

  // Close file
  fin.close();
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <class _Derived>
inline void loadMatrixMarket(
    matrix::MatrixSetWrapper<_Derived> &&set,
    const char *file
) noexcept {
  loadMatrixMarket(set, file);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_IO_MATRIX_MARKET_HPP_
