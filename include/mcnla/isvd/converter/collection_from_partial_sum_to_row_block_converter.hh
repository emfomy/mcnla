////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/converter/collection_from_partial_sum_to_row_block_converter.hh
/// @brief   The definition of the converter that converts a matrix collection from partial sum to row-block storage.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_CONVERTER_COLLECTION_FROM_PARTIAL_SUM_TO_ROW_BLOCK_CONVERTER_HH_
#define MCNLA_ISVD_CONVERTER_COLLECTION_FROM_PARTIAL_SUM_TO_ROW_BLOCK_CONVERTER_HH_

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
struct CollectionFromPartialSumToRowBlockConverterTag {};
template <typename _Val> using CollectionFromPartialSumToRowBlockConverter
    = Converter<CollectionFromPartialSumToRowBlockConverterTag, _Val>;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  isvd_converter_module
/// The converter that converts a matrix collection from partial sum to row-block storage.
///
/// @tparam  _Val  The value type.
///
template <class _Val>
#ifndef DOXYGEN_SHOULD_SKIP_THIS
class Converter<CollectionFromPartialSumToRowBlockConverterTag, _Val>
#else  // DOXYGEN_SHOULD_SKIP_THIS
class CollectionFromPartialSumToRowBlockConverter
#endif  // DOXYGEN_SHOULD_SKIP_THIS
  : public StageWrapper<CollectionFromPartialSumToRowBlockConverter<_Val>> {

  friend StageWrapper<CollectionFromPartialSumToRowBlockConverter<_Val>>;

 private:

  using BaseType = StageWrapper<CollectionFromPartialSumToRowBlockConverter<_Val>>;

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
  void runImpl( DenseMatrixCollectionColBlockRowMajor<_Val> &collection_qjp,
                DenseMatrixCollectionColBlockRowMajor<_Val> &collection_qj ) noexcept;

};

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_CONVERTER_COLLECTION_FROM_PARTIAL_SUM_TO_ROW_BLOCK_CONVERTER_HH_
