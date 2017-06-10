////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/la/dense/routine/gebrd.hpp
/// @brief   The LAPACK GEBRD routine.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_LA_DENSE_ROUTINE_GEBRD_HPP_
#define MCNLA_CORE_LA_DENSE_ROUTINE_GEBRD_HPP_

#include <mcnla/core/la/def.hpp>
#include <mcnla/core/matrix.hpp>
#include <mcnla/core/la/raw/lapack/gebrd.hpp>

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
inline void gebrdImpl2(
    DenseMatrix<_Val, Trans::NORMAL> &a,
    DenseVector<RealValT<_Val>> &d,
    DenseVector<RealValT<_Val>> &e,
    DenseVector<_Val> &tauq,
    DenseVector<_Val> &taup,
    DenseVector<_Val> &work
) noexcept {
  mcnla_assert_eq(d.len(),    std::min(a.nrow(), a.ncol()));
  mcnla_assert_eq(e.len(),    std::min(a.nrow(), a.ncol())-1);
  mcnla_assert_eq(tauq.len(), std::min(a.nrow(), a.ncol()));
  mcnla_assert_eq(taup.len(), std::min(a.nrow(), a.ncol()));
  mcnla_assert_ge(work.len(), std::max(a.nrow(), a.ncol()));
  mcnla_assert_true(d.isShrunk());
  mcnla_assert_true(e.isShrunk());
  mcnla_assert_true(tauq.isShrunk());
  mcnla_assert_true(taup.isShrunk());
  mcnla_assert_true(work.isShrunk());

  mcnla_assert_pass(gebrd(a.nrow(), a.ncol(), a.valPtr(), a.pitch(), d.valPtr(), e.valPtr(), tauq.valPtr(), taup.valPtr(),
                          work.valPtr(), work.len()));
}

// ========================================================================================================================== //
// Impl1
//

template <typename _Val>
inline void gebrdImpl1(
    DenseMatrix<_Val, Trans::NORMAL> &a,
    DenseVector<RealValT<_Val>> &d,
    DenseVector<RealValT<_Val>> &e,
    DenseVector<_Val> &tauq,
    DenseVector<_Val> &taup,
    DenseVector<_Val> &work
) noexcept {
  gebrdImpl2(a, d, e, tauq, taup, work);
}

template <typename _Val>
inline void gebrdImpl1(
    DenseMatrix<_Val, Trans::TRANS> &a,
    DenseVector<RealValT<_Val>> &d,
    DenseVector<RealValT<_Val>> &e,
    DenseVector<_Val> &tauq,
    DenseVector<_Val> &taup,
    DenseVector<_Val> &work
) noexcept {
  gebrdImpl2(a.t(), d, e, taup, tauq, work);
}

template <typename _Val, Trans _trans, bool dummy = 0>
inline void gebrdImpl1(
    DenseMatrix<_Val, _trans> &a,
    DenseVector<RealValT<_Val>> &d,
    DenseVector<RealValT<_Val>> &e,
    DenseVector<_Val> &tauq,
    DenseVector<_Val> &taup,
    DenseVector<_Val> &work
) noexcept {
  static_cast<void>(a);
  static_cast<void>(d);
  static_cast<void>(e);
  static_cast<void>(tauq);
  static_cast<void>(taup);
  static_cast<void>(work);
  static_assert(dummy && false, "GEBRD for conjugate matrices is not implemented!");
}

//@}

//@{

// ========================================================================================================================== //
// QueryImpl2
//

template <typename _Val>
inline index_t gebrdQueryImpl2(
    const DenseMatrix<_Val, Trans::NORMAL> &a
) noexcept {
  _Val lwork;
  mcnla_assert_pass(gebrd(a.nrow(), a.ncol(), nullptr, a.pitch(), nullptr, nullptr, nullptr, nullptr, &lwork, -1));
  return lwork;
}

// ========================================================================================================================== //
// QueryImpl1
//

template <typename _Val>
inline index_t gebrdQueryImpl1(
    const DenseMatrix<_Val, Trans::NORMAL> &a
) noexcept { return gebrdQueryImpl2(a); }

template <typename _Val>
inline index_t gebrdQueryImpl1(
    const DenseMatrix<_Val, Trans::TRANS> &a
) noexcept { return gebrdQueryImpl2(a.t()); }

template <typename _Val>
inline index_t gebrdQueryImpl1(
    const DenseMatrix<_Val, Trans::CONJ> &a
) noexcept { return gebrdQueryImpl2(a.c()); }

template <typename _Val>
inline index_t gebrdQueryImpl1(
    const DenseMatrix<_Val, Trans::HERM> &a
) noexcept { return gebrdQueryImpl2(a.h()); }

//@}

}  // namespace detail

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  la_dense_lapack_ls_module
/// @brief  Reduces a general matrix to bidiagonal form.
///
template <typename _Val, Trans _trans>
inline void gebrd(
    DenseMatrix<_Val, _trans> &a,
    DenseVector<RealValT<_Val>> &d,
    DenseVector<RealValT<_Val>> &e,
    DenseVector<_Val> &tauq,
    DenseVector<_Val> &taup,
    DenseVector<_Val> &work
) noexcept {
  detail::gebrdImpl1(a, d, e, tauq, taup, work);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  la_dense_lapack_ls_module
/// @brief  Query the optimal workspace size for GEBRD.
///
template <typename _Val, Trans _trans>
inline index_t gebrdQuery(
    const DenseMatrix<_Val, _trans> &a
) noexcept {
  return detail::gebrdQueryImpl1(a);
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <class _TypeA, class _TypeD, class _TypeE, class _TypeTauq, class _TypeTaup, class _TypeWork>
inline void gebrd(
    _TypeA &&a,
    _TypeD &&d,
    _TypeE &&e,
    _TypeTauq &&tauq,
    _TypeTaup &&taup,
    _TypeWork &&work
) noexcept {
  detail::gebrdImpl1(a, d, e, tauq, taup, work);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace la

}  // namespace mcnla

#endif  // MCNLA_CORE_LA_DENSE_ROUTINE_GEBRD_HPP_
