////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/utility/memory.hpp
/// @brief   The memory utilities.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_UTILITY_MEMORY_HPP_
#define MCNLA_CORE_UTILITY_MEMORY_HPP_

#include <mcnla/core/def.hpp>

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
/// @brief  The allocator.
/// Allocates an array of @a _Type with size @a num.
///
/// @tparam  _Type  The type of the array.
/// @param   num    The number of objects.
///
/// @return         The pointer to the array.
///
template <typename _Type>
inline _Type* malloc( const index_t num ) noexcept {
  return static_cast<_Type*>(std::malloc(num * sizeof(_Type*)));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  utility_module
/// @brief  The callocator.
/// Allocates an array of @a _Type with size @a num and initializes with zero.
///
/// @tparam  _Type  The type of the array.
/// @param   num    The number of objects.
///
/// @return         The pointer to the array.
///
template <typename _Type>
inline _Type* calloc( const index_t num ) noexcept {
  return static_cast<_Type*>(std::calloc(num, sizeof(_Type*)));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  utility_module
/// @brief  The reallocator.
/// Reallocates an array of @a _Type with size @a num.
///
/// @tparam  _Type  The type of the array.
/// @param   num    The number of objects.
/// @param   ptr    The pointer to the array.
///
/// @return         The pointer to the array.
///
template <typename _Type>
inline _Type* realloc( _Type *&ptr, const index_t num ) noexcept {
  return static_cast<_Type*>(std::realloc(ptr, num * sizeof(_Type*)));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  utility_module
/// @brief  The deallocator.
/// Deallocates @a ptr and set it to `nullptr`!
///
/// @tparam  _Type  The type of the array.
/// @param   ptr    The pointer to the array.
///
template <typename _Type>
inline void free( _Type *&ptr ) noexcept {
  std::free(ptr);
  ptr = nullptr;
}

}  // namespace utility

}  // namespace mcnla

#endif  // MCNLA_CORE_UTILITY_MEMORY_HPP_
