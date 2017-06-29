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
template <JobOption _jobz, typename _Val, Trans _trans, Uplo _uplo>
DenseSyevDriver<_jobz, _Val, _trans, _uplo>::DenseSyevDriver() noexcept
  : size_(0),
    work_(),
    rwork_() {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <JobOption _jobz, typename _Val, Trans _trans, Uplo _uplo>
DenseSyevDriver<_jobz, _Val, _trans, _uplo>::DenseSyevDriver(
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
template <JobOption _jobz, typename _Val, Trans _trans, Uplo _uplo>
DenseSyevDriver<_jobz, _Val, _trans, _uplo>::DenseSyevDriver(
    const MatrixType &a
) noexcept
  : DenseSyevDriver(a.nrow()) {
  mcnla_assert_true(a.isSquare());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  compute
///
template <JobOption _jobz, typename _Val, Trans _trans, Uplo _uplo> template <class _TypeA, class _TypeW>
void DenseSyevDriver<_jobz, _Val, _trans, _uplo>::operator()(
    _TypeA &&a,
    _TypeW &&w
) noexcept {
  compute(a, w);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Computes eigenvalues only.
///
template <JobOption _jobz, typename _Val, Trans _trans, Uplo _uplo> template <class _TypeA, class _TypeW>
void DenseSyevDriver<_jobz, _Val, _trans, _uplo>::computeValues(
    _TypeA &&a,
    _TypeW &&w
) noexcept {
  compute<'N'>(a, w);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Reconstruct the driver.
///
template <JobOption _jobz, typename _Val, Trans _trans, Uplo _uplo> template <typename ..._Args>
void DenseSyevDriver<_jobz, _Val, _trans, _uplo>::reconstruct(
    _Args... args
) noexcept {
  *this = DenseSyevDriver<_jobz, _Val, _trans, _uplo>(args...);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the sizes.
///
template <JobOption _jobz, typename _Val, Trans _trans, Uplo _uplo>
std::tuple<index_t, index_t> DenseSyevDriver<_jobz, _Val, _trans, _uplo>::sizes() const noexcept {
  return std::make_tuple(size_, size_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the workspace
///
template <JobOption _jobz, typename _Val, Trans _trans, Uplo _uplo>
DenseVector<_Val>& DenseSyevDriver<_jobz, _Val, _trans, _uplo>::getWork() noexcept {
  return work_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getWork
///
template <JobOption _jobz, typename _Val, Trans _trans, Uplo _uplo>
const DenseVector<_Val>& DenseSyevDriver<_jobz, _Val, _trans, _uplo>::getWork() const noexcept {
  return work_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the real workspace
///
template <JobOption _jobz, typename _Val, Trans _trans, Uplo _uplo>
DenseVector<RealValT<_Val>>& DenseSyevDriver<_jobz, _Val, _trans, _uplo>::getRwork() noexcept {
  return rwork_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getRwork
///
template <JobOption _jobz, typename _Val, Trans _trans, Uplo _uplo>
const DenseVector<RealValT<_Val>>& DenseSyevDriver<_jobz, _Val, _trans, _uplo>::getRwork() const noexcept {
  return rwork_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Computes the eigenvalue decomposition.
///
/// @attention  The eigenvectors are Stored in columnwise for column-major storage, in rowwise for row-major storage.
/// @attention  Matrix @a a will be destroyed!
///
template <JobOption _jobz, typename _Val, Trans _trans, Uplo _uplo> template <JobOption __jobz>
void DenseSyevDriver<_jobz, _Val, _trans, _uplo>::compute(
    MatrixType &a,
    RealVectorType &w
) noexcept {
  mcnla_assert_eq(a.sizes(), this->sizes());
  mcnla_assert_eq(w.len(), size_);
  mcnla_assert_true(w.isShrunk());

  mcnla_assert_pass(detail::syev(__jobz, toUploChar(_uplo, _trans), size_, a.valPtr(), a.pitch(),
                                 w.valPtr(), work_.valPtr(), work_.len(), rwork_.valPtr()));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Query the optimal workspace size.
///
template <JobOption _jobz, typename _Val, Trans _trans, Uplo _uplo>
index_t DenseSyevDriver<_jobz, _Val, _trans, _uplo>::query(
    const index_t size
) noexcept {
  ValType lwork;
  mcnla_assert_pass(detail::syev(_jobz, toUploChar(_uplo, _trans), size, nullptr, size, nullptr, &lwork, -1, nullptr));
  return lwork;
}

}  // namespace la

}  // namespace mcnla

#endif  // MCNLA_CORE_LA_DENSE_DRIVER_SYEV_HH_
