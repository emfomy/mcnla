////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core_gpu/matrix/kit/def.hpp
/// @brief   The GPU container kit definitions.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_GPU_MATRIX_KIT_DEF_HPP_
#define MCNLA_CORE_GPU_MATRIX_KIT_DEF_HPP_

#include <mcnla/core_gpu/matrix/def.hpp>
#include <mcnla/core/matrix/kit/def.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Val> using ArrayGpu = ArrI<GpuTag, _Val>;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_GPU_MATRIX_KIT_DEF_HPP_
