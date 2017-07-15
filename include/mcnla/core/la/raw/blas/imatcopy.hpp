////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/la/raw/blas/imatcopy.hpp
/// @brief   The BLAS IMATCOPY.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_LA_RAW_BLAS_IMATCOPY_HPP_
#define MCNLA_CORE_LA_RAW_BLAS_IMATCOPY_HPP_

#include <mcnla/core/la/def.hpp>

#ifndef DOXYGEN_SHOULD_SKIP_THIS

#ifdef MCNLA_USE_MKL

#include <mcnla/core/la/raw/plugin/blas_plugin_begin.h>

extern void mkl_simatcopy_( const FORTRAN_CHAR1 ordering, const FORTRAN_CHAR1 trans, const FORTRAN_INT rows,
                            const FORTRAN_INT cols, const FORTRAN_REAL4 alpha, const FORTRAN_REAL4 ab, const FORTRAN_INT lda,
                            const FORTRAN_INT ldb );
extern void mkl_dimatcopy_( const FORTRAN_CHAR1 ordering, const FORTRAN_CHAR1 trans, const FORTRAN_INT rows,
                            const FORTRAN_INT cols, const FORTRAN_REAL8 alpha, const FORTRAN_REAL8 ab, const FORTRAN_INT lda,
                            const FORTRAN_INT ldb );
extern void mkl_cimatcopy_( const FORTRAN_CHAR1 ordering, const FORTRAN_CHAR1 trans, const FORTRAN_INT rows,
                            const FORTRAN_INT cols, const FORTRAN_COMP4 alpha, const FORTRAN_COMP4 ab, const FORTRAN_INT lda,
                            const FORTRAN_INT ldb );
extern void mkl_zimatcopy_( const FORTRAN_CHAR1 ordering, const FORTRAN_CHAR1 trans, const FORTRAN_INT rows,
                            const FORTRAN_INT cols, const FORTRAN_COMP8 alpha, const FORTRAN_COMP8 ab, const FORTRAN_INT lda,
                            const FORTRAN_INT ldb );

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

static inline void imatcopy(
    const char ordering, const char trans, const index_t rows, const index_t cols, const float alpha,
    const float* ab, const index_t lda, const index_t ldb
) noexcept { mkl_simatcopy_(&ordering, &trans, &rows, &cols, &alpha, ab, &lda, &ldb); }
static inline void imatcopy(
    const char ordering, const char trans, const index_t rows, const index_t cols, const double alpha,
     const double* ab, const index_t lda, const index_t ldb
) noexcept { mkl_dimatcopy_(&ordering, &trans, &rows, &cols, &alpha, ab, &lda, &ldb); }
static inline void imatcopy(
    const char ordering, const char trans, const index_t rows, const index_t cols, const std::complex<float> alpha,
    const std::complex<float>* ab, const index_t lda, const index_t ldb
) noexcept { mkl_cimatcopy_(&ordering, &trans, &rows, &cols, &alpha, ab, &lda, &ldb); }
static inline void imatcopy(
    const char ordering, const char trans, const index_t rows, const index_t cols, const std::complex<double> alpha,
    const std::complex<double>* ab, const index_t lda, const index_t ldb
) noexcept { mkl_zimatcopy_(&ordering, &trans, &rows, &cols, &alpha, ab, &lda, &ldb); }

#else  // MCNLA_USE_MKL

template <typename _Val>
inline void imatcopy(
    const char ordering, const char trans, const index_t rows, const index_t cols, const _Val alpha,
    const _Val* ab, const index_t lda, const index_t ldb
) noexcept;

#endif  // MCNLA_USE_MKL
//@}

}  // namespace detail

}  // namespace la

}  // namespace mcnla

#endif  // MCNLA_CORE_LA_RAW_BLAS_IMATCOPY_HPP_
