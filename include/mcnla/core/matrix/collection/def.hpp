////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/collection/def.hpp
/// @brief   The container collection definitions.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_COLLECTION_DEF_HPP_
#define MCNLA_CORE_MATRIX_COLLECTION_DEF_HPP_

#include <mcnla/core/matrix/def.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace
//
namespace matrix {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The column-block tag.
///
struct ColBlockTag {};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The row-block tag.
///
struct RowBlockTag {};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The vector collection specialization.
///
/// @tparam  _Tag      The collection tag.
/// @tparam  _Core     The core tag.
/// @tparam  _Storage  The storage tag.
/// @tparam  _Val      The value type.
///
/// @see  Array, ArrayGpu
///
template <class _Tag, class _Core, class _Storage, typename _Val> class GeVecCollS;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The matrix collection specialization.
///
/// @tparam  _Tag      The collection tag.
/// @tparam  _Core     The core tag.
/// @tparam  _Storage  The storage tag.
/// @tparam  _Val      The value type.
/// @tparam  _trans    The transpose storage layout.
///
/// @see  Array, ArrayGpu
///
template <class _Tag, class _Core, class _Storage, typename _Val, Trans _trans> class GeMatCollS;

}  // namespace matrix

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The traits namespace.
//
namespace traits {

#define MCNLA_MATRIX_GEVECCOLL( ... ) matrix::GeVecCollS<_Tag, _Core, _Storage, __VA_ARGS__>
#define MCNLA_MATRIX_GEMATCOLL( ... ) matrix::GeMatCollS<_Tag, _Core, _Storage, __VA_ARGS__>

// Value traits

template <class _Tag, class _Core, class _Storage, typename _Val>
MCNLA_TRAITS_DEF(Val, MCNLA_MATRIX_GEVECCOLL(_Val), _Val)

template <class _Tag, class _Core, class _Storage, typename _Val, Trans _trans>
MCNLA_TRAITS_DEF(Val, MCNLA_MATRIX_GEMATCOLL(_Val, _trans), _Val)

// Vector/matrix traits

template <class _Tag, class _Core, class _Storage, typename _Val>
MCNLA_TRAITS_DEF(Matrix, MCNLA_MATRIX_GEVECCOLL(_Val), MCNLA_(matrix::GeVecS<_Core, _Storage, _Val>))

template <class _Tag, class _Core, class _Storage, typename _Val, Trans _trans>
MCNLA_TRAITS_DEF(Matrix, MCNLA_MATRIX_GEMATCOLL(_Val, _trans), MCNLA_(matrix::GeMatS<_Core, _Storage, _Val, _trans>))

#undef MCNLA_MATRIX_GEVECCOLL
#undef MCNLA_MATRIX_GEMATCOLL

}  // namespace traits

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_COLLECTION_DEF_HPP_
