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

#ifndef DOXYGEN_SHOULD_SKIP_THIS
  #define MCNLA_ALIAS0 Orthogonalizer
  #define MCNLA_ALIAS1 Orthogonalizer<RowBlockGramianOrthogonalizerTag, _Val>
#else  // DOXYGEN_SHOULD_SKIP_THIS
  #define MCNLA_ALIAS0 RowBlockGramianOrthogonalizer
  #define MCNLA_ALIAS1 RowBlockGramianOrthogonalizer
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
struct RowBlockGramianOrthogonalizerTag {};
template <typename _Val> using RowBlockGramianOrthogonalizer = Orthogonalizer<RowBlockGramianOrthogonalizerTag, _Val>;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  isvd_orthogonalizer_module
/// The Gramian orthogonalizer (row-block version).
///
/// @tparam  _Val  The value type.
///
template <typename _Val>
class MCNLA_ALIAS1
  : public StageWrapper<RowBlockGramianOrthogonalizer<_Val>> {

  friend StageWrapper<RowBlockGramianOrthogonalizer<_Val>>;

 private:

  using BaseType = StageWrapper<RowBlockGramianOrthogonalizer<_Val>>;

 protected:

  /// The name.
  static constexpr const char* name_ = "Gramian Orthogonalizer (Row-Block Version)";

  /// The name of each part of the stage.
  static constexpr const char* names_ = "orthogonalization";

  /// The matrices W.
  DenseMatrixCollectionRowBlockRowMajor<_Val> collection_w_;

  /// The matrix S.
  DenseMatrixColMajor<_Val> matrix_s_;

  /// The temporary matrices.
  DenseMatrixCollectionColBlockRowMajor<_Val> collection_tmp_;

  /// The empty matrix.
  DenseMatrixRowMajor<_Val> matrix_empty_;

  /// The GESVD driver.
  la::DenseGesvdDriverRowMajor<'N', 'O', _Val> gesvd_driver_;

  using BaseType::parameters_;
  using BaseType::initialized_;
  using BaseType::computed_;
  using BaseType::moments_;
  using BaseType::comm_times_;

 public:

  // Constructor
  inline MCNLA_ALIAS0( const Parameters<_Val> &parameters ) noexcept;

 protected:

  // Initializes
  void initializeImpl() noexcept;

  // Orthogonalizes
  void runImpl( DenseMatrixCollectionColBlockRowMajor<_Val> &collection_qj ) noexcept;

};

}  // namespace isvd

}  // namespace mcnla

#undef MCNLA_ALIAS0
#undef MCNLA_ALIAS1

#endif  // MCNLA_ISVD_ORTHOGONALIZER_ROW_BLOCK_GRAMIAN_ORTHOGONALIZER_HH_
