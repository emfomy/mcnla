////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/orthogonalizer/polar_orthogonalizer.hh
/// @brief   The definition of polar orthogonalizer.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_ORTHOGONALIZER_POLAR_ORTHOGONALIZER_HH_
#define MCNLA_ISVD_ORTHOGONALIZER_POLAR_ORTHOGONALIZER_HH_

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
/// The polar orthogonalizer tag.
///
struct PolarOrthogonalizerTag {};

/// @ingroup  isvd_orthogonalizer_module
template <typename _Val>
using PolarOrthogonalizer = Orthogonalizer<PolarOrthogonalizerTag, _Val>;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  isvd_orthogonalizer_module
/// The polar orthogonalizer.
///
/// @tparam  _Val  The value type.
///
template <typename _Val>
class Orthogonalizer<PolarOrthogonalizerTag, _Val>
  : public StageWrapper<PolarOrthogonalizer<_Val>> {

  friend StageWrapper<PolarOrthogonalizer<_Val>>;

 private:

  using BaseType = StageWrapper<PolarOrthogonalizer<_Val>>;

 public:

  using ValType = _Val;

 protected:

  /// The name.
  static constexpr const char* name_ = "Polar Orthogonalizer";

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

 public:

  // Constructor
  inline Orthogonalizer( const Parameters<ValType> &parameters ) noexcept;

 protected:

  // Initializes
  void initializeImpl() noexcept;

  // Orthogonalizes
  void runImpl( DenseMatrixCollection201<ValType> &collection_q ) noexcept;

};

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_ORTHOGONALIZER_POLAR_ORTHOGONALIZER_HH_
