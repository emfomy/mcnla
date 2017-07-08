////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/io/binary/dense_load_row_block.hpp
/// @brief   Load dense data from a binary file (row-block version).
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_IO_BINARY_DENSE_LOAD_ROW_BLOCK_HPP_
#define MCNLA_CORE_IO_BINARY_DENSE_LOAD_ROW_BLOCK_HPP_

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
  std::ifstream fin(file, std::ios::binary);
  mcnla_assert_false(fin.fail());

  std::int64_t num;

  // Skip format
  fin.seekg(4, std::ios_base::cur);

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
/// @note  If @a row_block is empty, the memory will be allocated.
/// @note  The file should be stored in column-major.
///
/// @todo  Implement for other routines
///
template <typename _Val, Trans _trans>
void loadBinaryRowBlock(
    DenseMatrix<_Val, _trans> &row_block,
    const char *file,
    const IdxRange &rowrange
) noexcept {
  static_assert(_trans == Trans::TRANS, "This routine is only available in row-major matrices.");

  auto i0 = rowrange.begin;
  auto i1 = rowrange.end;
  auto mj = rowrange.len();

  // Open file
  std::ifstream fin(file, std::ios::binary);
  mcnla_assert_false(fin.fail());

  std::int64_t num;

  // Skip format
  fin.seekg(4, std::ios_base::cur);

  // Get dimension
  fin.read(static_cast<char*>(static_cast<void*>(&num)), sizeof(num));
  mcnla_assert_eq(num, 2);

  // Get size
  fin.read(static_cast<char*>(static_cast<void*>(&num)), sizeof(num));
  index_t m = num;
  fin.read(static_cast<char*>(static_cast<void*>(&num)), sizeof(num));
  index_t n = num;
  mcnla_assert_ge(i0, 0);
  mcnla_assert_le(i1, m);

  // Allocate memory
  if ( row_block.isEmpty() ) {
    if ( !isTrans(_trans) ) {
      row_block.reconstruct(mj, n);
    } else {
      row_block.reconstruct(n, mj);
    }
  } else {
    mcnla_assert_eq(row_block.dims(), std::make_tuple(mj, n));
    mcnla_assert_true(row_block.isShrunk());
  }

  // Get values
  fin.seekg(i0 * n * sizeof(_Val), std::ios_base::cur);
  fin.read(static_cast<char*>(static_cast<void*>(row_block.valPtr())), row_block.nelem() * sizeof(_Val));

  // Close file
  fin.close();
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Val, Trans _trans>
inline void loadBinaryRowBlock(
    DenseMatrix<_Val, _trans> &&row_block,
    const char *file,
    const IdxRange &rowrange
) noexcept {
  loadBinaryRowBlock(row_block, file, rowrange);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace io

}  // namespace mcnla

#endif  // MCNLA_CORE_IO_BINARY_DENSE_LOAD_ROW_BLOCK_HPP_
