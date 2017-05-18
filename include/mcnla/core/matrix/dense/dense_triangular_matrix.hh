////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/dense/dense_triangular_matrix.hh
/// @brief   The definition of dense triangular matrix class.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_DENSE_DENSE_TRIANGULAR_MATRIX_HH_
#define MCNLA_CORE_MATRIX_DENSE_DENSE_TRIANGULAR_MATRIX_HH_

#include <mcnla/core/matrix/dense/def.hpp>
#include <mcnla/core/matrix/base/dense_matrix_wrapper.hpp>
#include <mcnla/core/matrix/base/iterable_wrapper.hpp>
#include <mcnla/core/matrix/dense/dense_triangular_matrix_base.hpp>
#include <mcnla/core/matrix/dense/dense_vector.hpp>
#include <mcnla/core/matrix/dense/dense_matrix.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The traits namespace.
//
namespace traits {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense triangular matrix traits.
///
template <typename _Val, Trans _trans, Uplo _uplo>
struct Traits<matrix::TrMatI<CoreTag, DenseTag, _Val, _trans, _uplo>> {

  static constexpr Trans trans = _trans;
  static constexpr Uplo uplo = _uplo;

  using ValType     = _Val;

  using RealType    = matrix::TrMatI<CoreTag, DenseTag, RealValT<_Val>, _trans, _uplo>;
  using ComplexType = matrix::TrMatI<CoreTag, DenseTag, ComplexValT<_Val>, _trans, _uplo>;

  using VectorType  = matrix::GeVecI<CoreTag, DenseTag, _Val>;
  using MatrixType  = matrix::TrMatI<CoreTag, DenseTag, _Val, _trans, _uplo>;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense triangular matrix instantiation type traits.
///
template <typename _Type>
struct IsDenseTriangularMatrix : std::false_type {};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc IsDenseTriangularMatrix
///
template <typename _Val, Trans _trans, Uplo _uplo>
struct IsDenseTriangularMatrix<matrix::TrMatI<CoreTag, DenseTag, _Val, _trans, _uplo>> : std::true_type {};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense triangular matrix assert.
///
#define assertDenseTriangularMatrix( Type ) \
    static_assert(traits::IsDenseTriangularMatrix<Type>::value, "'"#Type"' is not a dense triangular matrix!")

}  // namespace traits

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  matrix_dense_module
/// The dense triangular matrix class.
///
/// @tparam  _Val    The value type.
/// @tparam  _trans  The transpose storage layout.
/// @tparam  _uplo   The triangular storage layout.
///
template <typename _Val, Trans _trans, Uplo _uplo>
class TrMatI<CoreTag, DenseTag, _Val, _trans, _uplo>
  : public DenseTriangularMatrixBase<CoreTag, _Val, _trans, _uplo>,
    public DenseMatrixWrapper<TrMatI<CoreTag, DenseTag, _Val, _trans, _uplo>> {

  friend DenseMatrixWrapper<TrMatI<CoreTag, DenseTag, _Val, _trans, _uplo>>;

 private:

  using BaseType = DenseTriangularMatrixBase<CoreTag, _Val, _trans, _uplo>;

 public:

  using BaseType::DenseTriangularMatrixBase;

};

/// @ingroup  matrix_dense_module
template <typename _Val, Trans _trans = Trans::NORMAL, Uplo _uplo = Uplo::UPPER ^ _trans>
using DenseTriangularMatrix = TrMatI<CoreTag, DenseTag, _Val, _trans, _uplo>;

/// @ingroup  matrix_dense_module
template <typename _Val, Uplo _uplo = Uplo::UPPER>
using DenseTriangularMatrixColMajor = TrMatI<CoreTag, DenseTag, _Val, Trans::NORMAL, _uplo>;

/// @ingroup  matrix_dense_module
template <typename _Val, Uplo _uplo = Uplo::LOWER>
using DenseTriangularMatrixRowMajor = TrMatI<CoreTag, DenseTag, _Val, Trans::TRANS, _uplo>;

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_DENSE_DENSE_TRIANGULAR_MATRIX_HH_
