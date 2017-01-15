////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/blas/routine/axpby.hpp
/// @brief   The BLAS AXPBY routine.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_BLAS_ROUTINE_AXPBY_HPP_
#define MCNLA_CORE_BLAS_ROUTINE_AXPBY_HPP_

#include <mcnla/core/container.hpp>
#include <mcnla/core/blas/blas/axpby.hpp>

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
/// @brief  Scales two vectors, adds them to one another and stores result in the vector.
///
template <typename _Scalar>
inline void axpby(
    const DenseVector<_Scalar> &x,
          DenseVector<_Scalar> &y,
    const ScalarT<DenseVector<_Scalar>> alpha = 1,
    const ScalarT<DenseVector<_Scalar>> beta  = 1
) noexcept {
  detail::axpby(x.length(), alpha, x.valuePtr(), x.stride(), beta, y.valuePtr(), y.stride());
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Scalar>
inline void axpby(
    const DenseVector<_Scalar> &x,
          DenseVector<_Scalar> &&y,
    const ScalarT<DenseVector<_Scalar>> alpha = 1,
    const ScalarT<DenseVector<_Scalar>> beta  = 1
) noexcept {
  axpby(x, y, alpha, beta);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace blas

}  // namespace mcnla

#endif  // MCNLA_CORE_BLAS_ROUTINE_AXPBY_HPP_
