////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/la/raw/blas/omatcopy.hpp
/// @brief   The BLAS OMATCOPY.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_LA_RAW_BLAS_OMATCOPY_HPP_
#define MCNLA_CORE_LA_RAW_BLAS_OMATCOPY_HPP_

#include <mcnla/core/la/def.hpp>

#ifndef DOXYGEN_SHOULD_SKIP_THIS

#ifdef MCNLA_USE_MKL

#include <mcnla/core/la/raw/plugin/blas_plugin_begin.h>

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

#include <mcnla/core/la/raw/plugin/blas_plugin_end.h>

#else  // MCNLA_USE_MKL

#include <mcnla/core/la/raw/blas/copy.hpp>

#endif  // MCNLA_USE_MKL

#endif  // DOXYGEN_SHOULD_SKIP_THIS

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

template <typename _Val>
inline void omatcopy(
    const char ordering, const char trans, const index_t rows, const index_t cols, const _Val alpha,
    const _Val* a, const index_t lda, _Val* b, index_t ldb
) noexcept {
}

#endif  // MCNLA_USE_MKL
//@}

}  // namespace detail

}  // namespace la

}  // namespace mcnla

#endif  // MCNLA_CORE_LA_RAW_BLAS_OMATCOPY_HPP_
