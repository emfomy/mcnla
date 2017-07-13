////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/io/binary/dense_load_col_block.hpp
/// @brief   Load dense data from a binary file (row-block version).
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_IO_BINARY_DENSE_LOAD_COL_BLOCK_HPP_
#define MCNLA_CORE_IO_BINARY_DENSE_LOAD_COL_BLOCK_HPP_

#include <mcnla/core/io/binary/def.hpp>
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
/// Load a size information from a binary file.
///
/// @todo  Implement for other routines
///
inline void loadBinarySize(
          index_t &nrow,
          index_t &ncol,
    const char *file
) noexcept {
  // Open file
  std::ifstream fin(file);
  mcnla_assert_false(fin.fail());

  // Check header
  detail::checkHeader<DenseTag, void>(fin);
  std::int64_t num;

  // Get dimension
  fin.read(static_cast<char*>(static_cast<void*>(&num)), sizeof(num));
  mcnla_assert_eq(num, 2);

  // Get size
  fin.read(static_cast<char*>(static_cast<void*>(&num)), sizeof(num));
  nrow = num;
  fin.read(static_cast<char*>(static_cast<void*>(&num)), sizeof(num));
  ncol = num;

  // Close file
  fin.close();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  io_module
/// Load a dense sub-matrix from a binary file.
///
/// @note  If @a col_block is empty, the memory will be allocated.
/// @note  The file should be stored in column-major.
///
/// @todo  Implement for other routines
///
template <typename _Val, Trans _trans>
void loadBinaryColBlock(
    DenseMatrix<_Val, _trans> &col_block,
    const char *file,
    const IdxRange &colrange
) noexcept {
  static_assert(_trans == Trans::NORMAL, "This routine is only available in col-major matrices.");

  auto j0 = colrange.begin;
  auto j1 = colrange.end;
  auto js = colrange.len();

  // Open file
  std::ifstream fin(file);
  mcnla_assert_false(fin.fail());

  // Check header
  detail::checkHeader<DenseTag, _Val>(fin);
  std::int64_t num;

  // Get dimension
  fin.read(static_cast<char*>(static_cast<void*>(&num)), sizeof(num));
  mcnla_assert_eq(num, 2);

  // Get size
  fin.read(static_cast<char*>(static_cast<void*>(&num)), sizeof(num));
  index_t dim0 = num;
  fin.read(static_cast<char*>(static_cast<void*>(&num)), sizeof(num));
  index_t dim1 = num;
  mcnla_assert_ge(j0, 0);
  mcnla_assert_le(j1, dim1);

  // Allocate memory
  if ( col_block.isEmpty() ) {
    col_block.reconstruct(dim0, js);
  } else {
    mcnla_assert_eq(col_block.dims(), std::make_tuple(dim0, js));
    mcnla_assert_true(col_block.isShrunk());
  }

  // Get values
  fin.seekg(dim0 * j0 * sizeof(_Val), std::ios_base::cur);
  fin.read(static_cast<char*>(static_cast<void*>(col_block.valPtr())), col_block.nelem() * sizeof(_Val));

  // Close file
  fin.close();
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Val, Trans _trans>
inline void loadBinaryColBlock(
    DenseMatrix<_Val, _trans> &&col_block,
    const char *file,
    const IdxRange &colrange
) noexcept {
  loadBinaryColBlock(col_block, file, colrange);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace io

}  // namespace mcnla

#endif  // MCNLA_CORE_IO_BINARY_DENSE_LOAD_COL_BLOCK_HPP_
