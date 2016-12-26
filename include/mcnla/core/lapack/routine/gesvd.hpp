////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/lapack/routine/gesvd.hpp
/// @brief   The LAPACK GESVD routine.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_LAPACK_ROUTINE_GESVD_HPP_
#define MCNLA_CORE_LAPACK_ROUTINE_GESVD_HPP_

#include <mcnla/def.hpp>
#include <mcnla/core/def.hpp>
#include <mcnla/core/lapack/def.hpp>
#include <mcnla/core/matrix.hpp>
#include <mcnla/core/lapack/engine/gesvd.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The LAPACK namespace
//
namespace lapack {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The detail namespace
//
namespace detail {

template <JobOption _jobu, JobOption _jobvt, typename _Scalar, Trans _trans>
inline void gesvdImpl(
    DenseMatrix<_Scalar, _trans> &a,
    DenseVector<RealScalar<_Scalar>> &s,
    DenseMatrix<_Scalar, _trans> &u,
    DenseMatrix<_Scalar, _trans> &vt
) noexcept {
  GesvdEngine<DenseMatrix<_Scalar, _trans>, _jobu, _jobvt> engine(a);
  engine(a, s, u, vt);
}

}  // namespace detail

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  lapack_driver_module
/// @copydoc  mcnla::lapack::GesvdEngine::compute
///
/// @see  mcnla::lapack::GesvdEngine
///
template <JobOption _jobu, JobOption _jobvt, typename _Scalar, Trans _trans>
inline void gesvd(
    DenseMatrix<_Scalar, _trans> &a,
    DenseVector<RealScalar<_Scalar>> &s,
    DenseMatrix<_Scalar, _trans> &u,
    DenseMatrix<_Scalar, _trans> &vt
) noexcept {
  detail::gesvdImpl<_jobu, _jobvt>(a, s, u, vt);
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <JobOption _jobu, JobOption _jobvt, class _TypeA, class _TypeS, class _TypeU, class _TypeVt>
inline void gesvd( _TypeA &&a, _TypeS &&s, _TypeU &&u, _TypeVt &&vt ) noexcept {
  detail::gesvdImpl<_jobu, _jobvt>(a, s, u, vt);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace lapack

}  // namespace mcnla

#endif  // MCNLA_CORE_LAPACK_ROUTINE_GESVD_HPP_
