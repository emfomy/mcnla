////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/reconstructor/reconstructor_base.hpp
/// @brief   The MCNLA reconstructor interface.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_RECONSTRUCTOR_RECONSTRUCTOR_BASE_HPP_
#define MCNLA_ISVD_RECONSTRUCTOR_RECONSTRUCTOR_BASE_HPP_

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

/// @addtogroup  isvd_module
//@{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The interface of MCNLA reconstructor.
///
/// @tparam  _Derived  The derived type.
///
template <class _Derived>
class ReconstructorBase : protected CrtpBase<_Derived, ReconstructorBase<_Derived>> {

 public:

  using MatrixType     = typename traits::Traits<_Derived>::MatrixType;
  using ScalarType     = typename MatrixType::ScalarType;
  using RealScalarType = typename MatrixType::RealScalarType;

 protected:

  /// The parameters.
  const Parameters<ScalarType> &parameters_;

 protected:

  // Constructor
  inline ReconstructorBase( const Parameters<ScalarType> &parameters ) noexcept;

 public:

  // Initializes
  inline void initialize() noexcept;

  // Reconstructs
  inline void reconstruct( const MatrixType &matrix_a, const DenseMatrix<ScalarType, Layout::ROWMAJOR> &matrix_qc ) noexcept;

  // Gets name
  inline constexpr const char* getName() const noexcept;

  // Gets matrices
  inline const DenseVector<RealScalarType>& getVectorS() const noexcept;
  inline const DenseMatrix<ScalarType, Layout::COLMAJOR>& getMatrixU() const noexcept;
  inline const DenseMatrix<ScalarType, Layout::COLMAJOR>& getMatrixVt() const noexcept;

};

//@}  isvd_module

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_RECONSTRUCTOR_RECONSTRUCTOR_BASE_HPP_
