////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/la/dense/routine/scal.hpp
/// @brief   The BLAS SCAL routine.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_LA_DENSE_ROUTINE_SCAL_HPP_
#define MCNLA_CORE_LA_DENSE_ROUTINE_SCAL_HPP_

#include <mcnla/core/la/def.hpp>
#include <mcnla/core/matrix.hpp>
#include <mcnla/core/la/raw/blas/scal.hpp>

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
/// @brief  Computes the product of a vector by a scalar.
///
template <typename _Scalar>
inline void scal(
          DenseVector<_Scalar> &x,
    const ScalarT<DenseVector<_Scalar>> alpha
) noexcept {
  detail::scal(x.length(), alpha, x.valPtr(), x.stride());
}

template <typename _Scalar>
inline void scal(
          DenseVector<std::complex<_Scalar>> &x,
    const RealScalarT<ScalarT<DenseVector<std::complex<_Scalar>>>> alpha
) noexcept {
  detail::scal(x.length(), alpha, x.valPtr(), x.stride());
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Scalar>
inline void scal(
          DenseVector<_Scalar> &&x,
    const ScalarT<DenseVector<_Scalar>> alpha
) noexcept {
  scal(x, alpha);
}

template <typename _Scalar>
inline void scal(
          DenseVector<std::complex<_Scalar>> &&x,
    const RealScalarT<ScalarT<DenseVector<std::complex<_Scalar>>>> alpha
) noexcept {
  scal(x, alpha);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace la

}  // namespace mcnla

#endif  // MCNLA_CORE_LA_DENSE_ROUTINE_SCAL_HPP_
