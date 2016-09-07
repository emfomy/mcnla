////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/blas/blas/iamin.hpp
/// @brief   The BLAS IAMIN.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_BLAS_BLAS_IAMIN_HPP_
#define ISVD_BLAS_BLAS_IAMIN_HPP_

#include <isvd/isvd.hpp>

#ifndef DOXYGEN_SHOULD_SKIP_THIS

#ifdef ISVD_USE_MKL

#include <isvd/plugin/blas_plugin_begin.h>

// Finds the index of the element with minimum absolute value.
extern CPP_INT8 isamin_( const FORTRAN_INT8 n, const FORTRAN_REAL4 x, const FORTRAN_INT8 incx );
extern CPP_INT8 idamin_( const FORTRAN_INT8 n, const FORTRAN_REAL8 x, const FORTRAN_INT8 incx );
extern CPP_INT8 icamin_( const FORTRAN_INT8 n, const FORTRAN_COMP4 x, const FORTRAN_INT8 incx );
extern CPP_INT8 izamin_( const FORTRAN_INT8 n, const FORTRAN_COMP8 x, const FORTRAN_INT8 incx );

#include <isvd/plugin/blas_plugin_end.h>

#else  // ISVD_USE_MKL

#include <cmath>
#include <complex>

#endif  // ISVD_USE_MKL

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
/// @brief  Finds the index of the element with minimum absolute value.
///
//@{
#ifdef ISVD_USE_MKL
static inline index_t iamin(
    const index_t n, const float* x, const index_t incx
) noexcept { return isamin_(&n, x, &incx) - 1; }
static inline index_t iamin(
    const index_t n, const double* x, const index_t incx
) noexcept { return idamin_(&n, x, &incx) - 1; }
static inline index_t iamin(
    const index_t n, const std::complex<float>* x, const index_t incx
) noexcept { return icamin_(&n, x, &incx) - 1; }
static inline index_t iamin(
    const index_t n, const std::complex<double>* x, const index_t incx
) noexcept { return izamin_(&n, x, &incx) - 1; }
#else  // ISVD_USE_MKL
template <typename _Scalar>
inline index_t iamin(
    const index_t n, const _Scalar* x, const index_t incx
) noexcept {
  if ( n < 1 || incx <= 0 ) { return -1; }
  if ( n == 1 ) { return 0; }
  index_t idamin = 0;
  auto smin = std::abs(x[0]);
  for ( index_t i = 1, j = incx; i < n; ++i, j += incx ) {
    if ( std::abs(x[j]) < smin) { idamin = i; }
  }
  return idamin;
}
#endif  // ISVD_USE_MKL
//@}

}  // namespace internal

}  // namespace blas

}  // namespace isvd

#endif  // ISVD_BLAS_BLAS_IAMIN_HPP_
