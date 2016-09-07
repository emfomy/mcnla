////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/lapack/routine/gesvd.hpp
/// @brief   The LAPACK GESVD routine.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_LAPACK_ROUTINE_GESVD_HPP_
#define ISVD_LAPACK_ROUTINE_GESVD_HPP_

#include <isvd/isvd.hpp>
#include <isvd/matrix.hpp>
#include <isvd/lapack/lapack.hpp>
#include <isvd/lapack/driver/gesvd.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The LAPACK namespace
//
namespace lapack {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  isvd::lapack::GesvdDriver::compute
///
//@{
template <JobOption _jobu, JobOption _jobvt, class _TypeA, class _TypeS, class _TypeU, class _TypeVt>
inline void gesvd( _TypeA &&a, _TypeS &&s, _TypeU &&u, _TypeVt &&vt ) noexcept {
  GesvdDriver<typename std::remove_reference<_TypeA>::type, _jobu, _jobvt> driver(a);
  driver(a, s, u, vt);
}
//@}

}  // namespace lapack

}  // namespace isvd

#endif  // ISVD_LAPACK_ROUTINE_GESVD_HPP_
