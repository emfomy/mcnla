////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/la/dense/routine/bdsqr.hpp
/// @brief   The LAPACK BDSQR routine.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_LA_DENSE_ROUTINE_BDSQR_HPP_
#define MCNLA_CORE_LA_DENSE_ROUTINE_BDSQR_HPP_

#include <mcnla/core/la/def.hpp>
#include <mcnla/core/matrix.hpp>
#include <mcnla/core/la/raw/lapack/bdsqr.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The linear algebra namespace
//
namespace la {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The detail namespace
//
namespace detail {

//@{

// ========================================================================================================================== //
// Impl2
//

template <typename _Val>
inline void bdsqrImpl2(
    const DenseMatrix<_Val, Trans::NORMAL> &a,
          DenseVector<RealValT<_Val>> &d,
          DenseVector<RealValT<_Val>> &e,
          DenseMatrix<_Val, Trans::NORMAL> &u,
          DenseMatrix<_Val, Trans::NORMAL> &vt,
          DenseVector<RealValT<_Val>> &work
) noexcept {
  index_t n = std::min(a.nrow(), a.ncol());
  char uplo = (a.nrow() >= a.ncol()) ? 'U' : 'L';
  mcnla_assert_eq(d.len(), n);
  mcnla_assert_eq(e.len(), n-1);
  mcnla_assert_eq(u.ncol(), n);
  mcnla_assert_eq(vt.nrow(), n);
  mcnla_assert_ge(work.len(), 4*n);
  mcnla_assert_true(d.isShrunk());
  mcnla_assert_true(e.isShrunk());
  mcnla_assert_true(work.isShrunk());

  mcnla_assert_pass(bdsqr(uplo, n, vt.ncol(), u.nrow(), 0, d.valPtr(), e.valPtr(),
                          vt.valPtr(), vt.pitch(), u.valPtr(), u.pitch(), nullptr, 1, work.valPtr()));
}

// ========================================================================================================================== //
// Impl1
//

template <typename _Val>
inline void bdsqrImpl1(
    const DenseMatrix<_Val, Trans::NORMAL> &a,
          DenseVector<RealValT<_Val>> &d,
          DenseVector<RealValT<_Val>> &e,
          DenseMatrix<_Val, Trans::NORMAL> &u,
          DenseMatrix<_Val, Trans::NORMAL> &vt,
          DenseVector<RealValT<_Val>> &work
) noexcept {
  bdsqrImpl2(a, d, e, u, vt, work);
}

template <typename _Val>
inline void bdsqrImpl1(
    const DenseMatrix<_Val, Trans::TRANS> &a,
          DenseVector<RealValT<_Val>> &d,
          DenseVector<RealValT<_Val>> &e,
          DenseMatrix<_Val, Trans::TRANS> &u,
          DenseMatrix<_Val, Trans::TRANS> &vt,
          DenseVector<RealValT<_Val>> &work
) noexcept {
  bdsqrImpl2(a.t(), d, e, vt.t(), u.t(), work);
}

template <typename _Val, Trans _trans, bool dummy = 0>
inline void bdsqrImpl1(
    const DenseMatrix<_Val, _trans> &a,
          DenseVector<RealValT<_Val>> &d,
          DenseVector<RealValT<_Val>> &e,
          DenseMatrix<_Val, _trans> &u,
          DenseMatrix<_Val, _trans> &vt,
          DenseVector<RealValT<_Val>> &work
) noexcept {
  static_cast<void>(a);
  static_cast<void>(d);
  static_cast<void>(e);
  static_cast<void>(u);
  static_cast<void>(vt);
  static_cast<void>(work);
  static_assert(dummy && false, "BDSQR for conjugate matrices is not implemented!");
}

//@}

}  // namespace detail

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  la_dense_lapack_ls_module
/// @brief  Computes the singular value decomposition of a general matrix that has been reduced to bidiagonal form.
///
/// @note @p a is only for determining the size. The value are not referenced.
///
template <typename _Val, Trans _trans>
inline void bdsqr(
    const DenseMatrix<_Val, _trans> &a,
          DenseVector<RealValT<_Val>> &d,
          DenseVector<RealValT<_Val>> &e,
          DenseMatrix<_Val, _trans> &u,
          DenseMatrix<_Val, _trans> &vt,
          DenseVector<RealValT<_Val>> &work
) noexcept {
  detail::bdsqrImpl1(a, d, e, u, vt, work);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  la_dense_lapack_ls_module
/// @brief  Query the optimal workspace size for BDSQR.
///
template <typename _Val, Trans _trans>
inline index_t bdsqrQuery(
    const DenseMatrix<_Val, _trans> &a
) noexcept {
  return 4 * std::min(a.nrow(), a.ncol());
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <class _TypeA, class _TypeD, class _TypeE, class _TypeU, class _TypeVt, class _TypeWork>
inline void bdsqr(
    _TypeA &&a,
    _TypeD &&d,
    _TypeE &&e,
    _TypeU &&u,
    _TypeVt &&vt,
    _TypeWork &&work
) noexcept {
  detail::bdsqrImpl1(a, d, e, u, vt, work);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace la

}  // namespace mcnla

#endif  // MCNLA_CORE_LA_DENSE_ROUTINE_BDSQR_HPP_
