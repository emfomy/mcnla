////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/orthogonalizer/gramian_orthogonalizer.hh
/// @brief   The definition of Gramian orthogonalizer.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_ORTHOGONALIZER_GRAMIAN_ORTHOGONALIZER_HH_
#define MCNLA_ISVD_ORTHOGONALIZER_GRAMIAN_ORTHOGONALIZER_HH_

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
struct GramianOrthogonalizerTag {};
template <typename _Val> using GramianOrthogonalizer = Orthogonalizer<GramianOrthogonalizerTag, _Val>;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  isvd_orthogonalizer_module
/// The Gramian orthogonalizer.
///
/// @tparam  _Val  The value type.
///
template <typename _Val>
#ifndef DOXYGEN_SHOULD_SKIP_THIS
class Orthogonalizer<GramianOrthogonalizerTag, _Val>
#else  // DOXYGEN_SHOULD_SKIP_THIS
class GramianOrthogonalizer
#endif  // DOXYGEN_SHOULD_SKIP_THIS
  : public StageWrapper<GramianOrthogonalizer<_Val>> {

  friend StageWrapper<GramianOrthogonalizer<_Val>>;

 private:

  using BaseType = StageWrapper<GramianOrthogonalizer<_Val>>;

 protected:

  /// The name.
  static constexpr const char* name_ = "Gramian Orthogonalizer";

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
  inline Orthogonalizer( const Parameters<_Val> &parameters ) noexcept;

 protected:

  // Initializes
  void initializeImpl() noexcept;

  // Orthogonalizes
  void runImpl( DenseMatrixCollectionColBlockRowMajor<_Val> &collection_q ) noexcept;

};

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_ORTHOGONALIZER_GRAMIAN_ORTHOGONALIZER_HH_
