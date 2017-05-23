////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/la/dense/driver/syev.hpp
/// @brief   The LAPACK SYEV driver.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_LA_DENSE_DRIVER_SYEV_HH_
#define MCNLA_CORE_LA_DENSE_DRIVER_SYEV_HH_

#include <mcnla/core/la/dense/driver/syev.hh>
#include <mcnla/core/la/raw/lapack/syev.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The linear algebra namespace
//
namespace la {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Default constructor.
///
template <class _Matrix, JobOption _jobz>
SyevDriver<_Matrix, _jobz>::SyevDriver() noexcept
  : size_(0),
    work_(),
    rwork_() {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <class _Matrix, JobOption _jobz>
SyevDriver<_Matrix, _jobz>::SyevDriver(
    const index_t size
) noexcept
  : size_(size),
    work_(query(size)),
    rwork_(is_real ? RealVectorType() : RealVectorType(3*size)) {
  mcnla_assert_gt(size_, 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <class _Matrix, JobOption _jobz>
SyevDriver<_Matrix, _jobz>::SyevDriver(
    const MatrixType &a
) noexcept
  : SyevDriver(a.nrow()) {
  mcnla_assert_eq(a.nrow(), a.ncol());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  compute
///
template <class _Matrix, JobOption _jobz> template <class _TypeA, class _TypeW>
void SyevDriver<_Matrix, _jobz>::operator()(
    _TypeA &&a,
    _TypeW &&w
) noexcept {
  compute(a, w);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Computes eigenvalues only.
///
template <class _Matrix, JobOption _jobz> template <class _TypeA, class _TypeW>
void SyevDriver<_Matrix, _jobz>::computeValues(
    _TypeA &&a,
    _TypeW &&w
) noexcept {
  compute<'N'>(a, w);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Reconstruct the driver.
///
template <class _Matrix, JobOption _jobz> template <typename ..._Args>
void SyevDriver<_Matrix, _jobz>::reconstruct(
    _Args... args
) noexcept {
  *this = SyevDriver<_Matrix, _jobz>(args...);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the sizes.
///
template <class _Matrix, JobOption _jobz>
std::tuple<index_t> SyevDriver<_Matrix, _jobz>::sizes() const noexcept {
  return std::make_tuple(size_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the workspace
///
template <class _Matrix, JobOption _jobz>
VectorT<_Matrix>& SyevDriver<_Matrix, _jobz>::getWork() noexcept {
  return work_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getWork
///
template <class _Matrix, JobOption _jobz>
const VectorT<_Matrix>& SyevDriver<_Matrix, _jobz>::getWork() const noexcept {
  return work_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the real workspace
///
template <class _Matrix, JobOption _jobz>
RealT<VectorT<_Matrix>>& SyevDriver<_Matrix, _jobz>::getRwork() noexcept {
  return rwork_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getRwork
///
template <class _Matrix, JobOption _jobz>
const RealT<VectorT<_Matrix>>& SyevDriver<_Matrix, _jobz>::getRwork() const noexcept {
  return rwork_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Computes the eigenvalue decomposition.
///
/// @attention  The eigenvectors are Stored in columnwise for column-major storage, in rowwise for row-major storage.
/// @attention  Matrix @a a will be destroyed!
///
template <class _Matrix, JobOption _jobz> template <JobOption __jobz>
void SyevDriver<_Matrix, _jobz>::compute(
    MatrixType &a,
    RealVectorType &w
) noexcept {
  mcnla_assert_gt(size_, 0);
  mcnla_assert_eq(a.sizes(), std::make_tuple(size_, size_));
  mcnla_assert_eq(w.len(), size_);
  mcnla_assert_true(w.isShrunk());

  mcnla_assert_pass(detail::syev(__jobz, toUploChar(uplo, trans), a.nrow(), a.valPtr(), a.pitch(),
                                 w.valPtr(), work_.valPtr(), work_.len(), rwork_.valPtr()));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Query the optimal workspace size.
///
template <class _Matrix, JobOption _jobz>
index_t SyevDriver<_Matrix, _jobz>::query(
    const index_t size
) noexcept {
  ValType lwork;
  mcnla_assert_pass(detail::syev(_jobz, toUploChar(uplo, trans), size, nullptr, size, nullptr, &lwork, -1, nullptr));
  return lwork;
}

}  // namespace la

}  // namespace mcnla

#endif  // MCNLA_CORE_LA_DENSE_DRIVER_SYEV_HH_
