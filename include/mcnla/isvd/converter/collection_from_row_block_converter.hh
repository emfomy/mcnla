////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/converter/collection_from_row_block_converter.hh
/// @brief   The definition of the converter that converts collection Q from row-block storage.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_CONVERTER_COLLECTION_FORM_ROW_BLOCK_CONVERTER_HH_
#define MCNLA_ISVD_CONVERTER_COLLECTION_FORM_ROW_BLOCK_CONVERTER_HH_

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

#ifndef DOXYGEN_SHOULD_SKIP_THIS
struct CollectionFromRowBlockConverterTag {};
template <typename _Val> using CollectionFromRowBlockConverter = Converter<CollectionFromRowBlockConverterTag, _Val>;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  isvd_converter_module
/// The converter that converts collection Q from row-block storage.
///
/// @tparam  _Val  The value type.
///
template <class _Val>
#ifndef DOXYGEN_SHOULD_SKIP_THIS
class Converter<CollectionFromRowBlockConverterTag, _Val>
#else  // DOXYGEN_SHOULD_SKIP_THIS
class CollectionFromRowBlockConverter
#endif  // DOXYGEN_SHOULD_SKIP_THIS
  : public StageWrapper<CollectionFromRowBlockConverter<_Val>> {

  friend StageWrapper<CollectionFromRowBlockConverter<_Val>>;

 private:

  using BaseType = StageWrapper<CollectionFromRowBlockConverter<_Val>>;

 protected:

  using BaseType::parameters_;
  using BaseType::initialized_;
  using BaseType::computed_;
  using BaseType::moments_;
  using BaseType::comm_times_;

 public:

  // Constructor
  inline Converter( const Parameters<_Val> &parameters ) noexcept;

 protected:

  // Initializes
  void initializeImpl() noexcept;

  // Converts data
  void runImpl( DenseMatrixCollectionColBlockRowMajor<_Val> &collection_qj,
                DenseMatrixCollectionColBlockRowMajor<_Val> &collection_q ) noexcept;

};

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_CONVERTER_COLLECTION_FORM_ROW_BLOCK_CONVERTER_HH_
