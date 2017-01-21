////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/la/dense/routine/syev.hpp
/// @brief   The LAPACK SYEV routine.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_LA_DENSE_ROUTINE_SYEV_HPP_
#define MCNLA_CORE_LA_DENSE_ROUTINE_SYEV_HPP_

#include <mcnla/core/la/def.hpp>
#include <mcnla/core/matrix.hpp>
#include <mcnla/core/la/dense/engine/syev.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The linear algebra namespace
//
namespace la {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  la_dense_lapack_ls_module
/// @copydoc  mcnla::la::SyevEngine::compute
///
/// @see  mcnla::la::SyevEngine
///
template <JobOption _jobz, typename _Scalar, Trans _trans, Uplo _uplo>
inline void syev(
    DenseSymmetricMatrix<_Scalar, _trans, _uplo> &a,
    DenseVector<RealScalarT<_Scalar>> &w
) noexcept {
  SyevEngine<DenseSymmetricMatrix<_Scalar, _trans, _uplo>, _jobz> engine(a);
  engine(a, w);
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <JobOption _jobz, Uplo _uplo = Uplo::LOWER, class _TypeA, class _TypeW>
inline void syev(
    _TypeA &&a,
    _TypeW &&w
) noexcept {
  syev<_jobz, _uplo>(a, w);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace la

}  // namespace mcnla

#endif  // MCNLA_CORE_LA_DENSE_ROUTINE_SYEV_HPP_
