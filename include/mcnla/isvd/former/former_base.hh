////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/former/former_base.hh
/// @brief   The definition of iSVD former interface.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_FORMER_FORMER_BASE_HH_
#define MCNLA_ISVD_FORMER_FORMER_BASE_HH_

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
/// @ingroup  isvd_former_module
///
/// The interface of iSVD former.
///
/// @tparam  _Derived  The derived type.
///
template <class _Derived>
class FormerBase : public utility::CrtpBase<_Derived, FormerBase<_Derived>> {

 public:

  using MatrixType     = MatrixT<_Derived>;
  using ScalarType     = ScalarT<MatrixType>;
  using RealScalarType = typename MatrixType::RealScalarType;

 protected:

  /// The parameters.
  const Parameters<ScalarType> &parameters_;

 protected:

  // Constructor
  inline FormerBase( const Parameters<ScalarType> &parameters ) noexcept;

 public:

  // Initializes
  inline void initialize() noexcept;

  // Reconstructs
  inline void form( const MatrixType &matrix_a, const DenseMatrix<ScalarType, Layout::ROWMAJOR> &matrix_qc ) noexcept;

  // Gets name
  inline constexpr const char* name() const noexcept;

  // Gets compute time
  inline double getTime() const noexcept;
  inline const std::vector<double> getTimes() const noexcept;

  // Gets matrices
  inline const DenseVector<RealScalarType>& getVectorS() const noexcept;
  inline const DenseMatrix<ScalarType, Layout::COLMAJOR>& getMatrixU() const noexcept;
  inline const DenseMatrix<ScalarType, Layout::COLMAJOR>& getMatrixVt() const noexcept;

};

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_FORMER_FORMER_BASE_HH_
