////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla.hpp
/// @brief   The MCNLA header.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_HPP_
#define MCNLA_HPP_

#include <mcnla/def.hpp>
#include <mcnla/core.hpp>
#include <mcnla/isvd.hpp>

#ifdef MCNLA_USE_GPU
  #include <mcnla/core_gpu.hpp>
  #include <mcnla/isvd_gpu.hpp>
#endif  // MCNLA_USE_GPU

#ifdef MCNLA_ALIAS
  #error MCNLA_ALIAS should not be defined!
#endif  // MCNLA_ALIAS

#ifdef MCNLA_ALIAS0
  #error MCNLA_ALIAS0 should not be defined!
#endif  // MCNLA_ALIAS0

#ifdef MCNLA_ALIAS1
  #error MCNLA_ALIAS1 should not be defined!
#endif  // MCNLA_ALIAS1

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @defgroup  core_module  Core Module
/// @brief     The Core Module
///

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @defgroup  core_gpu_module  Core Module (GPU)
/// @brief     The Core Module (GPU Support)
///

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @defgroup  isvd_module  iSVD Module
/// @brief     The iSVD Module
///

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @defgroup  isvd_gpu_module  iSVD Module (GPU)
/// @brief     The iSVD Module (GPU Support)
///

#endif  // MCNLA_HPP_
