////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/former/gramian_former.hh
/// @brief   The definition of Gramian former.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_FORMER_GRAMIAN_FORMER_HH_
#define MCNLA_ISVD_FORMER_GRAMIAN_FORMER_HH_

#include <mcnla/isvd/def.hpp>
#include <mcnla/isvd/former/former.hpp>
#include <mcnla/core/la.hpp>

#ifndef DOXYGEN_SHOULD_SKIP_THIS
  #define MCNLA_ALIAS0 Former
  #define MCNLA_ALIAS1 Former<GramianFormerTag<_jobv>, _Val>
#else  // DOXYGEN_SHOULD_SKIP_THIS
  #define MCNLA_ALIAS0 GramianFormer
  #define MCNLA_ALIAS1 GramianFormer
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
template <bool _jobv> struct GramianFormerTag {};
template <typename _Val, bool _jobv = false> using GramianFormer = Former<GramianFormerTag<_jobv>, _Val>;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  isvd_former_module
/// The Gramian former.
///
/// @tparam  _Val  The value type.
///
#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Val, bool _jobv>
#else  // DOXYGEN_SHOULD_SKIP_THIS
template <typename _Val, bool _jobv = false>
#endif  // DOXYGEN_SHOULD_SKIP_THIS
class MCNLA_ALIAS1
  : public StageWrapper<GramianFormer<_Val, _jobv>> {

  friend StageWrapper<GramianFormer<_Val, _jobv>>;

 private:

  using BaseType    = StageWrapper<GramianFormer<_Val, _jobv>>;

 protected:

  /// The name.
  static constexpr const char* name_ = _jobv ? "Gramian Former"
                                             : "Gramian Former (without V)";

  /// The name of each part of the stage.
  static constexpr const char* names_ = "Projection / eigen / forming";

  /// The matrix W.
  DenseMatrixColMajor<_Val> matrix_w_;

  /// The cut matrix W.
  DenseMatrixColMajor<_Val> matrix_w_cut_;

  /// The vector S.
  DenseVector<RealValT<_Val>> vector_s_;

  /// The cut vector S.
  DenseVector<RealValT<_Val>> vector_s_cut_;

  /// The cut matrix U.
  DenseMatrixColMajor<_Val> matrix_u_cut_;

  /// The cut matrix V.
  DenseMatrixColMajor<_Val> matrix_v_cut_;

  /// The matrix Z.
  DenseMatrixRowMajor<_Val> matrix_z_;

  /// The empty matrix.
  DenseMatrixColMajor<_Val> matrix_empty_;

  /// The GESVD driver.
  la::DenseGesvdDriverColMajor<'O', 'N', _Val> gesvd_driver_;

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
  inline const DenseMatrixColMajor<_Val>& matrixV() const noexcept;

 protected:

  // Initializes
  void initializeImpl() noexcept;

  // Forms SVD
  template <class _Matrix>
  void runImpl( const _Matrix &matrix_aj, const DenseMatrixRowMajor<_Val> &matrix_qj ) noexcept;

};

}  // namespace isvd

}  // namespace mcnla

#undef MCNLA_ALIAS0
#undef MCNLA_ALIAS1

#endif  // MCNLA_ISVD_FORMER_GRAMIAN_FORMER_HH_
