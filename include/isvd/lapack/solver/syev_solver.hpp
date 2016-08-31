////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/lapack/solver/syev_solver.hpp
/// @brief   The definition of LAPACK SYEV solver.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_LAPACK_SOLVER_SYEV_SOLVER_HPP_
#define ISVD_LAPACK_SOLVER_SYEV_SOLVER_HPP_

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
/// @brief  The eigenvalue solver for symmetric or symmetric or Hermitian matrices.
///
template <class _Matrix, JobOption _jobz, UploOption _uplo = UploOption::LOWER>
class SyevSolver {

  static_assert(_jobz == 'N' || _jobz == 'V', "Job undefined!");

 private:

  using ScalarType     = typename isvd::internal::Traits<_Matrix>::ScalarType;
  using VectorType     = typename isvd::internal::Traits<_Matrix>::VectorType;
  using RealVectorType = typename isvd::internal::Traits<_Matrix>::RealVectorType;
  static const Layout layout = isvd::internal::Traits<_Matrix>::layout;
  static const bool is_real  = isvd::internal::ScalarTraits<ScalarType>::is_real;

  static_assert(std::is_same<DenseMatrix<ScalarType, layout>, _Matrix>::value, "'_Matrix' is not a isvd::DenseMatrix!");

 protected:

  /// The dimension.
  const index_t dim_;

  /// The workspace.
  VectorType work_;

  /// The real workspace.
  RealVectorType rwork_;

 public:

  // Constructor
  SyevSolver( const _Matrix &a ) noexcept;

  // Computes
  inline void compute( _Matrix &a, RealVectorType &w ) noexcept;
  template <class _TypeA, class _TypeW>
  inline void compute( _TypeA &&a, _TypeW &&w ) noexcept;

  // Gets workspaces
  inline       VectorType& getWork() noexcept;
  inline const VectorType& getWork() const noexcept;
  inline       RealVectorType& getRwork() noexcept;
  inline const RealVectorType& getRwork() const noexcept;

};

}  // namespace lapack

}  // namespace isvd

#endif  // ISVD_LAPACK_SOLVER_SYEV_SOLVER_HPP_
