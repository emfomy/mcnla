////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/core/sketcher_base.hpp
/// @brief   The iSVD sketcher interface.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_CORE_SKETCHER_BASE_HPP_
#define ISVD_CORE_SKETCHER_BASE_HPP_

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
/// The interface of iSVD sketcher.
///
/// @tparam  _Derived  The derived type.
///
template <class _Derived>
class SketcherBase : public internal::CrtpBase<_Derived, SketcherBase<_Derived>> {

 private:

  using ScalarType       = typename Traits<_Derived>::ScalarType;
  using MatrixType       = typename Traits<_Derived>::MatrixType;

 protected:

  /// The parameters.
  const internal::Parameters<ScalarType> &parameters_;

 protected:

  // Constructor
  SketcherBase( const internal::Parameters<ScalarType> &parameters ) noexcept;

 public:

  // Initializes
  void initialize() noexcept;

  // Random sketches
  inline void sketch( const MatrixType &matrix_a, DenseCube<ScalarType, Layout::ROWMAJOR> &cube_q ) noexcept;

};

}  // namespace internal

}  // namespace isvd

#endif  // ISVD_CORE_SKETCHER_BASE_HPP_
