////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/collection/dense_matrix_collection_102.hh
/// @brief   The definition of dense matrix collection with dimension order (dim1, dim0, dim2).
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_COLLECTION_DENSE_MATRIX_COLLECTION_102_HH_
#define MCNLA_CORE_MATRIX_COLLECTION_DENSE_MATRIX_COLLECTION_102_HH_

#include <mcnla/core/matrix/def.hpp>
#include <mcnla/core/matrix/collection/dense_matrix_collection.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The tag of dense matrix collection with dimension order (dim1, dim0, dim2).
///
struct DenseMatrixCollection102Tag {};

/// @ingroup  matrix_collection_module
template <typename _Val>
using DenseMatrixCollection102 = DenseMatrixCollection<DenseMatrixCollection102Tag, _Val, Trans::TRANS>;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  matrix_collection_module
/// The dense matrix collection with dimension order (dim1, dim0, dim2).
///
/// @tparam  _Val  The value type.
///
template <typename _Val>
class DenseMatrixCollection<DenseMatrixCollection102Tag, _Val, Trans::TRANS>
  : public MatrixCollectionWrapper<DenseMatrixCollection102<_Val>> {

  friend MatrixCollectionWrapper<DenseMatrixCollection102<_Val>>;

 public:

  using ValType        = _Val;
  using CollectionType = DenseMatrixCollection102<_Val>;
  using MatrixType     = DenseMatrixRowMajor<_Val>;

 private:

  using BaseType  = MatrixCollectionWrapper<DenseMatrixCollection102<_Val>>;
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
  inline DenseMatrixCollection() noexcept;
  inline DenseMatrixCollection( const index_t nrow, const index_t ncol, const index_t nmat ) noexcept;
  inline DenseMatrixCollection( const SizesType sizes ) noexcept;
  inline DenseMatrixCollection( const index_t nrow, const index_t ncol, const index_t nmat, const index_t mrow ) noexcept;
  inline DenseMatrixCollection( const SizesType sizes, const index_t mrow ) noexcept;
  inline DenseMatrixCollection( const index_t nrow, const MatrixType &data ) noexcept;
  inline DenseMatrixCollection( const index_t nrow, const index_t mrow, const MatrixType &data ) noexcept;
  inline DenseMatrixCollection( const DenseMatrixCollection &other ) noexcept;
  inline DenseMatrixCollection( DenseMatrixCollection &&other ) noexcept;

  // Operators
  inline DenseMatrixCollection& operator=( const DenseMatrixCollection &other ) noexcept;
  inline DenseMatrixCollection& operator=( DenseMatrixCollection &&other ) noexcept;

  // Gets information
  inline bool isShrunk() const noexcept;
  inline index_t mrow() const noexcept;

  // Gets data
  inline       MatrixType& data() noexcept;
  inline const MatrixType& data() const noexcept;

  // Resizes
  template <typename... Args>
  inline void reconstruct( Args... args ) noexcept;

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

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_COLLECTION_DENSE_MATRIX_COLLECTION_102_HH_
