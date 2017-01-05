////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/blas/routine/gemm_coo.hpp
/// @brief   The BLAS GEMM routine for COO types.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_BLAS_ROUTINE_GEMM_COO_HPP_
#define MCNLA_CORE_BLAS_ROUTINE_GEMM_COO_HPP_

#include <mcnla/core/matrix.hpp>
#include <mcnla/core/blas/routine/axpby.hpp>
#include <mcnla/core/blas/routine/memset0.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The BLAS namespace
//
namespace blas {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  blas3_module
/// @brief  Computes a matrix-matrix product where one input matrix is general COO matrix.
///
//@{
template <Trans _transa = Trans::NORMAL, Trans _transb = Trans::NORMAL,
          typename _Scalar, Layout _layouta, Layout _layoutb, Layout _layoutc>
inline void gemm(
    const ScalarT<DenseMatrix<_Scalar, _layoutc>> alpha,
    const CooMatrix<_Scalar, _layouta>   &a,
    const DenseMatrix<_Scalar, _layoutb> &b,
    const ScalarT<DenseMatrix<_Scalar, _layoutc>> beta,
          DenseMatrix<_Scalar, _layoutc> &c
) noexcept {
  static_assert(!isConj(_transa) && !isConj(_transb), "Conjugate version is not supported!");

  constexpr int dimb = (isColMajor(_layouta) ^ isTrans(_transa)) ? 1 : 0;
  constexpr int dimc = (isColMajor(_layouta) ^ isTrans(_transa)) ? 0 : 1;

  mcnla_assert_eq(c.nrow(),                   a.template nrow<_transa>());
  mcnla_assert_eq(c.ncol(),                   b.template ncol<_transb>());
  mcnla_assert_eq(a.template ncol<_transa>(), b.template nrow<_transb>());

  blas::memset0(c);
  if ( !isTrans(_transb) ) {
    for ( auto tuple : a ) {
      axpby(alpha * tuple.valuePtr(), b.getRow(tuple.template idx<dimb>()), beta, c.getRow(tuple.template idx<dimc>()));
    }
  } else {
    for ( auto tuple : a ) {
      axpby(alpha * tuple.valuePtr(), b.getCol(tuple.template idx<dimb>()), beta, c.getRow(tuple.template idx<dimc>()));
    }
  }
}

template <Trans _transb = Trans::NORMAL, Trans _transa = Trans::NORMAL,
          typename _Scalar, Layout _layoutb, Layout _layouta, Layout _layoutc>
inline void gemm(
    const ScalarT<DenseMatrix<_Scalar, _layoutc>> alpha,
    const DenseMatrix<_Scalar, _layoutb> &b,
    const CooMatrix<_Scalar, _layouta>   &a,
    const ScalarT<DenseMatrix<_Scalar, _layoutc>> beta,
          DenseMatrix<_Scalar, _layoutc> &c
) noexcept {
  static_assert(!isConj(_transa) && !isConj(_transb), "Conjugate version is not supported!");

  constexpr int dimb = (isColMajor(_layouta) ^ isTrans(_transa)) ? 0 : 1;
  constexpr int dimc = (isColMajor(_layouta) ^ isTrans(_transa)) ? 1 : 0;

  mcnla_assert_eq(c.ncol(),                   a.template ncol<_transb>());
  mcnla_assert_eq(c.nrow(),                   b.template nrow<_transa>());
  mcnla_assert_eq(a.template nrow<_transb>(), b.template ncol<_transa>());

  blas::memset0(c);
  if ( !isTrans(_transb) ) {
    for ( auto tuple : a ) {
      axpby(alpha * tuple.valuePtr(), b.getCol(tuple.template idx<dimb>()), beta, c.getCol(tuple.template idx<dimc>()));
    }
  } else {
    for ( auto tuple : a ) {
      axpby(alpha * tuple.valuePtr(), b.getRow(tuple.template idx<dimb>()), beta, c.getCol(tuple.template idx<dimc>()));
    }
  }
}
//@}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <Trans _transa = Trans::NORMAL, Trans _transb = Trans::NORMAL,
          typename _Scalar, Layout _layouta, Layout _layoutb, Layout _layoutc>
inline void gemm(
    const ScalarT<DenseMatrix<_Scalar, _layoutc>> alpha,
    const CooMatrix<_Scalar, _layouta>   &a,
    const DenseMatrix<_Scalar, _layoutb> &b,
    const ScalarT<DenseMatrix<_Scalar, _layoutc>> beta,
          DenseMatrix<_Scalar, _layoutc> &&c
) noexcept {
  detail::gemm<_transa, _transb>(alpha, a, b, beta, c);
}

template <Trans _transb = Trans::NORMAL, Trans _transa = Trans::NORMAL,
          typename _Scalar, Layout _layoutb, Layout _layouta, Layout _layoutc>
inline void gemm(
    const ScalarT<DenseMatrix<_Scalar, _layoutc>> alpha,
    const DenseMatrix<_Scalar, _layoutb> &b,
    const CooMatrix<_Scalar, _layouta>   &a,
    const ScalarT<DenseMatrix<_Scalar, _layoutc>> beta,
          DenseMatrix<_Scalar, _layoutc> &&c
) noexcept {
  detail::gemm<_transb, _transa>(alpha, b, a, beta, c);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace blas

}  // namespace mcnla

#endif  // MCNLA_CORE_BLAS_ROUTINE_GEMM_COO_HPP_
