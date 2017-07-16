////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd_gpu/sketcher/row_block_gaussian_projection_sketcher_gpu.hh
/// @brief   The definition of Gaussian projection sketcher with GPU support (row-block version).
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_GPU_SKETCHER_ROW_BLOCK_GAUSSIAN_PROJECTION_SKETCHER_GPU_HH_
#define MCNLA_ISVD_GPU_SKETCHER_ROW_BLOCK_GAUSSIAN_PROJECTION_SKETCHER_GPU_HH_

#include <mcnla/isvd_gpu/def.hpp>
#include <mcnla/isvd/sketcher/sketcher.hpp>

#ifndef DOXYGEN_SHOULD_SKIP_THIS
  #define MCNLA_ALIAS0 Sketcher
  #define MCNLA_ALIAS1 Sketcher<RowBlockGaussianProjectionSketcherGpuTag, _Val>
#else  // DOXYGEN_SHOULD_SKIP_THIS
  #define MCNLA_ALIAS0 RowBlockGaussianProjectionSketcherGpu
  #define MCNLA_ALIAS1 RowBlockGaussianProjectionSketcherGpu
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

#ifndef DOXYGEN_SHOULD_SKIP_THIS
struct RowBlockGaussianProjectionSketcherGpuTag {};
template <typename _Val> using RowBlockGaussianProjectionSketcherGpu = Sketcher<RowBlockGaussianProjectionSketcherGpuTag, _Val>;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  isvd_sketcher_gpu_module
/// The Gaussian projection sketcher (row-block version).
///
/// @tparam  _Val  The value type.
///
template <typename _Val>
class MCNLA_ALIAS1
  : public StageWrapper<RowBlockGaussianProjectionSketcherGpu<_Val>> {

  friend StageWrapper<RowBlockGaussianProjectionSketcherGpu<_Val>>;

 private:

  using BaseType = StageWrapper<RowBlockGaussianProjectionSketcherGpu<_Val>>;

 protected:

  /// The name.
  static constexpr const char* name_ = "GPU Gaussian Projection Sketcher (Row-Block Version)";

  /// The name of each part of the stage.
  static constexpr const char* names_ = "allocation / random generating / projection / receive";

  /// The random seed.
  index_t seed_;

  /// The number of columns of GPU matrix A.
  index_t ncol_gpu_;

  /// The matrix Omegas.
  DenseMatrixRowMajor<_Val> matrix_omegas_;

  using BaseType::parameters_;
  using BaseType::initialized_;
  using BaseType::computed_;
  using BaseType::moments_;
  using BaseType::comm_times_;

 public:

  // Constructor
  inline MCNLA_ALIAS0( const Parameters<_Val> &parameters, const index_t seed = rand() ) noexcept;

  // Gets parameters
  inline index_t seed() const noexcept;

  // Sets parameters
  inline MCNLA_ALIAS1& setSeed( const index_t seed ) noexcept;


 protected:

  // Initializes
  void initializeImpl() noexcept;

  // Random sketches
  void runImpl( const DenseMatrixRowMajor<_Val> &matrix_aj,
                      DenseMatrixCollectionColBlockRowMajor<_Val> &collection_qj ) noexcept;

  // Outputs name
  inline std::ostream& outputNameImpl( std::ostream& os ) const noexcept;

};

}  // namespace isvd

}  // namespace mcnla

#undef MCNLA_ALIAS0
#undef MCNLA_ALIAS1

#endif  // MCNLA_ISVD_GPU_SKETCHER_ROW_BLOCK_GAUSSIAN_PROJECTION_SKETCHER_GPU_HH_
