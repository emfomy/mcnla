////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/io/matrix_market/dense_load.hpp
/// @brief   Load dense data from a Matrix Market file.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_IO_MATRIX_MARKET_DENSE_LOAD_HPP_
#define MCNLA_CORE_IO_MATRIX_MARKET_DENSE_LOAD_HPP_

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
/// Load a dense vector from a Matrix Market file.
///
/// @note  If @a vector is empty, the memory will be allocated.
///
/// @todo  Read banner
///
template <typename _Scalar>
void loadMatrixMarket(
    DenseVector<_Scalar> &vector,
    const char *file
) noexcept {
  // Open file
  std::ifstream fin(file);
  mcnla_assert_false(fin.fail());

  // Skip comment
  while ( fin.peek() == '%' ) {
    fin.ignore(4096, '\n');
  }

  // Get size
  index_t m, n;
  fin >> m >> n;
  if ( vector.isEmpty() ) {
    vector.reconstruct(m);
  } else {
    mcnla_assert_eq(vector.dims(), std::make_tuple(m));
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
    DenseVector<_Scalar> &&vector,
    const char *file
) noexcept {
  loadMatrixMarket(vector, file);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  io_module
/// Load a dense matrix from a Matrix Market file.
///
/// @note  If @a matrix is empty, the memory will be allocated.
///
/// @todo  Read banner
///
template <typename _Scalar, Trans _trans>
void loadMatrixMarket(
    DenseMatrix<_Scalar, _trans> &matrix,
    const char *file
) noexcept {
  // Open file
  std::ifstream fin(file);
  mcnla_assert_false(fin.fail());

  // Skip comment
  while ( fin.peek() == '%' ) {
    fin.ignore(4096, '\n');
  }

  // Get size
  index_t m, n;
  fin >> m >> n;
  if ( matrix.isEmpty() ) {
    if ( !isTrans(_trans) ) {
      matrix.reconstruct(m, n);
    } else {
      matrix.reconstruct(n, m);
    }
  } else {
    mcnla_assert_eq(matrix.dims(), std::make_tuple(m, n));
  }

  // Read values
  for ( auto &value : matrix ) {
    fin >> value;
  }

  // Close file
  fin.close();
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Scalar, Trans _trans>
inline void loadMatrixMarket(
    DenseMatrix<_Scalar, _trans> &&matrix,
    const char *file
) noexcept {
  loadMatrixMarket(matrix, file);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  io_module
/// Load a dense vector set from a Matrix Market file.
///
/// @note  If @a set is empty, the memory will be allocated.
///
/// @todo  Read banner
///
template <class _Derived>
void loadMatrixMarket(
    VectorCollectionWrapper<_Derived> &set,
    const char *file
) noexcept {
  using VectorType = VectorT<_Derived>;
  using ScalarType = ScalarT<VectorType>;

  static_assert(std::is_base_of<DenseVector<ScalarType>, VectorType>::value, "'_Derived' is not a dense vector!");

  auto &derived = set.derived();

  // Open file
  std::ifstream fin(file);
  mcnla_assert_false(fin.fail());

  // Skip comment
  while ( fin.peek() == '%' ) {
    fin.ignore(4096, '\n');
  }

  // Get size
  index_t m, n;
  fin >> m >> n;
  if ( derived.unfold().isEmpty() ) {
    derived.reconstruct(m, n);
  } else {
    mcnla_assert_eq(set.vec(), n);
    mcnla_assert_eq(set(0).dims(), std::make_tuple(m));
  }

  // Read values
  for ( auto i = 0; i < n; ++i ) {
    auto vector = set(i);
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
    VectorCollectionWrapper<_Derived> &&set,
    const char *file
) noexcept {
  loadMatrixMarket(set, file);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  io_module
/// Load a dense matrix set from a Matrix Market file.
///
/// @note  If @a set is empty, the memory will be allocated.
///
/// @todo  Read banner
///
template <class _Derived>
void loadMatrixMarket(
    MatrixCollectionWrapper<_Derived> &set,
    const char *file
) noexcept {
  using MatrixType = MatrixT<_Derived>;
  using ScalarType = ScalarT<MatrixType>;
  constexpr Trans trans = MatrixType::trans;

  static_assert(std::is_base_of<DenseMatrix<ScalarType, trans>, MatrixType>::value, "'_Derived' is not a dense matrix!");

  auto &derived = set.derived();

  // Open file
  std::ifstream fin(file);
  mcnla_assert_false(fin.fail());

  // Skip comment
  while ( fin.peek() == '%' ) {
    fin.ignore(4096, '\n');
  }

  // Get size
  index_t m, n, k;
  fin >> m >> n >> k;
  if ( derived.unfold().isEmpty() ) {
    if ( !isTrans(trans) ) {
      derived.reconstruct(m, n, k);
    } else {
      derived.reconstruct(n, m, k);
    }
  } else {
    mcnla_assert_eq(set.nmat(), k);
    mcnla_assert_eq(set(0).dims(), std::make_tuple(m, n));
  }

  // Read values
  for ( auto i = 0; i < k; ++i ) {
    auto matrix = set(i);
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
    MatrixCollectionWrapper<_Derived> &&set,
    const char *file
) noexcept {
  loadMatrixMarket(set, file);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_IO_MATRIX_MARKET_DENSE_LOAD_HPP_