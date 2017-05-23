////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/def.hpp
/// @brief   The container definitions.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_DEF_HPP_
#define MCNLA_CORE_MATRIX_DEF_HPP_

#include <mcnla/core/def.hpp>
#include <mcnla/core/utility/traits.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  matrix_module
/// The matrix namespace.
///
namespace matrix {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The matrix detail namespace.
///
namespace detail {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The value array specialization.
///
/// @tparam  _Core  The core tag.
/// @tparam  _Val   The value type.
///
/// @see  Array, ArrayGpu
///
template <class _Core, typename _Val>
class ArrS {
  static_assert(traits::FalseType<_Core>::value, "Error using non-specialized array!");
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The vector specialization.
///
/// @tparam  _Core     The core tag.
/// @tparam  _Storage  The storage tag.
/// @tparam  _Val      The value type.
///
/// @see  DenseVector, DenseVectorGpu, CooVector
///
template <class _Core, class _Storage, typename _Val>
class GeVecS {
  static_assert(traits::FalseType<_Core>::value, "Error using non-specialized vector!");
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The matrix specialization.
///
/// @tparam  _Core     The core tag.
/// @tparam  _Storage  The storage tag.
/// @tparam  _Val      The value type.
/// @tparam  _trans    The transpose storage layout.
///
/// @see  DenseMatrix, DenseMatrixGpu, CooMatrix
///
template <class _Core, class _Storage, typename _Val, Trans _trans>
class GeMatS {
  static_assert(traits::FalseType<_Core>::value, "Error using non-specialized matrix!");
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The symmetric matrix specialization.
///
/// @tparam  _Core     The core tag.
/// @tparam  _Storage  The storage tag.
/// @tparam  _Val      The value type.
/// @tparam  _trans    The transpose storage layout.
/// @tparam  _uplo     The triangular storage layout.
///
/// @see  DenseSymmetricMatrix, DenseSymmetricMatrixGpu
///
template <class _Core, class _Storage, typename _Val, Trans _trans, Uplo _uplo>
class SyMatS {
  static_assert(traits::FalseType<_Core>::value, "Error using non-specialized symmetric matrix!");
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The triangular matrix specialization.
///
/// @tparam  _Core     The core tag.
/// @tparam  _Storage  The storage tag.
/// @tparam  _Val      The value type.
/// @tparam  _trans    The transpose storage layout.
/// @tparam  _uplo     The triangular storage layout.
///
/// @see  DenseTriangularMatrix, DenseTriangularMatrixGpu
///
template <class _Core, class _Storage, typename _Val, Trans _trans, Uplo _uplo>
class TrMatS {
  static_assert(traits::FalseType<_Core>::value, "Error using non-specialized triangular matrix!");
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The diagonal matrix specialization.
///
/// @tparam  _Core     The core tag.
/// @tparam  _Storage  The storage tag.
/// @tparam  _Val      The value type.
///
/// @see  DenseDiagonalMatrix, DenseDiagonalMatrixGpu
///
template <class _Core, class _Storage, typename _Val>
class DiMatS {
  static_assert(traits::FalseType<_Core>::value, "Error using non-specialized diagonal matrix!");
};

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_DEF_HPP_
