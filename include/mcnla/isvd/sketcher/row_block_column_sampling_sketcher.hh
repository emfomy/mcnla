////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/sketcher/row_block_column_sampling_sketcher.hh
/// @brief   The definition of column sampling sketcher (row-block version).
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_SKETCHER_ROW_BLOCK_COLUMN_SAMPLING_SKETCHER_HH_
#define MCNLA_ISVD_SKETCHER_ROW_BLOCK_COLUMN_SAMPLING_SKETCHER_HH_

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
/// The row-block column sampling sketcher tag.
///
struct RowBlockColumnSamplingSketcherTag {};

/// @ingroup  isvd_sketcher_module
template <typename _Val>
using RowBlockColumnSamplingSketcher = Sketcher<RowBlockColumnSamplingSketcherTag, _Val>;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  isvd_sketcher_module
/// The column sampling sketcher (row-block version).
///
/// @tparam  _Val    The value type.
///
template <typename _Val>
class Sketcher<RowBlockColumnSamplingSketcherTag, _Val>
  : public StageWrapper<RowBlockColumnSamplingSketcher<_Val>> {

  friend StageWrapper<RowBlockColumnSamplingSketcher<_Val>>;

 private:

  using BaseType = StageWrapper<RowBlockColumnSamplingSketcher<_Val>>;

 public:

  using ValType = _Val;

 protected:

  /// The name.
  static constexpr const char* name_ = "Column Sampling Sketcher (Row-Block Version)";

  /// The name of each part of the stage.
  static constexpr const char* names_ = "random generating / projection";

  /// The random seed.
  index_t seed_;

  // The index vector
  DenseVector<index_t> vector_idxs_;

  using BaseType::parameters_;
  using BaseType::initialized_;
  using BaseType::computed_;
  using BaseType::moments_;
  using BaseType::comm_times_;

 public:

  // Constructor
  inline Sketcher( const Parameters<ValType> &parameters, const index_t seed = rand() ) noexcept;

  // Gets parameters
  inline index_t seed() const noexcept;

  // Sets parameters
  inline Sketcher& setSeed( const index_t seed ) noexcept;

 protected:

  // Initializes
  void initializeImpl() noexcept;

  // Random sketches
  template <class _Matrix>
  void runImpl( const _Matrix &matrix_a, DenseMatrixCollection201<ValType> &collection_q ) noexcept;

};

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_SKETCHER_ROW_BLOCK_COLUMN_SAMPLING_SKETCHER_HH_
