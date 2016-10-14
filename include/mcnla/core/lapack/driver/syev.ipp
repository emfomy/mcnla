////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/lapack/driver/syev.ipp
/// @brief   The implementation of LAPACK SYEV driver.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_LAPACK_DRIVER_SYEV_IPP_
#define MCNLA_CORE_LAPACK_DRIVER_SYEV_IPP_

#include <mcnla/core/lapack/driver/syev.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The LAPACK namespace
//
namespace lapack {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Default constructor.
///
template <class _Matrix, JobOption _jobz, UploOption _uplo>
SyevDriver<_Matrix, _jobz, _uplo>::SyevDriver() noexcept
  : dim_(0),
    work_(),
    rwork_() {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <class _Matrix, JobOption _jobz, UploOption _uplo>
SyevDriver<_Matrix, _jobz, _uplo>::SyevDriver(
    const index_t dim
) noexcept
  : dim_(dim),
    work_(query(dim)),
    rwork_(is_real ? RealVectorType() : RealVectorType(3*dim)) {
  mcnla_assert_gt(dim_, 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <class _Matrix, JobOption _jobz, UploOption _uplo>
SyevDriver<_Matrix, _jobz, _uplo>::SyevDriver(
    const _Matrix &a
) noexcept
  : SyevDriver(a.getNrow()) {
  mcnla_assert_eq(a.getNrow(), a.getNcol());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  compute
///
template <class _Matrix, JobOption _jobz, UploOption _uplo> template <class _TypeA, class _TypeW>
void SyevDriver<_Matrix, _jobz, _uplo>::operator()( _TypeA &&a, _TypeW &&w ) noexcept {
  compute(a, w);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Computes eigenvalues only.
///
template <class _Matrix, JobOption _jobz, UploOption _uplo> template <class _TypeA, class _TypeW>
void SyevDriver<_Matrix, _jobz, _uplo>::computeValues( _TypeA &&a, _TypeW &&w ) noexcept {
  compute<'N'>(a, w);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Resizes the driver
///
template <class _Matrix, JobOption _jobz, UploOption _uplo>
void SyevDriver<_Matrix, _jobz, _uplo>::resize(
    const index_t dim
) noexcept {
  mcnla_assert_gt(dim, 0);
  dim_ = dim;
  work_ = VectorType(query(dim));
  if ( is_real ) {
    rwork_ = RealVectorType(3*dim);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  resize
///
template <class _Matrix, JobOption _jobz, UploOption _uplo>
void SyevDriver<_Matrix, _jobz, _uplo>::resize(
    const _Matrix &a
) noexcept {
  mcnla_assert_eq(a.getNrow(), a.getNcol());
  resize(a.getNrow());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the sizes.
///
template <class _Matrix, JobOption _jobz, UploOption _uplo>
index_t SyevDriver<_Matrix, _jobz, _uplo>::getSizes() const noexcept { return dim_; }

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
/// @attention  The eigenvectors are Stored in columnwise for column-major storage, in rowwise for row-major storage.
/// @attention  Matrix @a a will be destroyed!
///
template <class _Matrix, JobOption _jobz, UploOption _uplo> template <JobOption __jobz>
void SyevDriver<_Matrix, _jobz, _uplo>::compute(
    _Matrix &a,
    RealVectorType &w
) noexcept {
  mcnla_assert_gt(dim_, 0);
  mcnla_assert_eq(a.getSizes(), std::make_pair(dim_, dim_));
  mcnla_assert_eq(w.getLength(), a.getNrow());
  mcnla_assert_eq(detail::syev(__jobz, toUploChar(_uplo, layout), a.getNrow(), a.getValue(), a.getPitch(),
                               w.getValue(), work_.getValue(), work_.getLength(), rwork_.getValue()), 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Query the optimal workspace size.
///
template <class _Matrix, JobOption _jobz, UploOption _uplo>
index_t SyevDriver<_Matrix, _jobz, _uplo>::query(
    const index_t dim
) const noexcept {
  ScalarType lwork;
  mcnla_assert_eq(detail::syev(_jobz, toUploChar(_uplo, layout), dim, nullptr, dim, nullptr, &lwork, -1, nullptr), 0);
  return lwork;
}

}  // namespace lapack

}  // namespace mcnla

#endif  // MCNLA_CORE_LAPACK_DRIVER_SYEV_IPP_
