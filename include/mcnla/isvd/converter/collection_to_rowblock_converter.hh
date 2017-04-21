////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/converter/collection_to_rowblock_converter.hh
/// @brief   The definition of the converter that converts a matrix collection to row-block version.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_CONVERTER_COLLECTION_TO_ROWBLOCK_CONVERTER_HH_
#define MCNLA_ISVD_CONVERTER_COLLECTION_TO_ROWBLOCK_CONVERTER_HH_

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
/// The tag of the converter that converts a matrix collection to row-block version.
///
struct CollectionToRowBlockConverterTag {};

/// @ingroup  isvd_converter_module
template <typename _Val>
using CollectionToRowBlockConverter = Converter<CollectionToRowBlockConverterTag, _Val>;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  isvd_converter_module
/// The converter that converts a matrix collection to row-block version.
///
/// @tparam  _Val  The value type.
///
template <class _Val>
class Converter<CollectionToRowBlockConverterTag, _Val>
  : public StageWrapper<Converter<CollectionToRowBlockConverterTag, _Val>> {

  friend StageWrapper<Converter<CollectionToRowBlockConverterTag, _Val>>;

 private:

  using BaseType = StageWrapper<Converter<CollectionToRowBlockConverterTag, _Val>>;

 public:

  using ValType = _Val;

 protected:

  using BaseType::parameters_;
  using BaseType::initialized_;
  using BaseType::computed_;
  using BaseType::moments_;
  using BaseType::comm_times_;

 public:

  // Constructor
  inline Converter( const Parameters<ValType> &parameters ) noexcept;

 protected:

  // Initializes
  void initializeImpl() noexcept;

  // Converts data
  void runImpl( DenseMatrixCollection201<ValType> &collection_q, DenseMatrixCollection201<ValType> &collection_qj ) noexcept;

};

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_CONVERTER_COLLECTION_TO_ROWBLOCK_CONVERTER_HH_
