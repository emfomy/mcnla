////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/lapack/engine/syev.ipp
/// @brief   The implementation of LAPACK SYEV engine.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_LAPACK_ENGINE_SYEV_IPP_
#define MCNLA_CORE_LAPACK_ENGINE_SYEV_IPP_

#include <mcnla/core/lapack/engine/syev.hpp>
#include <mcnla/core/lapack/lapack/syev.hpp>

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
template <class _Matrix, JobOption _jobz>
SyevEngine<_Matrix, _jobz>::SyevEngine() noexcept
  : size_(0),
    work_(),
    rwork_() {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <class _Matrix, JobOption _jobz>
SyevEngine<_Matrix, _jobz>::SyevEngine(
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
SyevEngine<_Matrix, _jobz>::SyevEngine(
    const MatrixType &a
) noexcept
  : SyevEngine(a.nrow()) {
  mcnla_assert_eq(a.nrow(), a.ncol());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  compute
///
template <class _Matrix, JobOption _jobz> template <class _TypeA, class _TypeW>
void SyevEngine<_Matrix, _jobz>::operator()(
    _TypeA &&a,
    _TypeW &&w
) noexcept {
  compute(a, w);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Computes eigenvalues only.
///
template <class _Matrix, JobOption _jobz> template <class _TypeA, class _TypeW>
void SyevEngine<_Matrix, _jobz>::computeValues(
    _TypeA &&a,
    _TypeW &&w
) noexcept {
  compute<'N'>(a, w);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Reconstruct the engine.
///
template <class _Matrix, JobOption _jobz> template <typename... Args>
void SyevEngine<_Matrix, _jobz>::reconstruct(
    Args... args
) noexcept {
  *this = SyevEngine<_Matrix, _jobz>(args...);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the sizes.
///
template <class _Matrix, JobOption _jobz>
std::tuple<index_t> SyevEngine<_Matrix, _jobz>::sizes() const noexcept {
  return std::make_tuple(size_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the workspace
///
template <class _Matrix, JobOption _jobz>
VectorT<_Matrix>& SyevEngine<_Matrix, _jobz>::getWork() noexcept {
  return work_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getWork
///
template <class _Matrix, JobOption _jobz>
const VectorT<_Matrix>& SyevEngine<_Matrix, _jobz>::getWork() const noexcept {
  return work_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the real workspace
///
template <class _Matrix, JobOption _jobz>
RealT<VectorT<_Matrix>>& SyevEngine<_Matrix, _jobz>::getRwork() noexcept {
  return rwork_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getRwork
///
template <class _Matrix, JobOption _jobz>
const RealT<VectorT<_Matrix>>& SyevEngine<_Matrix, _jobz>::getRwork() const noexcept {
  return rwork_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Computes the eigenvalue decomposition.
///
/// @attention  The eigenvectors are Stored in columnwise for column-major storage, in rowwise for row-major storage.
/// @attention  Matrix @a a will be destroyed!
///
template <class _Matrix, JobOption _jobz> template <JobOption __jobz>
void SyevEngine<_Matrix, _jobz>::compute(
    MatrixType &a,
    RealVectorType &w
) noexcept {
  mcnla_assert_gt(size_, 0);
  mcnla_assert_eq(a.sizes(), std::make_tuple(size_, size_));
  mcnla_assert_eq(w.length(), a.nrow());
  mcnla_assert_eq(detail::syev(__jobz, toUploChar(uplo, trans), a.nrow(), a.valuePtr(), a.pitch(),
                               w.valuePtr(), work_.valuePtr(), work_.length(), rwork_.valuePtr()), 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Query the optimal workspace size.
///
template <class _Matrix, JobOption _jobz>
index_t SyevEngine<_Matrix, _jobz>::query(
    const index_t size
) noexcept {
  ScalarType lwork;
  mcnla_assert_eq(detail::syev(_jobz, toUploChar(uplo, trans), size, nullptr, size, nullptr, &lwork, -1, nullptr), 0);
  return lwork;
}

}  // namespace lapack

}  // namespace mcnla

#endif  // MCNLA_CORE_LAPACK_ENGINE_SYEV_IPP_
