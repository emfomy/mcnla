////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core_gpu/la/dense/routine/set_get.hpp
/// @brief   The GPU communication routine.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_GPU_LA_DENSE_ROUTINE_SET_GET_HPP_
#define MCNLA_CORE_GPU_LA_DENSE_ROUTINE_SET_GET_HPP_

#include <mcnla/core_gpu/la/def.hpp>
#include <mcnla/core_gpu/matrix.hpp>
#include <mcnla/core_gpu/la/raw/magma/setvector.hpp>
#include <mcnla/core_gpu/la/raw/magma/getvector.hpp>
#include <mcnla/core_gpu/la/raw/magma/setmatrix.hpp>
#include <mcnla/core_gpu/la/raw/magma/getmatrix.hpp>

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
/// @brief  Copies CPU vector to GPU vector.
///
template <typename _Val>
inline void copy(
    const DenseVector<_Val> &x,
          DenseVectorGpu<_Val> &y
) noexcept {
  mcnla_assert_eq(x.sizes(), y.sizes());
  detail::gpu::setvector(x.len(), x.valPtr(), x.stride(), y.valPtr(), y.stride());
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Val>
inline void copy(
    const DenseVector<_Val> &x,
          DenseVectorGpu<_Val> &&y
) noexcept {
  copy(x, y);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  la_dense_blas1_gpu_module
/// @brief  Copies GPU vector to CPU vector.
///
template <typename _Val>
inline void copy(
    const DenseVectorGpu<_Val> &x,
          DenseVector<_Val> &y
) noexcept {
  mcnla_assert_eq(x.sizes(), y.sizes());
  detail::gpu::getvector(x.len(), x.valPtr(), x.stride(), y.valPtr(), y.stride());
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Val>
inline void copy(
    const DenseVectorGpu<_Val> &x,
          DenseVector<_Val> &&y
) noexcept {
  copy(x, y);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  la_dense_blas1m_gpu_module
/// @brief  Copies CPU matrix to GPU matrix.
///
template <typename _Val, Trans _trans>
inline void copy(
    const DenseMatrix<_Val, _trans> &a,
          DenseMatrixGpu<_Val, _trans> &b
) noexcept {
  mcnla_assert_eq(a.sizes(), b.sizes());
  detail::gpu::setmatrix(a.dim0, a.dim1(), a.valPtr(), a.pitch(), b.valPtr(), b.pitch());
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Val, Trans _trans>
inline void copy(
    const DenseMatrix<_Val, _trans> &a,
          DenseMatrixGpu<_Val, _trans> &&b
) noexcept {
  copy(a, b);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  la_dense_blas1m_gpu_module
/// @brief  Copies GPU matrix to CPU matrix.
///
template <typename _Val, Trans _trans>
inline void copy(
    const DenseMatrixGpu<_Val, _trans> &a,
          DenseMatrix<_Val, _trans> &b
) noexcept {
  mcnla_assert_eq(a.sizes(), b.sizes());
  detail::gpu::getmatrix(a.dim0, a.dim1(), a.len(), a.valPtr(), a.pitch(), b.valPtr(), b.pitch());
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Val, Trans _trans>
inline void copy(
    const DenseMatrixGpu<_Val, _trans> &a,
          DenseMatrix<_Val, _trans> &&b
) noexcept {
  copy(a, b);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace la

}  // namespace mcnla

#endif  // MCNLA_CORE_GPU_LA_DENSE_ROUTINE_SET_GET_HPP_
