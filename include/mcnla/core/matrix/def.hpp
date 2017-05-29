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

}  // namespace matrix

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The traits namespace.
//
namespace traits {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  matrix_module
/// The collection templates traits.
///
//@{
template <class _Core, typename _Val> class ArrTraits;
template <class _Core, class _Storage, typename _Val> class GeVecTraits;
template <class _Core, class _Storage, typename _Val, Trans _trans> class GeMatTraits;
template <class _Core, class _Storage, typename _Val, Trans _trans, Uplo _uplo> class SyMatTraits;
template <class _Core, class _Storage, typename _Val, Trans _trans, Uplo _uplo> class TrMatTraits;
template <class _Core, class _Storage, typename _Val> class DiMatTraits;
//@}

#define MCNLA_ARR_TRAITS_DEF( _Core, _T ) \
  template <typename _Val> \
  struct ArrTraits<_Core, _Val> { using Type = _T<_Val>; };

#define MCNLA_GEVEC_TRAITS_DEF( _Core, _Storage, _T ) \
  template <class _Storage, typename _Val> \
  struct GeVecTraits<_Core, _Storage, _Val> { using Type = _T<_Val>; };

#define MCNLA_GEMAT_TRAITS_DEF( _Core, _Storage, _T ) \
  template <class _Storage, typename _Val, Trans _trans> \
  struct GeMatTraits<_Core, _Storage, _Val, Trans _trans> { using Type = _T<_Val, _trans>; };

#define MCNLA_SYMAT_TRAITS_DEF( _Core, _Storage, _T ) \
  template <class _Storage, typename _Val, Trans _trans, Uplo _uplo> \
  struct SyMatTraits<_Core, _Storage, _Val, Trans _trans, Uplo _uplo> { using Type = _T<_Val, _trans, _uplo>; };

#define MCNLA_TRMAT_TRAITS_DEF( _Core, _Storage, _T ) \
  template <class _Storage, typename _Val, Trans _trans, Uplo _uplo> \
  struct TrMatTraits<_Core, _Storage, _Val, Trans _trans, Uplo _uplo> { using Type = _T<_Val, _trans, _uplo>; };

#define MCNLA_DIMAT_TRAITS_DEF( _Core, _Storage, _T ) \
  template <class _Storage, typename _Val> \
  struct TrMatTraits<_Core, _Storage, _Val> { using Type = _T<_Val>; };

}  // namespace traits

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

/// @ingroup  matrix_module
template <class _Core, typename _Val>
using ArrT = typename traits::ArrTraits<_Core, _Val>::Type;

/// @ingroup  matrix_module
template <class _Core, class _Storage, typename _Val>
using GeVecT = typename traits::GeVecTraits<_Core, _Storage, _Val>::Type;

/// @ingroup  matrix_module
template <class _Core, class _Storage, typename _Val, Trans _trans>
using GeMatT = typename traits::GeMatTraits<_Core, _Storage, _Val, _trans>::Type;

/// @ingroup  matrix_module
template <class _Core, class _Storage, typename _Val, Trans _trans, Uplo _uplo>
using SyMatT = typename traits::SyMatTraits<_Core, _Storage, _Val, _trans, _uplo>::Type;

/// @ingroup  matrix_module
template <class _Core, class _Storage, typename _Val, Trans _trans, Uplo _uplo>
using TrMatT = typename traits::TrMatTraits<_Core, _Storage, _Val, _trans, _uplo>::Type;

/// @ingroup  matrix_module
template <class _Core, class _Storage, typename _Val>
using DiMatT = typename traits::DiMatTraits<_Core, _Storage, _Val>::Type;

}  // namespace matrix

// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// //  The traits namespace.
// //
// namespace traits {

// #define MCNLA_MATRIX_GEVEC( ... ) matrix::GeVecT<_Core, _Storage, __VA_ARGS__>
// #define MCNLA_MATRIX_GEMAT( ... ) matrix::GeMatT<_Core, _Storage, __VA_ARGS__>
// #define MCNLA_MATRIX_SYMAT( ... ) matrix::SyMatT<_Core, _Storage, __VA_ARGS__>
// #define MCNLA_MATRIX_TRMAT( ... ) matrix::TrMatT<_Core, _Storage, __VA_ARGS__>
// #define MCNLA_MATRIX_DIMAT( ... ) matrix::DiMatT<_Core, _Storage, __VA_ARGS__>

// // Real traits

// template <class _Core, class _Storage, typename _Val>
// MCNLA_TRAITS_DEF(Real, MCNLA_MATRIX_GEVEC(_Val), MCNLA_MATRIX_GEVEC(RealValT<_Val>))

// template <class _Core, class _Storage, typename _Val, Trans _trans>
// MCNLA_TRAITS_DEF(Real, MCNLA_MATRIX_GEMAT(_Val, _trans), MCNLA_MATRIX_GEMAT(RealValT<_Val>, _trans))

// template <class _Core, class _Storage, typename _Val, Trans _trans, Uplo _uplo>
// MCNLA_TRAITS_DEF(Real, MCNLA_MATRIX_SYMAT(_Val, _trans, _uplo), MCNLA_MATRIX_SYMAT(RealValT<_Val>, _trans, _uplo))

// template <class _Core, class _Storage, typename _Val, Trans _trans, Uplo _uplo>
// MCNLA_TRAITS_DEF(Real, MCNLA_MATRIX_TRMAT(_Val, _trans, _uplo), MCNLA_MATRIX_TRMAT(RealValT<_Val>, _trans, _uplo))

// template <class _Core, class _Storage, typename _Val>
// MCNLA_TRAITS_DEF(Real, MCNLA_MATRIX_DIMAT(_Val), MCNLA_MATRIX_DIMAT(RealValT<_Val>))

// // Complex traits

// template <class _Core, class _Storage, typename _Val>
// MCNLA_TRAITS_DEF(Complex, MCNLA_MATRIX_GEVEC(_Val), MCNLA_MATRIX_GEVEC(ComplexValT<_Val>))

// template <class _Core, class _Storage, typename _Val, Trans _trans>
// MCNLA_TRAITS_DEF(Complex, MCNLA_MATRIX_GEMAT(_Val, _trans), MCNLA_MATRIX_GEMAT(ComplexValT<_Val>, _trans))

// template <class _Core, class _Storage, typename _Val, Trans _trans, Uplo _uplo>
// MCNLA_TRAITS_DEF(Complex, MCNLA_MATRIX_SYMAT(_Val, _trans, _uplo), MCNLA_MATRIX_SYMAT(ComplexValT<_Val>, _trans, _uplo))

// template <class _Core, class _Storage, typename _Val, Trans _trans, Uplo _uplo>
// MCNLA_TRAITS_DEF(Complex, MCNLA_MATRIX_TRMAT(_Val, _trans, _uplo), MCNLA_MATRIX_TRMAT(ComplexValT<_Val>, _trans, _uplo))

// template <class _Core, class _Storage, typename _Val>
// MCNLA_TRAITS_DEF(Complex, MCNLA_MATRIX_DIMAT(_Val), MCNLA_MATRIX_DIMAT(ComplexValT<_Val>))

// // Value traits

// template <class _Core, class _Storage, typename _Val>
// MCNLA_TRAITS_DEF(Val, MCNLA_MATRIX_GEVEC(_Val), _Val)

// template <class _Core, class _Storage, typename _Val, Trans _trans>
// MCNLA_TRAITS_DEF(Val, MCNLA_MATRIX_GEMAT(_Val, _trans), _Val)

// template <class _Core, class _Storage, typename _Val, Trans _trans, Uplo _uplo>
// MCNLA_TRAITS_DEF(Val, MCNLA_MATRIX_SYMAT(_Val, _trans, _uplo), _Val)

// template <class _Core, class _Storage, typename _Val, Trans _trans, Uplo _uplo>
// MCNLA_TRAITS_DEF(Val, MCNLA_MATRIX_TRMAT(_Val, _trans, _uplo), _Val)

// template <class _Core, class _Storage, typename _Val>
// MCNLA_TRAITS_DEF(Val, MCNLA_MATRIX_DIMAT(_Val), _Val)

// // Vector traits

// template <class _Core, class _Storage, typename _Val, Trans _trans>
// MCNLA_TRAITS_DEF(Vector, MCNLA_MATRIX_GEMAT(_Val, _trans), MCNLA_MATRIX_GEVEC(_Val))

// template <class _Core, class _Storage, typename _Val, Trans _trans, Uplo _uplo>
// MCNLA_TRAITS_DEF(Vector, MCNLA_MATRIX_SYMAT(_Val, _trans, _uplo), MCNLA_MATRIX_GEVEC(_Val))

// template <class _Core, class _Storage, typename _Val, Trans _trans, Uplo _uplo>
// MCNLA_TRAITS_DEF(Vector, MCNLA_MATRIX_TRMAT(_Val, _trans, _uplo), MCNLA_MATRIX_GEVEC(_Val))

// template <class _Core, class _Storage, typename _Val>
// MCNLA_TRAITS_DEF(Vector, MCNLA_MATRIX_DIMAT(_Val), MCNLA_MATRIX_GEVEC(_Val))

// #undef MCNLA_MATRIX_GEVEC
// #undef MCNLA_MATRIX_GEMAT
// #undef MCNLA_MATRIX_SYMAT
// #undef MCNLA_MATRIX_TRMAT
// #undef MCNLA_MATRIX_DIMAT

// }  // namespace traits

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_DEF_HPP_
