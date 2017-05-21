////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/dense/dense_diagonal_matrix.hh
/// @brief   The definition of definition of dense diagonal matrix class.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_DENSE_DENSE_DIAGONAL_MATRIX_HH_
#define MCNLA_CORE_MATRIX_DENSE_DENSE_DIAGONAL_MATRIX_HH_

#include <mcnla/core/matrix/dense/def.hpp>
#include <mcnla/core/matrix/base/dense_matrix_wrapper.hpp>
#include <mcnla/core/matrix/dense/dense_diagonal_matrix_base.hpp>
#include <mcnla/core/matrix/dense/dense_vector.hpp>
#include <mcnla/core/utility/traits.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The traits namespace.
//
namespace traits {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense diagonal matrix traits.
///
template <typename _Val>
struct Traits<matrix::DiMatI<CpuTag, DenseTag, _Val>> {

  using ValType     = _Val;

  using RealType    = matrix::DiMatI<CpuTag, DenseTag, RealValT<_Val>>;
  using ComplexType = matrix::DiMatI<CpuTag, DenseTag, ComplexValT<_Val>>;

  using VectorType  = matrix::GeVecI<CpuTag, DenseTag, _Val>;
  using MatrixType  = matrix::DiMatI<CpuTag, DenseTag, _Val>;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense diagonal matrix instantiation type traits.
///
template <typename _Type>
struct IsDenseDiagonalMatrix : std::false_type {};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc IsDenseDiagonalMatrix
///
template <typename _Val>
struct IsDenseDiagonalMatrix<matrix::DiMatI<CpuTag, DenseTag, _Val>> : std::true_type {};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense diagonal matrix assert.
///
#define assertDenseDiagonalMatrix( Type ) \
    static_assert(traits::IsDenseDiagonalMatrix<Type>::value, "'"#Type"' is not a dense diagonal matrix!")

}  // namespace traits

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  matrix_dense_module
/// The dense diagonal matrix class.
///
/// @tparam  _Val  The value type.
///
template <typename _Val>
class DiMatI<CpuTag, DenseTag, _Val>
  : public DenseDiagonalMatrixBase<CpuTag, _Val>,
    public DenseMatrixWrapper<DiMatI<CpuTag, DenseTag, _Val>> {

  friend DenseMatrixWrapper<DiMatI<CpuTag, DenseTag, _Val>>;

 private:

  using BaseType = DenseDiagonalMatrixBase<CpuTag, _Val>;

 public:

  using BaseType::DenseDiagonalMatrixBase;

};

/// @ingroup  matrix_dense_module
template <typename _Val>
using DenseDiagonalMatrix = DiMatI<CpuTag, DenseTag, _Val>;

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_DENSE_DENSE_DIAGONAL_MATRIX_HH_
