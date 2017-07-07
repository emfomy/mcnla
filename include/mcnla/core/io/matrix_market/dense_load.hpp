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
/// @note  The file should be stored in column-major.
///
/// @todo  Read banner
///
template <typename _Val>
void loadMatrixMarket(
    DenseVector<_Val> &vector,
    const char *file
) noexcept {
  // Open file
  std::ifstream fin(file);
  mcnla_assert_false(fin.fail());

  // Skip comment
  while ( fin.peek() == '%' ) {
    fin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }

  // Get size
  index_t m, n;
  fin >> m >> n;
  if ( vector.isEmpty() ) {
    vector.reconstruct(m);
  } else {
    mcnla_assert_eq(vector.sizes(), std::make_tuple(m));
  }

  // Read values
  for ( index_t i = 0; i < m; ++i ) {
    fin >> vector(i);
  }

  // Close file
  fin.close();
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Val>
inline void loadMatrixMarket(
    DenseVector<_Val> &&vector,
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
/// @note  The file should be stored in column-major.
///
/// @todo  Read banner
///
template <typename _Val, Trans _trans>
void loadMatrixMarket(
    DenseMatrix<_Val, _trans> &matrix,
    const char *file
) noexcept {
  // Open file
  std::ifstream fin(file);
  mcnla_assert_false(fin.fail());

  // Skip comment
  while ( fin.peek() == '%' ) {
    fin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }

  // Get size
  index_t m, n;
  fin >> m >> n;
  if ( matrix.isEmpty() ) {
    matrix.reconstruct(m, n);
  } else {
    mcnla_assert_eq(matrix.sizes(), std::make_tuple(m, n));
  }

  // Read values
  for ( index_t j = 0; j < n; ++j ) {
    for ( index_t i = 0; i < m; ++i ) {
      fin >> matrix(i, j);
    }
  }

  // Close file
  fin.close();
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Val, Trans _trans>
inline void loadMatrixMarket(
    DenseMatrix<_Val, _trans> &&matrix,
    const char *file
) noexcept {
  loadMatrixMarket(matrix, file);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  io_module
/// Load a dense vector collection from a Matrix Market file.
///
/// @note  If @a collection is empty, the memory will be allocated.
/// @note  The file should be stored in column-major.
///
/// @todo  Read banner
///
template <class _Tag, typename _Val>
void loadMatrixMarket(
    DenseVectorCollection<_Tag, _Val> &collection,
    const char *file
) noexcept {
  // Open file
  std::ifstream fin(file);
  mcnla_assert_false(fin.fail());

  // Skip comment
  while ( fin.peek() == '%' ) {
    fin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }

  // Get size
  index_t m, n;
  fin >> m >> n;
  if ( collection.isEmpty() ) {
    collection.reconstruct(m, n);
  } else {
    mcnla_assert_eq(collection.sizes(), std::make_tuple(m, n));
  }

  // Read values
  for ( index_t j = 0; j < n; ++j ) {
    auto vector = collection(j);
    for ( index_t i = 0; i < m; ++i ) {
      fin >> vector(i);
    }
  }

  // Close file
  fin.close();
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <class _Tag, typename _Val>
inline void loadMatrixMarket(
    DenseVectorCollection<_Tag, _Val> &&collection,
    const char *file
) noexcept {
  loadMatrixMarket(collection, file);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  io_module
/// Load a dense matrix collection from a Matrix Market file.
///
/// @note  If @a collection is empty, the memory will be allocated.
/// @note  The file should be stored in column-major.
///
/// @todo  Read banner
///
template <class _Tag, typename _Val, Trans _trans>
void loadMatrixMarket(
    DenseMatrixCollection<_Tag, _Val, _trans> &collection,
    const char *file
) noexcept {
  // Open file
  std::ifstream fin(file);
  mcnla_assert_false(fin.fail());

  // Skip comment
  while ( fin.peek() == '%' ) {
    fin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }

  // Get size
  index_t m, n, l;
  fin >> m >> n >> l;
  if ( collection.isEmpty() ) {
    collection.reconstruct(m, n, l);
  } else {
    mcnla_assert_eq(collection.sizes(), std::make_tuple(m, n, l));
  }

  // Read values
  for ( auto k = 0; k < l; ++k ) {
    auto matrix = collection(k);
    for ( index_t j = 0; j < n; ++j ) {
      for ( index_t i = 0; i < m; ++i ) {
        fin >> matrix(i, j);
      }
    }
  }

  // Close file
  fin.close();
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <class _Tag, typename _Val, Trans _trans>
inline void loadMatrixMarket(
    DenseMatrixCollection<_Tag, _Val, _trans> &&collection,
    const char *file
) noexcept {
  loadMatrixMarket(collection, file);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace io

}  // namespace mcnla

#endif  // MCNLA_CORE_IO_MATRIX_MARKET_DENSE_LOAD_HPP_
