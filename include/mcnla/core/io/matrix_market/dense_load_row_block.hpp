////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/io/matrix_market/dense_load_row_block.hpp
/// @brief   Load dense data from a Matrix Market file (row-block version).
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_IO_MATRIX_MARKET_DENSE_LOAD_ROW_BLOCK_HPP_
#define MCNLA_CORE_IO_MATRIX_MARKET_DENSE_LOAD_ROW_BLOCK_HPP_

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
/// Load a size information from a Matrix Market file.
///
/// @todo  Implement for other routines
///
inline void loadMatrixMarketSize(
          index_t &nrow,
          index_t &ncol,
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
  fin >> nrow >> ncol;

  // Close file
  fin.close();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  io_module
/// Load a dense sub-matrix from a Matrix Market file.
///
/// @note  If @a matrix is empty, the memory will be allocated.
/// @note  The file should be stored in column-major.
///
/// @todo  Implement for other routines
///
template <typename _Val, Trans _trans>
void loadMatrixMarket(
    DenseMatrix<_Val, _trans> &row_block,
    const char *file,
    const IdxRange &rowrange
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
  if ( row_block.isEmpty() ) {
    row_block.reconstruct(rowrange.len(), n);
  } else {
    mcnla_assert_eq(row_block.sizes(), std::make_tuple(rowrange.len(), n));
  }

  // Read values
  _Val tmp;
  auto i0 = rowrange.begin;
  auto i1 = rowrange.end;
  for ( index_t j = 0; j < n; ++j ) {
    for ( index_t i = 0; i < m; ++i ) {
      if ( i >= i0 && i < i1 ) {
        fin >> row_block(i - i0, j);
      } else {
        fin >> tmp;
      }
    }
  }

  // Close file
  fin.close();
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Val, Trans _trans>
inline void loadMatrixMarket(
    DenseMatrix<_Val, _trans> &&row_block,
    const char *file,
    const IdxRange &rowrange
) noexcept {
  loadMatrixMarket(row_block, file, rowrange);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace io

}  // namespace mcnla

#endif  // MCNLA_CORE_IO_MATRIX_MARKET_DENSE_LOAD_ROW_BLOCK_HPP_
