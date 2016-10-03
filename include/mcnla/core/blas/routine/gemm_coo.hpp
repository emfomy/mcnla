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
template <TransOption _transa = TransOption::NORMAL, TransOption _transb = TransOption::NORMAL,
          typename _Scalar, Layout _layouta, Layout _layoutb, Layout _layoutc>
inline void gemm(
    const typename DenseMatrix<_Scalar, _layoutc>::ScalarType alpha,
    const CooMatrix<_Scalar, _layouta>   &a,
    const DenseMatrix<_Scalar, _layoutb> &b,
    const typename DenseMatrix<_Scalar, _layoutc>::ScalarType beta,
          DenseMatrix<_Scalar, _layoutc> &c
) noexcept {
  static_assert(!isConjugate(_transa) && !isConjugate(_transb), "Conjugate version is not supported!");

  constexpr int dimb = (isColMajor(_layouta) ^ isTranspose(_transa)) ? 1 : 0;
  constexpr int dimc = (isColMajor(_layouta) ^ isTranspose(_transa)) ? 0 : 1;

  assert(c.getNrow()                   == a.template getNrow<_transa>());
  assert(c.getNcol()                   == b.template getNcol<_transb>());
  assert(a.template getNcol<_transa>() == b.template getNrow<_transb>());

  blas::memset0(c);
  if ( !isTranspose(_transb) ) {
    for ( auto tuple : a ) {
      axpby(alpha * tuple.getValue(), b.getRow(tuple.template getIdx<dimb>()), beta, c.getRow(tuple.template getIdx<dimc>()));
    }
  } else {
    for ( auto tuple : a ) {
      axpby(alpha * tuple.getValue(), b.getCol(tuple.template getIdx<dimb>()), beta, c.getRow(tuple.template getIdx<dimc>()));
    }
  }
}

template <TransOption _transb = TransOption::NORMAL, TransOption _transa = TransOption::NORMAL,
          typename _Scalar, Layout _layoutb, Layout _layouta, Layout _layoutc>
inline void gemm(
    const typename DenseMatrix<_Scalar, _layoutc>::ScalarType alpha,
    const DenseMatrix<_Scalar, _layoutb> &b,
    const CooMatrix<_Scalar, _layouta>   &a,
    const typename DenseMatrix<_Scalar, _layoutc>::ScalarType beta,
          DenseMatrix<_Scalar, _layoutc> &c
) noexcept {
  static_assert(!isConjugate(_transa) && !isConjugate(_transb), "Conjugate version is not supported!");

  constexpr int dimb = (isColMajor(_layouta) ^ isTranspose(_transa)) ? 0 : 1;
  constexpr int dimc = (isColMajor(_layouta) ^ isTranspose(_transa)) ? 1 : 0;

  assert(c.getNcol()                   == a.template getNcol<_transb>());
  assert(c.getNrow()                   == b.template getNrow<_transa>());
  assert(a.template getNrow<_transb>() == b.template getNcol<_transa>());

  blas::memset0(c);
  if ( !isTranspose(_transb) ) {
    for ( auto tuple : a ) {
      axpby(alpha * tuple.getValue(), b.getCol(tuple.template getIdx<dimb>()), beta, c.getCol(tuple.template getIdx<dimc>()));
    }
  } else {
    for ( auto tuple : a ) {
      axpby(alpha * tuple.getValue(), b.getRow(tuple.template getIdx<dimb>()), beta, c.getCol(tuple.template getIdx<dimc>()));
    }
  }
}

template <TransOption _transa = TransOption::NORMAL, TransOption _transb = TransOption::NORMAL,
          typename _Scalar, Layout _layouta, Layout _layoutb, Layout _layoutc>
inline void gemm(
    const typename DenseMatrix<_Scalar, _layoutc>::ScalarType alpha,
    const CooMatrix<_Scalar, _layouta>   &a,
    const DenseMatrix<_Scalar, _layoutb> &b,
    const typename DenseMatrix<_Scalar, _layoutc>::ScalarType beta,
          DenseMatrix<_Scalar, _layoutc> &&c
) noexcept {
  detail::gemm<_transa, _transb>(alpha, a, b, beta, c);
}

template <TransOption _transb = TransOption::NORMAL, TransOption _transa = TransOption::NORMAL,
          typename _Scalar, Layout _layoutb, Layout _layouta, Layout _layoutc>
inline void gemm(
    const typename DenseMatrix<_Scalar, _layoutc>::ScalarType alpha,
    const DenseMatrix<_Scalar, _layoutb> &b,
    const CooMatrix<_Scalar, _layouta>   &a,
    const typename DenseMatrix<_Scalar, _layoutc>::ScalarType beta,
          DenseMatrix<_Scalar, _layoutc> &&c
) noexcept {
  detail::gemm<_transb, _transa>(alpha, b, a, beta, c);
}
//@}

}  // namespace blas

}  // namespace mcnla

#endif  // MCNLA_CORE_BLAS_ROUTINE_GEMM_COO_HPP_
