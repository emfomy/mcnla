////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/io/matrix_market/dense_load_block.hpp
/// @brief   Load dense data from a Matrix Market file (row-block version).
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_IO_MATRIX_MARKET_DENSE_LOAD_BLOCK_HPP_
#define MCNLA_CORE_IO_MATRIX_MARKET_DENSE_LOAD_BLOCK_HPP_

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
template <Trans _trans>
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
/// @note  If @a colblock is empty, the memory will be allocated.
/// @note  The file should be stored in column-major.
///
/// @todo  Implement for other routines
///
template <typename _Val, Trans _trans>
void loadMatrixMarketColBlock(
    DenseMatrix<_Val, _trans> &colblock,
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
  if ( colblock.isEmpty() ) {
    colblock.reconstruct(m, js);
  } else {
    mcnla_assert_eq(colblock.sizes(), std::make_tuple(m, js));
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
      fin >> colblock(i, j);
    }
  }
  // for ( index_t j = 0; j < n-j1; ++j ) {
  //   for ( index_t i = 0; i < m; ++i ) {
  //     fin >> tmp;
  //   }
  // }

  // Close file
  fin.close();
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Val, Trans _trans>
inline void loadMatrixMarketColBlock(
    DenseMatrix<_Val, _trans> &&colblock,
    const char *file,
    const IdxRange &colrange
) noexcept {
  loadMatrixMarketRowBlock(colblock, file, colrange);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  io_module
/// Load a dense sub-matrix from a Matrix Market file.
///
/// @note  If @a rowblock is empty, the memory will be allocated.
/// @note  The file should be stored in column-major.
///
/// @todo  Implement for other routines
///
template <typename _Val, Trans _trans>
void loadMatrixMarketRowBlock(
    DenseMatrix<_Val, _trans> &rowblock,
    const char *file,
    const IdxRange &rowrange
) noexcept {
  auto i0 = rowrange.begin;
  auto i1 = rowrange.end;
  auto is = rowrange.len();

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
  mcnla_assert_ge(i0, 0);
  mcnla_assert_le(i1, m);

  // Allocate memory
  if ( rowblock.isEmpty() ) {
    rowblock.reconstruct(is, n);
  } else {
    mcnla_assert_eq(rowblock.sizes(), std::make_tuple(is, n));
  }

  // Read values
  _Val tmp;
  for ( index_t j = 0; j < n; ++j ) {
    for ( index_t i = 0; i < i0; ++i ) {
      fin >> tmp;
    }
    for ( index_t i = 0; i < is; ++i ) {
      fin >> rowblock(i, j);
    }
    for ( index_t i = 0; i < n-i1; ++i ) {
      fin >> tmp;
    }
  }

  // Close file
  fin.close();
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Val, Trans _trans>
inline void loadMatrixMarketRowBlock(
    DenseMatrix<_Val, _trans> &&rowblock,
    const char *file,
    const IdxRange &rowrange
) noexcept {
  loadMatrixMarketRowBlock(rowblock, file, rowrange);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace io

}  // namespace mcnla

#endif  // MCNLA_CORE_IO_MATRIX_MARKET_DENSE_LOAD_BLOCK_HPP_
