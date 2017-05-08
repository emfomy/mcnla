////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/collection/dense_matrix_collection_012.hh
/// @brief   The definition of dense matrix collection with dimension order (dim0, dim1, dim2).
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_COLLECTION_DENSE_MATRIX_COLLECTION_012_HH_
#define MCNLA_CORE_MATRIX_COLLECTION_DENSE_MATRIX_COLLECTION_012_HH_

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
/// The tag of dense matrix collection with dimension order (dim0, dim1, dim2).
///
struct DenseMatrixCollection012Tag {};

/// @ingroup  matrix_collection_module
template <typename _Val>
using DenseMatrixCollection012 = DenseMatrixCollection<DenseMatrixCollection012Tag, _Val, Trans::NORMAL>;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  matrix_collection_module
/// The dense matrix collection with dimension order (dim0, dim1, dim2).
///
/// @tparam  _Val  The value type.
///
template <typename _Val>
class DenseMatrixCollection<DenseMatrixCollection012Tag, _Val, Trans::NORMAL>
  : public MatrixCollectionWrapper<DenseMatrixCollection012<_Val>> {

  friend MatrixCollectionWrapper<DenseMatrixCollection012<_Val>>;

 public:

  using ValType        = _Val;
  using CollectionType = DenseMatrixCollection012<_Val>;
  using MatrixType     = DenseMatrixColMajor<_Val>;

 private:

  using BaseType  = MatrixCollectionWrapper<DenseMatrixCollection012<_Val>>;
  using SizesType = std::tuple<index_t, index_t, index_t>;

 protected:

  /// The base data.
  MatrixType data_;

  /// The number of columns in each matrix.
  index_t ncol_;

  /// The maximum number of the columns.
  index_t mcol_;

 public:

  // Constructors
  inline DenseMatrixCollection() noexcept;
  inline DenseMatrixCollection( const index_t nrow, const index_t ncol, const index_t nmat ) noexcept;
  inline DenseMatrixCollection( const SizesType sizes ) noexcept;
  inline DenseMatrixCollection( const index_t nrow, const index_t ncol, const index_t nmat, const index_t mcol ) noexcept;
  inline DenseMatrixCollection( const SizesType sizes, const index_t mcol ) noexcept;
  inline DenseMatrixCollection( const index_t ncol, const MatrixType &data ) noexcept;
  inline DenseMatrixCollection( const index_t ncol, const index_t mcol, const MatrixType &data ) noexcept;
  inline DenseMatrixCollection( const DenseMatrixCollection &other ) noexcept;

  // Operators
  inline DenseMatrixCollection& operator=( const DenseMatrixCollection &other ) noexcept;

  // Copy
  inline DenseMatrixCollection copy() const noexcept;

  // Gets information
  inline bool isShrunk() const noexcept;
  inline index_t mrow() const noexcept;
  inline index_t mcol() const noexcept;

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
  inline       CollectionType operator()( const IdxRange &rowrange, const FullRange, const FullRange ) noexcept;
  inline const CollectionType operator()( const IdxRange &rowrange, const FullRange, const FullRange ) const noexcept;

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

#endif  // MCNLA_CORE_MATRIX_COLLECTION_DENSE_MATRIX_COLLECTION_012_HH_
