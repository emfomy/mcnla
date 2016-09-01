////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/matrix/dense_matrix.hpp
/// @brief   The dense matrix class.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_MATRIX_DENSE_MATRIX_HPP_
#define ISVD_MATRIX_DENSE_MATRIX_HPP_

#include <iostream>
#include <isvd/isvd.hpp>
#include <isvd/matrix/matrix_base.hpp>
#include <isvd/matrix/dense_base.hpp>
#include <isvd/matrix/dense_vector.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

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
  using RealScalarType = typename isvd::internal::ScalarTraits<_Scalar>::RealType;
  using VectorType     = DenseVector<ScalarType>;
  using RealVectorType = DenseVector<RealScalarType>;
  using TransposeType  = DenseMatrix<_Scalar, changeLayout(_layout)>;
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
  using RealScalarType = typename isvd::internal::ScalarTraits<_Scalar>::RealType;
  using VectorType     = DenseVector<ScalarType>;
  using RealVectorType = DenseVector<RealScalarType>;
  using TransposeType  = DenseMatrix<_Scalar, changeLayout(_layout)>;

 private:

  using MatrixBaseType = internal::MatrixBase<DenseMatrix<_Scalar, _layout>>;
  using DenseBaseType  = internal::DenseBase<DenseMatrix<_Scalar, _layout>>;

 protected:

  /// The leading dimension.
  index_t pitch_;

  using MatrixBaseType::nrow_;
  using MatrixBaseType::ncol_;
  using MatrixBaseType::dim1_;
  using MatrixBaseType::dim2_;
  using DenseBaseType::offset_;
  using DenseBaseType::data_;

 public:

  // Constructors
  DenseMatrix() noexcept;
  DenseMatrix( const index_t nrow, const index_t ncol ) noexcept;
  DenseMatrix( const index_t nrow, const index_t ncol, const index_t pitch ) noexcept;
  DenseMatrix( const index_t nrow, const index_t ncol, const index_t pitch, std::shared_ptr<_Scalar> value ) noexcept;
  DenseMatrix( const index_t nrow, const index_t ncol, const index_t pitch, std::shared_ptr<_Scalar> value,
               const index_t capability, const index_t offset = 0 ) noexcept;
  DenseMatrix( const index_t nrow, const index_t ncol, const index_t pitch,
               const DenseData<_Scalar> &data, const index_t offset = 0 ) noexcept;
  DenseMatrix( const DenseMatrix &other ) noexcept;
  DenseMatrix( DenseMatrix &&other ) noexcept;

  // Operators
  inline DenseMatrix& operator=( const DenseMatrix &other ) noexcept;
  inline DenseMatrix& operator=( DenseMatrix &&other ) noexcept;
  template <typename __Scalar, Layout __layout>
  friend std::ostream& operator<<( std::ostream &out, const DenseMatrix<__Scalar, __layout> &matrix );

  // Gets information
  inline index_t getPitch() const noexcept;

  // Gets element
  inline       _Scalar& getElement( const index_t rowidx, const index_t colidx ) noexcept;
  inline const _Scalar& getElement( const index_t rowidx, const index_t colidx ) const noexcept;
  inline       _Scalar& operator()( const index_t rowidx, const index_t colidx ) noexcept;
  inline const _Scalar& operator()( const index_t rowidx, const index_t colidx ) const noexcept;

  // Transpose
  inline DenseMatrix<_Scalar, changeLayout(_layout)> transpose() noexcept;

  // Resizes
  inline void resize( const index_t nrow, const index_t ncol ) noexcept;

  // Gets matrix block
  inline DenseMatrix<_Scalar, _layout> getBlock( const IndexRange rowrange, const IndexRange colrange ) noexcept;
  inline DenseMatrix<_Scalar, _layout> getCols( const IndexRange rowrange ) noexcept;
  inline DenseMatrix<_Scalar, _layout> getRows( const IndexRange colrange ) noexcept;

  // Gets vector segment
  inline DenseVector<_Scalar> getCol( const index_t colidx ) noexcept;
  inline DenseVector<_Scalar> getColSegment( const index_t colidx, const IndexRange rowrange ) noexcept;
  inline DenseVector<_Scalar> getRow( const index_t rowidx ) noexcept;
  inline DenseVector<_Scalar> getRowSegment( const index_t rowidx, const IndexRange colrange ) noexcept;
  inline DenseVector<_Scalar> getDiagonal( const index_t idx = 0 ) noexcept;
  inline DenseVector<_Scalar> vectorize() noexcept;

 protected:

  // Gets internal information
  inline index_t getIndexInternal( const index_t rowidx, const index_t colidx ) const noexcept;
  inline index_t getColIncInternal() const noexcept;
  inline index_t getRowIncInternal() const noexcept;

};

}  // namespace isvd

#endif  // ISVD_MATRIX_DENSE_MATRIX_HPP_
