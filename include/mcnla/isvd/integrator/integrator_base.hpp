////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/integrator/integrator_base.hpp
/// @brief   The MCNLA integrator interface.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_INTEGRATOR_INTEGRATOR_BASE_HPP_
#define MCNLA_ISVD_INTEGRATOR_INTEGRATOR_BASE_HPP_

#include <mcnla/def.hpp>
#include <mcnla/isvd/def.hpp>
#include <mcnla/core/matrix.hpp>
#include <mcnla/core/utility.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  isvd_module
///
/// The interface of MCNLA integrator.
///
/// @tparam  _Derived  The derived type.
///
template <class _Derived>
class IntegratorBase : public utility::CrtpBase<_Derived, IntegratorBase<_Derived>> {

 public:

  using MatrixType     = typename traits::Traits<_Derived>::MatrixType;
  using ScalarType     = typename MatrixType::ScalarType;
  using RealScalarType = typename MatrixType::RealScalarType;

 protected:

  /// The parameters.
  const Parameters<ScalarType> &parameters_;

 protected:

  // Constructor
  inline IntegratorBase( const Parameters<ScalarType> &parameters ) noexcept;

 public:

  // Initializes
  inline void initialize() noexcept;

  // Reconstructs
  inline void integrate() noexcept;

  // Gets name
  inline constexpr const char* getName() const noexcept;

  // Gets iterator number
  inline index_t getIter() const noexcept;

  // Gets matrices
  inline       DenseCube<ScalarType, Layout::ROWMAJOR>& getCubeQ() noexcept;
  inline const DenseCube<ScalarType, Layout::ROWMAJOR>& getCubeQ() const noexcept;
  inline       DenseMatrix<ScalarType, Layout::ROWMAJOR>& getMatrixQc() noexcept;
  inline const DenseMatrix<ScalarType, Layout::ROWMAJOR>& getMatrixQc() const noexcept;

};

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_INTEGRATOR_INTEGRATOR_BASE_HPP_
