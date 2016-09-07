////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/matrix/dense_matrix.hpp
/// @brief   The dense matrix class.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_MATRIX_DENSE_MATRIX_HPP_
#define ISVD_MATRIX_DENSE_MATRIX_HPP_

#include <iostream>
#include <utility>
#include <isvd/isvd.hpp>
#include <isvd/matrix/matrix_base.hpp>
#include <isvd/matrix/dense_base.hpp>
#include <isvd/matrix/dense_vector.hpp>
#include <isvd/matrix/dense_matrix_iterator.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

template <typename _Scalar> class DenseVector;
template <typename _Scalar, Layout _layout> class DenseMatrix;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The internal namespace.
//
namespace internal {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense matrix traits.
///
/// @tparam  _Scalar  The scalar type.
/// @tparam  _layout  The storage layout.
///
template <typename _Scalar, Layout _layout>
struct Traits<DenseMatrix<_Scalar, _layout>> {
  static const Layout layout = _layout;
  using ScalarType     = _Scalar;
  using RealScalarType = typename internal::ScalarTraits<_Scalar>::RealType;
  using VectorType     = DenseVector<ScalarType>;
  using RealVectorType = DenseVector<RealScalarType>;
  using TransposeType  = DenseMatrix<ScalarType, changeLayout(_layout)>;
};

}  // namespace internal

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense matrix class.
///
/// @tparam  _Scalar  The scalar type.
/// @tparam  _layout  The storage layout.
///
template <typename _Scalar, Layout _layout = Layout::COLMAJOR>
class DenseMatrix
  : public internal::MatrixBase<DenseMatrix<_Scalar, _layout>>,
    public internal::DenseBase<DenseMatrix<_Scalar, _layout>> {

 public:

  static const Layout layout = _layout;

  using ScalarType     = _Scalar;
  using RealScalarType = typename internal::ScalarTraits<_Scalar>::RealType;

  using VectorType     = DenseVector<ScalarType>;
  using RealVectorType = DenseVector<RealScalarType>;
  using TransposeType  = DenseMatrix<ScalarType, changeLayout(_layout)>;

  using DataType       = DenseData<ScalarType>;
  using IteratorType   = internal::DenseMatrixIterator<ScalarType, _layout>;

 private:

  using MatrixBaseType = internal::MatrixBase<DenseMatrix<_Scalar, _layout>>;
  using DenseBaseType  = internal::DenseBase<DenseMatrix<_Scalar, _layout>>;

 protected:

  /// The leading dimension.
  index_t pitch_;

  using MatrixBaseType::nrow_;
  using MatrixBaseType::ncol_;
  using MatrixBaseType::size1_;
  using MatrixBaseType::size2_;
  using DenseBaseType::offset_;
  using DenseBaseType::data_;

 public:

  // Constructors
  DenseMatrix() noexcept;
  DenseMatrix( const index_t nrow, const index_t ncol ) noexcept;
  DenseMatrix( const std::pair<index_t, index_t> sizes ) noexcept;
  DenseMatrix( const index_t nrow, const index_t ncol, const index_t pitch ) noexcept;
  DenseMatrix( const std::pair<index_t, index_t> sizes, const index_t pitch ) noexcept;
  DenseMatrix( const index_t nrow, const index_t ncol, const index_t pitch, std::shared_ptr<ScalarType> value ) noexcept;
  DenseMatrix( const index_t nrow, const index_t ncol, const index_t pitch, std::shared_ptr<ScalarType> value,
               const index_t capability, const index_t offset = 0 ) noexcept;
  DenseMatrix( const index_t nrow, const index_t ncol, const index_t pitch,
               const DataType &data, const index_t offset = 0 ) noexcept;
  DenseMatrix( const DenseMatrix &other ) noexcept;
  DenseMatrix( DenseMatrix &&other ) noexcept;

  // Operators
  inline DenseMatrix& operator=( const DenseMatrix &other ) noexcept;
  inline DenseMatrix& operator=( DenseMatrix &&other ) noexcept;
  template <typename __Scalar, Layout __layout>
  friend std::ostream& operator<<( std::ostream &out, const DenseMatrix<__Scalar, __layout> &matrix );

  // Gets information
  inline index_t getPitch() const noexcept;
  inline bool isShrunk() const noexcept;

  // Gets iterator
  inline       IteratorType begin() noexcept;
  inline const IteratorType begin() const noexcept;
  inline       IteratorType end() noexcept;
  inline const IteratorType end() const noexcept;

  // Gets element
  inline       ScalarType& getElem( const index_t rowidx, const index_t colidx ) noexcept;
  inline const ScalarType& getElem( const index_t rowidx, const index_t colidx ) const noexcept;
  inline       ScalarType& operator()( const index_t rowidx, const index_t colidx ) noexcept;
  inline const ScalarType& operator()( const index_t rowidx, const index_t colidx ) const noexcept;

  // Transpose
  inline TransposeType transpose() noexcept;

  // Resizes
  inline void resize( const index_t nrow, const index_t ncol ) noexcept;

  // Gets matrix block
  inline       DenseMatrix getBlock( const IndexRange rowrange, const IndexRange colrange ) noexcept;
  inline const DenseMatrix getBlock( const IndexRange rowrange, const IndexRange colrange ) const noexcept;
  inline       DenseMatrix getCols( const IndexRange rowrange ) noexcept;
  inline const DenseMatrix getCols( const IndexRange rowrange ) const noexcept;
  inline       DenseMatrix getRows( const IndexRange colrange ) noexcept;
  inline const DenseMatrix getRows( const IndexRange colrange ) const noexcept;

  // Gets vector segment
  inline       VectorType getCol( const index_t colidx ) noexcept;
  inline const VectorType getCol( const index_t colidx ) const noexcept;
  inline       VectorType getColSegment( const index_t colidx, const IndexRange rowrange ) noexcept;
  inline const VectorType getColSegment( const index_t colidx, const IndexRange rowrange ) const noexcept;
  inline       VectorType getRow( const index_t rowidx ) noexcept;
  inline const VectorType getRow( const index_t rowidx ) const noexcept;
  inline       VectorType getRowSegment( const index_t rowidx, const IndexRange colrange ) noexcept;
  inline const VectorType getRowSegment( const index_t rowidx, const IndexRange colrange ) const noexcept;
  inline       VectorType getDiagonal( const index_t idx = 0 ) noexcept;
  inline const VectorType getDiagonal( const index_t idx = 0 ) const noexcept;
  inline       VectorType vectorize() noexcept;
  inline const VectorType vectorize() const noexcept;

 protected:

  // Gets internal information
  inline index_t getIndexInternal( const index_t rowidx, const index_t colidx ) const noexcept;
  inline index_t getColIncInternal() const noexcept;
  inline index_t getRowIncInternal() const noexcept;

};

}  // namespace isvd

#endif  // ISVD_MATRIX_DENSE_MATRIX_HPP_
