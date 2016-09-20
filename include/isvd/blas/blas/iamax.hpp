////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/blas/blas/iamax.hpp
/// @brief   The BLAS IAMAX.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_BLAS_BLAS_IAMAX_HPP_
#define ISVD_BLAS_BLAS_IAMAX_HPP_

#include <isvd/isvd.hpp>

#ifndef DOXYGEN_SHOULD_SKIP_THIS

#include <isvd/plugin/blas_plugin_begin.h>

// Finds the index of the element with maximum absolute value.
extern CPP_INT8 isamax_( const FORTRAN_INT8 n, const FORTRAN_REAL4 x, const FORTRAN_INT8 incx );
extern CPP_INT8 idamax_( const FORTRAN_INT8 n, const FORTRAN_REAL8 x, const FORTRAN_INT8 incx );
extern CPP_INT8 icamax_( const FORTRAN_INT8 n, const FORTRAN_COMP4 x, const FORTRAN_INT8 incx );
extern CPP_INT8 izamax_( const FORTRAN_INT8 n, const FORTRAN_COMP8 x, const FORTRAN_INT8 incx );

#include <isvd/plugin/blas_plugin_end.h>

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
//  The detail namespace
//
namespace detail {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Finds the index of the element with maximum absolute value.
///
//@{
static inline index_t iamax(
    const index_t n, const float* x, const index_t incx
) noexcept { return isamax_(&n, x, &incx) - 1; }
static inline index_t iamax(
    const index_t n, const double* x, const index_t incx
) noexcept { return idamax_(&n, x, &incx) - 1; }
static inline index_t iamax(
    const index_t n, const std::complex<float>* x, const index_t incx
) noexcept { return icamax_(&n, x, &incx) - 1; }
static inline index_t iamax(
    const index_t n, const std::complex<double>* x, const index_t incx
) noexcept { return izamax_(&n, x, &incx) - 1; }
//@}

}  // namespace detail

}  // namespace blas

}  // namespace isvd

#endif  // ISVD_BLAS_BLAS_IAMAX_HPP_
