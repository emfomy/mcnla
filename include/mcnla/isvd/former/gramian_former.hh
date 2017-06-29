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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

#ifndef DOXYGEN_SHOULD_SKIP_THIS
struct GramianFormerTag {};
template <typename _Val> using GramianFormer = Former<GramianFormerTag, _Val>;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  isvd_former_module
/// The Gramian former.
///
/// @tparam  _Val  The value type.
///
template <typename _Val>
#ifndef DOXYGEN_SHOULD_SKIP_THIS
class Former<GramianFormerTag, _Val>
#else  // DOXYGEN_SHOULD_SKIP_THIS
class GramianFormer
#endif  // DOXYGEN_SHOULD_SKIP_THIS
  : public StageWrapper<GramianFormer<_Val>> {

  friend StageWrapper<GramianFormer<_Val>>;

 private:

  using BaseType    = StageWrapper<GramianFormer<_Val>>;

 protected:

  /// The name.
  static constexpr const char* name_ = "Gramian Former";

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

  /// The matrix Q'*A.
  DenseMatrixColMajor<_Val> matrix_qta_;

  /// The SYEV driver.
  la::DenseSyevDriverColMajor<'V', _Val> syev_driver_;

  using BaseType::parameters_;
  using BaseType::initialized_;
  using BaseType::computed_;
  using BaseType::moments_;
  using BaseType::comm_times_;

 public:

  // Constructor
  inline Former( const Parameters<_Val> &parameters ) noexcept;

  // Gets matrices
  inline const DenseVector<RealValT<_Val>>& vectorS() const noexcept;
  inline const DenseMatrixColMajor<_Val>& matrixU() const noexcept;
  inline const DenseMatrixColMajor<_Val>& matrixVt() const noexcept = delete;

 protected:

  // Initializes
  void initializeImpl() noexcept;

  // Forms SVD
  template <class _Matrix>
  void runImpl( const _Matrix &matrix_aj, const DenseMatrixRowMajor<_Val> &matrix_qj ) noexcept;

};

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_FORMER_GRAMIAN_FORMER_HH_
