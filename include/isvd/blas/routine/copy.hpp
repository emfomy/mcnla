////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/blas/routine/copy.hpp
/// @brief   The BLAS COPY routine.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_BLAS_ROUTINE_COPY_HPP_
#define ISVD_BLAS_ROUTINE_COPY_HPP_

#include <isvd/matrix.hpp>
#include <isvd/blas/blas.hpp>

#ifndef DOXYGEN_SHOULD_SKIP_THIS

extern "C" {

#include <isvd/plugin/blas_plugin_start.h>

// Copies vector to another vector.
extern void scopy_( const FORTRAN_INT8 n, const FORTRAN_REAL4 x, const FORTRAN_INT8 incx, FORTRAN_REAL4 y,
                    const FORTRAN_INT8 incy );
extern void dcopy_( const FORTRAN_INT8 n, const FORTRAN_REAL8 x, const FORTRAN_INT8 incx, FORTRAN_REAL8 y,
                    const FORTRAN_INT8 incy );
extern void ccopy_( const FORTRAN_INT8 n, const FORTRAN_COMP4 x, const FORTRAN_INT8 incx, FORTRAN_COMP4 y,
                    const FORTRAN_INT8 incy );
extern void zcopy_( const FORTRAN_INT8 n, const FORTRAN_COMP8 x, const FORTRAN_INT8 incx, FORTRAN_COMP8 y,
                    const FORTRAN_INT8 incy );

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
/// @copydoc isvd::blas::copy
///
//@{
static inline void copy(
    const index_t n, const float* x, const index_t incx, float* y, const index_t incy
) noexcept { scopy_(&n, x, &incx, y, &incy); }
static inline void copy(
    const index_t n, const double* x, const index_t incx, double* y, const index_t incy
) noexcept { dcopy_(&n, x, &incx, y, &incy); }
static inline void copy(
    const index_t n, const std::complex<float>* x, const index_t incx, std::complex<float>* y, const index_t incy
) noexcept { ccopy_(&n, x, &incx, y, &incy); }
static inline void copy(
    const index_t n, const std::complex<double>* x, const index_t incx, std::complex<double>* y, const index_t incy
) noexcept { zcopy_(&n, x, &incx, y, &incy); }
//@}

}  // namespace internal

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copies vector to another vector.
///
//@{
template <typename _Scalar>
inline void copy(
    const DenseVector<_Scalar> &x,
          DenseVector<_Scalar> &y
) noexcept {
  assert(y.getLength() == x.getLength());
  internal::copy(x.getLength(), x.getValue(), x.getIncrement(), y.getValue(), y.getIncrement());
}

template <typename _Scalar>
inline void copy(
    const DenseVector<_Scalar> &x,
          DenseVector<_Scalar> &&y
) noexcept {
  copy(x, y);
}
//@}

}  // namespace blas

}  // namespace isvd

#endif  // ISVD_BLAS_ROUTINE_COPY_HPP_
