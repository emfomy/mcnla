////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/lapack/solver/syev_solver.ipp
/// @brief   The implementation of LAPACK SYEV solver.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_LAPACK_SOLVER_SYEV_SOLVER_IPP_
#define ISVD_LAPACK_SOLVER_SYEV_SOLVER_IPP_

#include <isvd/utility/traits.hpp>
#include <isvd/matrix.hpp>
#include <isvd/lapack/routine.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The LAPACK namespace
//
namespace lapack {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <class _Matrix, JobOption _jobz, UploOption _uplo>
SyevSolver<_Matrix, _jobz, _uplo>::SyevSolver(
    const _Matrix &a
) noexcept
  : dim_(a.getNrow()),
    work_(syevQuery<_jobz, _uplo>(a)),
    rwork_(is_real ? RealVectorType() : RealVectorType(3*dim_)) {
  assert(a.getNrow() == a.getNcol());
  assert(dim_ > 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Computes the eigenvalue decomposition.
///
/// @attention  MATRIX @p a WILL BE DESTORIED!
///
template <class _Matrix, JobOption _jobz, UploOption _uplo>
void SyevSolver<_Matrix, _jobz, _uplo>::compute(
    _Matrix &a,
    RealVectorType &w
) noexcept {
  assert(a.getNrow() == dim_ && a.getNcol() == dim_);
  syev<_jobz, _uplo>(a, w, work_, rwork_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  compute
///
template <class _Matrix, JobOption _jobz, UploOption _uplo> template <class _TypeA, class _TypeW>
void SyevSolver<_Matrix, _jobz, _uplo>::compute( _TypeA &&a, _TypeW &&w ) noexcept {
  compute<_jobz, _uplo>(a, w);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the workspace
///
template <class _Matrix, JobOption _jobz, UploOption _uplo>
typename SyevSolver<_Matrix, _jobz, _uplo>::VectorType& SyevSolver<_Matrix, _jobz, _uplo>::getWork() noexcept {
  return work_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getWork
///
template <class _Matrix, JobOption _jobz, UploOption _uplo>
const typename SyevSolver<_Matrix, _jobz, _uplo>::VectorType& SyevSolver<_Matrix, _jobz, _uplo>::getWork() const noexcept {
  return work_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the real workspace
///
template <class _Matrix, JobOption _jobz, UploOption _uplo>
typename SyevSolver<_Matrix, _jobz, _uplo>::RealVectorType& SyevSolver<_Matrix, _jobz, _uplo>::getRwork() noexcept {
  return rwork_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getRwork
///
template <class _Matrix, JobOption _jobz, UploOption _uplo>
const typename SyevSolver<_Matrix, _jobz, _uplo>::RealVectorType& SyevSolver<_Matrix, _jobz, _uplo>::getRwork() const noexcept {
  return rwork_;
}

}  // namespace lapack

}  // namespace isvd

#endif  // ISVD_LAPACK_SOLVER_SYEV_SOLVER_IPP_
