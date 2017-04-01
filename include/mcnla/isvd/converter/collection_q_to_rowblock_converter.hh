////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/converter/collection_q_to_rowblock_converter.hh
/// @brief   The definition of the converter that converts collection Q to row-block version.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_CONVERTER_COLLECTION_Q_TO_ROWBLOCK_CONVERTER_HH_
#define MCNLA_ISVD_CONVERTER_COLLECTION_Q_TO_ROWBLOCK_CONVERTER_HH_

#include <mcnla/isvd/def.hpp>
#include <mcnla/isvd/core/component_wrapper.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  isvd_converter_module
/// The converter that converts collection Q to row-block version.
///
/// @tparam  _Val  The value type.
///
template <class _Val>
class CollectionQToRowBlockConverter
  : public ComponentWrapper<CollectionQToRowBlockConverter<_Val>> {

  friend ComponentWrapper<CollectionQToRowBlockConverter<_Val>>;

 private:

  using BaseType = ComponentWrapper<CollectionQToRowBlockConverter<_Val>>;

 public:

  using ValType = _Val;

 protected:

  using BaseType::parameters_;
  using BaseType::moments_;

 public:

  // Constructor
  inline CollectionQToRowBlockConverter( const Parameters &parameters ) noexcept;

 protected:

  // Initializes
  void initializeImpl() noexcept;

  // Converts data
  void runImpl( DenseMatrixCollection120<ValType> &collection_q, DenseMatrixCollection120<ValType> &collection_qj ) noexcept;

};

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_CONVERTER_COLLECTION_Q_TO_ROWBLOCK_CONVERTER_HH_
