////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/la/dense/driver/gesvd.hpp
/// @brief   The LAPACK GESVD driver.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_LA_DENSE_DRIVER_GESVD_HPP_
#define MCNLA_CORE_LA_DENSE_DRIVER_GESVD_HPP_

#include <mcnla/core/la/dense/driver/gesvd.hh>
#include <mcnla/core/la/raw/lapack/gesvd.hpp>

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
template <JobOption _jobu, JobOption _jobvt, typename _Val, Trans _trans>
DenseGesvdDriver<_jobu, _jobvt, _Val, _trans>::DenseGesvdDriver() noexcept
  : nrow_(0),
    ncol_(0),
    work_(),
    rwork_() {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <JobOption _jobu, JobOption _jobvt, typename _Val, Trans _trans>
DenseGesvdDriver<_jobu, _jobvt, _Val, _trans>::DenseGesvdDriver(
    const index_t nrow, const index_t ncol
) noexcept
  : nrow_(nrow),
    ncol_(ncol),
    work_(query(nrow, ncol)),
    rwork_(is_real ? RealVectorType() : RealVectorType(5 * std::min(nrow, ncol))) {
  mcnla_assert_gt(nrow_, 0);
  mcnla_assert_gt(ncol_, 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <JobOption _jobu, JobOption _jobvt, typename _Val, Trans _trans>
DenseGesvdDriver<_jobu, _jobvt, _Val, _trans>::DenseGesvdDriver(
    const MatrixType &a
) noexcept
  : DenseGesvdDriver(a.nrow(), a.ncol()) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  compute
///
template <JobOption _jobu, JobOption _jobvt, typename _Val, Trans _trans>
#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <class _TypeA, class _TypeS, class _TypeU, class _TypeVt>
void DenseGesvdDriver<_jobu, _jobvt, _Val, _trans>::operator()(
    _TypeA &&a,
    _TypeS &&s,
    _TypeU &&u,
    _TypeVt &&vt
#else  // DOXYGEN_SHOULD_SKIP_THIS
void DenseGesvdDriver<_jobu, _jobvt, _Val, _trans>::operator()(
    MatrixType &a,
    VectorType &s,
    MatrixType &u,
    MatrixType &vt
#endif  // DOXYGEN_SHOULD_SKIP_THIS
) noexcept {
  compute(a, s, u, vt);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Computes singular values only.
///
template <JobOption _jobu, JobOption _jobvt, typename _Val, Trans _trans>
#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <class _TypeA, class _TypeS>
void DenseGesvdDriver<_jobu, _jobvt, _Val, _trans>::computeValues(
    _TypeA &&a,
    _TypeS &&s
#else  // DOXYGEN_SHOULD_SKIP_THIS
void DenseGesvdDriver<_jobu, _jobvt, _Val, _trans>::computeValues(
    MatrixType &a,
    VectorType &s
#endif  // DOXYGEN_SHOULD_SKIP_THIS
) noexcept {
  compute<'N', 'N'>(a, s, matrix_empty_, matrix_empty_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Reconstruct the driver.
///
template <JobOption _jobu, JobOption _jobvt, typename _Val, Trans _trans> template <typename ..._Args>
void DenseGesvdDriver<_jobu, _jobvt, _Val, _trans>::reconstruct(
    _Args... args
) noexcept {
  *this = DenseGesvdDriver<_jobu, _jobvt, _Val, _trans>(args...);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the sizes.
///
template <JobOption _jobu, JobOption _jobvt, typename _Val, Trans _trans>
std::tuple<index_t, index_t> DenseGesvdDriver<_jobu, _jobvt, _Val, _trans>::sizes() const noexcept {
  return std::make_tuple(nrow_, ncol_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the workspace
///
template <JobOption _jobu, JobOption _jobvt, typename _Val, Trans _trans>
DenseVector<_Val>& DenseGesvdDriver<_jobu, _jobvt, _Val, _trans>::getWork() noexcept {
  return work_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getWork
///
template <JobOption _jobu, JobOption _jobvt, typename _Val, Trans _trans>
const DenseVector<_Val>& DenseGesvdDriver<_jobu, _jobvt, _Val, _trans>::getWork() const noexcept {
  return work_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the real workspace
///
template <JobOption _jobu, JobOption _jobvt, typename _Val, Trans _trans>
DenseVector<RealValT<_Val>>& DenseGesvdDriver<_jobu, _jobvt, _Val, _trans>::getRwork() noexcept {
  return rwork_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getRwork
///
template <JobOption _jobu, JobOption _jobvt, typename _Val, Trans _trans>
const DenseVector<RealValT<_Val>>& DenseGesvdDriver<_jobu, _jobvt, _Val, _trans>::getRwork() const noexcept {
  return rwork_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Computes the singular value decomposition.
///
/// @attention  The left singular vectors are stored in column-wise for column-major storage,
///                                                  in row-wise for row-major storage.
/// @attention  The right singular vectors are stored in row-wise for column-major storage,
///                                                   in column-wise for row-major storage.
/// @attention  Matrix @a a will be destroyed!
///
template <JobOption _jobu, JobOption _jobvt, typename _Val, Trans _trans>
template <JobOption __jobu, JobOption __jobvt>
void DenseGesvdDriver<_jobu, _jobvt, _Val, _trans>::compute(
    MatrixType &a,
    RealVectorType &s,
    MatrixType &u,
    MatrixType &vt
) noexcept {
  mcnla_assert_eq(a.sizes(), this->sizes());
  mcnla_assert_eq(s.len(),   std::min(nrow_, ncol_));
  mcnla_assert_true(s.isShrunk());

  if ( __jobu == 'A' ) {
    mcnla_assert_eq(u.sizes(), std::make_tuple(nrow_, nrow_));
  } else if ( __jobu == 'S' ) {
    mcnla_assert_eq(u.sizes(), std::make_tuple(nrow_, std::min(nrow_, ncol_)));
  }

  if ( __jobvt == 'A' ) {
    mcnla_assert_eq(u.sizes(), std::make_tuple(ncol_, ncol_));
  } else if ( __jobvt == 'S' ) {
    mcnla_assert_eq(vt.sizes(), std::make_tuple(std::min(nrow_, ncol_), ncol_));
  }

  auto u_pitch  = (u.pitch()  > 0) ? u.pitch()  : 1;
  auto vt_pitch = (vt.pitch() > 0) ? vt.pitch() : 1;

  if ( !isTrans(_trans) ) {
    mcnla_assert_pass(detail::gesvd(__jobu, __jobvt, nrow_, ncol_, a.valPtr(), a.pitch(),
                                    s.valPtr(), u.valPtr(), u_pitch, vt.valPtr(), vt_pitch,
                                    work_.valPtr(), work_.len(), rwork_.valPtr()));
  } else {
    mcnla_assert_pass(detail::gesvd(__jobvt, __jobu, ncol_, nrow_, a.valPtr(), a.pitch(),
                                    s.valPtr(), vt.valPtr(), vt_pitch, u.valPtr(), u_pitch,
                                    work_.valPtr(), work_.len(), rwork_.valPtr()));
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Query the optimal workspace size.
///
template <JobOption _jobu, JobOption _jobvt, typename _Val, Trans _trans>
index_t DenseGesvdDriver<_jobu, _jobvt, _Val, _trans>::query(
    const index_t nrow, const index_t ncol
) noexcept {
  ValType lwork;
  if ( !isTrans(_trans) ) {
    mcnla_assert_pass(detail::gesvd(_jobu, _jobvt, nrow, ncol, nullptr, nrow, nullptr,
                                    nullptr, nrow, nullptr, ncol, &lwork, -1, nullptr));
  } else {
    mcnla_assert_pass(detail::gesvd(_jobvt, _jobu, ncol, nrow, nullptr, ncol, nullptr,
                                    nullptr, ncol, nullptr, nrow, &lwork, -1, nullptr));
  }
  return lwork;
}

}  // namespace la

}  // namespace mcnla

#endif  // MCNLA_CORE_LA_DENSE_DRIVER_GESVD_HPP_
