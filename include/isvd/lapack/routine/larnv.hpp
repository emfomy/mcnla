////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/lapack/routine/larnv.hpp
/// @brief   The LAPACK LARNV & GELQF routines.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_LAPACK_ROUTINE_LARNV_HPP_
#define ISVD_LAPACK_ROUTINE_LARNV_HPP_

#include <isvd/utility/traits.hpp>
#include <isvd/matrix.hpp>
#include <isvd/lapack/lapack.hpp>

#ifndef DOXYGEN_SHOULD_SKIP_THIS

extern "C" {

#include <isvd/plugin/lapack_plugin_start.h>

// Returns a vector of random numbers from a uniform or normal distribution.
extern void slarnv_( const FORTRAN_INT8 idist, const FORTRAN_INT8 iseed, const FORTRAN_INT8 n, FORTRAN_REAL4 x );
extern void dlarnv_( const FORTRAN_INT8 idist, const FORTRAN_INT8 iseed, const FORTRAN_INT8 n, FORTRAN_REAL8 x );
extern void clarnv_( const FORTRAN_INT8 idist, const FORTRAN_INT8 iseed, const FORTRAN_INT8 n, FORTRAN_COMP4 x );
extern void zlarnv_( const FORTRAN_INT8 idist, const FORTRAN_INT8 iseed, const FORTRAN_INT8 n, FORTRAN_COMP8 x );

#include <isvd/plugin/lapack_plugin_end.h>

}  // extern "C"

#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The LAPACK namespace
//
namespace lapack {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The internal namespace
//
namespace internal {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc isvd::lapack::larnv
///
//@{
static inline void larnv(
    const index_t idist, const index_t iseed[4], const index_t n, float *x
) noexcept { slarnv_(&idist, iseed, &n, x); }
static inline void larnv(
    const index_t idist, const index_t iseed[4], const index_t n, double *x
) noexcept { dlarnv_(&idist, iseed, &n, x); }
static inline void larnv(
    const index_t idist, const index_t iseed[4], const index_t n, std::complex<float> *x
) noexcept { clarnv_(&idist, iseed, &n, x); }
static inline void larnv(
    const index_t idist, const index_t iseed[4], const index_t n, std::complex<double> *x
) noexcept { zlarnv_(&idist, iseed, &n, x); }
//@}

}  // namespace internal

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Returns a vector of random numbers from a uniform or normal distribution.
///
//@{
template <index_t idist, typename _Scalar>
inline void larnv(
    DenseVector<_Scalar> &x,
    const index_t iseed[4]
) noexcept {
  static_assert(isvd::internal::ScalarTraits<_Scalar>::is_real ? (1 <= idist && idist <= 3) : (1 <= idist && idist <= 5),
                "The value of 'idist' is invalid!");
  internal::larnv(idist, iseed, x.getLength(), x.getValue());
}

template <index_t idist, class _TypeX>
inline void larnv( _TypeX &&x, const index_t iseed[4] ) noexcept {
  larnv<idist>(x, iseed);
}
//@}

}  // namespace lapack

}  // namespace isvd

#endif  // ISVD_LAPACK_ROUTINE_LARNV_HPP_
