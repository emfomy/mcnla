////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/core/reconstructor_base.hpp
/// @brief   The iSVD reconstructor interface.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_CORE_RECONSTRUCTOR_BASE_HPP_
#define ISVD_CORE_RECONSTRUCTOR_BASE_HPP_

#include <isvd/isvd.hpp>
#include <isvd/matrix.hpp>
#include <isvd/utility.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The internal namespace.
//
namespace internal {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The interface of iSVD reconstructor.
///
/// @tparam  _Derived  The derived type.
///
template <class _Derived>
class ReconstructorBase : public internal::CrtpBase<_Derived, ReconstructorBase<_Derived>> {

 public:

  using MatrixType     = typename Traits<_Derived>::MatrixType;
  using ScalarType     = typename MatrixType::ScalarType;
  using RealScalarType = typename MatrixType::RealScalarType;

 protected:

  /// The parameters.
  const internal::Parameters<ScalarType> &parameters_;

 protected:

  // Constructor
  ReconstructorBase( const internal::Parameters<ScalarType> &parameters ) noexcept;

 public:

  // Initializes
  void initialize() noexcept;

  // Reconstructs
  inline void reconstruct( const MatrixType &matrix_a, const DenseMatrix<ScalarType, Layout::ROWMAJOR> &matrix_qc ) noexcept;

  // Gets matrices
  inline const DenseVector<RealScalarType>& getSingularValues() const noexcept;
  inline const DenseMatrix<ScalarType, Layout::COLMAJOR>& getLeftSingularVectors() const noexcept;
  inline const DenseMatrix<ScalarType, Layout::COLMAJOR>& getRightSingularVectors() const noexcept;

};

}  // namespace internal

}  // namespace isvd

#endif  // ISVD_CORE_RECONSTRUCTOR_BASE_HPP_
