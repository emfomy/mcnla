////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/lapack/driver/syev_driver.ipp
/// @brief   The implementation of LAPACK SYEV driver.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_LAPACK_DRIVER_SYEV_DRIVER_IPP_
#define ISVD_LAPACK_DRIVER_SYEV_DRIVER_IPP_

#include <isvd/lapack/driver/syev_driver.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The LAPACK namespace
//
namespace lapack {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <class _Matrix, JobOption _jobz, UploOption _uplo>
SyevDriver<_Matrix, _jobz, _uplo>::SyevDriver(
    const _Matrix &a
) noexcept
  : dim_(a.getNrow()),
    work_(query(a)),
    rwork_(is_real ? RealVectorType() : RealVectorType(3*dim_)) {
  assert(a.getNrow() == a.getNcol());
  assert(dim_ > 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Computes the eigenvalue decomposition.
///
/// @attention  MATRIX @p a WILL BE DESTORIED!
///
template <class _Matrix, JobOption _jobz, UploOption _uplo>
void SyevDriver<_Matrix, _jobz, _uplo>::compute(
    _Matrix &a,
    RealVectorType &w
) noexcept {
  assert(a.getNrow() == dim_ && a.getNcol() == dim_);
  assert(a.getNrow() == a.getNcol());
  assert(w.getLength() == a.getNrow());

  assert(internal::syev(_jobz, UploChar<_uplo, layout>::value, a.getNrow(), a.getValue(), a.getPitch(),
                        w.getValue(), work_.getValue(), work_.getLength(), rwork_.getValue()) == 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  compute
///
template <class _Matrix, JobOption _jobz, UploOption _uplo> template <class _TypeA, class _TypeW>
void SyevDriver<_Matrix, _jobz, _uplo>::compute( _TypeA &&a, _TypeW &&w ) noexcept {
  compute<_jobz, _uplo>(a, w);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the workspace
///
template <class _Matrix, JobOption _jobz, UploOption _uplo>
typename SyevDriver<_Matrix, _jobz, _uplo>::VectorType& SyevDriver<_Matrix, _jobz, _uplo>::getWork() noexcept {
  return work_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getWork
///
template <class _Matrix, JobOption _jobz, UploOption _uplo>
const typename SyevDriver<_Matrix, _jobz, _uplo>::VectorType& SyevDriver<_Matrix, _jobz, _uplo>::getWork() const noexcept {
  return work_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the real workspace
///
template <class _Matrix, JobOption _jobz, UploOption _uplo>
typename SyevDriver<_Matrix, _jobz, _uplo>::RealVectorType& SyevDriver<_Matrix, _jobz, _uplo>::getRwork() noexcept {
  return rwork_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getRwork
///
template <class _Matrix, JobOption _jobz, UploOption _uplo>
const typename SyevDriver<_Matrix, _jobz, _uplo>::RealVectorType& SyevDriver<_Matrix, _jobz, _uplo>::getRwork() const noexcept {
  return rwork_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Query the optimal workspace size.
///
template <class _Matrix, JobOption _jobz, UploOption _uplo>
index_t SyevDriver<_Matrix, _jobz, _uplo>::query(
    const _Matrix &a
) const noexcept {
  assert(a.getNrow() == a.getNcol());
  ScalarType lwork;
  assert(internal::syev(_jobz, UploChar<_uplo, layout>::value, a.getNrow(),
                        nullptr, a.getPitch(), nullptr, &lwork, -1, nullptr) == 0);
  return lwork;
}

}  // namespace lapack

}  // namespace isvd

#endif  // ISVD_LAPACK_DRIVER_SYEV_DRIVER_IPP_
