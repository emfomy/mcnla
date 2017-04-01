////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/sketcher/gaussian_projection_sketcher.hh
/// @brief   The definition of Gaussian projection sketcher.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_SKETCHER_GAUSSIAN_PROJECTION_SKETCHER_HH_
#define MCNLA_ISVD_SKETCHER_GAUSSIAN_PROJECTION_SKETCHER_HH_

#include <mcnla/isvd/def.hpp>
#include <mcnla/isvd/sketcher/sketcher.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  isvd_sketcher_module_detail
/// The Gaussian projection sketcher tag.
///
struct GaussianProjectionSketcherTag {};

/// @ingroup  isvd_sketcher_module
template <typename _Val>
using GaussianProjectionSketcher = Sketcher<GaussianProjectionSketcherTag, _Val>;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  isvd_sketcher_module
/// The Gaussian projection sketcher.
///
/// @tparam  _Val    The value type.
///
template <typename _Val>
class Sketcher<GaussianProjectionSketcherTag, _Val>
  : public ComponentWrapper<GaussianProjectionSketcher<_Val>> {

  friend ComponentWrapper<GaussianProjectionSketcher<_Val>>;

 private:

  using BaseType = ComponentWrapper<GaussianProjectionSketcher<_Val>>;

 protected:

  /// The name.
  static constexpr const char* name_ = "Gaussian Projection Sketcher";

  /// The starting time
  double moment0_;

  /// The ending time of random generating
  double moment1_;

  /// The ending time of random sketching
  double moment2_;

  /// The exponent of power method.
  index_t exponent_;

  /// The matrix Omega.
  DenseMatrixRowMajor<_Val> matrix_omegas_;

  using BaseType::parameters_;

 public:

  // Constructor
  inline Sketcher( const Parameters &parameters, const index_t exponent = 0 ) noexcept;

  // Get parameters
  inline index_t exponent() const noexcept;
  inline Sketcher& setExponent( const index_t exponent ) noexcept;


 protected:

  // Initializes
  void initializeImpl() noexcept;

  // Random sketches
  template <class _Matrix>
  void sketchImpl( const _Matrix &matrix_a, DenseMatrixCollection120<_Val> &collection_q ) noexcept;

  // Outputs name
  inline std::ostream& outputNameImpl( std::ostream& os ) const noexcept;

  // Gets time
  inline double timeImpl() const noexcept;
  inline std::vector<double> timesImpl() const noexcept;
  inline std::vector<double> momentsImpl() const noexcept;

};

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_SKETCHER_GAUSSIAN_PROJECTION_SKETCHER_HH_
