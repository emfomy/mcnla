////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/converter/matrix_from_rowblock_converter.hh
/// @brief   The definition of the converter that converts a matrix from row-block version.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_CONVERTER_MATRIX_FROM_ROWBLOCK_CONVERTER_HH_
#define MCNLA_ISVD_CONVERTER_MATRIX_FROM_ROWBLOCK_CONVERTER_HH_

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
/// The tag of the converter that converts a matrix from row-block version.
///
struct MatrixFromRowBlockConverterTag {};

/// @ingroup  isvd_converter_module
template <typename _Val>
using MatrixFromRowBlockConverter = Converter<MatrixFromRowBlockConverterTag, _Val>;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  isvd_converter_module
/// The converter that converts a matrix from row-block version.
///
/// @tparam  _Val  The value type.
///
template <class _Val>
class Converter<MatrixFromRowBlockConverterTag, _Val>
  : public ComponentWrapper<Converter<MatrixFromRowBlockConverterTag, _Val>> {

  friend ComponentWrapper<Converter<MatrixFromRowBlockConverterTag, _Val>>;

 private:

  using BaseType = ComponentWrapper<Converter<MatrixFromRowBlockConverterTag, _Val>>;

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
  void runImpl( const DenseMatrixRowMajor<ValType> &matrix, DenseMatrixRowMajor<ValType> &matrix_j ) noexcept;

};

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_CONVERTER_MATRIX_FROM_ROWBLOCK_CONVERTER_HH_
