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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The traits namespace.
//
namespace traits {

#define MCNLA_MATRIX_GEVEC( ... ) matrix::GeVecS<_Core, _Storage, __VA_ARGS__>
#define MCNLA_MATRIX_GEMAT( ... ) matrix::GeMatS<_Core, _Storage, __VA_ARGS__>
#define MCNLA_MATRIX_SYMAT( ... ) matrix::SyMatS<_Core, _Storage, __VA_ARGS__>
#define MCNLA_MATRIX_TRMAT( ... ) matrix::TrMatS<_Core, _Storage, __VA_ARGS__>
#define MCNLA_MATRIX_DIMAT( ... ) matrix::DiMatS<_Core, _Storage, __VA_ARGS__>

// Real traits

template <class _Core, class _Storage, typename _Val>
MCNLA_TRAITS_DEF(Real, MCNLA_MATRIX_GEVEC(_Val), MCNLA_MATRIX_GEVEC(RealValT<_Val>))

template <class _Core, class _Storage, typename _Val, Trans _trans>
MCNLA_TRAITS_DEF(Real, MCNLA_MATRIX_GEMAT(_Val, _trans), MCNLA_MATRIX_GEMAT(RealValT<_Val>, _trans))

template <class _Core, class _Storage, typename _Val, Trans _trans, Uplo _uplo>
MCNLA_TRAITS_DEF(Real, MCNLA_MATRIX_SYMAT(_Val, _trans, _uplo), MCNLA_MATRIX_SYMAT(RealValT<_Val>, _trans, _uplo))

template <class _Core, class _Storage, typename _Val, Trans _trans, Uplo _uplo>
MCNLA_TRAITS_DEF(Real, MCNLA_MATRIX_TRMAT(_Val, _trans, _uplo), MCNLA_MATRIX_TRMAT(RealValT<_Val>, _trans, _uplo))

template <class _Core, class _Storage, typename _Val>
MCNLA_TRAITS_DEF(Real, MCNLA_MATRIX_DIMAT(_Val), MCNLA_MATRIX_DIMAT(RealValT<_Val>))

// Complex traits

template <class _Core, class _Storage, typename _Val>
MCNLA_TRAITS_DEF(Complex, MCNLA_MATRIX_GEVEC(_Val), MCNLA_MATRIX_GEVEC(ComplexValT<_Val>))

template <class _Core, class _Storage, typename _Val, Trans _trans>
MCNLA_TRAITS_DEF(Complex, MCNLA_MATRIX_GEMAT(_Val, _trans), MCNLA_MATRIX_GEMAT(ComplexValT<_Val>, _trans))

template <class _Core, class _Storage, typename _Val, Trans _trans, Uplo _uplo>
MCNLA_TRAITS_DEF(Complex, MCNLA_MATRIX_SYMAT(_Val, _trans, _uplo), MCNLA_MATRIX_SYMAT(ComplexValT<_Val>, _trans, _uplo))

template <class _Core, class _Storage, typename _Val, Trans _trans, Uplo _uplo>
MCNLA_TRAITS_DEF(Complex, MCNLA_MATRIX_TRMAT(_Val, _trans, _uplo), MCNLA_MATRIX_TRMAT(ComplexValT<_Val>, _trans, _uplo))

template <class _Core, class _Storage, typename _Val>
MCNLA_TRAITS_DEF(Complex, MCNLA_MATRIX_DIMAT(_Val), MCNLA_MATRIX_DIMAT(ComplexValT<_Val>))

// Value traits

template <class _Core, class _Storage, typename _Val>
MCNLA_TRAITS_DEF(Val, MCNLA_MATRIX_GEVEC(_Val), _Val)

template <class _Core, class _Storage, typename _Val, Trans _trans>
MCNLA_TRAITS_DEF(Val, MCNLA_MATRIX_GEMAT(_Val, _trans), _Val)

template <class _Core, class _Storage, typename _Val, Trans _trans, Uplo _uplo>
MCNLA_TRAITS_DEF(Val, MCNLA_MATRIX_SYMAT(_Val, _trans, _uplo), _Val)

template <class _Core, class _Storage, typename _Val, Trans _trans, Uplo _uplo>
MCNLA_TRAITS_DEF(Val, MCNLA_MATRIX_TRMAT(_Val, _trans, _uplo), _Val)

template <class _Core, class _Storage, typename _Val>
MCNLA_TRAITS_DEF(Val, MCNLA_MATRIX_DIMAT(_Val), _Val)

// Vector traits

template <class _Core, class _Storage, typename _Val, Trans _trans>
MCNLA_TRAITS_DEF(Vector, MCNLA_MATRIX_GEMAT(_Val, _trans), MCNLA_MATRIX_GEVEC(_Val))

template <class _Core, class _Storage, typename _Val, Trans _trans, Uplo _uplo>
MCNLA_TRAITS_DEF(Vector, MCNLA_MATRIX_SYMAT(_Val, _trans, _uplo), MCNLA_MATRIX_GEVEC(_Val))

template <class _Core, class _Storage, typename _Val, Trans _trans, Uplo _uplo>
MCNLA_TRAITS_DEF(Vector, MCNLA_MATRIX_TRMAT(_Val, _trans, _uplo), MCNLA_MATRIX_GEVEC(_Val))

template <class _Core, class _Storage, typename _Val>
MCNLA_TRAITS_DEF(Vector, MCNLA_MATRIX_DIMAT(_Val), MCNLA_MATRIX_GEVEC(_Val))

#undef MCNLA_MATRIX_GEVEC
#undef MCNLA_MATRIX_GEMAT
#undef MCNLA_MATRIX_SYMAT
#undef MCNLA_MATRIX_TRMAT
#undef MCNLA_MATRIX_DIMAT

}  // namespace traits

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_DEF_HPP_
