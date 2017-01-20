////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/la/dense/engine/gesvd.hpp
/// @brief   The LAPACK GESVD engine.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_LA_DENSE_ENGINE_GESVD_HPP_
#define MCNLA_CORE_LA_DENSE_ENGINE_GESVD_HPP_

#include <mcnla/core/la/dense/engine/gesvd.hh>
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
template <class _Matrix, JobOption _jobu, JobOption _jobvt>
GesvdEngine<_Matrix, _jobu, _jobvt>::GesvdEngine() noexcept
  : nrow_(0),
    ncol_(0),
    work_(),
    rwork_() {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <class _Matrix, JobOption _jobu, JobOption _jobvt>
GesvdEngine<_Matrix, _jobu, _jobvt>::GesvdEngine(
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
template <class _Matrix, JobOption _jobu, JobOption _jobvt>
GesvdEngine<_Matrix, _jobu, _jobvt>::GesvdEngine(
    const MatrixType &a
) noexcept
  : GesvdEngine(a.nrow(), a.ncol()) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  compute
///
template <class _Matrix, JobOption _jobu, JobOption _jobvt>
template <class _TypeA, class _TypeS, class _TypeU, class _TypeVt>
void GesvdEngine<_Matrix, _jobu, _jobvt>::operator()(
    _TypeA &&a,
    _TypeS &&s,
    _TypeU &&u,
    _TypeVt &&vt
) noexcept {
  compute(a, s, u, vt);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Computes singular values only.
///
template <class _Matrix, JobOption _jobu, JobOption _jobvt> template <class _TypeA, class _TypeS>
void GesvdEngine<_Matrix, _jobu, _jobvt>::computeValues(
    _TypeA &&a,
    _TypeS &&s
) noexcept {
  compute<'N', 'N'>(a, s, matrix_empty_, matrix_empty_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Reconstruct the engine.
///
template <class _Matrix, JobOption _jobu, JobOption _jobvt> template <typename... Args>
void GesvdEngine<_Matrix, _jobu, _jobvt>::reconstruct(
    Args... args
) noexcept {
  *this = GesvdEngine<_Matrix, _jobu, _jobvt>(args...);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the sizes.
///
template <class _Matrix, JobOption _jobu, JobOption _jobvt>
std::tuple<index_t, index_t> GesvdEngine<_Matrix, _jobu, _jobvt>::sizes() const noexcept {
  return std::make_tuple(nrow_, ncol_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the workspace
///
template <class _Matrix, JobOption _jobu, JobOption _jobvt>
VectorT<_Matrix>& GesvdEngine<_Matrix, _jobu, _jobvt>::getWork() noexcept {
  return work_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getWork
///
template <class _Matrix, JobOption _jobu, JobOption _jobvt>
const VectorT<_Matrix>& GesvdEngine<_Matrix, _jobu, _jobvt>::getWork() const noexcept {
  return work_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the real workspace
///
template <class _Matrix, JobOption _jobu, JobOption _jobvt>
RealT<VectorT<_Matrix>>& GesvdEngine<_Matrix, _jobu, _jobvt>::getRwork() noexcept {
  return rwork_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getRwork
///
template <class _Matrix, JobOption _jobu, JobOption _jobvt>
const RealT<VectorT<_Matrix>>& GesvdEngine<_Matrix, _jobu, _jobvt>::getRwork() const noexcept {
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
template <class _Matrix, JobOption _jobu, JobOption _jobvt>
template <JobOption __jobu, JobOption __jobvt>
void GesvdEngine<_Matrix, _jobu, _jobvt>::compute(
    MatrixType &a,
    RealVectorType &s,
    MatrixType &u,
    MatrixType &vt
) noexcept {
  mcnla_assert_gt(nrow_, 0);
  mcnla_assert_gt(ncol_, 0);
  mcnla_assert_eq(a.sizes(),  std::make_tuple(nrow_, ncol_));
  mcnla_assert_eq(s.length(), std::min(nrow_, ncol_));

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

  if ( !isTrans(trans) ) {
    mcnla_assert_eq(detail::gesvd(__jobu, __jobvt, a.nrow(), a.ncol(), a.valuePtr(), a.pitch(),
                                  s.valuePtr(), u.valuePtr(), u_pitch, vt.valuePtr(), vt_pitch,
                                  work_.valuePtr(), work_.length(), rwork_.valuePtr()), 0);
  } else {
    mcnla_assert_eq(detail::gesvd(__jobvt, __jobu, a.ncol(), a.nrow(), a.valuePtr(), a.pitch(),
                                  s.valuePtr(), vt.valuePtr(), vt_pitch, u.valuePtr(), u_pitch,
                                  work_.valuePtr(), work_.length(), rwork_.valuePtr()), 0);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Query the optimal workspace size.
///
template <class _Matrix, JobOption _jobu, JobOption _jobvt>
index_t GesvdEngine<_Matrix, _jobu, _jobvt>::query(
    const index_t nrow, const index_t ncol
) noexcept {
  ScalarType lwork;
  if ( !isTrans(trans) ) {
    mcnla_assert_eq(detail::gesvd(_jobu, _jobvt, nrow, ncol, nullptr, nrow, nullptr,
                                  nullptr, nrow, nullptr, ncol, &lwork, -1, nullptr), 0);
  } else {
    mcnla_assert_eq(detail::gesvd(_jobvt, _jobu, ncol, nrow, nullptr, ncol, nullptr,
                                  nullptr, ncol, nullptr, nrow, &lwork, -1, nullptr), 0);
  }
  return lwork;
}

}  // namespace la

}  // namespace mcnla

#endif  // MCNLA_CORE_LA_DENSE_ENGINE_GESVD_HPP_
