////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/converter/matrix_q_from_rowblock_converter.hh
/// @brief   The definition of the converter that converts matrix Q from row-block version.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_CONVERTER_MATRIX_Q_FROM_ROWBLOCK_CONVERTER_HH_
#define MCNLA_ISVD_CONVERTER_MATRIX_Q_FROM_ROWBLOCK_CONVERTER_HH_

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
/// The tag of converter that converts matrix Q from row-block version.
///
struct MatrixQFromRowBlockConverterTag {};

/// @ingroup  isvd_converter_module
template <typename _Val>
using MatrixQFromRowBlockConverter = Converter<MatrixQFromRowBlockConverterTag, _Val>;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  isvd_converter_module
/// The converter that converts matrix Q from row-block version.
///
/// @tparam  _Val  The value type.
///
template <class _Val>
class Converter<MatrixQFromRowBlockConverterTag, _Val>
  : public ComponentWrapper<Converter<MatrixQFromRowBlockConverterTag, _Val>> {

  friend ComponentWrapper<Converter<MatrixQFromRowBlockConverterTag, _Val>>;

 private:

  using BaseType = ComponentWrapper<Converter<MatrixQFromRowBlockConverterTag, _Val>>;

 public:

  using ValType = _Val;

 protected:

  using BaseType::parameters_;
  using BaseType::moments_;

 public:

  // Constructor
  inline Converter( const Parameters<ValType> &parameters ) noexcept;

 protected:

  // Initializes
  void initializeImpl() noexcept;

  // Converts data
  void runImpl( DenseMatrixRowMajor<ValType> &collection_q, DenseMatrixRowMajor<ValType> &collection_qj ) noexcept;

};

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_CONVERTER_MATRIX_Q_FROM_ROWBLOCK_CONVERTER_HH_
