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
  : public ComponentWrapper<PolarOrthogonalizer<_Val>> {

  friend ComponentWrapper<PolarOrthogonalizer<_Val>>;

 private:

  using BaseType = ComponentWrapper<PolarOrthogonalizer<_Val>>;

 public:

  using ValType = _Val;

 protected:

  /// The name.
  static constexpr const char* name_ = "Polar Orthogonalizer";

  /// The matrix P.
  DenseMatrixCollection102<ValType> collection_p_;

  /// The matrix E.
  DenseMatrixColMajor<ValType> matrix_e_;

  /// The temporary matrices.
  DenseMatrixCollection201<ValType> collection_tmp_;

  /// The SYEV driver.
  la::SyevDriver<DenseSymmetricMatrixRowMajor<ValType>, 'V'> syev_driver_;

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
