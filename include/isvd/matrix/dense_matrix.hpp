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
#include <isvd/matrix/dense_matrix_base.hpp>
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
/// @tparam  _Scalar  The scalar type of matrix.
/// @tparam  _layout  The storage layout of matrix.
///
template <typename _Scalar, Layout _layout>
struct Traits<DenseMatrix<_Scalar, _layout>> {
  using ScalarType = _Scalar;
  using VectorType = DenseVector<_Scalar>;
};

}  // namespace internal

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense matrix class.
///
/// @tparam  _Scalar  The scalar type.
/// @tparam  _layout  The storage layout.
///
template <typename _Scalar, Layout _layout = Layout::COLMAJOR>
class DenseMatrix : public internal::DenseMatrixBase<DenseMatrix<_Scalar, _layout>> {

  friend internal::MatrixBase<DenseMatrix<_Scalar, _layout>>;
  friend internal::DenseBase<DenseMatrix<_Scalar, _layout>>;
  friend internal::DenseMatrixBase<DenseMatrix<_Scalar, _layout>>;

 protected:

  /// The number of rows.
  index_t nrow_;

  /// The number of columns.
  index_t ncol_;

  /// The size of major dimension.
  index_t &dim1_ = (_layout == Layout::COLMAJOR) ? nrow_ : ncol_;

  /// The size of minor dimension.
  index_t &dim2_ = (_layout == Layout::COLMAJOR) ? ncol_ : nrow_;

  /// The leading dimension.
  const index_t pitch_;

  /// The offset of starting position.
  const index_t offset_;

  /// The data storage
  DenseData<_Scalar> data_;

 public:

  // Constructors
  DenseMatrix() noexcept;
  DenseMatrix( const index_t nrow, const index_t ncol ) noexcept;
  DenseMatrix( const index_t nrow, const index_t ncol, const index_t pitch ) noexcept;
  DenseMatrix( const index_t nrow, const index_t ncol, const index_t pitch, _Scalar *value ) noexcept;
  DenseMatrix( const index_t nrow, const index_t ncol, const index_t pitch, _Scalar *value,
               const index_t capability, const index_t offset = 0 ) noexcept;
  DenseMatrix( const index_t nrow, const index_t ncol, const index_t pitch,
               const DenseData<_Scalar> &data, const index_t offset = 0 ) noexcept;

  // Destructor
  ~DenseMatrix() noexcept;

 protected:

  // Operators
  template <typename __Scalar, Layout __layout>
  friend std::ostream& operator<<( std::ostream &out, const DenseMatrix<__Scalar, __layout> &matrix );

  // Gets information
  inline Layout  getLayoutImpl() const noexcept;
  inline index_t getNrowImpl() const noexcept;
  inline index_t getNcolImpl() const noexcept;
  inline index_t getPitchImpl() const noexcept;
  inline index_t getOffsetImpl() const noexcept;

  // Gets data storage
  inline DenseData<_Scalar>& getDataImpl() noexcept;
  inline const DenseData<_Scalar>& getDataImpl() const noexcept;

  // Gets element
  inline       _Scalar& getElementImpl( const index_t rowidx, const index_t colidx ) noexcept;
  inline const _Scalar& getElementImpl( const index_t rowidx, const index_t colidx ) const noexcept;

  // Resizes
  inline void resizeImpl( const index_t nrow, const index_t ncol ) noexcept;

  // Gets matrix block
  inline DenseMatrix getBlockImpl( const IndexRange rowrange, const IndexRange colrange ) noexcept;

  // Gets vector segment
  inline DenseVector<_Scalar> getColImpl( const index_t colidx, const IndexRange rowrange ) noexcept;
  inline DenseVector<_Scalar> getRowImpl( const index_t rowidx, const IndexRange colrange ) noexcept;
  inline DenseVector<_Scalar> getDiagonalImpl( const index_t idx ) noexcept;

  // Gets internal information
  inline index_t getIndexInternal( const index_t rowidx, const index_t colidx ) const noexcept;
  inline index_t getColIncInternal() const noexcept;
  inline index_t getRowIncInternal() const noexcept;

};

}  // namespace isvd

#endif  // ISVD_MATRIX_DENSE_MATRIX_HPP_
