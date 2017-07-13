////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/io/matrix_market/dense_load_col_block.hpp
/// @brief   Load dense data from a Matrix Market file (row-block version).
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_IO_MATRIX_MARKET_DENSE_LOAD_COL_BLOCK_HPP_
#define MCNLA_CORE_IO_MATRIX_MARKET_DENSE_LOAD_COL_BLOCK_HPP_

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
/// @note  If @a col_block is empty, the memory will be allocated.
/// @note  The file should be stored in column-major.
///
/// @todo  Implement for other routines
///
template <typename _Val, Trans _trans>
void loadMatrixMarketColBlock(
    DenseMatrix<_Val, _trans> &col_block,
    const char *file,
    const IdxRange &colrange
) noexcept {
  auto j0 = colrange.begin;
  auto j1 = colrange.end;
  auto js = colrange.len();

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
  mcnla_assert_ge(j0, 0);
  mcnla_assert_le(j1, n);

  // Allocate memory
  if ( col_block.isEmpty() ) {
    col_block.reconstruct(m, js);
  } else {
    mcnla_assert_eq(col_block.sizes(), std::make_tuple(m, js));
  }

  // Read values
  _Val tmp;
  for ( index_t j = 0; j < j0; ++j ) {
    for ( index_t i = 0; i < m; ++i ) {
      fin >> tmp;
    }
  }
  for ( index_t j = 0; j < js; ++j ) {
    for ( index_t i = 0; i < m; ++i ) {
        fin >> col_block(i, j);
    }
  }
  for ( index_t j = 0; j < n-j1; ++j ) {
    for ( index_t i = 0; i < m; ++i ) {
      fin >> tmp;
    }
  }

  // Close file
  fin.close();
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Val, Trans _trans>
inline void loadMatrixMarketColBlock(
    DenseMatrix<_Val, _trans> &&col_block,
    const char *file,
    const IdxRange &colrange
) noexcept {
  loadMatrixMarketColBlock(col_block, file, colrange);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace io

}  // namespace mcnla

#endif  // MCNLA_CORE_IO_MATRIX_MARKET_DENSE_LOAD_COL_BLOCK_HPP_
