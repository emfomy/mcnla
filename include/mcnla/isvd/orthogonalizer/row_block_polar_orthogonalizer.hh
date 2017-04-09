////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/orthogonalizer/row_block_polar_orthogonalizer.hh
/// @brief   The definition of polar orthogonalizer (row-block version).
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_ORTHOGONALIZER_ROW_BLOCK_POLAR_ORTHOGONALIZER_HH_
#define MCNLA_ISVD_ORTHOGONALIZER_ROW_BLOCK_POLAR_ORTHOGONALIZER_HH_

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
/// @ingroup  isvd_orthogonalizer_module_detail
/// The row-block polar orthogonalizer tag.
///
struct RowBlockPolarOrthogonalizerTag {};

/// @ingroup  isvd_orthogonalizer_module
template <typename _Val>
using RowBlockPolarOrthogonalizer = Orthogonalizer<RowBlockPolarOrthogonalizerTag, _Val>;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  isvd_orthogonalizer_module
/// The polar orthogonalizer (row-block version).
///
/// @tparam  _Val  The value type.
///
template <typename _Val>
class Orthogonalizer<RowBlockPolarOrthogonalizerTag, _Val>
  : public ComponentWrapper<RowBlockPolarOrthogonalizer<_Val>> {

  friend ComponentWrapper<RowBlockPolarOrthogonalizer<_Val>>;

 private:

  using BaseType = ComponentWrapper<RowBlockPolarOrthogonalizer<_Val>>;

 public:

  using ValType = _Val;

 protected:

  /// The name.
  static constexpr const char* name_= "Polar Orthogonalizer (Row-Block Version)";

  /// The matrix P.
  DenseMatrixCollection102<ValType> collection_p_;

  /// The matrix E.
  DenseMatrixColMajor<ValType> matrix_e_;

  /// The temporary matrices.
  DenseMatrixCollection120<ValType> collection_tmp_;

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
  void runImpl( DenseMatrixCollection120<ValType> &collection_qj ) noexcept;

};

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_ORTHOGONALIZER_ROW_BLOCK_POLAR_ORTHOGONALIZER_HH_
