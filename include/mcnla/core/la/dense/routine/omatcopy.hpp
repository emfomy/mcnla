////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/la/dense/routine/omatcopy.hpp
/// @brief   The BLAS OMATCOPY routine.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_LA_DENSE_ROUTINE_OMATCOPY_HPP_
#define MCNLA_CORE_LA_DENSE_ROUTINE_OMATCOPY_HPP_

#include <mcnla/core/la/def.hpp>
#include <mcnla/core/matrix.hpp>
#include <mcnla/core/la/dense/routine/copy.hpp>
#include <mcnla/core/la/raw/blas/omatcopy.hpp>

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
template <typename _Val, Trans _transb>
inline void omatcopyImpl2(
    const DenseMatrix<_Val, Trans::NORMAL> &a,
          DenseMatrix<_Val, _transb> &b,
    const _Val alpha
) noexcept {
  mcnla_assert_eq(a.sizes(), b.sizes());

  omatcopy('C', toTransChar<_Val>(_transb), a.nrow(), a.ncol(),
           alpha, a.valPtr(), a.pitch(), b.valPtr(), b.pitch());
}

// ========================================================================================================================== //
// Impl1
//

template <typename _Val, Trans _transb>
inline void omatcopyImpl1(
    const DenseMatrix<_Val, Trans::NORMAL> &a,
          DenseMatrix<_Val, _transb> &b,
    const _Val alpha
) noexcept {
  omatcopyImpl2(a, b, alpha);
}

template <typename _Val, Trans _transb>
inline void omatcopyImpl1(
    const DenseMatrix<_Val, Trans::TRANS> &a,
          DenseMatrix<_Val, _transb> &b,
    const _Val alpha
) noexcept {
  omatcopyImpl2(a.t(), b.t(), alpha);
}

template <typename _Val, Trans _transb>
inline void omatcopyImpl1(
    const DenseMatrix<_Val, Trans::CONJ> &a,
          DenseMatrix<_Val, _transb> &b,
    const _Val alpha
) noexcept {
  omatcopyImpl2(a.c(), b.c(), alpha);
}

template <typename _Val, Trans _transb>
inline void omatcopyImpl1(
    const DenseMatrix<_Val, Trans::HERM> &a,
          DenseMatrix<_Val, _transb> &b,
    const _Val alpha
) noexcept {
  omatcopyImpl2(a.h(), b.h(), alpha);
}

// ========================================================================================================================== //
// Impl0
//

template <typename _Val, Trans _transa, Trans _transb>
inline void omatcopyImpl0(
    const DenseMatrix<_Val, _transa> &a,
          DenseMatrix<_Val, _transb> &b,
    const _Val alpha
) noexcept {
  for ( auto ait = a.cbegin(), bit = b.begin(); ait != a.cend(); ++ait, ++bit ) {
    *bit = alpha * (*ait);
  }
}

//@}

}  // namespace detail

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  la_dense_blas1m_module
/// @brief  Performs scaling and out-place transposition/copying of matrices.
///
template <typename _Val, Trans _transa, Trans _transb>
inline void omatcopy(
    const DenseMatrix<_Val, _transa> &a,
          DenseMatrix<_Val, _transb> &b,
    const ValT<DenseMatrix<_Val, _transb>> alpha = 1
) noexcept {
#ifdef MCNLA_USE_MKL
  detail::omatcopyImpl1(a, b, alpha);
#else  // MCNLA_USE_MKL
  detail::omatcopyImpl0(a, b, alpha);
#endif  // MCNLA_USE_MKL
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Val, Trans _transa, Trans _transb>
inline void omatcopy(
    const DenseMatrix<_Val, _transa> &a,
          DenseMatrix<_Val, _transb> &&b,
    const ValT<DenseMatrix<_Val, _transb>> alpha = 1
) noexcept {
#ifdef MCNLA_USE_MKL
  detail::omatcopyImpl1(a, b, alpha);
#else  // MCNLA_USE_MKL
  detail::omatcopyImpl0(a, b, alpha);
#endif  // MCNLA_USE_MKL
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  la_dense_blas1m_module
/// @brief  Copies a matrix to another matrix.
///
/// @note  This routines calls @ref copy "copy"(a.vectorize(), b.vectorize()) if both @a a and @a b are shrunk,
///        otherwise it calls @ref omatcopy "omatcopy"(a, b, 1).
///
template <typename _Val, Trans _transa, Trans _transb>
inline void copy(
    const DenseMatrix<_Val, _transa> &a,
          DenseMatrix<_Val, _transb> &b
) noexcept {
  if ( a.isShrunk() && b.isShrunk() ) {
    copy(a.vectorize(), b.vectorize());
  } else {
    omatcopy(a, b, 1);
  }
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Val, Trans _transa, Trans _transb>
inline void copy(
    const DenseMatrix<_Val, _transa> &a,
          DenseMatrix<_Val, _transb> &&b
) noexcept {
  if ( a.isShrunk() && b.isShrunk() ) {
    copy(a.vectorize(), b.vectorize());
  } else {
    omatcopy(a, b, 1);
  }
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace la

}  // namespace mcnla

#endif  // MCNLA_CORE_LA_DENSE_ROUTINE_OMATCOPY_HPP_
