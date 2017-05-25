////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/utility/memory.hpp
/// @brief   The memory utilities.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_UTILITY_MEMORY_HPP_
#define MCNLA_CORE_UTILITY_MEMORY_HPP_

#include <mcnla/core/utility/def.hpp>
#include <cstdlib>
#include <cstring>

#ifdef MCNLA_USE_MKL
  #include <mkl.h>
#endif  // MCNLA_USE_MKL

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The utility namespace.
//
namespace utility {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  utility_module
/// @brief  Allocates an array of @a _Type with size @a num.
///
/// @tparam  _Type  The type of the array.
/// @param   num    The number of objects.
///
/// @return         The pointer to the array.
///
template <typename _Type>
inline _Type* malloc( const index_t num ) noexcept {
  return static_cast<_Type*>(
#ifdef MCNLA_USE_MKL
      mkl_malloc(num * sizeof(_Type), 64)
#else  // MCNLA_USE_MKL
      std::malloc(num * sizeof(_Type))
#endif  // MCNLA_USE_MKL
  );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  utility_module
/// @brief  Allocates an array of @a _Type with size @a num and initializes with zero.
///
/// @tparam  _Type  The type of the array.
/// @param   num    The number of objects.
///
/// @return         The pointer to the array.
///
template <typename _Type>
inline _Type* calloc( const index_t num ) noexcept {
  return static_cast<_Type*>(
#ifdef MCNLA_USE_MKL
      mkl_calloc(num, sizeof(_Type), 64)
#else  // MCNLA_USE_MKL
      std::calloc(num, sizeof(_Type))
#endif  // MCNLA_USE_MKL
  );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  utility_module
/// @brief  Reallocates an array of @a _Type with size @a num.
///
/// @tparam  _Type  The type of the array.
/// @param   num    The number of objects.
/// @param   ptr    The pointer to the array.
///
/// @return         The pointer to the array.
///
template <typename _Type>
inline _Type* realloc( _Type *&ptr, const index_t num ) noexcept {
  return static_cast<_Type*>(
#ifdef MCNLA_USE_MKL
      mkl_realloc(ptr, num * sizeof(_Type))
#else  // MCNLA_USE_MKL
      std::realloc(ptr, num * sizeof(_Type))
#endif  // MCNLA_USE_MKL
  );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  utility_module
/// @brief  Deallocates @a ptr and set it to `nullptr`.
///
/// @tparam  _Type  The type of the array.
/// @param   ptr    The pointer to the array.
///
template <typename _Type>
inline void free( _Type *&ptr ) noexcept {
#ifdef MCNLA_USE_MKL
  mkl_free(ptr);
#else  // MCNLA_USE_MKL
  std::free(ptr);
#endif  // MCNLA_USE_MKL
  ptr = nullptr;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  utility_module
/// @brief  Copies the array.
///
/// @tparam  _Type  The type of the array.
/// @param   dst  The destination pointer to the array.
/// @param   src  The source pointer to the array.
/// @param   num  The number of objects.
///
template <typename _Type>
inline void memcpy( _Type *dst, const _Type *src, const index_t num ) noexcept {
  std::memcpy(dst, src, num * sizeof(_Type));
}

}  // namespace utility

}  // namespace mcnla

#endif  // MCNLA_CORE_UTILITY_MEMORY_HPP_
