////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/sketcher/sketcher_base.hpp
/// @brief   The MCNLA sketcher interface.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_SKETCHER_SKETCHER_BASE_HPP_
#define MCNLA_ISVD_SKETCHER_SKETCHER_BASE_HPP_

#include <mcnla/mcnla.hpp>
#include <mcnla/matrix.hpp>
#include <mcnla/utility.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The interface of MCNLA sketcher.
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
  inline constexpr const char* getName() const noexcept;

};

}  // namespace mcnla

#endif  // MCNLA_ISVD_SKETCHER_SKETCHER_BASE_HPP_
