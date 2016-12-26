////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/blas/routine/omatcopy.hpp
/// @brief   The BLAS OMATCOPY routine.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_BLAS_ROUTINE_OMATCOPY_HPP_
#define MCNLA_CORE_BLAS_ROUTINE_OMATCOPY_HPP_

#include <mcnla/core/matrix.hpp>
#include <mcnla/core/blas/blas/omatcopy.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The BLAS namespace
//
namespace blas {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The detail namespace
//
namespace detail {

//@{

// ========================================================================================================================== //
// Impl2
//
template <typename _Scalar, Trans _transb>
inline void omatcopyImpl2(
    const DenseMatrix<_Scalar, Trans::NORMAL> &a,
          DenseMatrix<_Scalar, _transb> &b,
    const _Scalar alpha
) noexcept {
  mcnla_assert_eq(a.getSizes(), b.getSizes());

  omatcopy('C', toTransChar<_Scalar>(_transb), a.getNrow(), a.getNcol(),
           alpha, a.getValuePtr(), a.getPitch(), b.getValuePtr(), b.getPitch());
}

// ========================================================================================================================== //
// Impl1
//

template <typename _Scalar, Trans _transb>
inline void omatcopyImpl1(
    const DenseMatrix<_Scalar, Trans::NORMAL> &a,
          DenseMatrix<_Scalar, _transb> &b,
    const _Scalar alpha
) noexcept {
  omatcopyImpl2(a, b, alpha);
}

template <typename _Scalar, Trans _transb>
inline void omatcopyImpl1(
    const DenseMatrix<_Scalar, Trans::TRANS> &a,
          DenseMatrix<_Scalar, _transb> &b,
    const _Scalar alpha
) noexcept {
  omatcopyImpl2(a.t(), b.t(), alpha);
}

template <typename _Scalar, Trans _transb>
inline void omatcopyImpl1(
    const DenseMatrix<_Scalar, Trans::CONJ> &a,
          DenseMatrix<_Scalar, _transb> &b,
    const _Scalar alpha
) noexcept {
  omatcopyImpl2(a.c(), b.c(), alpha);
}

template <typename _Scalar, Trans _transb>
inline void omatcopyImpl1(
    const DenseMatrix<_Scalar, Trans::HERM> &a,
          DenseMatrix<_Scalar, _transb> &b,
    const _Scalar alpha
) noexcept {
  omatcopyImpl2(a.h(), b.h(), alpha);
}

// ========================================================================================================================== //
// Impl0
//

template <typename _Scalar, Trans _transa, Trans _transb>
inline void omatcopyImpl0(
    const DenseMatrix<_Scalar, _transa> &a,
          DenseMatrix<_Scalar, _transb> &b,
    const _Scalar alpha
) noexcept {
  for ( auto ait = a.cbegin(), bit = b.begin(); ait != a.cend(); ++ait, ++bit ) {
    *bit = alpha * (*ait);
  }
}

//@}

}  // namespace detail

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  blas0_module
/// @brief  Performs scaling and out-place transposition/copying of matrices.
///
template <typename _Scalar, Trans _transa, Trans _transb>
inline void omatcopy(
    const DenseMatrix<_Scalar, _transa> &a,
          DenseMatrix<_Scalar, _transb> &b,
    const typename DenseMatrix<_Scalar, _transb>::ScalarType alpha = 1
) noexcept {
#ifdef MCNLA_USE_MKL
  detail::omatcopyImpl1(a, b, alpha);
#else  // MCNLA_USE_MKL
  detail::omatcopyImpl0(a, b, alpha);
#endif  // MCNLA_USE_MKL
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Scalar, Trans _transa, Trans _transb>
inline void omatcopy(
    const DenseMatrix<_Scalar, _transa> &a,
          DenseMatrix<_Scalar, _transb> &&b,
    const typename DenseMatrix<_Scalar, _transb>::ScalarType alpha = 1
) noexcept {
#ifdef MCNLA_USE_MKL
  detail::omatcopyImpl1(a, b, alpha);
#else  // MCNLA_USE_MKL
  detail::omatcopyImpl0(a, b, alpha);
#endif  // MCNLA_USE_MKL
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  blas_module
/// @brief  Copies a container to another container.
///
template <typename _Scalar, Trans _transa, Trans _transb>
inline void copy(
    const DenseMatrix<_Scalar, _transa> &a,
          DenseMatrix<_Scalar, _transb> &b
) noexcept {
  omatcopy(a, b, 1);
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Scalar, Trans _transa, Trans _transb>
inline void omatcopy(
    const DenseMatrix<_Scalar, _transa> &a,
          DenseMatrix<_Scalar, _transb> &&b
) noexcept {
  omatcopy(a, b, 1);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace blas

}  // namespace mcnla

#endif  // MCNLA_CORE_BLAS_ROUTINE_OMATCOPY_HPP_
