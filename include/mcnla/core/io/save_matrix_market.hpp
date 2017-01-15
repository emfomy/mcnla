////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/io/save_matrix_market.hpp
/// @brief   Save data into a matrix market file.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_IO_SAVE_MATRIX_MARKET_HPP_
#define MCNLA_CORE_IO_SAVE_MATRIX_MARKET_HPP_

#include <mcnla/def.hpp>
#include <mcnla/core/def.hpp>
#include <mcnla/core/io/def.hpp>
#include <fstream>
#include <mcnla/core/container.hpp>

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
/// Save a dense vector into a matrix market file.
///
/// @todo  Write banner
///
template <typename _Scalar>
void saveMatrixMarket(
    const container::DenseVector<_Scalar> &vector,
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
  fout << vector.dim0() << " 1" << std::endl;

  // Write values
  for ( auto value : vector ) {
    fout << value << std::endl;
  }

  // Close file
  fout.close();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  io_module
/// Save a dense matrix into a matrix market file.
///
/// @todo  Write banner
///
template <typename _Scalar, Trans _trans>
void saveMatrixMarket(
    const container::DenseMatrix<_Scalar, _trans> &matrix,
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
  fout << matrix.dim0() << " " << matrix.dim1() << std::endl;

  // Write values
  for ( auto value : matrix ) {
    fout << value << std::endl;
  }

  // Close file
  fout.close();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  io_module
/// Save a dense vector set into a matrix market file.
///
/// @todo  Write banner
///
template <class _Derived>
void saveMatrixMarket(
    const VectorCollectionWrapper<_Derived> &set,
    const char *file
) noexcept {
  using VectorType = VectorT<_Derived>;
  using ScalarType = ScalarT<VectorType>;

  static_assert(std::is_base_of<DenseVector<ScalarType>, VectorType>::value, "'_Derived' is not a dense vector!");

  // Open file
  std::ofstream fout(file);
  mcnla_assert_false(fout.fail());

  // Set format
  fout << std::scientific << std::setprecision(16);

  // Write banner
  fout << "%%%%MatrixMarket matrix array real general" << std::endl;

  // Write size
  fout << set.dim0() << " " << set.nvec() << std::endl;

  // Write values
  for ( auto i = 0; i < set.nvec(); ++i ) {
    auto vector = set(i);
    for ( auto value : vector ) {
      fout << value << std::endl;
    }
  }

  // Close file
  fout.close();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  io_module
/// Save a dense vector set into a matrix market file.
///
/// @todo  Write banner
///
template <class _Derived>
void saveMatrixMarket(
    const MatrixCollectionWrapper<_Derived> &set,
    const char *file
) noexcept {
  using MatrixType = MatrixT<_Derived>;
  using ScalarType = ScalarT<MatrixType>;
  constexpr Trans trans = MatrixType::trans;

  static_assert(std::is_base_of<DenseMatrix<ScalarType, trans>, MatrixType>::value, "'_Derived' is not a dense matrix!");

  // Open file
  std::ofstream fout(file);
  mcnla_assert_false(fout.fail());

  // Set format
  fout << std::scientific << std::setprecision(16);

  // Write banner
  fout << "%%%%MatrixMarket cube array real general" << std::endl;

  // Write size
  fout << set.dim0() << " " << set.dim1() << " " << set.nmat() << std::endl;

  // Write values
  for ( auto i = 0; i < set.nmat(); ++i ) {
    auto matrix = set(i);
    for ( auto value : matrix ) {
      fout << value;
    }
  }

  // Close file
  fout.close();
}

}  // namespace container

}  // namespace mcnla

#endif  // MCNLA_CORE_IO_SAVE_MATRIX_MARKET_HPP_
