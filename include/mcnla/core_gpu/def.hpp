////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core_gpu/def.hpp
/// @brief   The core definitions with GPU support.
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  gpu_core_module
/// Initializes the environment (including MPI and MAGMA).
///
static inline void gpuInit( int &argc, char **&argv ) {
  MPI_Init(&argc, &argv);
  magma_init();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  gpu_core_module
/// Finalizes the environment (including MPI and MAGMA).
///
static inline void gpuFinalize() {
  magma_finalize();
  MPI_Finalize();
}

}  // namespace mcnla

#endif  // MCNLA_CORE_GPU_DEF_HPP_
