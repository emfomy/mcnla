////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/blas/routine/scal.hpp
/// @brief   The BLAS SCAL routine.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_BLAS_ROUTINE_SCAL_HPP_
#define MCNLA_CORE_BLAS_ROUTINE_SCAL_HPP_

#include <mcnla/core/container.hpp>
#include <mcnla/core/blas/blas/scal.hpp>

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
/// @brief  Computes the product of a vector by a scalar.
///
template <typename _Scalar>
inline void scal(
    const ScalarT<DenseVector<_Scalar>> alpha,
          DenseVector<_Scalar> &x
) noexcept {
  detail::scal(x.length(), alpha, x.valuePtr(), x.stride());
}

template <typename _Scalar>
inline void scal(
    const RealScalarT<ScalarT<DenseVector<std::complex<_Scalar>>>> alpha,
          DenseVector<std::complex<_Scalar>> &x
) noexcept {
  detail::scal(x.length(), alpha, x.valuePtr(), x.stride());
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Scalar>
inline void scal(
    const ScalarT<DenseVector<_Scalar>> alpha,
          DenseVector<_Scalar> &&x
) noexcept {
  scal(alpha, x);
}

template <typename _Scalar>
inline void scal(
    const RealScalarT<ScalarT<DenseVector<std::complex<_Scalar>>>> alpha,
          DenseVector<std::complex<_Scalar>> &&x
) noexcept {
  scal(alpha, x);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace blas

}  // namespace mcnla

#endif  // MCNLA_CORE_BLAS_ROUTINE_SCAL_HPP_
