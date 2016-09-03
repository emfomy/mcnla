////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/lapack/driver/syev.ipp
/// @brief   The implementation of LAPACK SYEV driver.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_LAPACK_DRIVER_SYEV_IPP_
#define ISVD_LAPACK_DRIVER_SYEV_IPP_

#include <isvd/lapack/driver/syev.hpp>

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
    const index_t dim
) noexcept
  : dim_(dim),
    work_(dim),
    rwork_(is_real ? RealVectorType() : RealVectorType(3*dim)) {
  assert(dim_ > 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <class _Matrix, JobOption _jobz, UploOption _uplo>
SyevDriver<_Matrix, _jobz, _uplo>::SyevDriver(
    const _Matrix &a
) noexcept
  : SyevDriver(a.getNrow()) {
  assert(a.getNrow() == a.getNcol());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  compute
///
template <class _Matrix, JobOption _jobz, UploOption _uplo> template <class _TypeA, class _TypeW>
void SyevDriver<_Matrix, _jobz, _uplo>::operator()( _TypeA &&a, _TypeW &&w ) noexcept {
  compute(a, w);
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
/// @brief  Computes the eigenvalue decomposition.
///
/// @attention  MATRIX @p a WILL BE DESTORIED!
///
template <class _Matrix, JobOption _jobz, UploOption _uplo>
void SyevDriver<_Matrix, _jobz, _uplo>::compute(
    _Matrix &a,
    RealVectorType &w
) noexcept {
  assert(a.getSizes() == std::make_pair(dim_, dim_));
  assert(w.getLength() == a.getNrow());

  assert(internal::syev(_jobz, UploChar<_uplo, layout>::value, a.getNrow(), a.getValue(), a.getPitch(),
                        w.getValue(), work_.getValue(), work_.getLength(), rwork_.getValue()) == 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Query the optimal workspace size.
///
template <class _Matrix, JobOption _jobz, UploOption _uplo>
index_t SyevDriver<_Matrix, _jobz, _uplo>::query(
    const index_t dim
) const noexcept {
  ScalarType lwork;
  assert(internal::syev(_jobz, UploChar<_uplo, layout>::value, dim, nullptr, dim, nullptr, &lwork, -1, nullptr) == 0);
  return lwork;
}

}  // namespace lapack

}  // namespace isvd

#endif  // ISVD_LAPACK_DRIVER_SYEV_IPP_
