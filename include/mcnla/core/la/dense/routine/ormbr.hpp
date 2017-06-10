////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/la/dense/routine/ormbr.hpp
/// @brief   The LAPACK ORMBR routine.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_LA_DENSE_ROUTINE_ORMBR_HPP_
#define MCNLA_CORE_LA_DENSE_ROUTINE_ORMBR_HPP_

#include <mcnla/core/la/def.hpp>
#include <mcnla/core/matrix.hpp>
#include <mcnla/core/la/raw/lapack/ormbr.hpp>

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
// Impl3Query
//

template <Vect _vect, typename _Val>
inline void ormbrImpl3(
    const DenseMatrix<_Val, Trans::NORMAL> &a,
    const DenseVector<_Val> &tau,
          DenseMatrix<_Val, Trans::NORMAL> &c,
          _Val &lwork
) noexcept {
  static_cast<void>(tau);
  index_t k = isQ(_vect) ? a.ncol() : a.nrow();
  mcnla_assert_pass(ormbr(toVectChar(_vect), 'L', toTransChar(_vect), c.nrow(), c.ncol(), k,
                          nullptr, a.pitch(), nullptr, nullptr, c.pitch(), &lwork, -1));
}

template <Vect _vect, typename _Val>
inline void ormbrImpl3(
    const DenseMatrix<_Val, Trans::NORMAL> &a,
          DenseMatrix<_Val, Trans::NORMAL> &c,
    const DenseVector<_Val> &tau,
          _Val &lwork
) noexcept {
  static_cast<void>(tau);
  index_t k = isQ(_vect) ? a.ncol() : a.nrow();
  mcnla_assert_pass(ormbr(toVectChar(_vect), 'R', toTransChar(_vect), c.nrow(), c.ncol(), k,
                          nullptr, a.pitch(), nullptr, nullptr, c.pitch(), &lwork, -1));
}

// ========================================================================================================================== //
// Impl3
//

template <Vect _vect, typename _Val>
inline void ormbrImpl3(
    const DenseMatrix<_Val, Trans::NORMAL> &a,
    const DenseVector<_Val> &tau,
          DenseMatrix<_Val, Trans::NORMAL> &c,
          DenseVector<_Val> &work
) noexcept {
  index_t k = isQ(_vect) ? a.ncol() : a.nrow();

  mcnla_assert_eq(c.nrow(), (isQ(_vect) ? a.nrow() : a.ncol()));
  mcnla_assert_eq(tau.len(), std::min(a.nrow(), a.ncol()));
  mcnla_assert_ge(work.len(), c.ncol());
  mcnla_assert_true(tau.isShrunk());
  mcnla_assert_true(work.isShrunk());

  mcnla_assert_pass(ormbr(toVectChar(_vect), 'L', toTransChar(_vect), c.nrow(), c.ncol(), k,
                          a.valPtr(), a.pitch(), tau.valPtr(), c.valPtr(), c.pitch(), work.valPtr(), work.len()));
}

template <Vect _vect, typename _Val>
inline void ormbrImpl3(
    const DenseMatrix<_Val, Trans::NORMAL> &a,
          DenseMatrix<_Val, Trans::NORMAL> &c,
    const DenseVector<_Val> &tau,
          DenseVector<_Val> &work
) noexcept {
  index_t k = isQ(_vect) ? a.ncol() : a.nrow();

  mcnla_assert_eq(c.ncol(), (isQ(_vect) ? a.nrow() : a.ncol()));
  mcnla_assert_eq(tau.len(), std::min(a.nrow(), a.ncol()));
  mcnla_assert_ge(work.len(), c.nrow());
  mcnla_assert_true(tau.isShrunk());
  mcnla_assert_true(work.isShrunk());

  mcnla_assert_pass(ormbr(toVectChar(_vect), 'R', toTransChar(_vect), c.nrow(), c.ncol(), k,
                          a.valPtr(), a.pitch(), tau.valPtr(), c.valPtr(), c.pitch(), work.valPtr(), work.len()));
}

// ========================================================================================================================== //
// Impl2 Left
//

template <Vect _vect, typename _Val, class _Type>
inline void ormbrImpl2(
    const DenseMatrix<_Val, Trans::NORMAL> &a,
    const DenseVector<_Val> &tau,
          DenseMatrix<_Val, Trans::NORMAL> &c,
          _Type &work
) noexcept {
  ormbrImpl3<_vect>(a, tau, c, work);
}

template <Vect _vect, typename _Val, class _Type>
inline void ormbrImpl2(
    const DenseMatrix<_Val, Trans::TRANS> &a,
    const DenseVector<_Val> &tau,
          DenseMatrix<_Val, Trans::NORMAL> &c,
          _Type &work
) noexcept {
  ormbrImpl3<changeQP(_vect)>(a.t(), tau, c, work);
}

template <Vect _vect, typename _Val, Trans _transa, class _Type, bool dummy = 0>
inline void ormbrImpl2(
    const DenseMatrix<_Val, _transa> &a,
    const DenseVector<_Val> &tau,
          DenseMatrix<_Val, Trans::NORMAL> &c,
          _Type &work
) noexcept {
  static_cast<void>(a);
  static_cast<void>(tau);
  static_cast<void>(c);
  static_cast<void>(work);
  static_assert(dummy && false, "ORMBR for conjugate matrices is not implemented!");
}

// ========================================================================================================================== //
// Impl2 Right
//

template <Vect _vect, typename _Val, class _Type>
inline void ormbrImpl2(
    const DenseMatrix<_Val, Trans::NORMAL> &a,
          DenseMatrix<_Val, Trans::NORMAL> &c,
    const DenseVector<_Val> &tau,
          _Type &work
) noexcept {
  ormbrImpl3<_vect>(a, c, tau, work);
}

template <Vect _vect, typename _Val, class _Type>
inline void ormbrImpl2(
    const DenseMatrix<_Val, Trans::TRANS> &a,
          DenseMatrix<_Val, Trans::NORMAL> &c,
    const DenseVector<_Val> &tau,
          _Type &work
) noexcept {
  ormbrImpl3<changeQP(_vect)>(a.t(), c, tau, work);
}

template <Vect _vect, typename _Val, Trans _transa, class _Type, bool dummy = 0>
inline void ormbrImpl2(
    const DenseMatrix<_Val, _transa> &a,
          DenseMatrix<_Val, Trans::NORMAL> &c,
    const DenseVector<_Val> &tau,
          _Type &work
) noexcept {
  static_cast<void>(a);
  static_cast<void>(c);
  static_cast<void>(tau);
  static_cast<void>(work);
  static_assert(dummy && false, "ORMBR for conjugate matrices is not implemented!");
}

// ========================================================================================================================== //
// Impl1 Left
//

template <Vect _vect, typename _Val, Trans _transa, class _Type>
inline void ormbrImpl1(
    const DenseMatrix<_Val, _transa> &a,
    const DenseVector<_Val> &tau,
          DenseMatrix<_Val, Trans::NORMAL> &c,
          _Type &work
) noexcept {
  ormbrImpl2<_vect>(a, tau, c, work);
}

template <Vect _vect, typename _Val, Trans _transa, class _Type>
inline void ormbrImpl1(
    const DenseMatrix<_Val, _transa> &a,
    const DenseVector<_Val> &tau,
          DenseMatrix<_Val, Trans::TRANS> &c,
          _Type &work
) noexcept {
  ormbrImpl2<changeTrans(_vect)>(a, c.t(), tau, work);
}

template <Vect _vect, typename _Val, Trans _transa, Trans _transc, class _Type, bool dummy = 0>
inline void ormbrImpl1(
    const DenseMatrix<_Val, _transa> &a,
    const DenseVector<_Val> &tau,
          DenseMatrix<_Val, _transc> &c,
          _Type &work
) noexcept {
  static_cast<void>(a);
  static_cast<void>(tau);
  static_cast<void>(c);
  static_cast<void>(work);
  static_assert(dummy && false, "ORMBR for conjugate matrices is not implemented!");
}

// ========================================================================================================================== //
// Impl1 Right
//

template <Vect _vect, typename _Val, Trans _transa, class _Type>
inline void ormbrImpl1(
    const DenseMatrix<_Val, _transa> &a,
          DenseMatrix<_Val, Trans::NORMAL> &c,
    const DenseVector<_Val> &tau,
          _Type &work
) noexcept {
  ormbrImpl2<_vect>(a, c, tau, work);
}

template <Vect _vect, typename _Val, Trans _transa, class _Type>
inline void ormbrImpl1(
    const DenseMatrix<_Val, _transa> &a,
          DenseMatrix<_Val, Trans::TRANS> &c,
    const DenseVector<_Val> &tau,
          _Type &work
) noexcept {
  ormbrImpl2<changeTrans(_vect)>(a, tau, c.t(), work);
}

template <Vect _vect, typename _Val, Trans _transa, Trans _transc, class _Type, bool dummy = 0>
inline void ormbrImpl1(
    const DenseMatrix<_Val, _transa> &a,
          DenseMatrix<_Val, _transc> &c,
    const DenseVector<_Val> &tau,
          _Type &work
) noexcept {
  static_cast<void>(a);
  static_cast<void>(c);
  static_cast<void>(tau);
  static_cast<void>(work);
  static_assert(dummy && false, "ORMBR for conjugate matrices is not implemented!");
}

//@}

}  // namespace detail

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  la_dense_lapack_ls_module
/// @brief  Multiplies an arbitrary matrix by the orthogonal/unitary matrix Q or P determined by GEBRD.
///
/// @note  The routine applies Q or P on the left while calling `ormbr(a, tau, c, work)`;
///                          applies on the right while calling `ormbr(a, c, tau, work)`.
///
//@{
template <Vect _vect, typename _Val, Trans _transa, Trans _transc>
inline void ormbr(
    const DenseMatrix<_Val, _transa> &a,
          DenseMatrix<_Val, _transc> &c,
    const DenseVector<_Val> &tau,
          DenseVector<_Val> &work
) noexcept {
  detail::ormbrImpl1<_vect>(a, c, tau, work);
}

template <Vect _vect, typename _Val, Trans _transa, Trans _transc>
inline void ormbr(
    const DenseMatrix<_Val, _transa> &a,
    const DenseVector<_Val> &tau,
          DenseMatrix<_Val, _transc> &c,
          DenseVector<_Val> &work
) noexcept {
  detail::ormbrImpl1<_vect>(a, tau, c, work);
}
//@}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  la_dense_lapack_ls_module
/// @brief  Query the optimal workspace size for ORMBR.
///
//@{
template <Vect _vect, typename _Val, Trans _transa, Trans _transc>
inline index_t ormbrQuery(
    const DenseMatrix<_Val, _transa> &a,
    const DenseVector<_Val> &tau,
    const DenseMatrix<_Val, _transc> &c
) noexcept {
  _Val lwork; detail::ormbrImpl1<_vect>(a, tau, const_cast<DenseMatrix<_Val, _transc>&>(c), lwork); return lwork;
}

template <Vect _vect, typename _Val, Trans _transa, Trans _transc>
inline index_t ormbrQuery(
    const DenseMatrix<_Val, _transa> &a,
    const DenseMatrix<_Val, _transc> &c,
    const DenseVector<_Val> &tau
) noexcept {
  _Val lwork; detail::ormbrImpl1<_vect>(a, const_cast<DenseMatrix<_Val, _transc>&>(c), tau, lwork); return lwork;
}
//@}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <Vect _vect, typename _Val, Trans _transa, class _TypeC, class _TypeWork>
inline void ormbr(
    const DenseMatrix<_Val, _transa> &a,
    const DenseVector<_Val> &tau,
    _TypeC &&c,
    _TypeWork &&work
) noexcept {
  detail::ormbrImpl1<_vect>(a, tau, c, work);
}

template <Vect _vect, typename _Val, Trans _transa, class _TypeC, class _TypeWork>
inline void ormbr(
    const DenseMatrix<_Val, _transa> &a,
    _TypeC &&c,
    const DenseVector<_Val> &tau,
    _TypeWork &&work
) noexcept {
  detail::ormbrImpl1<_vect>(a, c, tau, work);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace la

}  // namespace mcnla

#endif  // MCNLA_CORE_LA_DENSE_ROUTINE_ORMBR_HPP_
