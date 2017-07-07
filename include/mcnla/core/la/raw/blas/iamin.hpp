////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/la/raw/blas/iamin.hpp
/// @brief   The BLAS IAMIN.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_LA_RAW_BLAS_IAMIN_HPP_
#define MCNLA_CORE_LA_RAW_BLAS_IAMIN_HPP_

#include <mcnla/core/la/def.hpp>

#ifndef DOXYGEN_SHOULD_SKIP_THIS

#ifdef MCNLA_USE_MKL

#include <mcnla/core/la/raw/plugin/blas_plugin_begin.h>

extern CPP_INT isamin_( const FORTRAN_INT n, const FORTRAN_REAL4 x, const FORTRAN_INT incx );
extern CPP_INT idamin_( const FORTRAN_INT n, const FORTRAN_REAL8 x, const FORTRAN_INT incx );
extern CPP_INT icamin_( const FORTRAN_INT n, const FORTRAN_COMP4 x, const FORTRAN_INT incx );
extern CPP_INT izamin_( const FORTRAN_INT n, const FORTRAN_COMP8 x, const FORTRAN_INT incx );

#include <mcnla/core/la/raw/plugin/blas_plugin_end.h>

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

#else  // MCNLA_USE_MKL

template <typename _Val>
static inline index_t iamin(
    const index_t n, const _Val* x, const index_t incx
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

#endif  // MCNLA_USE_MKL
//@}

}  // namespace detail

}  // namespace la

}  // namespace mcnla

#endif  // MCNLA_CORE_LA_RAW_BLAS_IAMIN_HPP_
