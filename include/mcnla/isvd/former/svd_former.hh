////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/former/svd_former.hh
/// @brief   The definition of SVD former.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_FORMER_SVD_FORMER_HH_
#define MCNLA_ISVD_FORMER_SVD_FORMER_HH_

#include <mcnla/isvd/def.hpp>
#include <mcnla/isvd/former/former.hpp>
#include <mcnla/core/la.hpp>

#ifndef DOXYGEN_SHOULD_SKIP_THIS
  #define MCNLA_ALIAS0 Former
  #define MCNLA_ALIAS1 Former<SvdFormerTag<_jobv>, _Val>
#else  // DOXYGEN_SHOULD_SKIP_THIS
  #define MCNLA_ALIAS0 SvdFormer
  #define MCNLA_ALIAS1 SvdFormer
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
template <bool _jobv> struct SvdFormerTag {};
template <typename _Val, bool _jobv = false> using SvdFormer = Former<SvdFormerTag<_jobv>, _Val>;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  isvd_former_module
/// The SVD former.
///
/// @tparam  _Val   The value type.
/// @tparam  _jobv  Computes V or not.
///
#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Val, bool _jobv>
#else  // DOXYGEN_SHOULD_SKIP_THIS
template <typename _Val, bool _jobv = false>
#endif  // DOXYGEN_SHOULD_SKIP_THIS
class MCNLA_ALIAS1
  : public StageWrapper<SvdFormer<_Val, _jobv>> {

  friend StageWrapper<SvdFormer<_Val, _jobv>>;

 private:

  using BaseType = StageWrapper<SvdFormer<_Val, _jobv>>;

 protected:

  /// The name.
  static constexpr const char* name_ = _jobv ? "SVD Former"
                                             : "SVD Former (without V)";

  /// The name of each part of the stage.
  static constexpr const char* names_ = "forming";

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

  /// The matrix Vt.
  DenseMatrixColMajor<_Val> matrix_vt_;

  /// The cut matrix Vt.
  DenseMatrixColMajor<_Val> matrix_vt_cut_;

  /// The empty matrix.
  DenseMatrixColMajor<_Val> matrix_empty_;

  /// The GESVD driver.
  la::DenseGesvdDriverColMajor<'S', (_jobv ? 'O' : 'N'), _Val> gesvd_driver_;

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
  inline const DenseMatrixRowMajor<_Val>& matrixV() const noexcept;

 protected:

  // Initializes
  void initializeImpl() noexcept;

  // Forms SVD
  template <class _Matrix>
  void runImpl( const _Matrix &matrix_a, const DenseMatrixRowMajor<_Val> &matrix_q ) noexcept;

};

}  // namespace isvd

}  // namespace mcnla

#undef MCNLA_ALIAS0
#undef MCNLA_ALIAS1

#endif  // MCNLA_ISVD_FORMER_SVD_FORMER_HH_
