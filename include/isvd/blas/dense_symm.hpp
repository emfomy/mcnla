////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/blas/dense_symm.hpp
/// @brief   The BLAS SYMM routine for dense matrices
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_BLAS_DENSE_SYMM_HPP_
#define ISVD_BLAS_DENSE_SYMM_HPP_

#include <utility>
#include <isvd/matrix.hpp>
#include <isvd/blas/blas.hpp>

#ifndef DOXYGEN_SHOULD_SKIP_THIS

extern "C" {

#include <isvd/plugin/blas_plugin_start.h>

// Computes a matrix-matrix product where one input matrix is symmetric.
extern void ssymm_( const FORTRAN_CHAR1 side, const FORTRAN_CHAR1 uplo, const FORTRAN_INT8 m, const FORTRAN_INT8 n,
                    const FORTRAN_REAL4 alpha, const FORTRAN_REAL4 a, const FORTRAN_INT8 lda, const FORTRAN_REAL4 b,
                    const FORTRAN_INT8 ldb, const FORTRAN_REAL4 beta, FORTRAN_REAL4 c, const FORTRAN_INT8 ldc );
extern void dsymm_( const FORTRAN_CHAR1 side, const FORTRAN_CHAR1 uplo, const FORTRAN_INT8 m, const FORTRAN_INT8 n,
                    const FORTRAN_REAL8 alpha, const FORTRAN_REAL8 a, const FORTRAN_INT8 lda, const FORTRAN_REAL8 b,
                    const FORTRAN_INT8 ldb, const FORTRAN_REAL8 beta, FORTRAN_REAL8 c, const FORTRAN_INT8 ldc );

// Computes a matrix-matrix product where one input matrix is Hermitian.
extern void chemm_( const FORTRAN_CHAR1 side, const FORTRAN_CHAR1 uplo, const FORTRAN_INT8 m, const FORTRAN_INT8 n,
                    const FORTRAN_COMP4 alpha, const FORTRAN_COMP4 a, const FORTRAN_INT8 lda, const FORTRAN_COMP4 b,
                    const FORTRAN_INT8 ldb, const FORTRAN_COMP4 beta, FORTRAN_COMP4 c, const FORTRAN_INT8 ldc );
extern void zhemm_( const FORTRAN_CHAR1 side, const FORTRAN_CHAR1 uplo, const FORTRAN_INT8 m, const FORTRAN_INT8 n,
                    const FORTRAN_COMP8 alpha, const FORTRAN_COMP8 a, const FORTRAN_INT8 lda, const FORTRAN_COMP8 b,
                    const FORTRAN_INT8 ldb, const FORTRAN_COMP8 beta, FORTRAN_COMP8 c, const FORTRAN_INT8 ldc );

#include <isvd/plugin/blas_plugin_end.h>

}  // extern "C"

#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The BLAS namespace
//
namespace blas {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The internal namespace
//
namespace internal {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc isvd::blas::symm
///
//@{
static inline void symm(
    const char side, const char uplo, const index_t m, const index_t n,
    const float alpha, const float *a, const index_t lda, const float *b, const index_t ldb,
    const float beta, float *c, const index_t ldc
) noexcept {
  ssymm_(&side, &uplo, &m, &n, &alpha, a, &lda, b, &ldb, &beta, c, &ldc);
}
static inline void symm(
    const char side, const char uplo, const index_t m, const index_t n,
    const double alpha, const double *a, const index_t lda, const double *b, const index_t ldb,
    const double beta, double *c, const index_t ldc
) noexcept {
  dsymm_(&side, &uplo, &m, &n, &alpha, a, &lda, b, &ldb, &beta, c, &ldc);
}
static inline void symm(
    const char side, const char uplo, const index_t m, const index_t n,
    const std::complex<float> alpha, const std::complex<float> *a, const index_t lda,
    const std::complex<float> *b, const index_t ldb,
    const std::complex<float> beta, std::complex<float> *c, const index_t ldc
) noexcept {
  chemm_(&side, &uplo, &m, &n, &alpha, a, &lda, b, &ldb, &beta, c, &ldc);
}
static inline void symm(
    const char side, const char uplo, const index_t m, const index_t n,
    const std::complex<double> alpha, const std::complex<double> *a, const index_t lda,
    const std::complex<double> *b, const index_t ldb,
    const std::complex<double> beta, std::complex<double> *c, const index_t ldc
) noexcept {
  zhemm_(&side, &uplo, &m, &n, &alpha, a, &lda, b, &ldb, &beta, c, &ldc);
}
//@}

}  // namespace internal

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Computes a matrix-matrix product where one input matrix is symmetric/Hermitian.
///
//@{
template <SideOption _side,
          UploOption _uplo = UploOption::LOWER, typename _Scalar, Layout _layout>
inline void symm(
    const typename DenseMatrix<_Scalar, _layout>::ScalarType alpha,
    const DenseMatrix<_Scalar, _layout> &a,
    const DenseMatrix<_Scalar, _layout> &b,
    const typename DenseMatrix<_Scalar, _layout>::ScalarType beta,
          DenseMatrix<_Scalar, _layout> &c
) noexcept {
  if ( isColMajor(_layout) ) {
    if ( isLeftSide(_side) ) {
      assert(a.getNrow() == a.getNcol());
      assert(a.getNrow() == c.getNrow());
      assert(b.getNrow() == c.getNrow());
      assert(b.getNcol() == c.getNcol());
    } else {
      assert(b.getNrow() == b.getNcol());
      assert(b.getNcol() == c.getNcol());
      assert(a.getNrow() == c.getNrow());
      assert(a.getNcol() == c.getNcol());
    }
    internal::symm(SideChar<_side, _layout>::value, UploChar<_uplo, _layout>::value, c.getNrow(), c.getNcol(),
                   alpha, a.getValue(), a.getPitch(), b.getValue(), b.getPitch(),
                   beta, c.getValue(), c.getPitch());
  } else {
    if ( isRightSide(_side) ) {
      assert(b.getNcol() == b.getNrow());
      assert(b.getNcol() == c.getNcol());
      assert(a.getNcol() == c.getNcol());
      assert(a.getNrow() == c.getNrow());
    } else {
      assert(a.getNcol() == a.getNrow());
      assert(a.getNrow() == c.getNrow());
      assert(b.getNcol() == c.getNcol());
      assert(b.getNrow() == c.getNrow());
    }
    internal::symm(SideChar<_side, _layout>::value, UploChar<_uplo, _layout>::value, c.getNcol(), c.getNrow(),
                   alpha, b.getValue(), b.getPitch(), a.getValue(), a.getPitch(),
                   beta, c.getValue(), c.getPitch());
  }
}

template <SideOption _side,
          UploOption _uplo = UploOption::LOWER, typename _Scalar, Layout _layout>
inline void symm(
    const typename DenseMatrix<_Scalar, _layout>::ScalarType alpha,
    const DenseMatrix<_Scalar, _layout> &a,
    const DenseMatrix<_Scalar, _layout> &b,
    const typename DenseMatrix<_Scalar, _layout>::ScalarType beta,
          DenseMatrix<_Scalar, _layout> &&c
) noexcept {
  symm<_side, _uplo>(alpha, a, b, beta, c);
}
//@}

}  // namespace blas

}  // namespace isvd

#endif  // ISVD_BLAS_DENSE_SYMM_HPP_
