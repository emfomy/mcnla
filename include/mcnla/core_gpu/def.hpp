////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core_gpu/def.hpp
/// @brief   The GPU core definitions.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_GPU_DEF_HPP_
#define MCNLA_CORE_GPU_DEF_HPP_

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
size_t kGpuMemorySize = 16000000000;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The GPU Core tag.
///
struct GpuTag {};

}  // namespace mcnla

#endif  // MCNLA_CORE_GPU_DEF_HPP_
