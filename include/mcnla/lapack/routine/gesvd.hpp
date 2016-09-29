////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/lapack/routine/gesvd.hpp
/// @brief   The LAPACK GESVD routine.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_LAPACK_ROUTINE_GESVD_HPP_
#define MCNLA_LAPACK_ROUTINE_GESVD_HPP_

#include <mcnla/mcnla.hpp>
#include <mcnla/matrix.hpp>
#include <mcnla/lapack/lapack.hpp>
#include <mcnla/lapack/driver/gesvd.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The LAPACK namespace
//
namespace lapack {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::lapack::GesvdDriver::compute
///
//@{
template <JobOption _jobu, JobOption _jobvt, typename _Scalar, Layout _layout>
inline void gesvd(
    DenseMatrix<_Scalar, _layout> &a,
    DenseVector<typename mcnla::detail::ScalarTraits<_Scalar>::RealType> &s,
    DenseMatrix<_Scalar, _layout> &u,
    DenseMatrix<_Scalar, _layout> &vt
) noexcept {
  GesvdDriver<DenseMatrix<_Scalar, _layout>, _jobu, _jobvt> driver(a);
  driver(a, s, u, vt);
}

template <JobOption _jobu, JobOption _jobvt, class _TypeA, class _TypeS, class _TypeU, class _TypeVt>
inline void gesvd( _TypeA &&a, _TypeS &&s, _TypeU &&u, _TypeVt &&vt ) noexcept {
  gesvd<_jobu, _jobvt>(a, s, u, vt);
}
//@}

}  // namespace lapack

}  // namespace mcnla

#endif  // MCNLA_LAPACK_ROUTINE_GESVD_HPP_
