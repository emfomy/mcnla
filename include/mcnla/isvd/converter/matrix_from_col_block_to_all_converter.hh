////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/converter/matrix_from_col_block_to_all_converter.hh
/// @brief   The definition of the converter that converts a matrix from column-block storage to all MPI node.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_CONVERTER_MATRIX_FROM_COL_BLOCK_TO_ALL_CONVERTER_HH_
#define MCNLA_ISVD_CONVERTER_MATRIX_FROM_COL_BLOCK_TO_ALL_CONVERTER_HH_

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
struct MatrixFromColBlockToAllConverterTag {};
template <typename _Val> using MatrixFromColBlockToAllConverter = Converter<MatrixFromColBlockToAllConverterTag, _Val>;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  isvd_converter_module
/// The converter that converts a matrix from column-block storage to all MPI node.
///
/// @tparam  _Val  The value type.
///
template <class _Val>
#ifndef DOXYGEN_SHOULD_SKIP_THIS
class Converter<MatrixFromColBlockToAllConverterTag, _Val>
#else  // DOXYGEN_SHOULD_SKIP_THIS
class MatrixFromColBlockToAllConverter
#endif  // DOXYGEN_SHOULD_SKIP_THIS
  : public StageWrapper<MatrixFromColBlockToAllConverter<_Val>> {

  friend StageWrapper<MatrixFromColBlockToAllConverter<_Val>>;

 private:

  using BaseType = StageWrapper<MatrixFromColBlockToAllConverter<_Val>>;

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
  void runImpl( const DenseMatrixColMajor<_Val> &matrix, DenseMatrixColMajor<_Val> &matrix_j ) noexcept;

};

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_CONVERTER_MATRIX_FROM_COL_BLOCK_TO_ALL_CONVERTER_HH_
