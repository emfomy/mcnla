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
  #define MCNLA_ALIAS  ArrS<GpuTag, _Val>
  #define MCNLA_ALIAS0 ArrS
#else  // DOXYGEN_SHOULD_SKIP_THIS
  #define MCNLA_ALIAS  ArrayGpu<_Val>
  #define MCNLA_ALIAS0 ArrayGpu
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
MCNLA_ALIAS::MCNLA_ALIAS0() noexcept
  : BaseType() {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Val>
MCNLA_ALIAS::MCNLA_ALIAS0(
    const size_t size,
    const index_t offset
) noexcept
  : BaseType(std::shared_ptr<_Val>(utility::gpuMalloc<_Val>(size), utility::gpuFree<_Val>), size, offset) {
  mcnla_assert_eq(bool(size), bool(**this));
}

}  // namespace matrix

}  // namespace mcnla

#undef MCNLA_ALIAS
#undef MCNLA_ALIAS0

#endif  // MCNLA_CORE_GPU_MATRIX_KIT_ARRAY_GPU_HPP_
