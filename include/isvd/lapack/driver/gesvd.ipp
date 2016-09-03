////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/lapack/driver/gesvd.ipp
/// @brief   The implementation of LAPACK GESVD driver.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_LAPACK_DRIVER_GESVD_IPP_
#define ISVD_LAPACK_DRIVER_GESVD_IPP_

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
/// @brief  Default constructor.
///
template <class _Matrix, JobOption _jobu, JobOption _jobvt>
GesvdDriver<_Matrix, _jobu, _jobvt>::GesvdDriver() noexcept
  : nrow_(0),
    ncol_(0),
    work_(),
    rwork_() {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <class _Matrix, JobOption _jobu, JobOption _jobvt>
GesvdDriver<_Matrix, _jobu, _jobvt>::GesvdDriver(
    const index_t nrow, const index_t ncol
) noexcept
  : nrow_(nrow),
    ncol_(ncol),
    work_(query(nrow, ncol)),
    rwork_(is_real ? RealVectorType() : RealVectorType(5 * std::min(nrow, ncol))) {
  assert(nrow_ > 0 && ncol_ > 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <class _Matrix, JobOption _jobu, JobOption _jobvt>
GesvdDriver<_Matrix, _jobu, _jobvt>::GesvdDriver(
    const _Matrix &a
) noexcept
  : GesvdDriver(a.getNrow(), a.getNcol()) {
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  compute
///
template <class _Matrix, JobOption _jobu, JobOption _jobvt> template <class _TypeA, class _TypeS, class _TypeU, class _TypeVt>
void GesvdDriver<_Matrix, _jobu, _jobvt>::operator()( _TypeA &&a, _TypeS &&s, _TypeU &&u, _TypeVt &&vt ) noexcept {
  compute(a, s, u, vt);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Resize the driver
///
template <class _Matrix, JobOption _jobu, JobOption _jobvt>
void GesvdDriver<_Matrix, _jobu, _jobvt>::resize(
    const index_t nrow, const index_t ncol
) noexcept {
  assert(nrow > 0 && ncol > 0);
  nrow_ = nrow;
  ncol_ = ncol;
  work_ = VectorType(query(nrow, ncol));
  if ( is_real ) {
    rwork_ = RealVectorType(5 * std::min(nrow, ncol));
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  resize
///
template <class _Matrix, JobOption _jobu, JobOption _jobvt>
void GesvdDriver<_Matrix, _jobu, _jobvt>::resize(
    const _Matrix &a
) noexcept {
  resize(a.getNrow(), a.getNcol());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the sizes.
///
template <class _Matrix, JobOption _jobu, JobOption _jobvt>
std::pair<index_t, index_t> GesvdDriver<_Matrix, _jobu, _jobvt>::getSizes() const noexcept {
  return std::make_pair(nrow_, ncol_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the workspace
///
template <class _Matrix, JobOption _jobu, JobOption _jobvt>
typename GesvdDriver<_Matrix, _jobu, _jobvt>::VectorType& GesvdDriver<_Matrix, _jobu, _jobvt>::getWork() noexcept {
  return work_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getWork
///
template <class _Matrix, JobOption _jobu, JobOption _jobvt>
const typename GesvdDriver<_Matrix, _jobu, _jobvt>::VectorType& GesvdDriver<_Matrix, _jobu, _jobvt>::getWork() const noexcept {
  return work_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the real workspace
///
template <class _Matrix, JobOption _jobu, JobOption _jobvt>
typename GesvdDriver<_Matrix, _jobu, _jobvt>::RealVectorType&
    GesvdDriver<_Matrix, _jobu, _jobvt>::getRwork() noexcept {
  return rwork_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getRwork
///
template <class _Matrix, JobOption _jobu, JobOption _jobvt>
const typename GesvdDriver<_Matrix, _jobu, _jobvt>::RealVectorType&
    GesvdDriver<_Matrix, _jobu, _jobvt>::getRwork() const noexcept {
  return rwork_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Computes the singular value decomposition.
///
/// @attention  MATRIX @p a WILL BE DESTORIED!
///
template <class _Matrix, JobOption _jobu, JobOption _jobvt>
void GesvdDriver<_Matrix, _jobu, _jobvt>::compute(
    _Matrix &a,
    RealVectorType &s,
    _Matrix &u,
    _Matrix &vt
) noexcept {
  assert(nrow_ > 0 && ncol_ > 0);
  assert(a.getSizes() == std::make_pair(nrow_, ncol_));

  if ( _jobu == 'A' ) {
    assert(u.getSizes() == std::make_pair(nrow_, nrow_));
  } else if ( _jobu == 'S' ) {
    assert(u.getSizes() == std::make_pair(nrow_, std::min(nrow_, ncol_)));
  }

  if ( _jobvt == 'A' ) {
    assert(u.getSizes() == std::make_pair(ncol_, ncol_));
  } else if ( _jobvt == 'S' ) {
    assert(vt.getSizes() == std::make_pair(std::min(nrow_, ncol_), ncol_));
  }

  if ( isColMajor(layout) ) {
    assert(internal::gesvd(_jobu, _jobvt, a.getNrow(), a.getNcol(), a.getValue(), a.getPitch(),
                           s.getValue(), u.getValue(), u.getPitch(), vt.getValue(), vt.getPitch(),
                           work_.getValue(), work_.getLength(), rwork_.getValue()) == 0);
  } else {
    assert(internal::gesvd(_jobvt, _jobu, a.getNcol(), a.getNrow(), a.getValue(), a.getPitch(),
                           s.getValue(), vt.getValue(), vt.getPitch(), u.getValue(), u.getPitch(),
                           work_.getValue(), work_.getLength(), rwork_.getValue()) == 0);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Query the optimal workspace size.
///
template <class _Matrix, JobOption _jobu, JobOption _jobvt>
index_t GesvdDriver<_Matrix, _jobu, _jobvt>::query(
    const index_t nrow, const index_t ncol
) const noexcept {
  ScalarType lwork;
  if ( isColMajor(layout) ) {
    assert(internal::gesvd(_jobu, _jobvt, nrow, ncol, nullptr, nrow, nullptr,
                           nullptr, nrow, nullptr, ncol, &lwork, -1, nullptr) == 0);
  } else {
    assert(internal::gesvd(_jobvt, _jobu, ncol, nrow, nullptr, ncol, nullptr,
                           nullptr, ncol, nullptr, nrow, &lwork, -1, nullptr) == 0);
  }
  return lwork;
}

}  // namespace lapack

}  // namespace isvd

#endif  // ISVD_LAPACK_DRIVER_GESVD_IPP_