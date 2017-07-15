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
// #include <mcnla/core/la/raw/lapack/lange.hpp>
#include <mcnla/core/la/dense/routine/nrm2.hpp>

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
template <typename _Val, Trans _trans>
inline RealValT<_Val> nrmf(
    const DenseMatrix<_Val, _trans> &a
) noexcept {
  /// @todo  Use LAPACK LANGE after MKL fix the bug with GNU OpenMP.
  // return detail::lange('F', a.dim0(), a.dim1(), a.valPtr(), a.pitch(), nullptr);
  return nrm2(a.vec());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  la_dense_blas1m_module
/// @brief  Computes the square of the Frobenius norm of a matrix.
///
template <typename _Val, Trans _trans>
inline RealValT<_Val> nrmf2(
    const DenseMatrix<_Val, _trans> &a
) noexcept {
  auto val = nrmf(a);
  return val * val;
}

}  // namespace la

}  // namespace mcnla

#endif  // MCNLA_CORE_LA_DENSE_ROUTINE_NRMF_HPP_
