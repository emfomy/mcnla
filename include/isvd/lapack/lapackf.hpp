////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/lapack/lapackf.hpp
/// @brief   The Fortran LAPACK simple driver routines
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_LAPACK_LAPACKF_HPP_
#define ISVD_LAPACK_LAPACKF_HPP_

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

#define REAL4_SELECT2(name) CPP_INT8 (*arg)( const FORTRAN_REAL4, const FORTRAN_REAL4 )
#define REAL8_SELECT2(name) CPP_INT8 (*arg)( const FORTRAN_REAL8, const FORTRAN_REAL8 )
#define COMP4_SELECT1(name) CPP_INT8 (*arg)( const FORTRAN_COMP4 )
#define COMP8_SELECT1(name) CPP_INT8 (*arg)( const FORTRAN_COMP8 )

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Simple Driver Routines for Linear Equations
//

// Computes the solution to the system of linear equations with a square coefficient matrix A and multiple right-hand sides.
extern void sgesv_( const FORTRAN_INT8 n, const FORTRAN_INT8 nrhs, FORTRAN_REAL4 a, const FORTRAN_INT8 lda, FORTRAN_INT8 ipiv, FORTRAN_REAL4 b, const FORTRAN_INT8 ldb, FORTRAN_INT8 info );
extern void dgesv_( const FORTRAN_INT8 n, const FORTRAN_INT8 nrhs, FORTRAN_REAL8 a, const FORTRAN_INT8 lda, FORTRAN_INT8 ipiv, FORTRAN_REAL8 b, const FORTRAN_INT8 ldb, FORTRAN_INT8 info );
extern void cgesv_( const FORTRAN_INT8 n, const FORTRAN_INT8 nrhs, FORTRAN_COMP4 a, const FORTRAN_INT8 lda, FORTRAN_INT8 ipiv, FORTRAN_COMP4 b, const FORTRAN_INT8 ldb, FORTRAN_INT8 info );
extern void zgesv_( const FORTRAN_INT8 n, const FORTRAN_INT8 nrhs, FORTRAN_COMP8 a, const FORTRAN_INT8 lda, FORTRAN_INT8 ipiv, FORTRAN_COMP8 b, const FORTRAN_INT8 ldb, FORTRAN_INT8 info );

// Computes the solution to the system of linear equations with a band coefficient matrix A and multiple right-hand sides.
extern void sgbsv_( const FORTRAN_INT8 n, const FORTRAN_INT8 kl, const FORTRAN_INT8 ku, const FORTRAN_INT8 nrhs, FORTRAN_REAL4 a, const FORTRAN_INT8 lda, FORTRAN_INT8 ipiv, FORTRAN_REAL4 b, const FORTRAN_INT8 ldb, FORTRAN_INT8 info );
extern void dgbsv_( const FORTRAN_INT8 n, const FORTRAN_INT8 kl, const FORTRAN_INT8 ku, const FORTRAN_INT8 nrhs, FORTRAN_REAL8 a, const FORTRAN_INT8 lda, FORTRAN_INT8 ipiv, FORTRAN_REAL8 b, const FORTRAN_INT8 ldb, FORTRAN_INT8 info );
extern void cgbsv_( const FORTRAN_INT8 n, const FORTRAN_INT8 kl, const FORTRAN_INT8 ku, const FORTRAN_INT8 nrhs, FORTRAN_COMP4 a, const FORTRAN_INT8 lda, FORTRAN_INT8 ipiv, FORTRAN_COMP4 b, const FORTRAN_INT8 ldb, FORTRAN_INT8 info );
extern void zgbsv_( const FORTRAN_INT8 n, const FORTRAN_INT8 kl, const FORTRAN_INT8 ku, const FORTRAN_INT8 nrhs, FORTRAN_COMP8 a, const FORTRAN_INT8 lda, FORTRAN_INT8 ipiv, FORTRAN_COMP8 b, const FORTRAN_INT8 ldb, FORTRAN_INT8 info );

// Computes the solution to the system of linear equations with a tridiagonal coefficient matrix A and multiple right-hand sides.
extern void sgtsv_( const FORTRAN_INT8 n, const FORTRAN_INT8 nrhs, const FORTRAN_REAL4 dl, const FORTRAN_REAL4 d, const FORTRAN_REAL4 du, FORTRAN_REAL4 b, const FORTRAN_INT8 ldb, FORTRAN_INT8 info );
extern void dgtsv_( const FORTRAN_INT8 n, const FORTRAN_INT8 nrhs, const FORTRAN_REAL8 dl, const FORTRAN_REAL8 d, const FORTRAN_REAL8 du, FORTRAN_REAL8 b, const FORTRAN_INT8 ldb, FORTRAN_INT8 info );
extern void cgtsv_( const FORTRAN_INT8 n, const FORTRAN_INT8 nrhs, const FORTRAN_COMP4 dl, const FORTRAN_COMP4 d, const FORTRAN_COMP4 du, FORTRAN_COMP4 b, const FORTRAN_INT8 ldb, FORTRAN_INT8 info );
extern void zgtsv_( const FORTRAN_INT8 n, const FORTRAN_INT8 nrhs, const FORTRAN_COMP8 dl, const FORTRAN_COMP8 d, const FORTRAN_COMP8 du, FORTRAN_COMP8 b, const FORTRAN_INT8 ldb, FORTRAN_INT8 info );

// Computes the solution to the system of linear equations with a symmetric or Hermitian positive-definite coefficient matrix A and multiple right-hand sides.
extern void sposv_( const FORTRAN_CHAR1 uplo, const FORTRAN_INT8 n, const FORTRAN_INT8 nrhs, FORTRAN_REAL4 a, const FORTRAN_INT8 lda, FORTRAN_REAL4 b, const FORTRAN_INT8 ldb, FORTRAN_INT8 info );
extern void dposv_( const FORTRAN_CHAR1 uplo, const FORTRAN_INT8 n, const FORTRAN_INT8 nrhs, FORTRAN_REAL8 a, const FORTRAN_INT8 lda, FORTRAN_REAL8 b, const FORTRAN_INT8 ldb, FORTRAN_INT8 info );
extern void cposv_( const FORTRAN_CHAR1 uplo, const FORTRAN_INT8 n, const FORTRAN_INT8 nrhs, FORTRAN_COMP4 a, const FORTRAN_INT8 lda, FORTRAN_COMP4 b, const FORTRAN_INT8 ldb, FORTRAN_INT8 info );
extern void zposv_( const FORTRAN_CHAR1 uplo, const FORTRAN_INT8 n, const FORTRAN_INT8 nrhs, FORTRAN_COMP8 a, const FORTRAN_INT8 lda, FORTRAN_COMP8 b, const FORTRAN_INT8 ldb, FORTRAN_INT8 info );

// Computes the solution to the system of linear equations with a symmetric or Hermitian positive definite packed coefficient matrix A and multiple right-hand sides.
extern void sppsv_( const FORTRAN_CHAR1 uplo, const FORTRAN_INT8 n, const FORTRAN_INT8 nrhs, FORTRAN_REAL4 ap, FORTRAN_REAL4 b, const FORTRAN_INT8 ldb, FORTRAN_INT8 info );
extern void dppsv_( const FORTRAN_CHAR1 uplo, const FORTRAN_INT8 n, const FORTRAN_INT8 nrhs, FORTRAN_REAL8 ap, FORTRAN_REAL8 b, const FORTRAN_INT8 ldb, FORTRAN_INT8 info );
extern void cppsv_( const FORTRAN_CHAR1 uplo, const FORTRAN_INT8 n, const FORTRAN_INT8 nrhs, FORTRAN_COMP4 ap, FORTRAN_COMP4 b, const FORTRAN_INT8 ldb, FORTRAN_INT8 info );
extern void zppsv_( const FORTRAN_CHAR1 uplo, const FORTRAN_INT8 n, const FORTRAN_INT8 nrhs, FORTRAN_COMP8 ap, FORTRAN_COMP8 b, const FORTRAN_INT8 ldb, FORTRAN_INT8 info );

// Computes the solution to the system of linear equations with a symmetric or Hermitian positive-definite band coefficient matrix A and multiple right-hand sides.
extern void spbsv_( const FORTRAN_CHAR1 uplo, const FORTRAN_INT8 n, const FORTRAN_INT8 kd, const FORTRAN_INT8 nrhs, FORTRAN_REAL4 a, const FORTRAN_INT8 lda, FORTRAN_REAL4 b, const FORTRAN_INT8 ldb, FORTRAN_INT8 info );
extern void dpbsv_( const FORTRAN_CHAR1 uplo, const FORTRAN_INT8 n, const FORTRAN_INT8 kd, const FORTRAN_INT8 nrhs, FORTRAN_REAL8 a, const FORTRAN_INT8 lda, FORTRAN_REAL8 b, const FORTRAN_INT8 ldb, FORTRAN_INT8 info );
extern void cpbsv_( const FORTRAN_CHAR1 uplo, const FORTRAN_INT8 n, const FORTRAN_INT8 kd, const FORTRAN_INT8 nrhs, FORTRAN_COMP4 a, const FORTRAN_INT8 lda, FORTRAN_COMP4 b, const FORTRAN_INT8 ldb, FORTRAN_INT8 info );
extern void zpbsv_( const FORTRAN_CHAR1 uplo, const FORTRAN_INT8 n, const FORTRAN_INT8 kd, const FORTRAN_INT8 nrhs, FORTRAN_COMP8 a, const FORTRAN_INT8 lda, FORTRAN_COMP8 b, const FORTRAN_INT8 ldb, FORTRAN_INT8 info );

// Computes the solution to the system of linear equations with a symmetric or Hermitian positive definite tridiagonal coefficient matrix A and multiple right-hand sides.
extern void sptsv_( const FORTRAN_INT8 n, const FORTRAN_INT8 nrhs, FORTRAN_REAL4 d, FORTRAN_REAL4 e, FORTRAN_REAL4 b, const FORTRAN_INT8 ldb, FORTRAN_INT8 info );
extern void dptsv_( const FORTRAN_INT8 n, const FORTRAN_INT8 nrhs, FORTRAN_REAL8 d, FORTRAN_REAL8 e, FORTRAN_REAL8 b, const FORTRAN_INT8 ldb, FORTRAN_INT8 info );
extern void cptsv_( const FORTRAN_INT8 n, const FORTRAN_INT8 nrhs, FORTRAN_COMP4 d, FORTRAN_COMP4 e, FORTRAN_COMP4 b, const FORTRAN_INT8 ldb, FORTRAN_INT8 info );
extern void zptsv_( const FORTRAN_INT8 n, const FORTRAN_INT8 nrhs, FORTRAN_COMP8 d, FORTRAN_COMP8 e, FORTRAN_COMP8 b, const FORTRAN_INT8 ldb, FORTRAN_INT8 info );

// Computes the solution to the system of linear equations with a real or complex symmetric coefficient matrix A and multiple right-hand sides.
extern void ssysv_( const FORTRAN_CHAR1 uplo, const FORTRAN_INT8 n, const FORTRAN_INT8 nrhs, FORTRAN_REAL4 a, const FORTRAN_INT8 lda, FORTRAN_INT8 ipiv, FORTRAN_REAL4 b, const FORTRAN_INT8 ldb, FORTRAN_REAL4 work, const FORTRAN_INT8 lwork, FORTRAN_INT8 info );
extern void dsysv_( const FORTRAN_CHAR1 uplo, const FORTRAN_INT8 n, const FORTRAN_INT8 nrhs, FORTRAN_REAL8 a, const FORTRAN_INT8 lda, FORTRAN_INT8 ipiv, FORTRAN_REAL8 b, const FORTRAN_INT8 ldb, FORTRAN_REAL8 work, const FORTRAN_INT8 lwork, FORTRAN_INT8 info );
extern void csysv_( const FORTRAN_CHAR1 uplo, const FORTRAN_INT8 n, const FORTRAN_INT8 nrhs, FORTRAN_COMP4 a, const FORTRAN_INT8 lda, FORTRAN_INT8 ipiv, FORTRAN_COMP4 b, const FORTRAN_INT8 ldb, FORTRAN_COMP4 work, const FORTRAN_INT8 lwork, FORTRAN_INT8 info );
extern void zsysv_( const FORTRAN_CHAR1 uplo, const FORTRAN_INT8 n, const FORTRAN_INT8 nrhs, FORTRAN_COMP8 a, const FORTRAN_INT8 lda, FORTRAN_INT8 ipiv, FORTRAN_COMP8 b, const FORTRAN_INT8 ldb, FORTRAN_COMP8 work, const FORTRAN_INT8 lwork, FORTRAN_INT8 info );

// Computes the solution to the system of linear equations with a Hermitian matrix A and multiple right-hand sides.
extern void chesv_( const FORTRAN_CHAR1 uplo, const FORTRAN_INT8 n, const FORTRAN_INT8 nrhs, FORTRAN_COMP4 a, const FORTRAN_INT8 lda, FORTRAN_INT8 ipiv, FORTRAN_COMP4 b, const FORTRAN_INT8 ldb, FORTRAN_COMP4 work, const FORTRAN_INT8 lwork, FORTRAN_INT8 info );
extern void zhesv_( const FORTRAN_CHAR1 uplo, const FORTRAN_INT8 n, const FORTRAN_INT8 nrhs, FORTRAN_COMP8 a, const FORTRAN_INT8 lda, FORTRAN_INT8 ipiv, FORTRAN_COMP8 b, const FORTRAN_INT8 ldb, FORTRAN_COMP8 work, const FORTRAN_INT8 lwork, FORTRAN_INT8 info );

// Computes the solution to the system of linear equations with a real or complex symmetric coefficient matrix A stored in packed format, and multiple right-hand sides.
extern void sspsv_( const FORTRAN_CHAR1 uplo, const FORTRAN_INT8 n, const FORTRAN_INT8 nrhs, FORTRAN_REAL4 ap, FORTRAN_INT8 ipiv, FORTRAN_REAL4 b, const FORTRAN_INT8 ldb, FORTRAN_INT8 info );
extern void dspsv_( const FORTRAN_CHAR1 uplo, const FORTRAN_INT8 n, const FORTRAN_INT8 nrhs, FORTRAN_REAL8 ap, FORTRAN_INT8 ipiv, FORTRAN_REAL8 b, const FORTRAN_INT8 ldb, FORTRAN_INT8 info );
extern void cspsv_( const FORTRAN_CHAR1 uplo, const FORTRAN_INT8 n, const FORTRAN_INT8 nrhs, FORTRAN_COMP4 ap, FORTRAN_INT8 ipiv, FORTRAN_COMP4 b, const FORTRAN_INT8 ldb, FORTRAN_INT8 info );
extern void zspsv_( const FORTRAN_CHAR1 uplo, const FORTRAN_INT8 n, const FORTRAN_INT8 nrhs, FORTRAN_COMP8 ap, FORTRAN_INT8 ipiv, FORTRAN_COMP8 b, const FORTRAN_INT8 ldb, FORTRAN_INT8 info );

// Computes the solution to the system of linear equations with a Hermitian coefficient matrix A stored in packed format, and multiple right-hand sides.
extern void chpsv_( const FORTRAN_CHAR1 uplo, const FORTRAN_INT8 n, const FORTRAN_INT8 nrhs, FORTRAN_COMP4 ap, FORTRAN_INT8 ipiv, FORTRAN_COMP4 b, const FORTRAN_INT8 ldb, FORTRAN_INT8 info );
extern void zhpsv_( const FORTRAN_CHAR1 uplo, const FORTRAN_INT8 n, const FORTRAN_INT8 nrhs, FORTRAN_COMP8 ap, FORTRAN_INT8 ipiv, FORTRAN_COMP8 b, const FORTRAN_INT8 ldb, FORTRAN_INT8 info );

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Simple Driver Routines for Generalized Linear Least Squares Problems
//

// Uses QR or LQ factorization to solve a overdetermined or underdetermined linear system with full rank matrix.
extern void sgels_( const FORTRAN_CHAR1 trans, const FORTRAN_INT8 m, const FORTRAN_INT8 n, const FORTRAN_INT8 nrhs, FORTRAN_REAL4 a, const FORTRAN_INT8 lda, FORTRAN_REAL4 b, const FORTRAN_INT8 ldb, FORTRAN_REAL4 work, const FORTRAN_INT8 lwork, FORTRAN_INT8 info );
extern void dgels_( const FORTRAN_CHAR1 trans, const FORTRAN_INT8 m, const FORTRAN_INT8 n, const FORTRAN_INT8 nrhs, FORTRAN_REAL8 a, const FORTRAN_INT8 lda, FORTRAN_REAL8 b, const FORTRAN_INT8 ldb, FORTRAN_REAL8 work, const FORTRAN_INT8 lwork, FORTRAN_INT8 info );
extern void cgels_( const FORTRAN_CHAR1 trans, const FORTRAN_INT8 m, const FORTRAN_INT8 n, const FORTRAN_INT8 nrhs, FORTRAN_COMP4 a, const FORTRAN_INT8 lda, FORTRAN_COMP4 b, const FORTRAN_INT8 ldb, FORTRAN_COMP4 work, const FORTRAN_INT8 lwork, FORTRAN_INT8 info );
extern void zgels_( const FORTRAN_CHAR1 trans, const FORTRAN_INT8 m, const FORTRAN_INT8 n, const FORTRAN_INT8 nrhs, FORTRAN_COMP8 a, const FORTRAN_INT8 lda, FORTRAN_COMP8 b, const FORTRAN_INT8 ldb, FORTRAN_COMP8 work, const FORTRAN_INT8 lwork, FORTRAN_INT8 info );

// Solves the linear equality-constrained least squares problem using a generalized RQ factorization.
extern void sgglse_( const FORTRAN_INT8 m, const FORTRAN_INT8 n, const FORTRAN_INT8 p, FORTRAN_REAL4 a, const FORTRAN_INT8 lda, FORTRAN_REAL4 b, const FORTRAN_INT8 ldb, FORTRAN_REAL4 c, FORTRAN_REAL4 d, FORTRAN_REAL4 x, FORTRAN_REAL4 work, const FORTRAN_INT8 lwork, FORTRAN_INT8 info );
extern void dgglse_( const FORTRAN_INT8 m, const FORTRAN_INT8 n, const FORTRAN_INT8 p, FORTRAN_REAL8 a, const FORTRAN_INT8 lda, FORTRAN_REAL8 b, const FORTRAN_INT8 ldb, FORTRAN_REAL8 c, FORTRAN_REAL8 d, FORTRAN_REAL8 x, FORTRAN_REAL8 work, const FORTRAN_INT8 lwork, FORTRAN_INT8 info );
extern void cgglse_( const FORTRAN_INT8 m, const FORTRAN_INT8 n, const FORTRAN_INT8 p, FORTRAN_COMP4 a, const FORTRAN_INT8 lda, FORTRAN_COMP4 b, const FORTRAN_INT8 ldb, FORTRAN_COMP4 c, FORTRAN_COMP4 d, FORTRAN_COMP4 x, FORTRAN_COMP4 work, const FORTRAN_INT8 lwork, FORTRAN_INT8 info );
extern void zgglse_( const FORTRAN_INT8 m, const FORTRAN_INT8 n, const FORTRAN_INT8 p, FORTRAN_COMP8 a, const FORTRAN_INT8 lda, FORTRAN_COMP8 b, const FORTRAN_INT8 ldb, FORTRAN_COMP8 c, FORTRAN_COMP8 d, FORTRAN_COMP8 x, FORTRAN_COMP8 work, const FORTRAN_INT8 lwork, FORTRAN_INT8 info );

// Solves a general Gauss-Markov linear model problem using a generalized QR factorization.
extern void sgglsm_( const FORTRAN_INT8 m, const FORTRAN_INT8 n, const FORTRAN_INT8 p, FORTRAN_REAL4 a, const FORTRAN_INT8 lda, FORTRAN_REAL4 b, const FORTRAN_INT8 ldb, FORTRAN_REAL4 c, FORTRAN_REAL4 d, FORTRAN_REAL4 x, FORTRAN_REAL4 work, const FORTRAN_INT8 lwork, FORTRAN_INT8 info );
extern void dgglsm_( const FORTRAN_INT8 m, const FORTRAN_INT8 n, const FORTRAN_INT8 p, FORTRAN_REAL8 a, const FORTRAN_INT8 lda, FORTRAN_REAL8 b, const FORTRAN_INT8 ldb, FORTRAN_REAL8 c, FORTRAN_REAL8 d, FORTRAN_REAL8 x, FORTRAN_REAL8 work, const FORTRAN_INT8 lwork, FORTRAN_INT8 info );
extern void cgglsm_( const FORTRAN_INT8 m, const FORTRAN_INT8 n, const FORTRAN_INT8 p, FORTRAN_COMP4 a, const FORTRAN_INT8 lda, FORTRAN_COMP4 b, const FORTRAN_INT8 ldb, FORTRAN_COMP4 c, FORTRAN_COMP4 d, FORTRAN_COMP4 x, FORTRAN_COMP4 work, const FORTRAN_INT8 lwork, FORTRAN_INT8 info );
extern void zgglsm_( const FORTRAN_INT8 m, const FORTRAN_INT8 n, const FORTRAN_INT8 p, FORTRAN_COMP8 a, const FORTRAN_INT8 lda, FORTRAN_COMP8 b, const FORTRAN_INT8 ldb, FORTRAN_COMP8 c, FORTRAN_COMP8 d, FORTRAN_COMP8 x, FORTRAN_COMP8 work, const FORTRAN_INT8 lwork, FORTRAN_INT8 info );

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Simple and Divide and Conquer Driver Routines for Standard Eigenvalue and Singular Value Problems
//

// Computes all eigenvalues and, optionally, eigenvectors of a symmetric or Hermitian matrix.
extern void ssyev_( const FORTRAN_CHAR1 jobz, const FORTRAN_CHAR1 uplo, const FORTRAN_INT8 n, FORTRAN_REAL4 a, const FORTRAN_INT8 lda, FORTRAN_REAL4 w, FORTRAN_REAL4 work, const FORTRAN_INT8 lwork,                      FORTRAN_INT8 info );
extern void dsyev_( const FORTRAN_CHAR1 jobz, const FORTRAN_CHAR1 uplo, const FORTRAN_INT8 n, FORTRAN_REAL8 a, const FORTRAN_INT8 lda, FORTRAN_REAL8 w, FORTRAN_REAL8 work, const FORTRAN_INT8 lwork,                      FORTRAN_INT8 info );
extern void cheev_( const FORTRAN_CHAR1 jobz, const FORTRAN_CHAR1 uplo, const FORTRAN_INT8 n, FORTRAN_COMP4 a, const FORTRAN_INT8 lda, FORTRAN_COMP4 w, FORTRAN_COMP4 work, const FORTRAN_INT8 lwork, FORTRAN_REAL4 rwork, FORTRAN_INT8 info );
extern void zheev_( const FORTRAN_CHAR1 jobz, const FORTRAN_CHAR1 uplo, const FORTRAN_INT8 n, FORTRAN_COMP8 a, const FORTRAN_INT8 lda, FORTRAN_COMP8 w, FORTRAN_COMP8 work, const FORTRAN_INT8 lwork, FORTRAN_REAL8 rwork, FORTRAN_INT8 info );

// Computes all eigenvalues and, optionally, all eigenvectors of a symmetric or Hermitian matrix using divide and conquer algorithm.
extern void ssyevd_( const FORTRAN_CHAR1 jobz, const FORTRAN_CHAR1 uplo, const FORTRAN_INT8 n, FORTRAN_REAL4 a, const FORTRAN_INT8 lda, FORTRAN_REAL4 w, FORTRAN_REAL4 work, const FORTRAN_INT8 lwork,                                                 FORTRAN_INT8 iwork, const FORTRAN_INT8 liwork, FORTRAN_INT8 info );
extern void dsyevd_( const FORTRAN_CHAR1 jobz, const FORTRAN_CHAR1 uplo, const FORTRAN_INT8 n, FORTRAN_REAL8 a, const FORTRAN_INT8 lda, FORTRAN_REAL8 w, FORTRAN_REAL8 work, const FORTRAN_INT8 lwork,                                                 FORTRAN_INT8 iwork, const FORTRAN_INT8 liwork, FORTRAN_INT8 info );
extern void cheevd_( const FORTRAN_CHAR1 jobz, const FORTRAN_CHAR1 uplo, const FORTRAN_INT8 n, FORTRAN_COMP4 a, const FORTRAN_INT8 lda, FORTRAN_COMP4 w, FORTRAN_COMP4 work, const FORTRAN_INT8 lwork, FORTRAN_REAL4 rwork, const FORTRAN_INT8 lrwork, FORTRAN_INT8 iwork, const FORTRAN_INT8 liwork, FORTRAN_INT8 info );
extern void zheevd_( const FORTRAN_CHAR1 jobz, const FORTRAN_CHAR1 uplo, const FORTRAN_INT8 n, FORTRAN_COMP8 a, const FORTRAN_INT8 lda, FORTRAN_COMP8 w, FORTRAN_COMP8 work, const FORTRAN_INT8 lwork, FORTRAN_REAL8 rwork, const FORTRAN_INT8 lrwork, FORTRAN_INT8 iwork, const FORTRAN_INT8 liwork, FORTRAN_INT8 info );

// Computes all eigenvalues and, optionally, eigenvectors of a symmetric or Hermitian matrix in packed storage.
extern void sspev_( const FORTRAN_CHAR1 jobz, const FORTRAN_CHAR1 uplo, const FORTRAN_INT8 n, FORTRAN_REAL4 ap, FORTRAN_REAL4 w, FORTRAN_REAL4 z, const FORTRAN_INT8 ldz, FORTRAN_REAL4 work, const FORTRAN_INT8 lwork,                      FORTRAN_INT8 info );
extern void dspev_( const FORTRAN_CHAR1 jobz, const FORTRAN_CHAR1 uplo, const FORTRAN_INT8 n, FORTRAN_REAL8 ap, FORTRAN_REAL8 w, FORTRAN_REAL8 z, const FORTRAN_INT8 ldz, FORTRAN_REAL8 work, const FORTRAN_INT8 lwork,                      FORTRAN_INT8 info );
extern void chpev_( const FORTRAN_CHAR1 jobz, const FORTRAN_CHAR1 uplo, const FORTRAN_INT8 n, FORTRAN_COMP4 ap, FORTRAN_COMP4 w, FORTRAN_COMP4 z, const FORTRAN_INT8 ldz, FORTRAN_COMP4 work, const FORTRAN_INT8 lwork, FORTRAN_REAL4 rwork, FORTRAN_INT8 info );
extern void zhpev_( const FORTRAN_CHAR1 jobz, const FORTRAN_CHAR1 uplo, const FORTRAN_INT8 n, FORTRAN_COMP8 ap, FORTRAN_COMP8 w, FORTRAN_COMP8 z, const FORTRAN_INT8 ldz, FORTRAN_COMP8 work, const FORTRAN_INT8 lwork, FORTRAN_REAL8 rwork, FORTRAN_INT8 info );

// Computes all eigenvalues and, optionally, all eigenvectors of a symmetric or Hermitian matrix in packed storage using divide and conquer algorithm.
extern void sspevd_( const FORTRAN_CHAR1 jobz, const FORTRAN_CHAR1 uplo, const FORTRAN_INT8 n, FORTRAN_REAL4 ap, FORTRAN_REAL4 w, FORTRAN_REAL4 z, const FORTRAN_INT8 ldz, FORTRAN_REAL4 work, const FORTRAN_INT8 lwork,                                                 FORTRAN_INT8 iwork, const FORTRAN_INT8 liwork, FORTRAN_INT8 info );
extern void dspevd_( const FORTRAN_CHAR1 jobz, const FORTRAN_CHAR1 uplo, const FORTRAN_INT8 n, FORTRAN_REAL8 ap, FORTRAN_REAL8 w, FORTRAN_REAL8 z, const FORTRAN_INT8 ldz, FORTRAN_REAL8 work, const FORTRAN_INT8 lwork,                                                 FORTRAN_INT8 iwork, const FORTRAN_INT8 liwork, FORTRAN_INT8 info );
extern void chpevd_( const FORTRAN_CHAR1 jobz, const FORTRAN_CHAR1 uplo, const FORTRAN_INT8 n, FORTRAN_COMP4 ap, FORTRAN_COMP4 w, FORTRAN_COMP4 z, const FORTRAN_INT8 ldz, FORTRAN_COMP4 work, const FORTRAN_INT8 lwork, FORTRAN_REAL4 rwork, const FORTRAN_INT8 lrwork, FORTRAN_INT8 iwork, const FORTRAN_INT8 liwork, FORTRAN_INT8 info );
extern void zhpevd_( const FORTRAN_CHAR1 jobz, const FORTRAN_CHAR1 uplo, const FORTRAN_INT8 n, FORTRAN_COMP8 ap, FORTRAN_COMP8 w, FORTRAN_COMP8 z, const FORTRAN_INT8 ldz, FORTRAN_COMP8 work, const FORTRAN_INT8 lwork, FORTRAN_REAL8 rwork, const FORTRAN_INT8 lrwork, FORTRAN_INT8 iwork, const FORTRAN_INT8 liwork, FORTRAN_INT8 info );

// Computes all eigenvalues and, optionally, eigenvectors of a symmetric or Hermitian band matrix.
extern void ssbev_( const FORTRAN_CHAR1 jobz, const FORTRAN_CHAR1 uplo, const FORTRAN_INT8 n, const FORTRAN_INT8 kd, FORTRAN_REAL4 a, const FORTRAN_INT8 lda, FORTRAN_REAL4 w, FORTRAN_REAL4 z, const FORTRAN_INT8 ldz, FORTRAN_REAL4 work, const FORTRAN_INT8 lwork,                      FORTRAN_INT8 info );
extern void dsbev_( const FORTRAN_CHAR1 jobz, const FORTRAN_CHAR1 uplo, const FORTRAN_INT8 n, const FORTRAN_INT8 kd, FORTRAN_REAL8 a, const FORTRAN_INT8 lda, FORTRAN_REAL8 w, FORTRAN_REAL8 z, const FORTRAN_INT8 ldz, FORTRAN_REAL8 work, const FORTRAN_INT8 lwork,                      FORTRAN_INT8 info );
extern void chbev_( const FORTRAN_CHAR1 jobz, const FORTRAN_CHAR1 uplo, const FORTRAN_INT8 n, const FORTRAN_INT8 kd, FORTRAN_COMP4 a, const FORTRAN_INT8 lda, FORTRAN_COMP4 w, FORTRAN_COMP4 z, const FORTRAN_INT8 ldz, FORTRAN_COMP4 work, const FORTRAN_INT8 lwork, FORTRAN_REAL4 rwork, FORTRAN_INT8 info );
extern void zhbev_( const FORTRAN_CHAR1 jobz, const FORTRAN_CHAR1 uplo, const FORTRAN_INT8 n, const FORTRAN_INT8 kd, FORTRAN_COMP8 a, const FORTRAN_INT8 lda, FORTRAN_COMP8 w, FORTRAN_COMP8 z, const FORTRAN_INT8 ldz, FORTRAN_COMP8 work, const FORTRAN_INT8 lwork, FORTRAN_REAL8 rwork, FORTRAN_INT8 info );

// Computes all eigenvalues and, optionally, all eigenvectors of a symmetric or Hermitian band matrix using divide and conquer algorithm.
extern void ssbevd_( const FORTRAN_CHAR1 jobz, const FORTRAN_CHAR1 uplo, const FORTRAN_INT8 n, const FORTRAN_INT8 kd, FORTRAN_REAL4 a, const FORTRAN_INT8 lda, FORTRAN_REAL4 w, FORTRAN_REAL4 z, const FORTRAN_INT8 ldz, FORTRAN_REAL4 work, const FORTRAN_INT8 lwork,                                                 FORTRAN_INT8 iwork, const FORTRAN_INT8 liwork, FORTRAN_INT8 info );
extern void dsbevd_( const FORTRAN_CHAR1 jobz, const FORTRAN_CHAR1 uplo, const FORTRAN_INT8 n, const FORTRAN_INT8 kd, FORTRAN_REAL8 a, const FORTRAN_INT8 lda, FORTRAN_REAL8 w, FORTRAN_REAL8 z, const FORTRAN_INT8 ldz, FORTRAN_REAL8 work, const FORTRAN_INT8 lwork,                                                 FORTRAN_INT8 iwork, const FORTRAN_INT8 liwork, FORTRAN_INT8 info );
extern void chbevd_( const FORTRAN_CHAR1 jobz, const FORTRAN_CHAR1 uplo, const FORTRAN_INT8 n, const FORTRAN_INT8 kd, FORTRAN_COMP4 a, const FORTRAN_INT8 lda, FORTRAN_COMP4 w, FORTRAN_COMP4 z, const FORTRAN_INT8 ldz, FORTRAN_COMP4 work, const FORTRAN_INT8 lwork, FORTRAN_REAL4 rwork, const FORTRAN_INT8 lrwork, FORTRAN_INT8 iwork, const FORTRAN_INT8 liwork, FORTRAN_INT8 info );
extern void zhbevd_( const FORTRAN_CHAR1 jobz, const FORTRAN_CHAR1 uplo, const FORTRAN_INT8 n, const FORTRAN_INT8 kd, FORTRAN_COMP8 a, const FORTRAN_INT8 lda, FORTRAN_COMP8 w, FORTRAN_COMP8 z, const FORTRAN_INT8 ldz, FORTRAN_COMP8 work, const FORTRAN_INT8 lwork, FORTRAN_REAL8 rwork, const FORTRAN_INT8 lrwork, FORTRAN_INT8 iwork, const FORTRAN_INT8 liwork, FORTRAN_INT8 info );

// Computes all eigenvalues and, optionally, eigenvectors of a real symmetric tridiagonal matrix.
extern void sstev_( const FORTRAN_CHAR1 jobz, const FORTRAN_INT8 n, const FORTRAN_REAL4 d, FORTRAN_REAL4 e, FORTRAN_REAL4 z, const FORTRAN_INT8 ldz, FORTRAN_REAL4 work, FORTRAN_INT8 info );
extern void dstev_( const FORTRAN_CHAR1 jobz, const FORTRAN_INT8 n, const FORTRAN_REAL8 d, FORTRAN_REAL8 e, FORTRAN_REAL8 z, const FORTRAN_INT8 ldz, FORTRAN_REAL8 work, FORTRAN_INT8 info );

// Computes all eigenvalues and, optionally, all eigenvectors of a real symmetric tridiagonal matrix using divide and conquer algorithm.
extern void sstevd_( const FORTRAN_CHAR1 jobz, const FORTRAN_INT8 n, const FORTRAN_REAL4 d, FORTRAN_REAL4 e, FORTRAN_REAL4 z, const FORTRAN_INT8 ldz, FORTRAN_REAL4 work, const FORTRAN_INT8 lwork, FORTRAN_INT8 iwork, const FORTRAN_INT8 liwork, FORTRAN_INT8 info );
extern void dstevd_( const FORTRAN_CHAR1 jobz, const FORTRAN_INT8 n, const FORTRAN_REAL8 d, FORTRAN_REAL8 e, FORTRAN_REAL8 z, const FORTRAN_INT8 ldz, FORTRAN_REAL8 work, const FORTRAN_INT8 lwork, FORTRAN_INT8 iwork, const FORTRAN_INT8 liwork, FORTRAN_INT8 info );

// Computes the eigenvalues and Schur factorization of a general matrix, and orders the factorization so that selected eigenvalues are at the top left of the Schur form.
extern void sgees_( const FORTRAN_CHAR1 jobvs, const FORTRAN_CHAR1 sort, REAL4_SELECT2(select), const FORTRAN_INT8 n, const FORTRAN_INT8 kd, FORTRAN_REAL4 a, const FORTRAN_INT8 lda, FORTRAN_INT8 sdim, FORTRAN_REAL4 wr, FORTRAN_REAL4 wi, FORTRAN_REAL4 vs, const FORTRAN_INT8 ldvs, FORTRAN_REAL4 work, const FORTRAN_INT8 lwork,                      FORTRAN_INT8 bwork, FORTRAN_INT8 info );
extern void dgees_( const FORTRAN_CHAR1 jobvs, const FORTRAN_CHAR1 sort, REAL4_SELECT2(select), const FORTRAN_INT8 n, const FORTRAN_INT8 kd, FORTRAN_REAL8 a, const FORTRAN_INT8 lda, FORTRAN_INT8 sdim, FORTRAN_REAL8 wr, FORTRAN_REAL8 wi, FORTRAN_REAL8 vs, const FORTRAN_INT8 ldvs, FORTRAN_REAL8 work, const FORTRAN_INT8 lwork,                      FORTRAN_INT8 bwork, FORTRAN_INT8 info );
extern void cgees_( const FORTRAN_CHAR1 jobvs, const FORTRAN_CHAR1 sort, COMP8_SELECT1(select), const FORTRAN_INT8 n, const FORTRAN_INT8 kd, FORTRAN_COMP4 a, const FORTRAN_INT8 lda, FORTRAN_INT8 sdim, FORTRAN_COMP4 w,                    FORTRAN_COMP4 vs, const FORTRAN_INT8 ldvs, FORTRAN_COMP4 work, const FORTRAN_INT8 lwork, FORTRAN_REAL4 rwork, FORTRAN_INT8 bwork, FORTRAN_INT8 info );
extern void zgees_( const FORTRAN_CHAR1 jobvs, const FORTRAN_CHAR1 sort, COMP8_SELECT1(select), const FORTRAN_INT8 n, const FORTRAN_INT8 kd, FORTRAN_COMP8 a, const FORTRAN_INT8 lda, FORTRAN_INT8 sdim, FORTRAN_COMP8 w,                    FORTRAN_COMP8 vs, const FORTRAN_INT8 ldvs, FORTRAN_COMP8 work, const FORTRAN_INT8 lwork, FORTRAN_REAL8 rwork, FORTRAN_INT8 bwork, FORTRAN_INT8 info );

// Computes the eigenvalues and left and right eigenvectors of a general matrix.
extern void sgeev_( const FORTRAN_CHAR1 jobvl, const FORTRAN_CHAR1 jobvr, const FORTRAN_INT8 n, const FORTRAN_INT8 kd, FORTRAN_REAL4 a, const FORTRAN_INT8 lda, FORTRAN_REAL4 wr, FORTRAN_REAL4 wi, FORTRAN_REAL4 vl, const FORTRAN_INT8 ldvl, FORTRAN_REAL4 vr, const FORTRAN_INT8 ldvr, FORTRAN_REAL4 work, const FORTRAN_INT8 lwork,                      FORTRAN_INT8 info );
extern void dgeev_( const FORTRAN_CHAR1 jobvl, const FORTRAN_CHAR1 jobvr, const FORTRAN_INT8 n, const FORTRAN_INT8 kd, FORTRAN_REAL8 a, const FORTRAN_INT8 lda, FORTRAN_REAL8 wr, FORTRAN_REAL8 wi, FORTRAN_REAL8 vl, const FORTRAN_INT8 ldvl, FORTRAN_REAL8 vr, const FORTRAN_INT8 ldvr, FORTRAN_REAL8 work, const FORTRAN_INT8 lwork,                      FORTRAN_INT8 info );
extern void cgeev_( const FORTRAN_CHAR1 jobvl, const FORTRAN_CHAR1 jobvr, const FORTRAN_INT8 n, const FORTRAN_INT8 kd, FORTRAN_COMP4 a, const FORTRAN_INT8 lda, FORTRAN_COMP4 w,                    FORTRAN_COMP4 vl, const FORTRAN_INT8 ldvl, FORTRAN_COMP4 vr, const FORTRAN_INT8 ldvr, FORTRAN_COMP4 work, const FORTRAN_INT8 lwork, FORTRAN_REAL4 rwork, FORTRAN_INT8 info );
extern void zgeev_( const FORTRAN_CHAR1 jobvl, const FORTRAN_CHAR1 jobvr, const FORTRAN_INT8 n, const FORTRAN_INT8 kd, FORTRAN_COMP8 a, const FORTRAN_INT8 lda, FORTRAN_COMP8 w,                    FORTRAN_COMP8 vl, const FORTRAN_INT8 ldvl, FORTRAN_COMP8 vr, const FORTRAN_INT8 ldvr, FORTRAN_COMP8 work, const FORTRAN_INT8 lwork, FORTRAN_REAL8 rwork, FORTRAN_INT8 info );

// Computes the eigenvalues and left and right eigenvectors of a general matrix.
extern void sgeev_( const FORTRAN_CHAR1 jobvl, const FORTRAN_CHAR1 jobvr, const FORTRAN_INT8 n, const FORTRAN_INT8 kd, FORTRAN_REAL4 a, const FORTRAN_INT8 lda, FORTRAN_REAL4 wr, FORTRAN_REAL4 wi, FORTRAN_REAL4 vl, const FORTRAN_INT8 ldvl, FORTRAN_REAL4 vr, const FORTRAN_INT8 ldvr, FORTRAN_REAL4 work, const FORTRAN_INT8 lwork,                      FORTRAN_INT8 info );
extern void dgeev_( const FORTRAN_CHAR1 jobvl, const FORTRAN_CHAR1 jobvr, const FORTRAN_INT8 n, const FORTRAN_INT8 kd, FORTRAN_REAL8 a, const FORTRAN_INT8 lda, FORTRAN_REAL8 wr, FORTRAN_REAL8 wi, FORTRAN_REAL8 vl, const FORTRAN_INT8 ldvl, FORTRAN_REAL8 vr, const FORTRAN_INT8 ldvr, FORTRAN_REAL8 work, const FORTRAN_INT8 lwork,                      FORTRAN_INT8 info );
extern void cgeev_( const FORTRAN_CHAR1 jobvl, const FORTRAN_CHAR1 jobvr, const FORTRAN_INT8 n, const FORTRAN_INT8 kd, FORTRAN_COMP4 a, const FORTRAN_INT8 lda, FORTRAN_COMP4 w,                    FORTRAN_COMP4 vl, const FORTRAN_INT8 ldvl, FORTRAN_COMP4 vr, const FORTRAN_INT8 ldvr, FORTRAN_COMP4 work, const FORTRAN_INT8 lwork, FORTRAN_REAL4 rwork, FORTRAN_INT8 info );
extern void zgeev_( const FORTRAN_CHAR1 jobvl, const FORTRAN_CHAR1 jobvr, const FORTRAN_INT8 n, const FORTRAN_INT8 kd, FORTRAN_COMP8 a, const FORTRAN_INT8 lda, FORTRAN_COMP8 w,                    FORTRAN_COMP8 vl, const FORTRAN_INT8 ldvl, FORTRAN_COMP8 vr, const FORTRAN_INT8 ldvr, FORTRAN_COMP8 work, const FORTRAN_INT8 lwork, FORTRAN_REAL8 rwork, FORTRAN_INT8 info );

// Computes the singular value decomposition of a general rectangular matrix.
extern void sgesvd_( const FORTRAN_CHAR1 jobu, const FORTRAN_CHAR1 jobvt, const FORTRAN_INT8 m, const FORTRAN_INT8 n, FORTRAN_REAL4 a, const FORTRAN_INT8 lda, FORTRAN_REAL4 s, FORTRAN_REAL4 u, const FORTRAN_INT8 ldu, FORTRAN_REAL4 vt, const FORTRAN_INT8 ldvt, FORTRAN_REAL4 work, const FORTRAN_INT8 lwork,                      FORTRAN_INT8 info );
extern void dgesvd_( const FORTRAN_CHAR1 jobu, const FORTRAN_CHAR1 jobvt, const FORTRAN_INT8 m, const FORTRAN_INT8 n, FORTRAN_REAL8 a, const FORTRAN_INT8 lda, FORTRAN_REAL8 s, FORTRAN_REAL8 u, const FORTRAN_INT8 ldu, FORTRAN_REAL8 vt, const FORTRAN_INT8 ldvt, FORTRAN_REAL8 work, const FORTRAN_INT8 lwork,                      FORTRAN_INT8 info );
extern void cgesvd_( const FORTRAN_CHAR1 jobu, const FORTRAN_CHAR1 jobvt, const FORTRAN_INT8 m, const FORTRAN_INT8 n, FORTRAN_COMP4 a, const FORTRAN_INT8 lda, FORTRAN_COMP4 s, FORTRAN_COMP4 u, const FORTRAN_INT8 ldu, FORTRAN_COMP4 vt, const FORTRAN_INT8 ldvt, FORTRAN_COMP4 work, const FORTRAN_INT8 lwork, FORTRAN_REAL4 rwork, FORTRAN_INT8 info );
extern void zgesvd_( const FORTRAN_CHAR1 jobu, const FORTRAN_CHAR1 jobvt, const FORTRAN_INT8 m, const FORTRAN_INT8 n, FORTRAN_COMP8 a, const FORTRAN_INT8 lda, FORTRAN_COMP8 s, FORTRAN_COMP8 u, const FORTRAN_INT8 ldu, FORTRAN_COMP8 vt, const FORTRAN_INT8 ldvt, FORTRAN_COMP8 work, const FORTRAN_INT8 lwork, FORTRAN_REAL8 rwork, FORTRAN_INT8 info );

// Computes the singular value decomposition of a general rectangular matrix using a divide and conquer method.
extern void sgesdd_( const FORTRAN_CHAR1 jobz, const FORTRAN_INT8 m, const FORTRAN_INT8 n, FORTRAN_REAL4 a, const FORTRAN_INT8 lda, FORTRAN_REAL4 s, FORTRAN_REAL4 u, const FORTRAN_INT8 ldu, FORTRAN_REAL4 vt, const FORTRAN_INT8 ldvt, FORTRAN_REAL4 work, const FORTRAN_INT8 lwork,                      FORTRAN_INT8 info );
extern void dgesdd_( const FORTRAN_CHAR1 jobz, const FORTRAN_INT8 m, const FORTRAN_INT8 n, FORTRAN_REAL8 a, const FORTRAN_INT8 lda, FORTRAN_REAL8 s, FORTRAN_REAL8 u, const FORTRAN_INT8 ldu, FORTRAN_REAL8 vt, const FORTRAN_INT8 ldvt, FORTRAN_REAL8 work, const FORTRAN_INT8 lwork,                      FORTRAN_INT8 info );
extern void cgesdd_( const FORTRAN_CHAR1 jobz, const FORTRAN_INT8 m, const FORTRAN_INT8 n, FORTRAN_COMP4 a, const FORTRAN_INT8 lda, FORTRAN_COMP4 s, FORTRAN_COMP4 u, const FORTRAN_INT8 ldu, FORTRAN_COMP4 vt, const FORTRAN_INT8 ldvt, FORTRAN_COMP4 work, const FORTRAN_INT8 lwork, FORTRAN_REAL4 rwork, FORTRAN_INT8 info );
extern void zgesdd_( const FORTRAN_CHAR1 jobz, const FORTRAN_INT8 m, const FORTRAN_INT8 n, FORTRAN_COMP8 a, const FORTRAN_INT8 lda, FORTRAN_COMP8 s, FORTRAN_COMP8 u, const FORTRAN_INT8 ldu, FORTRAN_COMP8 vt, const FORTRAN_INT8 ldvt, FORTRAN_COMP8 work, const FORTRAN_INT8 lwork, FORTRAN_REAL8 rwork, FORTRAN_INT8 info );

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

#undef REAL4_SELECT2
#undef REAL8_SELECT2
#undef COMP4_SELECT1
#undef COMP8_SELECT1

}  // extern "C"

#endif  // DOXYGEN_SHOULD_SKIP_THIS

#endif  // ISVD_LAPACK_LAPACKF_HPP_
