////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/io/binary/dense_load.hpp
/// @brief   Load dense data from a binary file.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_IO_BINARY_DENSE_LOAD_HPP_
#define MCNLA_CORE_IO_BINARY_DENSE_LOAD_HPP_

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
/// Load a dense vector from a binary file.
///
/// @note  If @a vector is empty, the memory will be allocated.
  /// @note  The data will be loaded in storage layout.
///
template <typename _Val>
void loadBinary(
    DenseVector<_Val> &vector,
    const char *file
) noexcept {
  // Open file
  std::ifstream fin(file);
  mcnla_assert_false(fin.fail());

  std::int64_t num;

  // Skip format
  fin.seekg(4, std::ios_base::cur);

  // Get dimension
  fin.read(static_cast<char*>(static_cast<void*>(&num)), sizeof(num));
  mcnla_assert_eq(num, 1);

  // Get size
  fin.read(static_cast<char*>(static_cast<void*>(&num)), sizeof(num));
  index_t dim0 = num;

  // Allocate memory
  if ( vector.isEmpty() ) {
    vector.reconstruct(dim0);
  } else {
    mcnla_assert_eq(vector.sizes(), std::make_tuple(dim0));
    mcnla_assert_true(vector.isShrunk());
  }

  // Get values
  fin.read(static_cast<char*>(static_cast<void*>(vector.valPtr())), vector.nelem() * sizeof(_Val));

  // Close file
  fin.close();
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Val>
inline void loadBinary(
    DenseVector<_Val> &&vector,
    const char *file
) noexcept {
  loadBinary(vector, file);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  io_module
/// Load a dense matrix from a binary file.
///
/// @note  If @a matrix is empty, the memory will be allocated.
/// @note  The data will be loaded in storage layout.
///
template <typename _Val, Trans _trans>
void loadBinary(
    DenseMatrix<_Val, _trans> &matrix,
    const char *file
) noexcept {
  // Open file
  std::ifstream fin(file);
  mcnla_assert_false(fin.fail());

  std::int64_t num;

  // Skip format
  fin.seekg(4, std::ios_base::cur);

  // Get dimension
  fin.read(static_cast<char*>(static_cast<void*>(&num)), sizeof(num));
  mcnla_assert_eq(num, 2);

  // Get size
  fin.read(static_cast<char*>(static_cast<void*>(&num)), sizeof(num));
  index_t dim0 = num;
  fin.read(static_cast<char*>(static_cast<void*>(&num)), sizeof(num));
  index_t dim1 = num;

  // Allocate memory
  if ( matrix.isEmpty() ) {
    if ( !isTrans(_trans) ) {
      matrix.reconstruct(dim0, dim1);
    } else {
      matrix.reconstruct(dim1, dim0);
    }
  } else {
    mcnla_assert_eq(matrix.dims(), std::make_tuple(dim0, dim1));
    mcnla_assert_true(matrix.isShrunk());
  }

  // Get values
  fin.read(static_cast<char*>(static_cast<void*>(matrix.valPtr())), matrix.nelem() * sizeof(_Val));

  // Close file
  fin.close();
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Val, Trans _trans>
inline void loadBinary(
    DenseMatrix<_Val, _trans> &&matrix,
    const char *file
) noexcept {
  loadBinary(matrix, file);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace io

}  // namespace mcnla

#endif  // MCNLA_CORE_IO_BINARY_DENSE_LOAD_HPP_
