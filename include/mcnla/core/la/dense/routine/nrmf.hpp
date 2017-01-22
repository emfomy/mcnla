////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/la/dense/routine/nrmf.hpp
/// @brief   The BLAS NRMF routine.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_LA_DENSE_ROUTINE_NRMF_HPP_
#define MCNLA_CORE_LA_DENSE_ROUTINE_NRMF_HPP_

#include <mcnla/core/la/def.hpp>
#include <mcnla/core/matrix.hpp>
#include <mcnla/core/la/raw/lapack/lange.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The linear algebra namespace
//
namespace la {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  la_dense_blas1m_module
/// @brief  Computes the Frobenius norm of a matrix.
///
//@{
template <typename _Scalar, Trans _trans>
inline RealScalarT<_Scalar> nrmf(
    const DenseMatrix<_Scalar, _trans> &a
) noexcept {
  return detail::lange('F', a.dim0(), a.dim1(), a.valPtr(), a.pitch(), nullptr);
}
//@}

}  // namespace la

}  // namespace mcnla

#endif  // MCNLA_CORE_LA_DENSE_ROUTINE_NRMF_HPP_