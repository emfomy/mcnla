////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/io/matrix_market/coo_load.hpp
/// @brief   Load COO data from a matrix market file.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_IO_MATRIX_MARKET_COO_LOAD_HPP_
#define MCNLA_CORE_IO_MATRIX_MARKET_COO_LOAD_HPP_

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
/// Load a COO vector from a matrix market file.
///
/// @note  If @a vector is empty, the memory will be allocated.
///
/// @todo  Read banner
///
template <typename _Scalar>
void loadMatrixMarket(
    CooVector<_Scalar> &vector,
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
  index_t m, n, nnz;
  fin >> m >> n >> nnz;
  if ( vector.isEmpty() ) {
    vector.reconstruct(m, nnz);
  } else {
    mcnla_assert_eq(vector.dims(), std::make_tuple(m));
    mcnla_assert_eq(vector.nnz(), nnz);
  }

  // Read values
  index_t x, y;
  for ( index_t i = 0; i < nnz; ++i ) {
    fin >> x >> y >> vector.valPtr()[i];
    vector.idx0Ptr()[i] = x-1;
  }

  // Close file
  fin.close();
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Scalar>
inline void loadMatrixMarket(
    CooVector<_Scalar> &&vector,
    const char *file
) noexcept {
  loadMatrixMarket(vector, file);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  io_module
/// Load a COO matrix from a matrix market file.
///
/// @note  If @a matrix is empty, the memory will be allocated.
///
/// @todo  Read banner
///
template <typename _Scalar, Trans _trans>
void loadMatrixMarket(
    CooMatrix<_Scalar, _trans> &matrix,
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
  index_t m, n, nnz;
  fin >> m >> n >> nnz;
  if ( matrix.isEmpty() ) {
    if ( !isTrans(_trans) ) {
      matrix.reconstruct(m, n, nnz);
    } else {
      matrix.reconstruct(n, m, nnz);
    }
  } else {
    mcnla_assert_eq(matrix.dims(), std::make_tuple(m, n));
    mcnla_assert_eq(matrix.nnz(), nnz);
  }

  // Read values
  index_t x, y;
  for ( index_t i = 0; i < nnz; ++i ) {
    fin >> x >> y >> matrix.valPtr()[i];
    matrix.idx0Ptr()[i] = x-1;
    matrix.idx1Ptr()[i] = y-1;
  }

  // Close file
  fin.close();
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Scalar, Trans _trans>
inline void loadMatrixMarket(
    CooMatrix<_Scalar, _trans> &&matrix,
    const char *file
) noexcept {
  loadMatrixMarket(matrix, file);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_IO_MATRIX_MARKET_COO_LOAD_HPP_
