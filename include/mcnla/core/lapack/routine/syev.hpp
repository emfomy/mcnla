////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/lapack/routine/syev.hpp
/// @brief   The LAPACK SYEV routine.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_LAPACK_ROUTINE_SYEV_HPP_
#define MCNLA_CORE_LAPACK_ROUTINE_SYEV_HPP_

#include <mcnla/def.hpp>
#include <mcnla/core/def.hpp>
#include <mcnla/core/lapack/def.hpp>
#include <mcnla/core/matrix.hpp>
#include <mcnla/core/lapack/driver/syev.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The LAPACK namespace
//
namespace lapack {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  lapack_driver_module
/// @copydoc  mcnla::lapack::SyevDriver::compute
///
/// @see  mcnla::lapack::SyevDriver
///
template <JobOption _jobz, UploOption _uplo = UploOption::LOWER, typename _Scalar, Layout _layout>
inline void syev(
    DenseMatrix<_Scalar, _layout> &a,
    DenseVector<RealType<_Scalar>> &w
) noexcept {
  SyevDriver<DenseMatrix<_Scalar, _layout>, _jobz, _uplo> driver(a);
  driver(a, w);
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <JobOption _jobz, UploOption _uplo = UploOption::LOWER, class _TypeA, class _TypeW>
inline void syev( _TypeA &&a, _TypeW &&w ) noexcept {
  syev<_jobz, _uplo>(a, w);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace lapack

}  // namespace mcnla

#endif  // MCNLA_CORE_LAPACK_ROUTINE_SYEV_HPP_
