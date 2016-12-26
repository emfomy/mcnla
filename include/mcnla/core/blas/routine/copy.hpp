////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/blas/routine/copy.hpp
/// @brief   The BLAS COPY routine.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_BLAS_ROUTINE_COPY_HPP_
#define MCNLA_CORE_BLAS_ROUTINE_COPY_HPP_

#include <mcnla/core/matrix.hpp>
#include <mcnla/core/blas/blas/copy.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The BLAS namespace
//
namespace blas {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  blas1_module
/// @brief  Copies vector to another vector.
///
template <typename _Scalar>
inline void copy(
    const DenseVector<_Scalar> &x,
          DenseVector<_Scalar> &y
) noexcept {
  mcnla_assert_eq(x.sizes(), y.sizes());
  detail::copy(x.length(), x.valuePtr(), x.stride(), y.valuePtr(), y.stride());
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Scalar>
inline void copy(
    const DenseVector<_Scalar> &x,
          DenseVector<_Scalar> &&y
) noexcept {
  copy(x, y);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace blas

}  // namespace mcnla

#endif  // MCNLA_CORE_BLAS_ROUTINE_COPY_HPP_
