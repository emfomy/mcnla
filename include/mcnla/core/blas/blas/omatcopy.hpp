////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/blas/blas/omatcopy.hpp
/// @brief   The BLAS OMATCOPY.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_BLAS_BLAS_OMATCOPY_HPP_
#define MCNLA_CORE_BLAS_BLAS_OMATCOPY_HPP_

#include <mcnla/def.hpp>
#include <mcnla/core/def.hpp>

#ifndef DOXYGEN_SHOULD_SKIP_THIS

#ifdef MCNLA_USE_MKL

#include <mcnla/core/blas/plugin/blas_plugin_begin.h>

// Performs scaling and out-place transposition/copying of matrices.
extern void mkl_somatcopy_( const FORTRAN_CHAR1 ordering, const FORTRAN_CHAR1 trans, const FORTRAN_INT rows,
                            const FORTRAN_INT cols, const FORTRAN_REAL4 alpha, const FORTRAN_REAL4 a, const FORTRAN_INT lda,
                            const FORTRAN_REAL4 b, const FORTRAN_INT ldb );
extern void mkl_domatcopy_( const FORTRAN_CHAR1 ordering, const FORTRAN_CHAR1 trans, const FORTRAN_INT rows,
                            const FORTRAN_INT cols, const FORTRAN_REAL8 alpha, const FORTRAN_REAL8 a, const FORTRAN_INT lda,
                            const FORTRAN_REAL8 b, const FORTRAN_INT ldb );
extern void mkl_comatcopy_( const FORTRAN_CHAR1 ordering, const FORTRAN_CHAR1 trans, const FORTRAN_INT rows,
                            const FORTRAN_INT cols, const FORTRAN_COMP4 alpha, const FORTRAN_COMP4 a, const FORTRAN_INT lda,
                            const FORTRAN_COMP4 b, const FORTRAN_INT ldb );
extern void mkl_zomatcopy_( const FORTRAN_CHAR1 ordering, const FORTRAN_CHAR1 trans, const FORTRAN_INT rows,
                            const FORTRAN_INT cols, const FORTRAN_COMP8 alpha, const FORTRAN_COMP8 a, const FORTRAN_INT lda,
                            const FORTRAN_COMP8 b, const FORTRAN_INT ldb );

#include <mcnla/core/blas/plugin/blas_plugin_end.h>

#else  // MCNLA_USE_MKL

#include <mcnla/core/blas/blas/copy.hpp>

#endif  // MCNLA_USE_MKL

#endif  // DOXYGEN_SHOULD_SKIP_THIS

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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Performs scaling and out-place transposition/copying of matrices.
///
//@{
#ifdef MCNLA_USE_MKL

static inline void omatcopy(
    const char ordering, const char trans, const index_t rows, const index_t cols, const float alpha,
    const float* a, const index_t lda, float* b, index_t ldb
) noexcept { mkl_somatcopy_(&ordering, &trans, &rows, &cols, &alpha, a, &lda, b, &ldb); }
static inline void omatcopy(
    const char ordering, const char trans, const index_t rows, const index_t cols, const double alpha,
     const double* a, const index_t lda, double* b, index_t ldb
) noexcept { mkl_domatcopy_(&ordering, &trans, &rows, &cols, &alpha, a, &lda, b, &ldb); }
static inline void omatcopy(
    const char ordering, const char trans, const index_t rows, const index_t cols, const std::complex<float> alpha,
    const std::complex<float>* a, const index_t lda, std::complex<float>* b, index_t ldb
) noexcept { mkl_comatcopy_(&ordering, &trans, &rows, &cols, &alpha, a, &lda, b, &ldb); }
static inline void omatcopy(
    const char ordering, const char trans, const index_t rows, const index_t cols, const std::complex<double> alpha,
    const std::complex<double>* a, const index_t lda, std::complex<double>* b, index_t ldb
) noexcept { mkl_zomatcopy_(&ordering, &trans, &rows, &cols, &alpha, a, &lda, b, &ldb); }

#else  // MCNLA_USE_MKL

template <typename _Scalar>
inline void omatcopy(
    const char ordering, const char trans, const index_t rows, const index_t cols, const _Scalar alpha,
    const _Scalar* a, const index_t lda, _Scalar* b, index_t ldb
) noexcept {
  #pragma warning Not Implemented!
}

#endif  // MCNLA_USE_MKL
//@}

}  // namespace detail

}  // namespace blas

}  // namespace mcnla

#endif  // MCNLA_CORE_BLAS_BLAS_OMATCOPY_HPP_
