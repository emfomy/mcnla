////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/matrix/dense/dense_matrix.hpp
/// @brief   The dense matrix class.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_MATRIX_DENSE_DENSE_MATRIX_HPP_
#define ISVD_MATRIX_DENSE_DENSE_MATRIX_HPP_

#include <isvd/isvd.hpp>
#include <iostream>
#include <utility>
#include <isvd/matrix/base/container_base.hpp>
#include <isvd/matrix/base/matrix_base.hpp>
#include <isvd/matrix/dense/dense_base.hpp>
#include <isvd/matrix/dense/dense_vector.hpp>
#include <isvd/matrix/dense/dense_matrix_iterator.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Scalar, Layout _layout> class DenseMatrix;
template <typename _Scalar> class DenseVector;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The detail namespace.
//
namespace detail {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense matrix traits.
///
/// @tparam  _Scalar  The scalar type.
/// @tparam  _layout  The storage layout.
///
template <typename _Scalar, Layout _layout>
struct Traits<DenseMatrix<_Scalar, _layout>> {
  static constexpr index_t ndim = 2;
  static constexpr Layout layout = _layout;

  using ScalarType        = _Scalar;
  using RealScalarType    = typename detail::ScalarTraits<_Scalar>::RealType;

  using VectorType        = DenseVector<ScalarType>;
  using RealVectorType    = DenseVector<RealScalarType>;
  using MatrixType        = DenseMatrix<ScalarType, _layout>;
  using RealMatrixType    = DenseMatrix<RealScalarType, _layout>;
  using TransposeType     = DenseMatrix<ScalarType, changeLayout(_layout)>;
  using RealTransposeType = DenseMatrix<RealScalarType, changeLayout(_layout)>;

  using IteratorType      = DenseMatrixIterator<ScalarType, _layout>;
  using ConstIteratorType = DenseMatrixConstIterator<ScalarType, _layout>;
};

}  // namespace detail

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense matrix class.
///
/// @tparam  _Scalar  The scalar type.
/// @tparam  _layout  The storage layout.
///
template <typename _Scalar, Layout _layout = Layout::COLMAJOR>
class DenseMatrix
  : public ContainerBase<DenseMatrix<_Scalar, _layout>>,
    public MatrixBase<DenseMatrix<_Scalar, _layout>>,
    public DenseBase<DenseMatrix<_Scalar, _layout>> {

 public:

  static constexpr index_t ndim = 2;
  static constexpr Layout layout = _layout;

  using ScalarType        = _Scalar;
  using RealScalarType    = typename detail::ScalarTraits<_Scalar>::RealType;
  using ValuePtrType      = std::shared_ptr<std::valarray<ScalarType>>;

  using VectorType        = DenseVector<ScalarType>;
  using RealVectorType    = DenseVector<RealScalarType>;
  using MatrixType        = DenseMatrix<ScalarType, _layout>;
  using RealMatrixType    = DenseMatrix<RealScalarType, _layout>;
  using TransposeType     = DenseMatrix<ScalarType, changeLayout(_layout)>;
  using RealTransposeType = DenseMatrix<RealScalarType, changeLayout(_layout)>;

  using DataType          = DenseData<ScalarType>;

  using IteratorType      = DenseMatrixIterator<ScalarType, _layout>;
  using ConstIteratorType = DenseMatrixConstIterator<ScalarType, _layout>;

 private:

  using MatrixBaseType    = MatrixBase<DenseMatrix<_Scalar, _layout>>;
  using DenseBaseType     = DenseBase<DenseMatrix<_Scalar, _layout>>;

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
  inline DenseMatrix() noexcept;
  inline DenseMatrix( const index_t nrow, const index_t ncol ) noexcept;
  inline DenseMatrix( const std::pair<index_t, index_t> sizes ) noexcept;
  inline DenseMatrix( const index_t nrow, const index_t ncol, const index_t pitch ) noexcept;
  inline DenseMatrix( const std::pair<index_t, index_t> sizes, const index_t pitch ) noexcept;
  inline DenseMatrix( const index_t nrow, const index_t ncol, const index_t pitch,
                      const index_t capability, const index_t offset = 0 ) noexcept;
  inline DenseMatrix( const std::pair<index_t, index_t> sizes, const index_t pitch,
                      const index_t capability, const index_t offset = 0 ) noexcept;
  inline DenseMatrix( const index_t nrow, const index_t ncol, const index_t pitch,
                      const ValuePtrType &value, const index_t offset = 0 ) noexcept;
  inline DenseMatrix( const index_t nrow, const index_t ncol, const index_t pitch,
                      const DataType &data, const index_t offset = 0 ) noexcept;
  inline DenseMatrix( const DenseMatrix &other ) noexcept;
  inline DenseMatrix( DenseMatrix &&other ) noexcept;

  // Operators
  inline DenseMatrix& operator=( const DenseMatrix &other ) noexcept;
  inline DenseMatrix& operator=( DenseMatrix &&other ) noexcept;
  template <typename __Scalar, Layout __layout>
  friend inline std::ostream& operator<<( std::ostream &out, const DenseMatrix<__Scalar, __layout> &matrix );

  // Gets information
  inline index_t getPitch() const noexcept;
  inline bool isShrunk() const noexcept;

  // Gets element
  inline       ScalarType& getElem( const index_t rowidx, const index_t colidx ) noexcept;
  inline const ScalarType& getElem( const index_t rowidx, const index_t colidx ) const noexcept;
  inline       ScalarType& operator()( const index_t rowidx, const index_t colidx ) noexcept;
  inline const ScalarType& operator()( const index_t rowidx, const index_t colidx ) const noexcept;

  // Gets internal position
  inline index_t getPos( const index_t rowidx, const index_t colidx ) const noexcept;

  // Transpose
  inline TransposeType transpose() noexcept;

  // Finds the iterator
  inline IteratorType      find( const index_t rowidx, const index_t colidx ) noexcept;
  inline ConstIteratorType find( const index_t rowidx, const index_t colidx ) const noexcept;
  inline ConstIteratorType cfind( const index_t rowidx, const index_t colidx ) const noexcept;

  // Resizes
  inline void resize( const index_t nrow, const index_t ncol ) noexcept;

  // Gets matrix block
  inline       MatrixType getBlock( const IdxRange rowrange, const IdxRange colrange ) noexcept;
  inline const MatrixType getBlock( const IdxRange rowrange, const IdxRange colrange ) const noexcept;
  inline       MatrixType getCols( const IdxRange rowrange ) noexcept;
  inline const MatrixType getCols( const IdxRange rowrange ) const noexcept;
  inline       MatrixType getRows( const IdxRange colrange ) noexcept;
  inline const MatrixType getRows( const IdxRange colrange ) const noexcept;

  // Gets vector segment
  inline       VectorType getCol( const index_t colidx ) noexcept;
  inline const VectorType getCol( const index_t colidx ) const noexcept;
  inline       VectorType getColSegment( const index_t colidx, const IdxRange rowrange ) noexcept;
  inline const VectorType getColSegment( const index_t colidx, const IdxRange rowrange ) const noexcept;
  inline       VectorType getRow( const index_t rowidx ) noexcept;
  inline const VectorType getRow( const index_t rowidx ) const noexcept;
  inline       VectorType getRowSegment( const index_t rowidx, const IdxRange colrange ) noexcept;
  inline const VectorType getRowSegment( const index_t rowidx, const IdxRange colrange ) const noexcept;
  inline       VectorType getDiagonal( const index_t idx = 0 ) noexcept;
  inline const VectorType getDiagonal( const index_t idx = 0 ) const noexcept;
  inline       VectorType vectorize() noexcept;
  inline const VectorType vectorize() const noexcept;

 protected:

  // Gets stride
  inline index_t getColInc() const noexcept;
  inline index_t getRowInc() const noexcept;

};

}  // namespace isvd

#endif  // ISVD_MATRIX_DENSE_DENSE_MATRIX_HPP_
