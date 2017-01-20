////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/la/dense/routine/axpy.hpp
/// @brief   The BLAS AXPY routine.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_LA_DENSE_ROUTINE_AXPY_HPP_
#define MCNLA_CORE_LA_DENSE_ROUTINE_AXPY_HPP_

#include <mcnla/core/la/def.hpp>
#include <mcnla/core/matrix.hpp>
#include <mcnla/core/la/raw/blas/axpy.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The linear algebra namespace
//
namespace la {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  la_dense_blas1_module
/// @brief  Computes a vector-scalar product and adds the result to a vector.
///
template <typename _Scalar>
inline void axpy(
    const DenseVector<_Scalar> &x,
          DenseVector<_Scalar> &y,
    const ScalarT<DenseVector<_Scalar>> alpha = 1
) noexcept {
  detail::axpy(x.length(), alpha, x.valuePtr(), x.stride(), y.valuePtr(), y.stride());
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Scalar>
inline void axpy(
    const DenseVector<_Scalar> &x,
          DenseVector<_Scalar> &&y,
    const ScalarT<DenseVector<_Scalar>> alpha = 1
) noexcept {
  axpy(x, y, alpha);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace la

}  // namespace mcnla

#endif  // MCNLA_CORE_LA_DENSE_ROUTINE_AXPY_HPP_
