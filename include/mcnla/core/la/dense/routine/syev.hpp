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
#include <mcnla/core/la/dense/driver/syev.hpp>

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
/// @copydoc  mcnla::la::DenseSyevDriver::compute
///
/// @see  mcnla::la::DenseSyevDriver
///
template <JobOption _jobz, typename _Val, Trans _trans, Uplo _uplo>
inline void syev(
    DenseSymmetricMatrix<_Val, _trans, _uplo> &a,
    DenseVector<RealValT<_Val>> &w
) noexcept {
  DenseSyevDriver<_jobz, _Val, _trans, _uplo> driver(a);
  driver(a, w);
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <JobOption _jobz, class _TypeA, class _TypeW>
inline void syev(
    _TypeA &&a,
    _TypeW &&w
) noexcept {
  syev<_jobz>(a, w);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace la

}  // namespace mcnla

#endif  // MCNLA_CORE_LA_DENSE_ROUTINE_SYEV_HPP_
