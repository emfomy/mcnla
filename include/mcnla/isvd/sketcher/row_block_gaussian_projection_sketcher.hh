////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/sketcher/row_block_gaussian_projection_sketcher.hh
/// @brief   The definition of Gaussian projection sketcher (row-block version).
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_SKETCHER_ROW_BLOCK_GAUSSIAN_PROJECTION_SKETCHER_HH_
#define MCNLA_ISVD_SKETCHER_ROW_BLOCK_GAUSSIAN_PROJECTION_SKETCHER_HH_

#include <mcnla/isvd/def.hpp>
#include <mcnla/isvd/sketcher/sketcher.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The row-block Gaussian projection sketcher tag.
///
struct RowBlockGaussianProjectionSketcherTag {};

/// @ingroup  isvd_sketcher_module
template <typename _Val>
using RowBlockGaussianProjectionSketcher = Sketcher<RowBlockGaussianProjectionSketcherTag, _Val>;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  isvd_sketcher_module
/// The Gaussian projection sketcher (row-block version).
///
/// @tparam  _Val    The value type.
///
template <typename _Val>
class Sketcher<RowBlockGaussianProjectionSketcherTag, _Val>
  : public StageWrapper<RowBlockGaussianProjectionSketcher<_Val>> {

  friend StageWrapper<RowBlockGaussianProjectionSketcher<_Val>>;

 private:

  using BaseType = StageWrapper<RowBlockGaussianProjectionSketcher<_Val>>;

 public:

  using ValType = _Val;

 protected:

  /// The name.
  static constexpr const char* name_ = "Gaussian Projection Sketcher (Row-Block Version)";

  /// The random seed.
  index_t seed_;

  /// The exponent of power method.
  index_t exponent_;

  /// The matrix Omega.
  DenseMatrixRowMajor<ValType> matrix_omegas_;

  using BaseType::parameters_;
  using BaseType::initialized_;
  using BaseType::computed_;
  using BaseType::moments_;

 public:

  // Constructor
  inline Sketcher( const Parameters<ValType> &parameters, const index_t seed = rand(), const index_t exponent = 0 ) noexcept;

  // Gets parameters
  inline index_t seed() const noexcept;
  inline index_t exponent() const noexcept;

  // Sets parameters
  inline Sketcher& setSeed( const index_t seed ) noexcept;
  inline Sketcher& setExponent( const index_t exponent ) noexcept;


 protected:

  // Initializes
  void initializeImpl() noexcept;

  // Random sketches
  template <class _Matrix>
  void runImpl( const _Matrix &matrix_aj, DenseMatrixCollection201<_Val> &collection_qj ) noexcept;

  // Outputs name
  inline std::ostream& outputNameImpl( std::ostream& os ) const noexcept;

};

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_SKETCHER_ROW_BLOCK_GAUSSIAN_PROJECTION_SKETCHER_HH_
