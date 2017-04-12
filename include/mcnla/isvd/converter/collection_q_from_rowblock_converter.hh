////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/converter/collection_q_from_rowblock_converter.hh
/// @brief   The definition of the converter that converts collection Q from row-block version.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_CONVERTER_COLLECTION_Q_FORM_ROWBLOCK_CONVERTER_HH_
#define MCNLA_ISVD_CONVERTER_COLLECTION_Q_FORM_ROWBLOCK_CONVERTER_HH_

#include <mcnla/isvd/def.hpp>
#include <mcnla/isvd/converter/converter.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  isvd_converter_module_detail
/// The tag of the converter that converts collection Q from row-block version.
///
struct CollectionQFromRowBlockConverterTag {};

/// @ingroup  isvd_converter_module
template <typename _Val>
using CollectionQFromRowBlockConverter = Converter<CollectionQFromRowBlockConverterTag, _Val>;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  isvd_converter_module
/// The converter that converts collection Q from row-block version.
///
/// @tparam  _Val  The value type.
///
template <class _Val>
class Converter<CollectionQFromRowBlockConverterTag, _Val>
  : public ComponentWrapper<Converter<CollectionQFromRowBlockConverterTag, _Val>> {

  friend ComponentWrapper<Converter<CollectionQFromRowBlockConverterTag, _Val>>;

 private:

  using BaseType = ComponentWrapper<Converter<CollectionQFromRowBlockConverterTag, _Val>>;

 public:

  using ValType = _Val;

 protected:

  using BaseType::parameters_;
  using BaseType::initialized_;
  using BaseType::computed_;
  using BaseType::moments_;

 public:

  // Constructor
  inline Converter( const Parameters<ValType> &parameters ) noexcept;

 protected:

  // Initializes
  void initializeImpl() noexcept;

  // Converts data
  void runImpl( DenseMatrixCollection201<ValType> &collection_qj, DenseMatrixCollection201<ValType> &collection_q ) noexcept;

};

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_CONVERTER_COLLECTION_Q_FORM_ROWBLOCK_CONVERTER_HH_
