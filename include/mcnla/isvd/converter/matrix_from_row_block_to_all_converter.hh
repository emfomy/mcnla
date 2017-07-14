////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/converter/matrix_from_row_block_to_all_converter.hh
/// @brief   The definition of the converter that converts a matrix from row-block storage to all MPI node.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_CONVERTER_MATRIX_FROM_ROW_BLOCK_TO_ALLCONVERTER_HH_
#define MCNLA_ISVD_CONVERTER_MATRIX_FROM_ROW_BLOCK_TO_ALLCONVERTER_HH_

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
struct MatrixFromRowBlockToAllConverterTag {};
template <typename _Val> using MatrixFromRowBlockToAllConverter = Converter<MatrixFromRowBlockToAllConverterTag, _Val>;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  isvd_converter_module
/// The converter that converts a matrix from row-block storage to all MPI node.
///
/// @tparam  _Val  The value type.
///
template <class _Val>
#ifndef DOXYGEN_SHOULD_SKIP_THIS
class Converter<MatrixFromRowBlockToAllConverterTag, _Val>
#else  // DOXYGEN_SHOULD_SKIP_THIS
class MatrixFromRowBlockToAllConverter
#endif  // DOXYGEN_SHOULD_SKIP_THIS
  : public StageWrapper<MatrixFromRowBlockToAllConverter<_Val>> {

  friend StageWrapper<MatrixFromRowBlockToAllConverter<_Val>>;

 private:

  using BaseType = StageWrapper<MatrixFromRowBlockToAllConverter<_Val>>;

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

#endif  // MCNLA_ISVD_CONVERTER_MATRIX_FROM_ROW_BLOCK_TO_ALLCONVERTER_HH_
