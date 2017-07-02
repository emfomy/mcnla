////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/la/dense/routine/geqrfg.hpp
/// @brief   The LAPACK GEQRF+ORGQR routine.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_LA_DENSE_ROUTINE_GEQRFG_HPP_
#define MCNLA_CORE_LA_DENSE_ROUTINE_GEQRFG_HPP_

#include <mcnla/core/la/def.hpp>
#include <mcnla/core/matrix.hpp>
#include <mcnla/core/la/dense/driver/geqrfg.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The linear algebra namespace
//
namespace la {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  la_dense_lapack_ls_module
/// @copydoc  mcnla::la::DenseGeqrfgDriver::compute
///
/// @see  mcnla::la::DenseGeqrfgDriver
///
template <JobOption _jobu, JobOption _jobvt, typename _Val, Trans _trans>
inline void geqrfg(
    DenseMatrix<_Val, _trans> &a,
    DenseVector<_Val> &tau,
    DenseMatrix<_Val, _trans> &q,
    DenseMatrix<_Val, _trans> &r
) noexcept {
  DenseGeqrfgDriver<_jobu, _jobvt, _Val, _trans> driver(a);
  driver(a, tau, q, r);
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <JobOption _jobu, JobOption _jobvt, class _TypeA, class _TypeTau, class _TypeQ, class _TypeR>
inline void geqrfg(
    _TypeA   &&a,
    _TypeTau &&tau,
    _TypeQ   &&q,
    _TypeR   &&r
) noexcept {
  geqrfg<_jobu, _jobvt>(a, tau, q, r);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace la

}  // namespace mcnla

#endif  // MCNLA_CORE_LA_DENSE_ROUTINE_GEQRFG_HPP_
