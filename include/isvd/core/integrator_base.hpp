////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/core/integrator_base.hpp
/// @brief   The iSVD integrator interface.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_CORE_INTEGRATOR_BASE_HPP_
#define ISVD_CORE_INTEGRATOR_BASE_HPP_

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
/// The interface of iSVD integrator.
///
/// @tparam  _Derived  The derived type.
///
template <class _Derived>
class IntegratorBase : public internal::CrtpBase<_Derived, IntegratorBase<_Derived>> {

 public:

  using MatrixType     = typename Traits<_Derived>::MatrixType;
  using ScalarType     = typename MatrixType::ScalarType;
  using RealScalarType = typename MatrixType::RealScalarType;

 protected:

  /// The parameters.
  const internal::Parameters<ScalarType> &parameters_;

 protected:

  // Constructor
  IntegratorBase( const internal::Parameters<ScalarType> &parameters ) noexcept;

 public:

  // Initializes
  void initialize() noexcept;

  // Reconstructs
  inline void integrate() noexcept;

  // Gets name
  inline const char* getName() const noexcept;

  // Gets matrices
  inline DenseCube<ScalarType, Layout::ROWMAJOR>& getCubeQ() noexcept;
  inline DenseMatrix<ScalarType, Layout::ROWMAJOR>& getMatrixQc() noexcept;

};

}  // namespace internal

}  // namespace isvd

#endif  // ISVD_CORE_INTEGRATOR_BASE_HPP_
