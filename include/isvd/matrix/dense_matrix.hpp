////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/matrix/dense_matrix.hpp
/// @brief   The dense matrix class.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_MATRIX_DENSE_MATRIX_HPP_
#define ISVD_MATRIX_DENSE_MATRIX_HPP_

#include <isvd/config.hpp>
#include <isvd/matrix/matrix.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The implementation namespace.
//
namespace impl {

template <typename _Scalar, Layout _layout> class DenseBlockData;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense matrix data storage.
///
/// @tparam _Scalar    The scalar type of matrix.
/// @tparam _layout    The storage layout of matrix.
///
//@{
template <typename _Scalar, Layout _layout>
class DenseMatrixData : public MatrixData<_Scalar> {

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
  index_t pitch_;

  /// The data array.
  _Scalar *value_;

 public:

  // Constructors
  DenseMatrixData() noexcept;
  DenseMatrixData( const index_t nrow, const index_t ncol ) noexcept;
  DenseMatrixData( const index_t nrow, const index_t ncol, const index_t pitch ) noexcept;
  DenseMatrixData( const index_t nrow, const index_t ncol, const index_t pitch, _Scalar *value ) noexcept;

  // Destructor
  ~DenseMatrixData() noexcept;

  // Gets data
  Layout  getLayout() const noexcept;
  index_t getNrow() const noexcept;
  index_t getNcol() const noexcept;
  index_t getPitch() const noexcept;
  _Scalar*       getValue() noexcept;
  const _Scalar* getValue() const noexcept;
  _Scalar&       getValue( const index_t rowid, const index_t colid ) noexcept;
  const _Scalar& getValue( const index_t rowid, const index_t colid ) const noexcept;

  // Gets block
  DenseBlockData<_Scalar, _layout>* getBlock() noexcept;
  DenseBlockData<_Scalar, _layout>* getBlock( const index_t rowid, const index_t colid,
                                              const index_t nrow, const index_t ncol ) noexcept;
  DenseBlockData<_Scalar, _layout>* getRows( const index_t rowid, const index_t nrow ) noexcept;
  DenseBlockData<_Scalar, _layout>* getCols( const index_t colid, const index_t ncol ) noexcept;

};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense matrix base.
///
/// @tparam _Data    The storage data type.
/// @tparam _Scalar  The type of numeric value in matrix.
///
template <class _Data>
class DenseMatrixBase : public MatrixBase<_Data> {

 private:

  /// Type alias
  using ScalarType = typename _Data::ScalarType;

 public:

  // Constructors
  DenseMatrixBase() noexcept;
  DenseMatrixBase( const index_t nrow, const index_t ncol ) noexcept;
  DenseMatrixBase( const index_t nrow, const index_t ncol, const index_t pitch ) noexcept;
  DenseMatrixBase( const index_t nrow, const index_t ncol, const index_t pitch, ScalarType *value ) noexcept;

  // Gets data
  Layout  getLayout() const noexcept;
  index_t getNrow() const noexcept;
  index_t getNcol() const noexcept;
  index_t getPitch() const noexcept;
  ScalarType*       getValue() noexcept;
  const ScalarType* getValue() const noexcept;
  ScalarType&       getValue( const index_t rowid, const index_t colid ) noexcept;
  const ScalarType& getValue( const index_t rowid, const index_t colid ) const noexcept;

};

}  // namespace impl

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense matrix.
///
/// @tparam _Scalar  The type of numeric value in matrix.
/// @tparam _layout  The storage layout of matrix.
///
template <typename _Scalar, Layout _layout = Layout::COLMAJOR>
class DenseMatrix : public impl::DenseMatrixBase<impl::DenseMatrixData<_Scalar, _layout>> {
  using impl::DenseMatrixBase<impl::DenseMatrixData<_Scalar, _layout>>::DenseMatrixBase;
};

}  // namespace isvd

#endif  // ISVD_MATRIX_DENSE_MATRIX_HPP_
