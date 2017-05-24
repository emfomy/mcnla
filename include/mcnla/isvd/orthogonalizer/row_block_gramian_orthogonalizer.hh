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
#ifndef DOXYGEN_SHOULD_SKIP_THIS
class Orthogonalizer<RowBlockGramianOrthogonalizerTag, _Val>
#else  // DOXYGEN_SHOULD_SKIP_THIS
class RowBlockGramianOrthogonalizer
#endif  // DOXYGEN_SHOULD_SKIP_THIS
  : public StageWrapper<RowBlockGramianOrthogonalizer<_Val>, _Val> {

  friend StageWrapper<RowBlockGramianOrthogonalizer<_Val>, _Val>;

 private:

  using BaseType = StageWrapper<RowBlockGramianOrthogonalizer<_Val>, _Val>;

 public:

//  using _Val = _Val;

 protected:

  /// The name.
  static constexpr const char* name_ = "Gramian Orthogonalizer (Row-Block Version)";

  /// The name of each part of the stage.
  static constexpr const char* names_ = "orthogonalization";

  /// The matrices W.
  DenseMatrixCollection102<_Val> collection_w_;

  /// The matrix S.
  DenseMatrixColMajor<_Val> matrix_s_;

  /// The temporary matrices.
  DenseMatrixCollection201<_Val> collection_tmp_;

  /// The empty matrix.
  DenseMatrixRowMajor<_Val> matrix_empty_;

  /// The GESVD driver.
  la::GesvdDriver<DenseMatrixRowMajor<_Val>, 'N', 'O'> gesvd_driver_;

  using BaseType::parameters_;
  using BaseType::initialized_;
  using BaseType::computed_;
  using BaseType::moments_;
  using BaseType::comm_times_;

 public:

  // Constructor
  inline Orthogonalizer( const Parameters<_Val> &parameters ) noexcept;

 protected:

  // Initializes
  void initializeImpl() noexcept;

  // Orthogonalizes
  void runImpl( DenseMatrixCollection201<_Val> &collection_qj ) noexcept;

};

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_ORTHOGONALIZER_ROW_BLOCK_GRAMIAN_ORTHOGONALIZER_HH_
