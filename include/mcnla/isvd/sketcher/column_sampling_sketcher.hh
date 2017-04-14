////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/sketcher/column_sampling_sketcher.hh
/// @brief   The definition of column sampling sketcher.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_SKETCHER_COLUMN_SAMPLING_SKETCHER_HH_
#define MCNLA_ISVD_SKETCHER_COLUMN_SAMPLING_SKETCHER_HH_

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
/// The column sampling sketcher tag.
///
struct ColumnSamplingSketcherTag {};

/// @ingroup  isvd_sketcher_module
template <typename _Val>
using ColumnSamplingSketcher = Sketcher<ColumnSamplingSketcherTag, _Val>;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  isvd_sketcher_module
/// The column sampling sketcher.
///
/// @tparam  _Val    The value type.
///
template <typename _Val>
class Sketcher<ColumnSamplingSketcherTag, _Val>
  : public StageWrapper<ColumnSamplingSketcher<_Val>> {

  friend StageWrapper<ColumnSamplingSketcher<_Val>>;

 private:

  using BaseType = StageWrapper<ColumnSamplingSketcher<_Val>>;

 public:

  using ValType = _Val;

 protected:

  /// The name.
  static constexpr const char* name_ = "Column Sampling Sketcher";

  /// The random seed.
  index_t seed_;

  // The index vector
  DenseVector<index_t> vector_idxs_;

  using BaseType::parameters_;
  using BaseType::initialized_;
  using BaseType::computed_;
  using BaseType::moments_;

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

#endif  // MCNLA_ISVD_SKETCHER_COLUMN_SAMPLING_SKETCHER_HH_
