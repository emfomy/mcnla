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
#include <mcnla/core/lapack/engine/syev.hpp>

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
/// @copydoc  mcnla::lapack::SyevEngine::compute
///
/// @see  mcnla::lapack::SyevEngine
///
template <JobOption _jobz, typename _Scalar, Trans _trans, Uplo _uplo>
inline void syev(
    DenseSymmetricMatrix<_Scalar, _trans, _uplo> &a,
    DenseVector<RealScalar<_Scalar>> &w
) noexcept {
  SyevEngine<DenseSymmetricMatrix<_Scalar, _trans, _uplo>, _jobz> engine(a);
  engine(a, w);
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <JobOption _jobz, Uplo _uplo = Uplo::LOWER, class _TypeA, class _TypeW>
inline void syev( _TypeA &&a, _TypeW &&w ) noexcept {
  syev<_jobz, _uplo>(a, w);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace lapack

}  // namespace mcnla

#endif  // MCNLA_CORE_LAPACK_ROUTINE_SYEV_HPP_
