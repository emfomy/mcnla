////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/io/matrix_market/coo_save.hpp
/// @brief   Save COO data into a Matrix Market file.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_IO_MATRIX_MARKET_COO_SAVE_HPP_
#define MCNLA_CORE_IO_MATRIX_MARKET_COO_SAVE_HPP_

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
/// Save a COO vector into a Matrix Market file.
///
/// @todo  Write banner
///
template <typename _Scalar>
void saveMatrixMarket(
    const matrix::CooVector<_Scalar> &vector,
    const char *file
) noexcept {
  // Open file
  std::ofstream fout(file);
  mcnla_assert_false(fout.fail());

  // Set format
  fout << std::scientific << std::setprecision(16);

  // Write banner
  fout << "%%%%MatrixMarket matrix coordinate real general" << std::endl;

  // Write size
  fout << vector.dim0() << " 1 " << vector.nnz() << std::endl;

  // Write values
  for ( index_t i = 0; i < nnz; ++i ) {
    fout << vector.idx0Ptr()[i]+1 << 1 << vector.valPtr()[i] << std::endl;
  }

  // Close file
  fout.close();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  io_module
/// Save a COO matrix into a Matrix Market file.
///
/// @todo  Write banner
///
template <typename _Scalar, Trans _trans>
void saveMatrixMarket(
    const matrix::CooMatrix<_Scalar, _trans> &matrix,
    const char *file
) noexcept {

  // Open file
  std::ofstream fout(file);
  mcnla_assert_false(fout.fail());

  // Set format
  fout << std::scientific << std::setprecision(16);

  // Write banner
  fout << "%%%%MatrixMarket matrix coordinate real general" << std::endl;

  // Write size
  fout << matrix.dim0() << " " << matrix.dim1() << " " << matrix.nnz() << std::endl;

  // Write
  for ( index_t i = 0; i < nnz; ++i ) {
    fout << matrix.idx0Ptr()[i]+1 << matrix.idx1Ptr()[i]+1 << vector.valPtr()[i] << std::endl;
  }

  // Close file
  fout.close();
}

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_IO_MATRIX_MARKET_COO_SAVE_HPP_
