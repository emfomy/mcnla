////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/converter/matrix_to_rowblock_converter.hh
/// @brief   The definition of the converter that converts a matrix to row-block version.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_CONVERTER_MATRIX_TO_ROWBLOCK_CONVERTER_HH_
#define MCNLA_ISVD_CONVERTER_MATRIX_TO_ROWBLOCK_CONVERTER_HH_

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
struct MatrixToRowBlockConverterTag {};
template <typename _Val> using MatrixToRowBlockConverter = Converter<MatrixToRowBlockConverterTag, _Val>;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  isvd_converter_module
/// The converter that converts a matrix to row-block version.
///
/// @tparam  _Val  The value type.
///
template <class _Val>
#ifndef DOXYGEN_SHOULD_SKIP_THIS
class Converter<MatrixToRowBlockConverterTag, _Val>
#else  // DOXYGEN_SHOULD_SKIP_THIS
class MatrixToRowBlockConverter
#endif  // DOXYGEN_SHOULD_SKIP_THIS
  : public StageWrapper<MatrixToRowBlockConverter<_Val>> {

  friend StageWrapper<MatrixToRowBlockConverter<_Val>>;

 private:

  using BaseType = StageWrapper<MatrixToRowBlockConverter<_Val>>;

 public:

//  using _Val = _Val;

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
  void runImpl( const DenseMatrixRowMajor<_Val> &matrix_j, DenseMatrixRowMajor<_Val> &matrix ) noexcept;

};

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_CONVERTER_MATRIX_TO_ROWBLOCK_CONVERTER_HH_
