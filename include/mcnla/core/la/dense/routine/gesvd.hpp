////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/la/dense/routine/gesvd.hpp
/// @brief   The LAPACK GESVD routine.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_LA_DENSE_ROUTINE_GESVD_HPP_
#define MCNLA_CORE_LA_DENSE_ROUTINE_GESVD_HPP_

#include <mcnla/core/la/def.hpp>
#include <mcnla/core/matrix.hpp>
#include <mcnla/core/la/dense/driver/gesvd.hpp>

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
/// @copydoc  mcnla::la::DenseGesvdDriver::compute
///
/// @see  mcnla::la::DenseGesvdDriver
///
template <JobOption _jobu, JobOption _jobvt, typename _Val, Trans _trans>
inline void gesvd(
    DenseMatrix<_Val, _trans> &a,
    DenseVector<RealValT<_Val>> &s,
    DenseMatrix<_Val, _trans> &u,
    DenseMatrix<_Val, _trans> &vt
) noexcept {
  DenseGesvdDriver<_jobu, _jobvt, _Val, _trans> driver(a);
  driver(a, s, u, vt);
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <JobOption _jobu, JobOption _jobvt, class ..._Args>
inline void gesvd(
    _Args&&... args
) noexcept {
  gesvd<_jobu, _jobvt>(args...);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace la

}  // namespace mcnla

#endif  // MCNLA_CORE_LA_DENSE_ROUTINE_GESVD_HPP_
