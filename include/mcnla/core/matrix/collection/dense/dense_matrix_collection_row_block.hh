////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/collection/dense/dense_matrix_collection_row_block.hh
/// @brief   The definition of dense matrix collection with dimension order (dim1, dim0, dim2).
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_COLLECTION_DENSE_DENSE_MATRIX_COLLECTION_ROW_BLOCK_HH_
#define MCNLA_CORE_MATRIX_COLLECTION_DENSE_DENSE_MATRIX_COLLECTION_ROW_BLOCK_HH_

#include <mcnla/core/matrix/collection/dense/def.hpp>
#include <mcnla/core/matrix/collection/base/matrix_collection_wrapper.hpp>

#ifndef DOXYGEN_SHOULD_SKIP_THIS
  #define MCNLA_TMP0 GeMatCollS
  #define MCNLA_TMP1 GeMatCollS<RowBlockTag, _Core, DenseTag, _Val, _trans>
#else  // DOXYGEN_SHOULD_SKIP_THIS
  #define MCNLA_TMP0 DenseMatrixCollectionRowBlockBase
  #define MCNLA_TMP1 DenseMatrixCollectionRowBlockBase
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <class _Core, typename _Val, Trans _trans>
using DenseMatrixCollectionRowBlockBase = GeMatCollS<RowBlockTag, _Core, DenseTag, _Val, _trans>;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  matrix_collection_module
/// dense matrix collection of row-blocks.
///
/// @tparam  _Core   The core type.
/// @tparam  _Val    The value type.
/// @tparam  _trans  The transpose storage layout.
///
template <class _Core, typename _Val, Trans _trans>
class MCNLA_TMP1
  : public MatrixCollectionWrapper<DenseMatrixCollectionRowBlockBase<_Core, _Val, _trans>> {

  friend MatrixCollectionWrapper<DenseMatrixCollectionRowBlockBase<_Core, _Val, _trans>>;

 public:

  using ValType        = _Val;
  using CollectionType = DenseMatrixCollectionRowBlockBase<_Core, _Val, _trans>;
  using MatrixType     = GeMatS<_Core, DenseTag, _Val, _trans>;

 private:

  using BaseType  = MatrixCollectionWrapper<DenseMatrixCollectionRowBlockBase<_Core, _Val, _trans>>;
  using SizesType = std::tuple<index_t, index_t, index_t>;

 protected:

  /// The base data.
  MatrixType data_;

  /// The number of rows in each matrix.
  index_t nrow_;

  /// The maximum number of the rows.
  index_t mrow_;

 public:

  // Constructors
  inline MCNLA_TMP0() noexcept;
  inline MCNLA_TMP0( const index_t nrow, const index_t ncol, const index_t nmat ) noexcept;
  inline MCNLA_TMP0( const SizesType sizes ) noexcept;
  inline MCNLA_TMP0( const index_t nrow, const index_t ncol, const index_t nmat, const index_t mrow ) noexcept;
  inline MCNLA_TMP0( const SizesType sizes, const index_t mrow ) noexcept;
  inline MCNLA_TMP0( const index_t nrow, const MatrixType &data ) noexcept;
  inline MCNLA_TMP0( const index_t nrow, const index_t mrow, const MatrixType &data ) noexcept;
  inline MCNLA_TMP0( const CollectionType &other ) noexcept;

  // Operators
  inline CollectionType& operator=( const CollectionType &other ) noexcept;

  // Copy
  inline CollectionType copy() const noexcept;

  // Gets information
  inline bool isShrunk() const noexcept;
  inline index_t mrow() const noexcept;

  // Gets data
  inline       MatrixType& data() noexcept;
  inline const MatrixType& data() const noexcept;

  // Resizes
  template <typename ..._Args>
  inline void reconstruct( _Args... args ) noexcept;

  // Gets collection
  using BaseType::operator();
  inline       CollectionType operator()( const IdxRange &idxrange ) noexcept;
  inline const CollectionType operator()( const IdxRange &idxrange ) const noexcept;
  inline       CollectionType operator()( const FullRange, const FullRange, const IdxRange &idxrange ) noexcept;
  inline const CollectionType operator()( const FullRange, const FullRange, const IdxRange &idxrange ) const noexcept;
  inline       CollectionType operator()( const FullRange, const IdxRange &colrange, const FullRange ) noexcept;
  inline const CollectionType operator()( const FullRange, const IdxRange &colrange, const FullRange ) const noexcept;

  // Gets matrix
  inline       MatrixType& unfold() noexcept;
  inline const MatrixType& unfold() const noexcept;

 protected:

  // Gets information
  inline bool    isEmptyImpl() const noexcept;
  inline index_t nrowImpl() const noexcept;
  inline index_t ncolImpl() const noexcept;
  inline index_t nmatImpl() const noexcept;

  // Gets matrix
  inline       MatrixType getImpl( const index_t idx ) noexcept;
  inline const MatrixType getImpl( const index_t idx ) const noexcept;

};

/// @ingroup  matrix_collection_module
/// @see  DenseMatrixCollectionRowBlockBase
template <typename _Val, Trans _trans>
using DenseMatrixCollectionRowBlock = DenseMatrixCollectionRowBlockBase<CpuTag, _Val, _trans>;

/// @ingroup  matrix_collection_module
/// @see  DenseMatrixCollectionRowBlockBase
template <typename _Val>
using DenseMatrixCollectionRowBlockColMajor = DenseMatrixCollectionRowBlock<_Val, Trans::NORMAL>;

/// @ingroup  matrix_collection_module
/// @see  DenseMatrixCollectionRowBlockBase
template <typename _Val>
using DenseMatrixCollectionRowBlockRowMajor = DenseMatrixCollectionRowBlock<_Val, Trans::TRANS>;

}  // namespace matrix

}  // namespace mcnla

#undef MCNLA_TMP0
#undef MCNLA_TMP1

#endif  // MCNLA_CORE_MATRIX_COLLECTION_DENSE_DENSE_MATRIX_COLLECTION_ROW_BLOCK_HH_
