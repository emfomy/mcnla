////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/blas/blasf.hpp
/// @brief   The Fortran BLAS routines and functions
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_BLAS_BLASF_HPP_
#define ISVD_BLAS_BLASF_HPP_

#include <complex>
#include <isvd/isvd.hpp>

#ifndef DOXYGEN_SHOULD_SKIP_THIS

extern "C" {

#define CPP_CHAR1 char
#define CPP_INT8  isvd::index_t
#define CPP_REAL4 float
#define CPP_REAL8 double
#define CPP_COMP4 std::complex<float>
#define CPP_COMP8 std::complex<double>

#define FORTRAN_CHAR1 CPP_CHAR1*
#define FORTRAN_INT8  CPP_INT8*
#define FORTRAN_REAL4 CPP_REAL4*
#define FORTRAN_REAL8 CPP_REAL8*
#define FORTRAN_COMP4 CPP_COMP4*
#define FORTRAN_COMP8 CPP_COMP8*

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Level 1 BLAS functions
//

// Computes a vector-vector dot product.
extern CPP_REAL4 sdot_( const FORTRAN_INT8 n, const FORTRAN_REAL4 x, const FORTRAN_INT8 incx, const FORTRAN_REAL4 y, const FORTRAN_INT8 incy );
extern CPP_REAL8 ddot_( const FORTRAN_INT8 n, const FORTRAN_REAL8 x, const FORTRAN_INT8 incx, const FORTRAN_REAL8 y, const FORTRAN_INT8 incy );
extern CPP_REAL8 dsdot_( const FORTRAN_INT8 n, const FORTRAN_REAL4 x, const FORTRAN_INT8 incx, const FORTRAN_REAL4 y, const FORTRAN_INT8 incy );
extern CPP_REAL4 sdsdot_( const FORTRAN_INT8 n, const FORTRAN_REAL4 alpha, const FORTRAN_REAL4 x, const FORTRAN_INT8 incx, const FORTRAN_REAL4 y, const FORTRAN_INT8 incy );

// Computes a vector-vector dot product.
extern CPP_COMP4 cdotu_( const FORTRAN_INT8 n, const FORTRAN_COMP4 x, const FORTRAN_INT8 incx, const FORTRAN_COMP4 y, const FORTRAN_INT8 incy );
extern CPP_COMP8 zdotu_( const FORTRAN_INT8 n, const FORTRAN_COMP8 x, const FORTRAN_INT8 incx, const FORTRAN_COMP8 y, const FORTRAN_INT8 incy );

// Computes a dot product of a conjugated vector with another vector.
extern CPP_COMP4 cdotc_( const FORTRAN_INT8 n, const FORTRAN_COMP4 x, const FORTRAN_INT8 incx, const FORTRAN_COMP4 y, const FORTRAN_INT8 incy );
extern CPP_COMP8 zdotc_( const FORTRAN_INT8 n, const FORTRAN_COMP8 x, const FORTRAN_INT8 incx, const FORTRAN_COMP8 y, const FORTRAN_INT8 incy );

// Computes the Euclidean norm of a vector.
extern CPP_REAL4 snrm2_( const FORTRAN_INT8 n, const FORTRAN_REAL4 x, const FORTRAN_INT8 incx );
extern CPP_REAL8 dnrm2_( const FORTRAN_INT8 n, const FORTRAN_REAL8 x, const FORTRAN_INT8 incx );
extern CPP_REAL4 scnrm2_( const FORTRAN_INT8 n, const FORTRAN_COMP4 x, const FORTRAN_INT8 incx );
extern CPP_REAL8 dznrm2_( const FORTRAN_INT8 n, const FORTRAN_COMP8 x, const FORTRAN_INT8 incx );

// Computes the sum of magnitudes of the vector elements.
extern CPP_REAL4 sasum_( const FORTRAN_INT8 n, const FORTRAN_REAL4 x, const FORTRAN_INT8 incx );
extern CPP_REAL8 dasum_( const FORTRAN_INT8 n, const FORTRAN_REAL8 x, const FORTRAN_INT8 incx );
extern CPP_REAL4 scasum_( const FORTRAN_INT8 n, const FORTRAN_COMP4 x, const FORTRAN_INT8 incx );
extern CPP_REAL8 dzasum_( const FORTRAN_INT8 n, const FORTRAN_COMP8 x, const FORTRAN_INT8 incx );

// Computes the sum of magnitudes of the vector elements.
extern CPP_INT8 isamax_( const FORTRAN_INT8 n, const FORTRAN_REAL4 x, const FORTRAN_INT8 incx );
extern CPP_INT8 idamax_( const FORTRAN_INT8 n, const FORTRAN_REAL8 x, const FORTRAN_INT8 incx );
extern CPP_INT8 icamax_( const FORTRAN_INT8 n, const FORTRAN_COMP4 x, const FORTRAN_INT8 incx );
extern CPP_INT8 izamax_( const FORTRAN_INT8 n, const FORTRAN_COMP8 x, const FORTRAN_INT8 incx );

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Level 1 BLAS routines
//

// Computes the parameters for a Givens rotation.
extern void srotg_( FORTRAN_REAL4 a, FORTRAN_REAL4 b, FORTRAN_REAL4 c, FORTRAN_REAL4 s );
extern void drotg_( FORTRAN_REAL8 a, FORTRAN_REAL8 b, FORTRAN_REAL8 c, FORTRAN_REAL8 s );

// Computes the parameters for a modified Givens rotation.
extern void srotmg_( FORTRAN_REAL4 d1, FORTRAN_REAL4 d2, FORTRAN_REAL4 a, const FORTRAN_REAL4 b, FORTRAN_REAL4 param );
extern void drotmg_( FORTRAN_REAL8 d1, FORTRAN_REAL8 d2, FORTRAN_REAL8 a, const FORTRAN_REAL8 b, FORTRAN_REAL8 param );

// Performs rotation of points in the plane.
extern void srot_( const FORTRAN_INT8 n, FORTRAN_REAL4 x, const FORTRAN_INT8 incx, FORTRAN_REAL4 y, const FORTRAN_INT8 incy, const FORTRAN_REAL4 c, const FORTRAN_REAL4 s );
extern void drot_( const FORTRAN_INT8 n, FORTRAN_REAL8 x, const FORTRAN_INT8 incx, FORTRAN_REAL8 y, const FORTRAN_INT8 incy, const FORTRAN_REAL8 c, const FORTRAN_REAL8 s );

// Performs modified Givens rotation of poFORTRAN_INT8s in the plane.
extern void srotm_( const FORTRAN_INT8 n, FORTRAN_REAL4 x, const FORTRAN_INT8 incx, FORTRAN_REAL4 y, const FORTRAN_INT8 incy, const FORTRAN_REAL4 param );
extern void drotm_( const FORTRAN_INT8 n, FORTRAN_REAL8 x, const FORTRAN_INT8 incx, FORTRAN_REAL8 y, const FORTRAN_INT8 incy, const FORTRAN_REAL8 param );

// Swaps a vector with another vector.
extern void sswap_( const FORTRAN_INT8 n, FORTRAN_REAL4 x, const FORTRAN_INT8 incx, FORTRAN_REAL4 y, const FORTRAN_INT8 incy );
extern void dswap_( const FORTRAN_INT8 n, FORTRAN_REAL8 x, const FORTRAN_INT8 incx, FORTRAN_REAL8 y, const FORTRAN_INT8 incy );
extern void cswap_( const FORTRAN_INT8 n, FORTRAN_COMP4 x, const FORTRAN_INT8 incx, FORTRAN_COMP4 y, const FORTRAN_INT8 incy );
extern void zswap_( const FORTRAN_INT8 n, FORTRAN_COMP8 x, const FORTRAN_INT8 incx, FORTRAN_COMP8 y, const FORTRAN_INT8 incy );

// Computes the product of a vector by a scalar.
extern void sscal_( const FORTRAN_INT8 n, const FORTRAN_REAL4 alpha, FORTRAN_REAL4 x, const FORTRAN_INT8 incx );
extern void dscal_( const FORTRAN_INT8 n, const FORTRAN_REAL8 alpha, FORTRAN_REAL8 x, const FORTRAN_INT8 incx );
extern void cscal_( const FORTRAN_INT8 n, const FORTRAN_COMP4 alpha, FORTRAN_COMP4 x, const FORTRAN_INT8 incx );
extern void zscal_( const FORTRAN_INT8 n, const FORTRAN_COMP8 alpha, FORTRAN_COMP8 x, const FORTRAN_INT8 incx );
extern void csscal_( const FORTRAN_INT8 n, const FORTRAN_REAL4 alpha, FORTRAN_COMP4 x, const FORTRAN_INT8 incx );
extern void zdscal_( const FORTRAN_INT8 n, const FORTRAN_REAL8 alpha, FORTRAN_COMP8 x, const FORTRAN_INT8 incx );

// Copies vector to another vector.
extern void scopy_( const FORTRAN_INT8 n, const FORTRAN_REAL4 x, const FORTRAN_INT8 incx, FORTRAN_REAL4 y, const FORTRAN_INT8 incy );
extern void dcopy_( const FORTRAN_INT8 n, const FORTRAN_REAL8 x, const FORTRAN_INT8 incx, FORTRAN_REAL8 y, const FORTRAN_INT8 incy );
extern void ccopy_( const FORTRAN_INT8 n, const FORTRAN_COMP4 x, const FORTRAN_INT8 incx, FORTRAN_COMP4 y, const FORTRAN_INT8 incy );
extern void zcopy_( const FORTRAN_INT8 n, const FORTRAN_COMP8 x, const FORTRAN_INT8 incx, FORTRAN_COMP8 y, const FORTRAN_INT8 incy );

// Computes a vector-scalar product and adds the result to a vector.
extern void saxpy_( const FORTRAN_INT8 n, const FORTRAN_REAL4 alpha, const FORTRAN_REAL4 x, const FORTRAN_INT8 incx, FORTRAN_REAL4 y, const FORTRAN_INT8 incy );
extern void daxpy_( const FORTRAN_INT8 n, const FORTRAN_REAL8 alpha, const FORTRAN_REAL8 x, const FORTRAN_INT8 incx, FORTRAN_REAL8 y, const FORTRAN_INT8 incy );
extern void caxpy_( const FORTRAN_INT8 n, const FORTRAN_COMP4 alpha, const FORTRAN_COMP4 x, const FORTRAN_INT8 incx, FORTRAN_COMP4 y, const FORTRAN_INT8 incy );
extern void zaxpy_( const FORTRAN_INT8 n, const FORTRAN_COMP8 alpha, const FORTRAN_COMP8 x, const FORTRAN_INT8 incx, FORTRAN_COMP8 y, const FORTRAN_INT8 incy );

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Level 2 BLAS routines
//

// Computes a matrix-vector product using a general matrix.
extern void sgemv_( const FORTRAN_CHAR1 trans, const FORTRAN_INT8 m, const FORTRAN_INT8 n, const FORTRAN_REAL4 alpha, const FORTRAN_REAL4 a, const FORTRAN_INT8 lda, const FORTRAN_REAL4 x, const FORTRAN_INT8 incx, const FORTRAN_REAL4 beta, FORTRAN_REAL4 y, const FORTRAN_INT8 incy );
extern void dgemv_( const FORTRAN_CHAR1 trans, const FORTRAN_INT8 m, const FORTRAN_INT8 n, const FORTRAN_REAL8 alpha, const FORTRAN_REAL8 a, const FORTRAN_INT8 lda, const FORTRAN_REAL8 x, const FORTRAN_INT8 incx, const FORTRAN_REAL8 beta, FORTRAN_REAL8 y, const FORTRAN_INT8 incy );
extern void cgemv_( const FORTRAN_CHAR1 trans, const FORTRAN_INT8 m, const FORTRAN_INT8 n, const FORTRAN_COMP4 alpha, const FORTRAN_COMP4 a, const FORTRAN_INT8 lda, const FORTRAN_COMP4 x, const FORTRAN_INT8 incx, const FORTRAN_COMP4 beta, FORTRAN_COMP4 y, const FORTRAN_INT8 incy );
extern void zgemv_( const FORTRAN_CHAR1 trans, const FORTRAN_INT8 m, const FORTRAN_INT8 n, const FORTRAN_COMP8 alpha, const FORTRAN_COMP8 a, const FORTRAN_INT8 lda, const FORTRAN_COMP8 x, const FORTRAN_INT8 incx, const FORTRAN_COMP8 beta, FORTRAN_COMP8 y, const FORTRAN_INT8 incy );

// Computes a matrix-vector product using a general band matrix.
extern void sgbmv_( const FORTRAN_CHAR1 trans, const FORTRAN_INT8 m, const FORTRAN_INT8 n, const FORTRAN_INT8 kl, const FORTRAN_INT8 ku, const FORTRAN_REAL4 alpha, const FORTRAN_REAL4 a, const FORTRAN_INT8 lda, const FORTRAN_REAL4 x, const FORTRAN_INT8 incx, const FORTRAN_REAL4 beta, FORTRAN_REAL4 y, const FORTRAN_INT8 incy );
extern void dgbmv_( const FORTRAN_CHAR1 trans, const FORTRAN_INT8 m, const FORTRAN_INT8 n, const FORTRAN_INT8 kl, const FORTRAN_INT8 ku, const FORTRAN_REAL8 alpha, const FORTRAN_REAL8 a, const FORTRAN_INT8 lda, const FORTRAN_REAL8 x, const FORTRAN_INT8 incx, const FORTRAN_REAL8 beta, FORTRAN_REAL8 y, const FORTRAN_INT8 incy );
extern void cgbmv_( const FORTRAN_CHAR1 trans, const FORTRAN_INT8 m, const FORTRAN_INT8 n, const FORTRAN_INT8 kl, const FORTRAN_INT8 ku, const FORTRAN_COMP4 alpha, const FORTRAN_COMP4 a, const FORTRAN_INT8 lda, const FORTRAN_COMP4 x, const FORTRAN_INT8 incx, const FORTRAN_COMP4 beta, FORTRAN_COMP4 y, const FORTRAN_INT8 incy );
extern void zgbmv_( const FORTRAN_CHAR1 trans, const FORTRAN_INT8 m, const FORTRAN_INT8 n, const FORTRAN_INT8 kl, const FORTRAN_INT8 ku, const FORTRAN_COMP8 alpha, const FORTRAN_COMP8 a, const FORTRAN_INT8 lda, const FORTRAN_COMP8 x, const FORTRAN_INT8 incx, const FORTRAN_COMP8 beta, FORTRAN_COMP8 y, const FORTRAN_INT8 incy );

// Computes a matrix-vector product using a symmetric matrix.
extern void ssymv_( const FORTRAN_CHAR1 uplo, const FORTRAN_INT8 n, const FORTRAN_REAL4 alpha, const FORTRAN_REAL4 a, const FORTRAN_INT8 lda, const FORTRAN_REAL4 x, const FORTRAN_INT8 incx, const FORTRAN_REAL4 beta, FORTRAN_REAL4 y, const FORTRAN_INT8 incy );
extern void dsymv_( const FORTRAN_CHAR1 uplo, const FORTRAN_INT8 n, const FORTRAN_REAL8 alpha, const FORTRAN_REAL8 a, const FORTRAN_INT8 lda, const FORTRAN_REAL8 x, const FORTRAN_INT8 incx, const FORTRAN_REAL8 beta, FORTRAN_REAL8 y, const FORTRAN_INT8 incy );

// Computes a matrix-vector product using a symmetric band matrix.
extern void ssbmv_( const FORTRAN_CHAR1 uplo, const FORTRAN_INT8 n, const FORTRAN_INT8 k, const FORTRAN_REAL4 alpha, const FORTRAN_REAL4 a, const FORTRAN_INT8 lda, const FORTRAN_REAL4 x, const FORTRAN_INT8 incx, const FORTRAN_REAL4 beta, FORTRAN_REAL4 y, const FORTRAN_INT8 incy );
extern void dsbmv_( const FORTRAN_CHAR1 uplo, const FORTRAN_INT8 n, const FORTRAN_INT8 k, const FORTRAN_REAL8 alpha, const FORTRAN_REAL8 a, const FORTRAN_INT8 lda, const FORTRAN_REAL8 x, const FORTRAN_INT8 incx, const FORTRAN_REAL8 beta, FORTRAN_REAL8 y, const FORTRAN_INT8 incy );

// Computes a matrix-vector product using a symmetric packed matrix.
extern void sspmv_( const FORTRAN_CHAR1 uplo, const FORTRAN_INT8 n, const FORTRAN_REAL4 alpha, const FORTRAN_REAL4 ap, const FORTRAN_REAL4 x, const FORTRAN_INT8 incx, const FORTRAN_REAL4 beta, FORTRAN_REAL4 y, const FORTRAN_INT8 incy );
extern void dspmv_( const FORTRAN_CHAR1 uplo, const FORTRAN_INT8 n, const FORTRAN_REAL8 alpha, const FORTRAN_REAL8 ap, const FORTRAN_REAL8 x, const FORTRAN_INT8 incx, const FORTRAN_REAL8 beta, FORTRAN_REAL8 y, const FORTRAN_INT8 incy );

// Computes a matrix-vector product using a Hermitian matrix.
extern void chemv_( const FORTRAN_CHAR1 uplo, const FORTRAN_INT8 n, const FORTRAN_COMP4 alpha, const FORTRAN_COMP4 a, const FORTRAN_INT8 lda, const FORTRAN_COMP4 x, const FORTRAN_INT8 incx, const FORTRAN_COMP4 beta, FORTRAN_COMP4 y, const FORTRAN_INT8 incy );
extern void zhemv_( const FORTRAN_CHAR1 uplo, const FORTRAN_INT8 n, const FORTRAN_COMP8 alpha, const FORTRAN_COMP8 a, const FORTRAN_INT8 lda, const FORTRAN_COMP8 x, const FORTRAN_INT8 incx, const FORTRAN_COMP8 beta, FORTRAN_COMP8 y, const FORTRAN_INT8 incy );

// Computes a matrix-vector product using a Hermitian band matrix.
extern void chbmv_( const FORTRAN_CHAR1 uplo, const FORTRAN_INT8 n, const FORTRAN_INT8 k, const FORTRAN_COMP4 alpha, const FORTRAN_COMP4 a, const FORTRAN_INT8 lda, const FORTRAN_COMP4 x, const FORTRAN_INT8 incx, const FORTRAN_COMP4 beta, FORTRAN_COMP4 y, const FORTRAN_INT8 incy );
extern void zhbmv_( const FORTRAN_CHAR1 uplo, const FORTRAN_INT8 n, const FORTRAN_INT8 k, const FORTRAN_COMP8 alpha, const FORTRAN_COMP8 a, const FORTRAN_INT8 lda, const FORTRAN_COMP8 x, const FORTRAN_INT8 incx, const FORTRAN_COMP8 beta, FORTRAN_COMP8 y, const FORTRAN_INT8 incy );

// Computes a matrix-vector product using a Hermitian packed matrix.
extern void chpmv_( const FORTRAN_CHAR1 uplo, const FORTRAN_INT8 n, const FORTRAN_COMP4 alpha, const FORTRAN_COMP4 ap, const FORTRAN_COMP4 x, const FORTRAN_INT8 incx, const FORTRAN_COMP4 beta, FORTRAN_COMP4 y, const FORTRAN_INT8 incy );
extern void zhpmv_( const FORTRAN_CHAR1 uplo, const FORTRAN_INT8 n, const FORTRAN_COMP8 alpha, const FORTRAN_COMP8 ap, const FORTRAN_COMP8 x, const FORTRAN_INT8 incx, const FORTRAN_COMP8 beta, FORTRAN_COMP8 y, const FORTRAN_INT8 incy );

// Computes a matrix-vector product using a triangular band matrix.
extern void strmv_( const FORTRAN_CHAR1 uplo, const FORTRAN_CHAR1 trans, const FORTRAN_CHAR1 diag, const FORTRAN_INT8 n, const FORTRAN_REAL4 a, const FORTRAN_INT8 lda, const FORTRAN_REAL4 x, const FORTRAN_INT8 incx );
extern void dtrmv_( const FORTRAN_CHAR1 uplo, const FORTRAN_CHAR1 trans, const FORTRAN_CHAR1 diag, const FORTRAN_INT8 n, const FORTRAN_REAL8 a, const FORTRAN_INT8 lda, const FORTRAN_REAL8 x, const FORTRAN_INT8 incx );
extern void ctrmv_( const FORTRAN_CHAR1 uplo, const FORTRAN_CHAR1 trans, const FORTRAN_CHAR1 diag, const FORTRAN_INT8 n, const FORTRAN_COMP4 a, const FORTRAN_INT8 lda, const FORTRAN_COMP4 x, const FORTRAN_INT8 incx );
extern void ztrmv_( const FORTRAN_CHAR1 uplo, const FORTRAN_CHAR1 trans, const FORTRAN_CHAR1 diag, const FORTRAN_INT8 n, const FORTRAN_COMP8 a, const FORTRAN_INT8 lda, const FORTRAN_COMP8 x, const FORTRAN_INT8 incx );

// Computes a matrix-vector product using a triangular band matrix.
extern void stbmv_( const FORTRAN_CHAR1 uplo, const FORTRAN_CHAR1 trans, const FORTRAN_CHAR1 diag, const FORTRAN_INT8 n, const FORTRAN_INT8 k, const FORTRAN_REAL4 a, const FORTRAN_INT8 lda, const FORTRAN_REAL4 x, const FORTRAN_INT8 incx );
extern void dtbmv_( const FORTRAN_CHAR1 uplo, const FORTRAN_CHAR1 trans, const FORTRAN_CHAR1 diag, const FORTRAN_INT8 n, const FORTRAN_INT8 k, const FORTRAN_REAL8 a, const FORTRAN_INT8 lda, const FORTRAN_REAL8 x, const FORTRAN_INT8 incx );
extern void ctbmv_( const FORTRAN_CHAR1 uplo, const FORTRAN_CHAR1 trans, const FORTRAN_CHAR1 diag, const FORTRAN_INT8 n, const FORTRAN_INT8 k, const FORTRAN_COMP4 a, const FORTRAN_INT8 lda, const FORTRAN_COMP4 x, const FORTRAN_INT8 incx );
extern void ztbmv_( const FORTRAN_CHAR1 uplo, const FORTRAN_CHAR1 trans, const FORTRAN_CHAR1 diag, const FORTRAN_INT8 n, const FORTRAN_INT8 k, const FORTRAN_COMP8 a, const FORTRAN_INT8 lda, const FORTRAN_COMP8 x, const FORTRAN_INT8 incx );

// Computes a matrix-vector product using a triangular packed matrix.
extern void stpmv_( const FORTRAN_CHAR1 uplo, const FORTRAN_CHAR1 trans, const FORTRAN_CHAR1 diag, const FORTRAN_INT8 n, const FORTRAN_REAL4 ap, const FORTRAN_REAL4 x, const FORTRAN_INT8 incx );
extern void dtpmv_( const FORTRAN_CHAR1 uplo, const FORTRAN_CHAR1 trans, const FORTRAN_CHAR1 diag, const FORTRAN_INT8 n, const FORTRAN_REAL8 ap, const FORTRAN_REAL8 x, const FORTRAN_INT8 incx );
extern void ctpmv_( const FORTRAN_CHAR1 uplo, const FORTRAN_CHAR1 trans, const FORTRAN_CHAR1 diag, const FORTRAN_INT8 n, const FORTRAN_COMP4 ap, const FORTRAN_COMP4 x, const FORTRAN_INT8 incx );
extern void ztpmv_( const FORTRAN_CHAR1 uplo, const FORTRAN_CHAR1 trans, const FORTRAN_CHAR1 diag, const FORTRAN_INT8 n, const FORTRAN_COMP8 ap, const FORTRAN_COMP8 x, const FORTRAN_INT8 incx );

// Solves a system of linear equations whose coefficients are in a triangular band matrix.
extern void strsv_( const FORTRAN_CHAR1 uplo, const FORTRAN_CHAR1 trans, const FORTRAN_CHAR1 diag, const FORTRAN_INT8 n, const FORTRAN_REAL4 a, const FORTRAN_INT8 lda, const FORTRAN_REAL4 x, const FORTRAN_INT8 incx );
extern void dtrsv_( const FORTRAN_CHAR1 uplo, const FORTRAN_CHAR1 trans, const FORTRAN_CHAR1 diag, const FORTRAN_INT8 n, const FORTRAN_REAL8 a, const FORTRAN_INT8 lda, const FORTRAN_REAL8 x, const FORTRAN_INT8 incx );
extern void ctrsv_( const FORTRAN_CHAR1 uplo, const FORTRAN_CHAR1 trans, const FORTRAN_CHAR1 diag, const FORTRAN_INT8 n, const FORTRAN_COMP4 a, const FORTRAN_INT8 lda, const FORTRAN_COMP4 x, const FORTRAN_INT8 incx );
extern void ztrsv_( const FORTRAN_CHAR1 uplo, const FORTRAN_CHAR1 trans, const FORTRAN_CHAR1 diag, const FORTRAN_INT8 n, const FORTRAN_COMP8 a, const FORTRAN_INT8 lda, const FORTRAN_COMP8 x, const FORTRAN_INT8 incx );

// Solves a system of linear equations whose coefficients are in a triangular band matrix.
extern void stbsv_( const FORTRAN_CHAR1 uplo, const FORTRAN_CHAR1 trans, const FORTRAN_CHAR1 diag, const FORTRAN_INT8 n, const FORTRAN_INT8 k, const FORTRAN_REAL4 a, const FORTRAN_INT8 lda, const FORTRAN_REAL4 x, const FORTRAN_INT8 incx );
extern void dtbsv_( const FORTRAN_CHAR1 uplo, const FORTRAN_CHAR1 trans, const FORTRAN_CHAR1 diag, const FORTRAN_INT8 n, const FORTRAN_INT8 k, const FORTRAN_REAL8 a, const FORTRAN_INT8 lda, const FORTRAN_REAL8 x, const FORTRAN_INT8 incx );
extern void ctbsv_( const FORTRAN_CHAR1 uplo, const FORTRAN_CHAR1 trans, const FORTRAN_CHAR1 diag, const FORTRAN_INT8 n, const FORTRAN_INT8 k, const FORTRAN_COMP4 a, const FORTRAN_INT8 lda, const FORTRAN_COMP4 x, const FORTRAN_INT8 incx );
extern void ztbsv_( const FORTRAN_CHAR1 uplo, const FORTRAN_CHAR1 trans, const FORTRAN_CHAR1 diag, const FORTRAN_INT8 n, const FORTRAN_INT8 k, const FORTRAN_COMP8 a, const FORTRAN_INT8 lda, const FORTRAN_COMP8 x, const FORTRAN_INT8 incx );

// Solves a system of linear equations whose coefficients are in a triangular packed matrix.
extern void stpsv_( const FORTRAN_CHAR1 uplo, const FORTRAN_CHAR1 trans, const FORTRAN_CHAR1 diag, const FORTRAN_INT8 n, const FORTRAN_REAL4 ap, const FORTRAN_REAL4 x, const FORTRAN_INT8 incx );
extern void dtpsv_( const FORTRAN_CHAR1 uplo, const FORTRAN_CHAR1 trans, const FORTRAN_CHAR1 diag, const FORTRAN_INT8 n, const FORTRAN_REAL8 ap, const FORTRAN_REAL8 x, const FORTRAN_INT8 incx );
extern void ctpsv_( const FORTRAN_CHAR1 uplo, const FORTRAN_CHAR1 trans, const FORTRAN_CHAR1 diag, const FORTRAN_INT8 n, const FORTRAN_COMP4 ap, const FORTRAN_COMP4 x, const FORTRAN_INT8 incx );
extern void ztpsv_( const FORTRAN_CHAR1 uplo, const FORTRAN_CHAR1 trans, const FORTRAN_CHAR1 diag, const FORTRAN_INT8 n, const FORTRAN_COMP8 ap, const FORTRAN_COMP8 x, const FORTRAN_INT8 incx );

// Performs a rank-1 update of a general matrix.
extern void sger_( const FORTRAN_INT8 m, const FORTRAN_INT8 n, const FORTRAN_REAL4 alpha, const FORTRAN_REAL4 x, const FORTRAN_INT8 incx, const FORTRAN_REAL4 y, const FORTRAN_INT8 incy, FORTRAN_REAL4 a, const FORTRAN_INT8 lda );
extern void dger_( const FORTRAN_INT8 m, const FORTRAN_INT8 n, const FORTRAN_REAL8 alpha, const FORTRAN_REAL8 x, const FORTRAN_INT8 incx, const FORTRAN_REAL8 y, const FORTRAN_INT8 incy, FORTRAN_REAL8 a, const FORTRAN_INT8 lda );

// Performs a rank-1 update (unconjugated) of a general matrix.
extern void cgeru_( const FORTRAN_INT8 m, const FORTRAN_INT8 n, const FORTRAN_COMP4 alpha, const FORTRAN_COMP4 x, const FORTRAN_INT8 incx, const FORTRAN_COMP4 y, const FORTRAN_INT8 incy, FORTRAN_COMP4 a, const FORTRAN_INT8 lda );
extern void zgeru_( const FORTRAN_INT8 m, const FORTRAN_INT8 n, const FORTRAN_COMP8 alpha, const FORTRAN_COMP8 x, const FORTRAN_INT8 incx, const FORTRAN_COMP8 y, const FORTRAN_INT8 incy, FORTRAN_COMP8 a, const FORTRAN_INT8 lda );

// Performs a rank-1 update (conjugated) of a general matrix.
extern void cgerc_( const FORTRAN_INT8 m, const FORTRAN_INT8 n, const FORTRAN_COMP4 alpha, const FORTRAN_COMP4 x, const FORTRAN_INT8 incx, const FORTRAN_COMP4 y, const FORTRAN_INT8 incy, FORTRAN_COMP4 a, const FORTRAN_INT8 lda );
extern void zgerc_( const FORTRAN_INT8 m, const FORTRAN_INT8 n, const FORTRAN_COMP8 alpha, const FORTRAN_COMP8 x, const FORTRAN_INT8 incx, const FORTRAN_COMP8 y, const FORTRAN_INT8 incy, FORTRAN_COMP8 a, const FORTRAN_INT8 lda );

// Performs a rank-1 update of a symmetric matrix.
extern void ssyr_( const FORTRAN_CHAR1 uplo, const FORTRAN_INT8 n, const FORTRAN_REAL4 alpha, const FORTRAN_REAL4 x, const FORTRAN_INT8 incx, FORTRAN_REAL4 a, const FORTRAN_INT8 lda );
extern void dsyr_( const FORTRAN_CHAR1 uplo, const FORTRAN_INT8 n, const FORTRAN_REAL8 alpha, const FORTRAN_REAL8 x, const FORTRAN_INT8 incx, FORTRAN_REAL8 a, const FORTRAN_INT8 lda );

// Performs a rank-1 update of a symmetric packed matrix.
extern void sspr_( const FORTRAN_CHAR1 uplo, const FORTRAN_INT8 n, const FORTRAN_REAL4 alpha, const FORTRAN_REAL4 x, const FORTRAN_INT8 incx, FORTRAN_REAL4 ap );
extern void dspr_( const FORTRAN_CHAR1 uplo, const FORTRAN_INT8 n, const FORTRAN_REAL8 alpha, const FORTRAN_REAL8 x, const FORTRAN_INT8 incx, FORTRAN_REAL8 ap );

// Performs a rank-2 update of a symmetric matrix.
extern void ssyr2_( const FORTRAN_CHAR1 uplo, const FORTRAN_INT8 n, const FORTRAN_REAL4 alpha, const FORTRAN_REAL4 x, const FORTRAN_INT8 incx, const FORTRAN_REAL4 y, const FORTRAN_INT8 incy, FORTRAN_REAL4 a, const FORTRAN_INT8 lda );
extern void dsyr2_( const FORTRAN_CHAR1 uplo, const FORTRAN_INT8 n, const FORTRAN_REAL8 alpha, const FORTRAN_REAL8 x, const FORTRAN_INT8 incx, const FORTRAN_REAL8 y, const FORTRAN_INT8 incy, FORTRAN_REAL8 a, const FORTRAN_INT8 lda );

// Performs a rank-2 update of a symmetric packed matrix.
extern void sspr2_( const FORTRAN_CHAR1 uplo, const FORTRAN_INT8 n, const FORTRAN_REAL4 alpha, const FORTRAN_REAL4 x, const FORTRAN_INT8 incx, const FORTRAN_REAL4 y, const FORTRAN_INT8 incy, FORTRAN_REAL4 ap );
extern void dspr2_( const FORTRAN_CHAR1 uplo, const FORTRAN_INT8 n, const FORTRAN_REAL8 alpha, const FORTRAN_REAL8 x, const FORTRAN_INT8 incx, const FORTRAN_REAL8 y, const FORTRAN_INT8 incy, FORTRAN_REAL8 ap );

// Performs a rank-1 update of a Hermitian matrix.
extern void cher_( const FORTRAN_CHAR1 uplo, const FORTRAN_INT8 n, const FORTRAN_COMP4 alpha, const FORTRAN_COMP4 x, const FORTRAN_INT8 incx, FORTRAN_COMP4 a, const FORTRAN_INT8 lda );
extern void zher_( const FORTRAN_CHAR1 uplo, const FORTRAN_INT8 n, const FORTRAN_COMP8 alpha, const FORTRAN_COMP8 x, const FORTRAN_INT8 incx, FORTRAN_COMP8 a, const FORTRAN_INT8 lda );

// Performs a rank-1 update of a Hermitian packed matrix.
extern void chpr_( const FORTRAN_CHAR1 uplo, const FORTRAN_INT8 n, const FORTRAN_COMP4 alpha, const FORTRAN_COMP4 x, const FORTRAN_INT8 incx, FORTRAN_COMP4 ap );
extern void zhpr_( const FORTRAN_CHAR1 uplo, const FORTRAN_INT8 n, const FORTRAN_COMP8 alpha, const FORTRAN_COMP8 x, const FORTRAN_INT8 incx, FORTRAN_COMP8 ap );

// Performs a rank-2 update of a Hermitian matrix.
extern void cher2_( const FORTRAN_CHAR1 uplo, const FORTRAN_INT8 n, const FORTRAN_COMP4 alpha, const FORTRAN_COMP4 x, const FORTRAN_INT8 incx, const FORTRAN_COMP4 y, const FORTRAN_INT8 incy, FORTRAN_COMP4 a, const FORTRAN_INT8 lda );
extern void zher2_( const FORTRAN_CHAR1 uplo, const FORTRAN_INT8 n, const FORTRAN_COMP8 alpha, const FORTRAN_COMP8 x, const FORTRAN_INT8 incx, const FORTRAN_COMP8 y, const FORTRAN_INT8 incy, FORTRAN_COMP8 a, const FORTRAN_INT8 lda );

// Performs a rank-2 update of a Hermitian packed matrix.
extern void chpr2_( const FORTRAN_CHAR1 uplo, const FORTRAN_INT8 n, const FORTRAN_COMP4 alpha, const FORTRAN_COMP4 x, const FORTRAN_INT8 incx, const FORTRAN_COMP4 y, const FORTRAN_INT8 incy, FORTRAN_COMP4 ap );
extern void zhpr2_( const FORTRAN_CHAR1 uplo, const FORTRAN_INT8 n, const FORTRAN_COMP8 alpha, const FORTRAN_COMP8 x, const FORTRAN_INT8 incx, const FORTRAN_COMP8 y, const FORTRAN_INT8 incy, FORTRAN_COMP8 ap );

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Level 3 BLAS routines
//

// Computes a matrix-matrix product with general matrices.
extern void sgemm_( const FORTRAN_CHAR1 transa, const FORTRAN_CHAR1 transb, const FORTRAN_INT8 m, const FORTRAN_INT8 n, const FORTRAN_INT8 k, const FORTRAN_REAL4 alpha, const FORTRAN_REAL4 a, const FORTRAN_INT8 lda, const FORTRAN_REAL4 b, const FORTRAN_INT8 ldb, const FORTRAN_REAL4 beta, FORTRAN_REAL4 c, const FORTRAN_INT8 ldc );
extern void dgemm_( const FORTRAN_CHAR1 transa, const FORTRAN_CHAR1 transb, const FORTRAN_INT8 m, const FORTRAN_INT8 n, const FORTRAN_INT8 k, const FORTRAN_REAL8 alpha, const FORTRAN_REAL8 a, const FORTRAN_INT8 lda, const FORTRAN_REAL8 b, const FORTRAN_INT8 ldb, const FORTRAN_REAL8 beta, FORTRAN_REAL8 c, const FORTRAN_INT8 ldc );
extern void cgemm_( const FORTRAN_CHAR1 transa, const FORTRAN_CHAR1 transb, const FORTRAN_INT8 m, const FORTRAN_INT8 n, const FORTRAN_INT8 k, const FORTRAN_COMP4 alpha, const FORTRAN_COMP4 a, const FORTRAN_INT8 lda, const FORTRAN_COMP4 b, const FORTRAN_INT8 ldb, const FORTRAN_COMP4 beta, FORTRAN_COMP4 c, const FORTRAN_INT8 ldc );
extern void zgemm_( const FORTRAN_CHAR1 transa, const FORTRAN_CHAR1 transb, const FORTRAN_INT8 m, const FORTRAN_INT8 n, const FORTRAN_INT8 k, const FORTRAN_COMP8 alpha, const FORTRAN_COMP8 a, const FORTRAN_INT8 lda, const FORTRAN_COMP8 b, const FORTRAN_INT8 ldb, const FORTRAN_COMP8 beta, FORTRAN_COMP8 c, const FORTRAN_INT8 ldc );

// Computes a matrix-matrix product where one input matrix is symmetric.
extern void ssymm_( const FORTRAN_CHAR1 side, const FORTRAN_CHAR1 uplo, const FORTRAN_INT8 m, const FORTRAN_INT8 n, const FORTRAN_REAL4 alpha, const FORTRAN_REAL4 a, const FORTRAN_INT8 lda, const FORTRAN_REAL4 b, const FORTRAN_INT8 ldb, const FORTRAN_REAL4 beta, FORTRAN_REAL4 c, const FORTRAN_INT8 ldc );
extern void dsymm_( const FORTRAN_CHAR1 side, const FORTRAN_CHAR1 uplo, const FORTRAN_INT8 m, const FORTRAN_INT8 n, const FORTRAN_REAL8 alpha, const FORTRAN_REAL8 a, const FORTRAN_INT8 lda, const FORTRAN_REAL8 b, const FORTRAN_INT8 ldb, const FORTRAN_REAL8 beta, FORTRAN_REAL8 c, const FORTRAN_INT8 ldc );

// Computes a matrix-matrix product where one input matrix is Hermitian.
extern void chemm_( const FORTRAN_CHAR1 side, const FORTRAN_CHAR1 uplo, const FORTRAN_INT8 m, const FORTRAN_INT8 n, const FORTRAN_COMP4 alpha, const FORTRAN_COMP4 a, const FORTRAN_INT8 lda, const FORTRAN_COMP4 b, const FORTRAN_INT8 ldb, const FORTRAN_COMP4 beta, FORTRAN_COMP4 c, const FORTRAN_INT8 ldc );
extern void zhemm_( const FORTRAN_CHAR1 side, const FORTRAN_CHAR1 uplo, const FORTRAN_INT8 m, const FORTRAN_INT8 n, const FORTRAN_COMP8 alpha, const FORTRAN_COMP8 a, const FORTRAN_INT8 lda, const FORTRAN_COMP8 b, const FORTRAN_INT8 ldb, const FORTRAN_COMP8 beta, FORTRAN_COMP8 c, const FORTRAN_INT8 ldc );

// Computes a matrix-matrix product where one input matrix is triangular.
extern void strmm_( const FORTRAN_CHAR1 side, const FORTRAN_CHAR1 uplo, const FORTRAN_CHAR1 transa, const FORTRAN_CHAR1 diag, const FORTRAN_INT8 m, const FORTRAN_INT8 n, const FORTRAN_REAL4 alpha, const FORTRAN_REAL4 a, const FORTRAN_INT8 lda, FORTRAN_REAL4 b, const FORTRAN_INT8 ldb );
extern void dtrmm_( const FORTRAN_CHAR1 side, const FORTRAN_CHAR1 uplo, const FORTRAN_CHAR1 transa, const FORTRAN_CHAR1 diag, const FORTRAN_INT8 m, const FORTRAN_INT8 n, const FORTRAN_REAL8 alpha, const FORTRAN_REAL8 a, const FORTRAN_INT8 lda, FORTRAN_REAL8 b, const FORTRAN_INT8 ldb );
extern void ctrmm_( const FORTRAN_CHAR1 side, const FORTRAN_CHAR1 uplo, const FORTRAN_CHAR1 transa, const FORTRAN_CHAR1 diag, const FORTRAN_INT8 m, const FORTRAN_INT8 n, const FORTRAN_COMP4 alpha, const FORTRAN_COMP4 a, const FORTRAN_INT8 lda, FORTRAN_COMP4 b, const FORTRAN_INT8 ldb );
extern void ztrmm_( const FORTRAN_CHAR1 side, const FORTRAN_CHAR1 uplo, const FORTRAN_CHAR1 transa, const FORTRAN_CHAR1 diag, const FORTRAN_INT8 m, const FORTRAN_INT8 n, const FORTRAN_COMP8 alpha, const FORTRAN_COMP8 a, const FORTRAN_INT8 lda, FORTRAN_COMP8 b, const FORTRAN_INT8 ldb );

// Solves a triangular matrix equation.
extern void strsm_( const FORTRAN_CHAR1 side, const FORTRAN_CHAR1 uplo, const FORTRAN_CHAR1 transa, const FORTRAN_CHAR1 diag, const FORTRAN_INT8 m, const FORTRAN_INT8 n, const FORTRAN_REAL4 alpha, const FORTRAN_REAL4 a, const FORTRAN_INT8 lda, FORTRAN_REAL4 b, const FORTRAN_INT8 ldb );
extern void dtrsm_( const FORTRAN_CHAR1 side, const FORTRAN_CHAR1 uplo, const FORTRAN_CHAR1 transa, const FORTRAN_CHAR1 diag, const FORTRAN_INT8 m, const FORTRAN_INT8 n, const FORTRAN_REAL8 alpha, const FORTRAN_REAL8 a, const FORTRAN_INT8 lda, FORTRAN_REAL8 b, const FORTRAN_INT8 ldb );
extern void ctrsm_( const FORTRAN_CHAR1 side, const FORTRAN_CHAR1 uplo, const FORTRAN_CHAR1 transa, const FORTRAN_CHAR1 diag, const FORTRAN_INT8 m, const FORTRAN_INT8 n, const FORTRAN_COMP4 alpha, const FORTRAN_COMP4 a, const FORTRAN_INT8 lda, FORTRAN_COMP4 b, const FORTRAN_INT8 ldb );
extern void ztrsm_( const FORTRAN_CHAR1 side, const FORTRAN_CHAR1 uplo, const FORTRAN_CHAR1 transa, const FORTRAN_CHAR1 diag, const FORTRAN_INT8 m, const FORTRAN_INT8 n, const FORTRAN_COMP8 alpha, const FORTRAN_COMP8 a, const FORTRAN_INT8 lda, FORTRAN_COMP8 b, const FORTRAN_INT8 ldb );

// Performs a symmetric rank-k update.
extern void ssyrk_( const FORTRAN_CHAR1 uplo, const FORTRAN_CHAR1 trans, const FORTRAN_INT8 n, const FORTRAN_INT8 k, const FORTRAN_REAL4 alpha, const FORTRAN_REAL4 a, const FORTRAN_INT8 lda, const FORTRAN_REAL4 beta, FORTRAN_REAL4 c, const FORTRAN_INT8 ldc );
extern void dsyrk_( const FORTRAN_CHAR1 uplo, const FORTRAN_CHAR1 trans, const FORTRAN_INT8 n, const FORTRAN_INT8 k, const FORTRAN_REAL8 alpha, const FORTRAN_REAL8 a, const FORTRAN_INT8 lda, const FORTRAN_REAL8 beta, FORTRAN_REAL8 c, const FORTRAN_INT8 ldc );

// Performs a symmetric rank-2k update.
extern void ssyr2k_( const FORTRAN_CHAR1 uplo, const FORTRAN_CHAR1 trans, const FORTRAN_INT8 n, const FORTRAN_INT8 k, const FORTRAN_REAL4 alpha, const FORTRAN_REAL4 a, const FORTRAN_INT8 lda, const FORTRAN_REAL4 b, const FORTRAN_INT8 ldb, const FORTRAN_REAL4 beta, FORTRAN_REAL4 c, const FORTRAN_INT8 ldc );
extern void dsyr2k_( const FORTRAN_CHAR1 uplo, const FORTRAN_CHAR1 trans, const FORTRAN_INT8 n, const FORTRAN_INT8 k, const FORTRAN_REAL8 alpha, const FORTRAN_REAL8 a, const FORTRAN_INT8 lda, const FORTRAN_REAL8 b, const FORTRAN_INT8 ldb, const FORTRAN_REAL8 beta, FORTRAN_REAL8 c, const FORTRAN_INT8 ldc );

// Performs a Hermitian rank-k update.
extern void cherk_( const FORTRAN_CHAR1 uplo, const FORTRAN_CHAR1 trans, const FORTRAN_INT8 n, const FORTRAN_INT8 k, const FORTRAN_COMP4 alpha, const FORTRAN_COMP4 a, const FORTRAN_INT8 lda, const FORTRAN_COMP4 b, FORTRAN_COMP4 c, const FORTRAN_INT8 ldc );
extern void zherk_( const FORTRAN_CHAR1 uplo, const FORTRAN_CHAR1 trans, const FORTRAN_INT8 n, const FORTRAN_INT8 k, const FORTRAN_COMP8 alpha, const FORTRAN_COMP8 a, const FORTRAN_INT8 lda, const FORTRAN_COMP8 b, FORTRAN_COMP8 c, const FORTRAN_INT8 ldc );

// Performs a Hermitian rank-2k update.
extern void cher2k_( const FORTRAN_CHAR1 uplo, const FORTRAN_CHAR1 trans, const FORTRAN_INT8 n, const FORTRAN_INT8 k, const FORTRAN_COMP4 alpha, const FORTRAN_COMP4 a, const FORTRAN_INT8 lda, const FORTRAN_COMP4 b, const FORTRAN_INT8 ldb, const FORTRAN_COMP4 beta, FORTRAN_COMP4 c, const FORTRAN_INT8 ldc );
extern void zher2k_( const FORTRAN_CHAR1 uplo, const FORTRAN_CHAR1 trans, const FORTRAN_INT8 n, const FORTRAN_INT8 k, const FORTRAN_COMP8 alpha, const FORTRAN_COMP8 a, const FORTRAN_INT8 lda, const FORTRAN_COMP8 b, const FORTRAN_INT8 ldb, const FORTRAN_COMP8 beta, FORTRAN_COMP8 c, const FORTRAN_INT8 ldc );

#undef CPP_CHAR1
#undef CPP_INT8
#undef CPP_REAL4
#undef CPP_REAL8
#undef CPP_COMP4
#undef CPP_COMP8

#undef FORTRAN_CHAR1
#undef FORTRAN_INT8
#undef FORTRAN_REAL4
#undef FORTRAN_REAL8
#undef FORTRAN_COMP4
#undef FORTRAN_COMP8

}  // extern "C"

#endif  // DOXYGEN_SHOULD_SKIP_THIS

#endif  // ISVD_BLAS_BLASF_HPP_
