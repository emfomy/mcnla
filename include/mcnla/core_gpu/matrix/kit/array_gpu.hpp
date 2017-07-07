////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core_gpu/matrix/kit/array_gpu.hpp
/// @brief   The GPU value array.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_GPU_MATRIX_KIT_ARRAY_GPU_HPP_
#define MCNLA_CORE_GPU_MATRIX_KIT_ARRAY_GPU_HPP_

#include <mcnla/core_gpu/matrix/kit/array_gpu.hh>
#include <mcnla/core_gpu/utility/memory.hpp>

#ifndef DOXYGEN_SHOULD_SKIP_THIS
  #define MCNLA_TMP ArrS<GpuTag, _Val>
#else  // DOXYGEN_SHOULD_SKIP_THIS
  #define MCNLA_TMP ArrayGpu<_Val>
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Default constructor.
///
template <typename _Val>
MCNLA_TMP::ArrS() noexcept
  : BaseType() {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Val>
MCNLA_TMP::ArrS(
    const index_t size,
    const index_t offset
) noexcept
  : BaseType(std::shared_ptr<_Val>(utility::gpuMalloc<_Val>(size), utility::gpuFree<_Val>), size, offset) {}

}  // namespace matrix

}  // namespace mcnla

#undef MCNLA_TMP

#endif  // MCNLA_CORE_GPU_MATRIX_KIT_ARRAY_GPU_HPP_
