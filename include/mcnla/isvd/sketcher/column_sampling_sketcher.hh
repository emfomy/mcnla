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
/// @ingroup  isvd_sketcher_module_detail
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
  : public ComponentWrapper<ColumnSamplingSketcher<_Val>> {

  friend ComponentWrapper<ColumnSamplingSketcher<_Val>>;

 private:

  using BaseType = ComponentWrapper<ColumnSamplingSketcher<_Val>>;

 public:

  using ValType = _Val;

 protected:

  /// The name.
  static constexpr const char* name_ = "Column Sampling Sketcher";

  // The index vector
  DenseVector<index_t> vector_idxs_;

  using BaseType::parameters_;
  using BaseType::moments_;

 public:

  // Constructor
  inline Sketcher( const Parameters<ValType> &parameters ) noexcept;

 protected:

  // Initializes
  void initializeImpl() noexcept;

  // Random sketches
  template <class _Matrix>
  void runImpl( const _Matrix &matrix_a, DenseMatrixCollection120<ValType> &collection_q ) noexcept;

};

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_SKETCHER_COLUMN_SAMPLING_SKETCHER_HH_
