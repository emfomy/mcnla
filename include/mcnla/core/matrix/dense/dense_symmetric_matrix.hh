////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/dense/dense_symmetric_matrix.hh
/// @brief   The definition of dense symmetric matrix class.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_DENSE_DENSE_SYMMETRIC_MATRIX_HH_
#define MCNLA_CORE_MATRIX_DENSE_DENSE_SYMMETRIC_MATRIX_HH_

#include <mcnla/core/matrix/dense/def.hpp>
#include <mcnla/core/matrix/base/dense_matrix_wrapper.hpp>
#include <mcnla/core/matrix/base/iterable_wrapper.hpp>
#include <mcnla/core/matrix/dense/dense_symmetric_matrix_base.hpp>
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
/// The dense symmetric matrix traits.
///
template <typename _Val, Trans _trans, Uplo _uplo>
struct Traits<matrix::SyMatI<CoreTag, DenseTag, _Val, _trans, _uplo>> {

  static constexpr Trans trans = _trans;
  static constexpr Uplo uplo = _uplo;

  using ValType     = _Val;

  using RealType    = matrix::SyMatI<CoreTag, DenseTag, RealValT<_Val>, _trans, _uplo>;
  using ComplexType = matrix::SyMatI<CoreTag, DenseTag, ComplexValT<_Val>, _trans, _uplo>;

  using VectorType  = matrix::GeVecI<CoreTag, DenseTag, _Val>;
  using MatrixType  = matrix::SyMatI<CoreTag, DenseTag, _Val, _trans, _uplo>;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense symmetric matrix instantiation type traits.
///
template <typename _Type>
struct IsDenseSymmetricMatrix : std::false_type {};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc IsDenseSymmetricMatrix
///
template <typename _Val, Trans _trans, Uplo _uplo>
struct IsDenseSymmetricMatrix<matrix::SyMatI<CoreTag, DenseTag, _Val, _trans, _uplo>> : std::true_type {};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense symmetric matrix assert.
///
#define assertDenseSymmetricMatrix( Type ) \
    static_assert(traits::IsDenseSymmetricMatrix<Type>::value, "'"#Type"' is not a dense symmetric matrix!")

}  // namespace traits

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  matrix_dense_module
/// The dense symmetric matrix class.
///
/// @tparam  _Val    The value type.
/// @tparam  _trans  The transpose storage layout.
/// @tparam  _uplo   The triangular storage layout.
///
template <typename _Val, Trans _trans, Uplo _uplo>
class SyMatI<CoreTag, DenseTag, _Val, _trans, _uplo>
  : public DenseSymmetricMatrixBase<CoreTag, _Val, _trans, _uplo>,
    public DenseMatrixWrapper<SyMatI<CoreTag, DenseTag, _Val, _trans, _uplo>> {

  friend DenseMatrixWrapper<SyMatI<CoreTag, DenseTag, _Val, _trans, _uplo>>;

 private:

  using BaseType = DenseSymmetricMatrixBase<CoreTag, _Val, _trans, _uplo>;

 public:

  using BaseType::DenseSymmetricMatrixBase;

};

/// @ingroup  matrix_dense_module
template <typename _Val, Trans _trans = Trans::NORMAL, Uplo _uplo = Uplo::UPPER ^ _trans>
using DenseSymmetricMatrix = SyMatI<CoreTag, DenseTag, _Val, _trans, _uplo>;

/// @ingroup  matrix_dense_module
template <typename _Val, Uplo _uplo = Uplo::UPPER>
using DenseSymmetricMatrixColMajor = SyMatI<CoreTag, DenseTag, _Val, Trans::NORMAL, _uplo>;

/// @ingroup  matrix_dense_module
template <typename _Val, Uplo _uplo = Uplo::LOWER>
using DenseSymmetricMatrixRowMajor = SyMatI<CoreTag, DenseTag, _Val, Trans::TRANS, _uplo>;

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_DENSE_DENSE_SYMMETRIC_MATRIX_HH_
