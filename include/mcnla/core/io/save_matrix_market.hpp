////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/io/matrix_market.hpp
/// @brief   Save data info a matrix market file.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_IO_SAVE_MATRIX_MARKET_HPP_
#define MCNLA_CORE_IO_SAVE_MATRIX_MARKET_HPP_

#include <mcnla/def.hpp>
#include <mcnla/core/def.hpp>
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
/// Save a dense vector info a matrix market file.
///
/// @todo  Write banner
///
template <typename _Scalar>
void saveMatrixMarket(
    const matrix::DenseVector<_Scalar> &vector,
    const char *file
) noexcept {
  // Open file
  std::ofstream fout(file);
  mcnla_assert_false(fout.fail());

  // Set format
  fout << std::scientific << std::setprecision(16);

  // Write banner
  fout << "%%%%MatrixMarket matrix array real general" << std::endl;

  // Write size
  fout << vector.template getSize<0>() << " 1" << std::endl;

  // Write values
  for ( auto value : vector ) {
    fout << value << std::endl;
  }

  // Close file
  fout.close();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  io_module
/// Save a dense matrix info a matrix market file.
///
/// @todo  Write banner
///
template <typename _Scalar, Layout _layout>
void saveMatrixMarket(
    const matrix::DenseMatrix<_Scalar, _layout> &matrix,
    const char *file
) noexcept {
  // Open file
  std::ofstream fout(file);
  mcnla_assert_false(fout.fail());

  // Set format
  fout << std::scientific << std::setprecision(16);

  // Write banner
  fout << "%%%%MatrixMarket matrix array real general" << std::endl;

  // Write size
  fout << matrix.template getSize<0>() << " " << matrix.template getSize<1>() << std::endl;

  // Write values
  for ( auto value : matrix ) {
    fout << value << std::endl;
  }

  // Close file
  fout.close();
}

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_IO_SAVE_MATRIX_MARKET_HPP_
