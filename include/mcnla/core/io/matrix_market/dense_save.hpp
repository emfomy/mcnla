////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/io/matrix_market/dense_save.hpp
/// @brief   Save dense data into a Matrix Market file.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_IO_MATRIX_MARKET_DENSE_SAVE_HPP_
#define MCNLA_CORE_IO_MATRIX_MARKET_DENSE_SAVE_HPP_

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
/// Save a dense vector into a Matrix Market file.
///
/// @note  The file will be stored in column-major.
///
/// @todo  Write banner
///
template <typename _Val>
void saveMatrixMarket(
    const matrix::DenseVector<_Val> &vector,
    const char *file
) noexcept {
  // Open file
  std::ofstream fout(file);
  mcnla_assert_false(fout.fail());

  // Set format
  fout << std::scientific << std::setprecision(16);

  // Write banner
  fout << "%%MatrixMarket matrix array real general" << std::endl;

  // Write size
  fout << vector.length() << " 1" << std::endl;

  // Write values
  for ( index_t i = 0; i < vector.length(); ++i ) {
    fout << vector(i) << std::endl;
  }

  // Close file
  fout.close();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  io_module
/// Save a dense matrix into a Matrix Market file.
///
/// @note  The file will be stored in column-major.
///
/// @todo  Write banner
///
template <typename _Val, Trans _trans>
void saveMatrixMarket(
    const matrix::DenseMatrix<_Val, _trans> &matrix,
    const char *file
) noexcept {
  // Open file
  std::ofstream fout(file);
  mcnla_assert_false(fout.fail());

  // Set format
  fout << std::scientific << std::setprecision(16);

  // Write banner
  fout << "%%MatrixMarket matrix array real general" << std::endl;

  // Write size
  fout << matrix.nrow() << " " << matrix.ncol() << std::endl;

  // Write values
  for ( index_t j = 0; j < matrix.ncol(); ++j ) {
    for ( index_t i = 0; i < matrix.nrow(); ++i ) {
      fout << matrix(i, j) << std::endl;
    }
  }

  // Close file
  fout.close();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  io_module
/// Save a dense vector set into a Matrix Market file.
///
/// @note  The file will be stored in column-major.
///
/// @todo  Write banner
///
template <class _Tag, typename _Val>
void saveMatrixMarket(
    const DenseVectorCollection<_Tag, _Val> &collection,
    const char *file
) noexcept {
  // Open file
  std::ofstream fout(file);
  mcnla_assert_false(fout.fail());

  // Set format
  fout << std::scientific << std::setprecision(16);

  // Write banner
  fout << "%%MatrixMarket matrix array real general" << std::endl;

  // Write size
  fout << collection.length() << " " << collection.nvec() << std::endl;

  // Write values
  for ( index_t j = 0; j < collection.nvec(); ++j ) {
    auto vector = collection(j);
    for ( index_t i = 0; i < vector.length(); ++i ) {
      fout << vector(i) << std::endl;
    }
  }

  // Close file
  fout.close();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  io_module
/// Save a dense vector set into a Matrix Market file.
///
/// @note  The file will be stored in column-major.
///
/// @todo  Write banner
///
template <class _Tag, typename _Val, Trans _trans>
void saveMatrixMarket(
    const DenseMatrixCollection<_Tag, _Val, _trans> &collection,
    const char *file
) noexcept {
  // Open file
  std::ofstream fout(file);
  mcnla_assert_false(fout.fail());

  // Set format
  fout << std::scientific << std::setprecision(16);

  // Write banner
  fout << "%%MatrixMarket 3D array real general" << std::endl;

  // Write size
  fout << collection.nrow() << " " << collection.ncol() << " " << collection.nmat() << std::endl;

  // Write values
  for ( index_t k = 0; k < collection.nmat(); ++k ) {
    auto matrix = collection(k);
    for ( index_t j = 0; j < matrix.ncol(); ++j ) {
      for ( index_t i = 0; i < matrix.nrow(); ++i ) {
        fout << matrix(i, j) << std::endl;
      }
    }
  }

  // Close file
  fout.close();
}

}  // namespace io

}  // namespace mcnla

#endif  // MCNLA_CORE_IO_MATRIX_MARKET_DENSE_SAVE_HPP_
