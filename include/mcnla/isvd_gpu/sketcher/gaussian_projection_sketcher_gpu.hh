////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd_gpu/sketcher/gaussian_projection_sketcher_gpu.hh
/// @brief   The definition of GPU Gaussian projection sketcher.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_GPU_SKETCHER_GAUSSIAN_PROJECTION_SKETCHER_GPU_HH_
#define MCNLA_ISVD_GPU_SKETCHER_GAUSSIAN_PROJECTION_SKETCHER_GPU_HH_

#include <mcnla/isvd_gpu/def.hpp>
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
struct GaussianProjectionSketcherGpuTag {};
template <typename _Val> using GaussianProjectionSketcherGpu = Sketcher<GaussianProjectionSketcherGpuTag, _Val>;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  isvd_sketcher_gpu_module
/// The GPU Gaussian projection sketcher.
///
/// @tparam  _Val    The value type.
///
template <typename _Val>
#ifndef DOXYGEN_SHOULD_SKIP_THIS
class Sketcher<GaussianProjectionSketcherGpuTag, _Val>
#else  // DOXYGEN_SHOULD_SKIP_THIS
class GaussianProjectionSketcherGpu
#endif  // DOXYGEN_SHOULD_SKIP_THIS
  : public StageWrapper<GaussianProjectionSketcherGpu<_Val>> {

  friend StageWrapper<GaussianProjectionSketcherGpu<_Val>>;

 private:

  using BaseType = StageWrapper<GaussianProjectionSketcherGpu<_Val>>;

 public:

  using ValType = _Val;

 protected:

  /// The name.
  static constexpr const char* name_ = "GPU Gaussian Projection Sketcher";

  /// The name of each part of the stage.
  static constexpr const char* names_ = "random generating / projection";

  /// The random seed.
  index_t seed_;

  /// The exponent of power method.
  index_t exponent_;

  /// The matrix Omega.
  DenseMatrixGpuRowMajor<ValType> matrix_omegas_;

  using BaseType::parameters_;
  using BaseType::initialized_;
  using BaseType::computed_;
  using BaseType::moments_;
  using BaseType::comm_times_;

 public:

  // Constructor
  inline Sketcher( const Parameters<ValType> &parameters, const index_t seed = rand(), const index_t exponent = 0 ) noexcept;

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
  void runImpl( const _Matrix &matrix_a, DenseMatrixCollection201Gpu<_Val> &collection_q ) noexcept;

  // Outputs name
  inline std::ostream& outputNameImpl( std::ostream& os ) const noexcept;

};

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_GPU_SKETCHER_GAUSSIAN_PROJECTION_SKETCHER_GPU_HH_
