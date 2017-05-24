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

#ifndef DOXYGEN_SHOULD_SKIP_THIS
struct MatrixFromRowBlockConverterTag {};
template <typename _Val> using MatrixFromRowBlockConverter = Converter<MatrixFromRowBlockConverterTag, _Val>;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  isvd_converter_module
/// The converter that converts a matrix from row-block version.
///
/// @tparam  _Val  The value type.
///
template <class _Val>
#ifndef DOXYGEN_SHOULD_SKIP_THIS
class Converter<MatrixFromRowBlockConverterTag, _Val>
#else  // DOXYGEN_SHOULD_SKIP_THIS
class MatrixFromRowBlockConverter
#endif  // DOXYGEN_SHOULD_SKIP_THIS
  : public StageWrapper<MatrixFromRowBlockConverter<_Val>> {

  friend StageWrapper<MatrixFromRowBlockConverter<_Val>>;

 private:

  using BaseType = StageWrapper<MatrixFromRowBlockConverter<_Val>>;

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
  void runImpl( const DenseMatrixRowMajor<_Val> &matrix, DenseMatrixRowMajor<_Val> &matrix_j ) noexcept;

};

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_CONVERTER_MATRIX_FROM_ROWBLOCK_CONVERTER_HH_
