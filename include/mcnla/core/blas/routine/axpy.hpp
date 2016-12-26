////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/blas/routine/axpy.hpp
/// @brief   The BLAS AXPY routine.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_BLAS_ROUTINE_AXPY_HPP_
#define MCNLA_CORE_BLAS_ROUTINE_AXPY_HPP_

#include <mcnla/core/matrix.hpp>
#include <mcnla/core/blas/blas/axpy.hpp>

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
/// @brief  Computes a vector-scalar product and adds the result to a vector.
///
template <typename _Scalar>
inline void axpy(
    const typename DenseVector<_Scalar>::ScalarType alpha,
    const DenseVector<_Scalar> &x,
          DenseVector<_Scalar> &y
) noexcept {
  detail::axpy(x.length(), alpha, x.valuePtr(), x.stride(), y.valuePtr(), y.stride());
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Scalar>
inline void axpy(
    const typename DenseVector<_Scalar>::ScalarType alpha,
    const DenseVector<_Scalar> &x,
          DenseVector<_Scalar> &&y
) noexcept {
  axpy(alpha, x, y);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace blas

}  // namespace mcnla

#endif  // MCNLA_CORE_BLAS_ROUTINE_AXPY_HPP_
