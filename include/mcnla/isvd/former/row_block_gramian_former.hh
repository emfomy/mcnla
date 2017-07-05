////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/former/row_block_gramian_former.hh
/// @brief   The definition of Gramian former (row-block version).
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_FORMER_ROW_BLOCK_GRAMIAN_FORMER_HH_
#define MCNLA_ISVD_FORMER_ROW_BLOCK_GRAMIAN_FORMER_HH_

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
struct RowBlockGramianFormerTag {};
template <typename _Val> using RowBlockGramianFormer = Former<RowBlockGramianFormerTag, _Val>;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  isvd_former_module
/// The Gramian former (row-block version).
///
/// @tparam  _Val  The value type.
///
template <typename _Val>
#ifndef DOXYGEN_SHOULD_SKIP_THIS
class Former<RowBlockGramianFormerTag, _Val>
#else  // DOXYGEN_SHOULD_SKIP_THIS
class RowBlockGramianFormer
#endif  // DOXYGEN_SHOULD_SKIP_THIS
  : public StageWrapper<RowBlockGramianFormer<_Val>> {

  friend StageWrapper<RowBlockGramianFormer<_Val>>;

 private:

  using BaseType = StageWrapper<RowBlockGramianFormer<_Val>>;

 protected:

  /// The name.
  static constexpr const char* name_ = "Gramian Former (Row-Block Version)";

  /// The name of each part of the stage.
  static constexpr const char* names_ = "forming";

  /// The matrix W.
  DenseMatrixRowMajor<_Val> matrix_w_;

  /// The cut matrix W.
  DenseMatrixRowMajor<_Val> matrix_w_cut_;

  /// The vector S.
  DenseVector<RealValT<_Val>> vector_s_;

  /// The cut vector S.
  DenseVector<RealValT<_Val>> vector_s_cut_;

  /// The cut matrix U (row-block).
  DenseMatrixRowMajor<_Val> matrix_uj_cut_;

  /// The matrix Z.
  DenseMatrixRowMajor<_Val> matrix_z_;

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
  inline Former( const Parameters<_Val> &parameters ) noexcept;

  // Gets matrices
  inline const DenseVector<RealValT<_Val>>& vectorS() const noexcept;
  inline const DenseMatrixRowMajor<_Val>& matrixUj() const noexcept;
  inline const DenseMatrixRowMajor<_Val>& matrixVj() const noexcept = delete;

 protected:

  // Initializes
  void initializeImpl() noexcept;

  // Forms SVD
  template <class _Matrix>
  void runImpl( const _Matrix &matrix_a, const DenseMatrixRowMajor<_Val> &matrix_q ) noexcept;

};

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_FORMER_ROW_BLOCK_GRAMIAN_FORMER_HH_
