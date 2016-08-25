////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/utility/memory.hpp
/// @brief   The memory utilities
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_UTILITY_MEMORY_HPP_
#define ISVD_UTILITY_MEMORY_HPP_

#include <isvd/config.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  The allocator.
/// Allocates an array of @a _Type with size @a num.
///
/// @tparam  _Type  The type of the array.
/// @param   num    The number of objects.
///
/// @return         The pointer to the array.
///
template <typename _Type>
_Type* Malloc( const index_t num ) noexcept {
  return static_cast<_Type*>(malloc(num * sizeof(_Type*)));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  The callocator.
/// Allocates an array of @a _Type with size @a num and initializes with zero.
///
/// @tparam  _Type  The type of the array.
/// @param   num    The number of objects.
///
/// @return         The pointer to the array.
///
template <typename _Type>
_Type* Calloc( const index_t num ) noexcept {
  return static_cast<_Type*>(calloc(num, sizeof(_Type*)));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
_Type* Realloc( _Type *&ptr, const index_t num ) noexcept {
  return static_cast<_Type*>(realloc(ptr, num * sizeof(_Type*)));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  The deallocator.
/// Deallocates @a ptr and set it to @c nullptr.
///
/// @tparam  _Type  The type of the array.
/// @param   ptr    The pointer to the array.
///
template <typename _Type>
void Free( _Type *&ptr ) noexcept {
  free(ptr);
  ptr = nullptr;
}

}  // namespace isvd

#endif  // ISVD_UTILITY_MEMORY_HPP_
