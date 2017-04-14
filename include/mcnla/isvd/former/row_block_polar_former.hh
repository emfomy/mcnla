////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/former/row_block_polar_former.hh
/// @brief   The definition of polar former (row-block version).
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_FORMER_ROW_BLOCK_POLAR_FORMER_HH_
#define MCNLA_ISVD_FORMER_ROW_BLOCK_POLAR_FORMER_HH_

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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The row-block polar former tag.
///
struct RowBlockPolarFormerTag {};

/// @ingroup  isvd_former_module
template <typename _Val>
using RowBlockPolarFormer = Former<RowBlockPolarFormerTag, _Val>;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  isvd_former_module
/// The polar former (row-block version).
///
/// @tparam  _Val  The value type.
///
template <typename _Val>
class Former<RowBlockPolarFormerTag, _Val>
  : public StageWrapper<RowBlockPolarFormer<_Val>> {

  friend StageWrapper<RowBlockPolarFormer<_Val>>;

 private:

  using BaseType = StageWrapper<RowBlockPolarFormer<_Val>>;

 public:

  using ValType     = _Val;
  using RealValType = RealValT<ValType>;

 protected:

  /// The name.
  static constexpr const char* name_ = "Polar Former (Row-Block Version)";

  /// The matrix W.
  DenseMatrixColMajor<ValType> matrix_w_;

  /// The cut matrix W.
  DenseMatrixColMajor<ValType> matrix_w_cut_;

  /// The vector S.
  DenseVector<RealValType> vector_s_;

  /// The cut vector S.
  DenseVector<RealValType> vector_s_cut_;

  /// The cut matrix U (row-block).
  DenseMatrixRowMajor<ValType> matrix_uj_cut_;

  /// The matrix Q'*A.
  DenseMatrixColMajor<ValType> matrix_qta_;

  /// The matrix Q'*A (row-block).
  DenseMatrixColMajor<ValType> matrix_qtaj_;

  /// The SYEV driver.
  la::SyevDriver<DenseSymmetricMatrixColMajor<ValType>, 'V'> syev_driver_;

  using BaseType::parameters_;
  using BaseType::initialized_;
  using BaseType::computed_;
  using BaseType::moments_;

 public:

  // Constructor
  inline Former( const Parameters<ValType> &parameters ) noexcept;

  // Gets matrices
  inline const DenseVector<RealValType>& vectorS() const noexcept;
  inline const DenseMatrixRowMajor<ValType>& matrixUj() const noexcept;
  inline const DenseMatrixColMajor<ValType>& matrixVtj() const noexcept = delete;

 protected:

  // Initializes
  void initializeImpl() noexcept;

  // Forms SVD
  template <class _Matrix>
  void runImpl( const _Matrix &matrix_a, const DenseMatrixRowMajor<ValType> &matrix_q ) noexcept;

};

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_FORMER_ROW_BLOCK_POLAR_FORMER_HH_
