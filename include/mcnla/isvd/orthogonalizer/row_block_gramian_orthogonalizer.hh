////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/orthogonalizer/row_block_gramian_orthogonalizer.hh
/// @brief   The definition of Gramian orthogonalizer (row-block version).
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_ORTHOGONALIZER_ROW_BLOCK_GRAMIAN_ORTHOGONALIZER_HH_
#define MCNLA_ISVD_ORTHOGONALIZER_ROW_BLOCK_GRAMIAN_ORTHOGONALIZER_HH_

#include <mcnla/isvd/def.hpp>
#include <mcnla/isvd/orthogonalizer/orthogonalizer.hpp>
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
/// The row-block Gramian orthogonalizer tag.
///
struct RowBlockGramianOrthogonalizerTag {};

/// @ingroup  isvd_orthogonalizer_module
template <typename _Val>
using RowBlockGramianOrthogonalizer = Orthogonalizer<RowBlockGramianOrthogonalizerTag, _Val>;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  isvd_orthogonalizer_module
/// The Gramian orthogonalizer (row-block version).
///
/// @tparam  _Val  The value type.
///
template <typename _Val>
class Orthogonalizer<RowBlockGramianOrthogonalizerTag, _Val>
  : public StageWrapper<RowBlockGramianOrthogonalizer<_Val>> {

  friend StageWrapper<RowBlockGramianOrthogonalizer<_Val>>;

 private:

  using BaseType = StageWrapper<RowBlockGramianOrthogonalizer<_Val>>;

 public:

  using ValType = _Val;

 protected:

  /// The name.
  static constexpr const char* name_ = "Gramian Orthogonalizer (Row-Block Version)";

  /// The name of each part of the stage.
  static constexpr const char* names_ = "orthogonalization";

  /// The matrices W.
  DenseMatrixCollection102<ValType> collection_w_;

  /// The matrix S.
  DenseMatrixColMajor<ValType> matrix_s_;

  /// The temporary matrices.
  DenseMatrixCollection201<ValType> collection_tmp_;

  /// The empty matrix.
  DenseMatrixRowMajor<ValType> matrix_empty_;

  /// The GESVD driver.
  la::GesvdDriver<DenseMatrixRowMajor<ValType>, 'N', 'O'> gesvd_driver_;

  using BaseType::parameters_;
  using BaseType::initialized_;
  using BaseType::computed_;
  using BaseType::moments_;
  using BaseType::comm_times_;

 public:

  // Constructor
  inline Orthogonalizer( const Parameters<ValType> &parameters ) noexcept;

 protected:

  // Initializes
  void initializeImpl() noexcept;

  // Orthogonalizes
  void runImpl( DenseMatrixCollection201<ValType> &collection_qj ) noexcept;

};

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_ORTHOGONALIZER_ROW_BLOCK_GRAMIAN_ORTHOGONALIZER_HH_
