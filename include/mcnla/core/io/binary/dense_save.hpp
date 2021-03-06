////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/io/binary/dense_save.hpp
/// @brief   Save dense data into a binary file.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_IO_BINARY_DENSE_SAVE_HPP_
#define MCNLA_CORE_IO_BINARY_DENSE_SAVE_HPP_

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
/// Save a dense vector into a binary file.
///
/// @note  The file will be stored in storage layout.
///
template <typename _Val>
void saveBinary(
    const matrix::DenseVector<_Val> &vector,
    const char *file,
    const char *comment = ""
) noexcept {
  mcnla_assert_true(vector.isShrunk());

  // Open file
  std::ofstream fout(file);
  mcnla_assert_false(fout.fail());

  // Write header
  detail::writeHeader<DenseTag, _Val>(fout, comment);
  std::int64_t num = 1;

  // Write dimension
  fout.write(static_cast<const char*>(static_cast<const void*>(&num)), sizeof(num));

  // Write size
  num = vector.dim0();
  fout.write(static_cast<const char*>(static_cast<const void*>(&num)), sizeof(num));

  // Write values
  mcnla_assert_true(vector.isShrunk());
  fout.write(static_cast<const char*>(static_cast<const void*>(vector.valPtr())), vector.nelem() * sizeof(_Val));

  // Close file
  fout.close();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  io_module
/// Save a dense matrix into a binary file.
///
/// @note  The file will be stored in storage layout.
///
template <typename _Val, Trans _trans>
void saveBinary(
    const matrix::DenseMatrix<_Val, _trans> &matrix,
    const char *file,
    const char *comment = ""
) noexcept {
  mcnla_assert_true(matrix.isShrunk());

  // Open file
  std::ofstream fout(file);
  mcnla_assert_false(fout.fail());

  // Write header
  detail::writeHeader<DenseTag, _Val>(fout, comment);
  std::int64_t num = 2;

  // Write dimension
  fout.write(static_cast<const char*>(static_cast<const void*>(&num)), sizeof(num));

  // Write size
  num = matrix.dim0();
  fout.write(static_cast<const char*>(static_cast<const void*>(&num)), sizeof(num));
  num = matrix.dim1();
  fout.write(static_cast<const char*>(static_cast<const void*>(&num)), sizeof(num));

  // Write values
  mcnla_assert_true(matrix.isShrunk());
  fout.write(static_cast<const char*>(static_cast<const void*>(matrix.valPtr())), matrix.nelem() * sizeof(_Val));

  // Close file
  fout.close();
}

}  // namespace io

}  // namespace mcnla

#endif  // MCNLA_CORE_IO_BINARY_DENSE_SAVE_HPP_
