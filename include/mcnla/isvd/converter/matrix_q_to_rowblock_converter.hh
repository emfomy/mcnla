////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/converter/matrix_q_to_rowblock_converter.hh
/// @brief   The definition of the converter that converts matrix Q to row-block version.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_CONVERTER_MATRIX_Q_TO_ROWBLOCK_CONVERTER_HH_
#define MCNLA_ISVD_CONVERTER_MATRIX_Q_TO_ROWBLOCK_CONVERTER_HH_

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
/// The tag of the converter that converts matrix Q to row-block version.
///
struct MatrixQToRowBlockConverterTag {};

/// @ingroup  isvd_converter_module
template <typename _Val>
using MatrixQToRowBlockConverter = Converter<MatrixQToRowBlockConverterTag, _Val>;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  isvd_converter_module
/// The converter that converts matrix Q to row-block version.
///
/// @tparam  _Val  The value type.
///
template <class _Val>
class Converter<MatrixQToRowBlockConverterTag, _Val>
  : public ComponentWrapper<Converter<MatrixQToRowBlockConverterTag, _Val>> {

  friend ComponentWrapper<Converter<MatrixQToRowBlockConverterTag, _Val>>;

 private:

  using BaseType = ComponentWrapper<Converter<MatrixQToRowBlockConverterTag, _Val>>;

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
  void runImpl( DenseMatrixRowMajor<ValType> &collection_qj, DenseMatrixRowMajor<ValType> &collection_q ) noexcept;

};

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_CONVERTER_MATRIX_Q_TO_ROWBLOCK_CONVERTER_HH_
