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

#ifndef DOXYGEN_SHOULD_SKIP_THIS
struct GaussianProjectionSketcherTag {};
template <typename _Val> using GaussianProjectionSketcher = Sketcher<GaussianProjectionSketcherTag, _Val>;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  isvd_sketcher_module
/// The Gaussian projection sketcher.
///
/// @tparam  _Val  The value type.
///
template <typename _Val>
#ifndef DOXYGEN_SHOULD_SKIP_THIS
class Sketcher<GaussianProjectionSketcherTag, _Val>
#else  // DOXYGEN_SHOULD_SKIP_THIS
class GaussianProjectionSketcher
#endif  // DOXYGEN_SHOULD_SKIP_THIS
  : public StageWrapper<GaussianProjectionSketcher<_Val>> {

  friend StageWrapper<GaussianProjectionSketcher<_Val>>;

 private:

  using BaseType = StageWrapper<GaussianProjectionSketcher<_Val>>;

 protected:

  /// The name.
  static constexpr const char* name_ = "Gaussian Projection Sketcher";

  /// The name of each part of the stage.
  static constexpr const char* names_ = "random generating / projection";

  /// The random seed.
  index_t seed_;

  /// The exponent of power method.
  index_t exponent_;

  /// The matrix Omega.
  DenseMatrixRowMajor<_Val> matrix_omegas_;

  using BaseType::parameters_;
  using BaseType::initialized_;
  using BaseType::computed_;
  using BaseType::moments_;
  using BaseType::comm_times_;

 public:

  // Constructor
  inline Sketcher( const Parameters<_Val> &parameters, const index_t seed = rand(), const index_t exponent = 0 ) noexcept;

  // Gets parameters
  inline index_t seed() const noexcept;
  inline index_t exponent() const noexcept;

  // Sets parameters
  inline Sketcher& setSeed( const index_t seed ) noexcept;
  inline Sketcher& setExponent( const index_t exponent ) noexcept;


 protected:

  // Initializes
  void initializeImpl() noexcept;

  // Random sketches
  template <class _Matrix>
  void runImpl( const _Matrix &matrix_a, DenseMatrixCollectionColBlockRowMajor<_Val> &collection_q ) noexcept;

  // Outputs name
  inline std::ostream& outputNameImpl( std::ostream& os ) const noexcept;

};

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_SKETCHER_GAUSSIAN_PROJECTION_SKETCHER_HH_
