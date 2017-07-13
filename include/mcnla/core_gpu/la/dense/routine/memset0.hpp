////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core_gpu/la/dense/routine/memset0.hpp
/// @brief   The BLAS MEMSET0 routine.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_GPU_LA_DENSE_ROUTINE_MEMSET0_HPP_
#define MCNLA_CORE_GPU_LA_DENSE_ROUTINE_MEMSET0_HPP_

#include <mcnla/core_gpu/la/def.hpp>
#include <mcnla/core_gpu/matrix.hpp>
#include <mcnla/core_gpu/utility.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The linear algebra namespace
//
namespace la {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  la_dense_blas1_gpu_module
/// @brief  Set a vector to zero.
///
/// @attention  the out-of-range spaces are also changed.
///
template <typename _Val>
inline void memset0(
  DenseVectorGpu<_Val> &x
) noexcept {
  mcnla_assert_true(x.isShrunk());
  utility::gpuMemset0(x.valPtr(), x.nelem());
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Val>
inline void memset0(
  DenseVectorGpu<_Val> &&x
) noexcept {
  memset0(x);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  la_dense_blas1m_gpu_module
/// @brief  Set a matrix to zero.
///
/// @attention  the out-of-range spaces are also changed.
///
template <typename _Val, Trans _trans>
inline void memset0(
  DenseMatrixGpu<_Val, _trans> &a
) noexcept {
  mcnla_assert_true(a.isShrunk());
  utility::gpuMemset0(a.valPtr(), a.nelem());
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Val, Trans _trans>
inline void memset0(
  DenseMatrixGpu<_Val, _trans> &&a
) noexcept {
  memset0(a);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace la

}  // namespace mcnla

#endif  // MCNLA_CORE_GPU_LA_DENSE_ROUTINE_MEMSET0_HPP_
