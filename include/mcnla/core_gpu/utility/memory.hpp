////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core_gpu/utility/memory.hpp
/// @brief   The GPU memory utilities.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_GPU_UTILITY_MEMORY_HPP_
#define MCNLA_CORE_GPU_UTILITY_MEMORY_HPP_

#include <mcnla/core_gpu/utility/def.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The utility namespace.
//
namespace utility {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  utility_gpu_module
/// @copydoc  malloc
///
/// @attention  The pointer should be GPU pointer.
///
template <typename _Type>
inline _Type* gpuMalloc( const index_t num ) noexcept {
  void *ptr;
  magma_malloc(&ptr, num * sizeof(_Type));
  return static_cast<_Type*>(ptr);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  utility_gpu_module
/// @copydoc  free
///
/// @attention  The pointer should be GPU pointer.
///
template <typename _Type>
inline void gpuFree( _Type *&ptr ) noexcept {
  magma_free(ptr);
  ptr = nullptr;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  utility_gpu_module
/// @copydoc  memset0
///
/// @attention  The pointer should be GPU pointer.
///
template <typename _Type>
inline void gpuMemset0( _Type *ptr, const index_t num ) noexcept {
  mcnla_assert_pass(cudaMemset(ptr, 0, num * sizeof(_Type)));
}

}  // namespace utility

}  // namespace mcnla

#endif  // MCNLA_CORE_GPU_UTILITY_MEMORY_HPP_
