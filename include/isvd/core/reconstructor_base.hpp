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

 private:

  using ScalarType         = typename Traits<_Derived>::ScalarType;
  using RealScalarType     = typename Traits<_Derived>::RealScalarType;
  using MatrixType         = typename Traits<_Derived>::MatrixType;

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
  inline void reconstruct( const MatrixType &matrix_a,
                           const DenseMatrix<ScalarType, Layout::ROWMAJOR> &matrix_q,
                                 DenseVector<RealScalarType> &vector_s,
                                 DenseMatrix<ScalarType, Layout::COLMAJOR> &matrix_u,
                                 DenseMatrix<ScalarType, Layout::COLMAJOR> &matrix_vt ) noexcept;

};

}  // namespace internal

}  // namespace isvd

#endif  // ISVD_CORE_RECONSTRUCTOR_BASE_HPP_
