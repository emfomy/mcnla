////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/core/sketcher/sketcher_base.hpp
/// @brief   The iSVD sketcher interface.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_CORE_SKETCHER_SKETCHER_BASE_HPP_
#define ISVD_CORE_SKETCHER_SKETCHER_BASE_HPP_

#include <isvd/isvd.hpp>
#include <isvd/matrix.hpp>
#include <isvd/utility.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The interface of iSVD sketcher.
///
/// @tparam  _Derived  The derived type.
///
template <class _Derived>
class SketcherBase : protected CrtpBase<_Derived, SketcherBase<_Derived>> {

 public:

  using MatrixType = typename detail::Traits<_Derived>::MatrixType;
  using ScalarType = typename MatrixType::ScalarType;

 protected:

  /// The parameters.
  const Parameters<ScalarType> &parameters_;

  /// The random seed
  index_t *seed_;

 protected:

  // Constructor
  inline SketcherBase( const Parameters<ScalarType> &parameters, index_t *seed ) noexcept;

 public:

  // Initializes
  inline void initialize() noexcept;

  // Random sketches
  inline void sketch( const MatrixType &matrix_a, DenseCube<ScalarType, Layout::ROWMAJOR> &cube_q ) noexcept;

  // Gets name
  inline const char* getName() const noexcept;

};

}  // namespace isvd

#endif  // ISVD_CORE_SKETCHER_SKETCHER_BASE_HPP_
