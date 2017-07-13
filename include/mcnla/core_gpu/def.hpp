////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core_gpu/def.hpp
/// @brief   The GPU core definitions.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_GPU_DEF_HPP_
#define MCNLA_CORE_GPU_DEF_HPP_

#ifndef MCNLA_USE_GPU
  #error 'MCNLA_USE_GPU' should not be set!.
#endif

#include <mcnla/def.hpp>
#include <mcnla/core/def.hpp>
#include <magma.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace
//
namespace mcnla {

/// @ingroup  core_gpu_module
/// The GPU block size
static constexpr index_t kBlockSizeGpu = 64;

/// @ingroup  core_gpu_module
/// The memory size of GPU.
/// @todo  Determine GPU memory size dynamically.
static constexpr size_t kGpuMemorySize = 16000000000;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The GPU Core tag.
///
struct GpuTag {};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  core_gpu_module
/// Initializes the GPU environment.
///
static inline void gpuInit( const index_t device_id ) noexcept {
  int count;
  cudaGetDeviceCount(&count);
  magma_init();
  magma_setdevice(device_id % count);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  core_gpu_module
/// Finalizes the GPU environment
///
static inline void gpuFinalize() noexcept {
  magma_finalize();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  core_gpu_module
/// Print the GPU environment
///
static inline void gpuPrintEnvironment() noexcept {
  magma_print_environment();
}

}  // namespace mcnla

#endif  // MCNLA_CORE_GPU_DEF_HPP_
