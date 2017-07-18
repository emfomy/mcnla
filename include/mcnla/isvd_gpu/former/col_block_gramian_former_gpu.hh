////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd_gpu/former/col_block_gramian_former_gpu.hh
/// @brief   The definition of Gramian former with GPU support (column-block version).
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_GPU_FORMER_COL_BLOCK_GRAMIAN_FORMER_GPU_HH_
#define MCNLA_ISVD_GPU_FORMER_COL_BLOCK_GRAMIAN_FORMER_GPU_HH_

#include <mcnla/isvd_gpu/def.hpp>
#include <mcnla/isvd/former/former.hpp>
#include <mcnla/core/la.hpp>

#ifndef DOXYGEN_SHOULD_SKIP_THIS
  #define MCNLA_ALIAS0 Former
  #define MCNLA_ALIAS1 Former<ColBlockGramianFormerGpuTag<_jobv>, _Val>
#else  // DOXYGEN_SHOULD_SKIP_THIS
  #define MCNLA_ALIAS0 ColBlockGramianFormerGpu
  #define MCNLA_ALIAS1 ColBlockGramianFormerGpu
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
template <bool _jobv> struct ColBlockGramianFormerGpuTag {};
template <typename _Val, bool _jobv = false> using ColBlockGramianFormerGpu = Former<ColBlockGramianFormerGpuTag<_jobv>, _Val>;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  isvd_sketcher_gpu_module
/// The GPU Gramian former (column-block version).
///
/// @tparam  _Val  The value type.
///
#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Val, bool _jobv>
#else  // DOXYGEN_SHOULD_SKIP_THIS
template <typename _Val, bool _jobv = false>
#endif  // DOXYGEN_SHOULD_SKIP_THIS
class MCNLA_ALIAS1
  : public StageWrapper<ColBlockGramianFormerGpu<_Val, _jobv>> {

  friend StageWrapper<ColBlockGramianFormerGpu<_Val, _jobv>>;

 private:

  using BaseType = StageWrapper<ColBlockGramianFormerGpu<_Val, _jobv>>;

 protected:

  /// The name.
  static constexpr const char* name_ = _jobv ? "GPU Gramian Former (Column-Block Version)"
                                             : "GPU Gramian Former (Column-Block Version) (without V)";

  /// The name of each part of the stage.
  static constexpr const char* names_ = "allocation / Projection / eigen / forming";

  /// The number of columns of GPU matrix A.
  index_t ncol_gpu_;

  /// The matrix W.
  DenseMatrixRowMajor<_Val> matrix_w_;

  /// The cut matrix W.
  DenseMatrixRowMajor<_Val> matrix_w_cut_;

  /// The vector S.
  DenseVector<RealValT<_Val>> vector_s_;

  /// The cut vector S.
  DenseVector<RealValT<_Val>> vector_s_cut_;

  /// The cut matrix U.
  DenseMatrixColMajor<_Val> matrix_u_cut_;

  /// The cut matrix V (row-block).
  DenseMatrixRowMajor<_Val> matrix_vj_cut_;

  /// The matrix Z (row-block).
  DenseMatrixRowMajor<_Val> matrix_zj_;

  /// The empty matrix.
  DenseMatrixRowMajor<_Val> matrix_empty_;

  /// The GESVD driver.
  la::DenseGesvdDriverRowMajor<'O', 'N', _Val> gesvd_driver_;

  using BaseType::parameters_;
  using BaseType::initialized_;
  using BaseType::computed_;
  using BaseType::moments_;
  using BaseType::comm_times_;

 public:

  // Constructor
  inline MCNLA_ALIAS0( const Parameters<_Val> &parameters ) noexcept;

  // Gets matrices
  inline const DenseVector<RealValT<_Val>>& vectorS() const noexcept;
  inline const DenseMatrixColMajor<_Val>& matrixU() const noexcept;
  inline const DenseMatrixRowMajor<_Val>& matrixVj() const noexcept;

 protected:

  // Initializes
  void initializeImpl() noexcept;

  // Forms SVD
  template <class _Matrix>
  void runImpl( const _Matrix &matrix_ac, const DenseMatrixRowMajor<_Val> &matrix_q ) noexcept;

};

}  // namespace isvd

}  // namespace mcnla

#undef MCNLA_ALIAS0
#undef MCNLA_ALIAS1

#endif  // MCNLA_ISVD_GPU_FORMER_COL_BLOCK_GRAMIAN_FORMER_GPU_HH_
