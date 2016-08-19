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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense matrix data storage.
///
/// @tparam _Type   The type of numeric value in matrix.
/// @tparam _layout The storage layout of matrix.
///
//@{
template <typename _Type, Layout _layout>
class DenseMatrixData : public MatrixData<_Type> {

 protected:

  /// The size of major dimension.
  index_t dim1_;

  /// The size of minor dimension.
  index_t dim2_;

  /// The leading dimension.
  index_t pitch_;

  /// The data array.
  _Type  *value_;

 public:

  // Constructors
  DenseMatrixData() noexcept;
  DenseMatrixData( const index_t nrow, const index_t ncol ) noexcept;
  DenseMatrixData( const index_t nrow, const index_t ncol, const index_t pitch ) noexcept;
  DenseMatrixData( const index_t nrow, const index_t ncol, const index_t pitch, _Type *&value ) noexcept;

  // Destructor
  ~DenseMatrixData() noexcept;

  // Gets data
  Layout  getLayout() const noexcept;
  index_t getNrow() const noexcept;
  index_t getNcol() const noexcept;
  index_t getPitch() const noexcept;
  _Type*  getValue() const noexcept;

 protected:

  // Gets data
  static index_t getNcol( const DenseMatrixData<_Type, Layout::COLMAJOR> &data ) noexcept;
  static index_t getNcol( const DenseMatrixData<_Type, Layout::ROWMAJOR> &data ) noexcept;
  static index_t getNrow( const DenseMatrixData<_Type, Layout::COLMAJOR> &data ) noexcept;
  static index_t getNrow( const DenseMatrixData<_Type, Layout::ROWMAJOR> &data ) noexcept;

  // Sets data
  static void setNcol( DenseMatrixData<_Type, Layout::COLMAJOR> &data, const index_t ncol ) noexcept;
  static void setNcol( DenseMatrixData<_Type, Layout::ROWMAJOR> &data, const index_t ncol ) noexcept;
  static void setNrow( DenseMatrixData<_Type, Layout::COLMAJOR> &data, const index_t nrow ) noexcept;
  static void setNrow( DenseMatrixData<_Type, Layout::ROWMAJOR> &data, const index_t nrow ) noexcept;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense matrix base.
///
/// @tparam _Data  The storage data type.
/// @tparam _Type  The type of numeric value in matrix.
///
template <class _Data>
class DenseMatrixBase : MatrixBase<_Data> {

 private:

  /// Type alias
  using ValueType = typename _Data::ValueType;

 public:

  // Constructors
  DenseMatrixBase() noexcept;
  DenseMatrixBase( const index_t nrow, const index_t ncol ) noexcept;
  DenseMatrixBase( const index_t nrow, const index_t ncol, const index_t pitch ) noexcept;
  DenseMatrixBase( const index_t nrow, const index_t ncol, const index_t pitch, ValueType *&value ) noexcept;

  // Gets data
  Layout  getLayout() const noexcept;
  index_t getNrow() const noexcept;
  index_t getNcol() const noexcept;
  index_t getPitch() const noexcept;
  ValueType* getValue() const noexcept;

};

}  // namespace impl

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense matrix.
///
/// @tparam _Type  The type of numeric value in matrix.
/// @tparam _layout The storage layout of matrix.
///
template <typename _Type, Layout _layout = Layout::COLMAJOR>
class DenseMatrix : public impl::DenseMatrixBase<impl::DenseMatrixData<_Type, _layout>> {
  using impl::DenseMatrixBase<impl::DenseMatrixData<_Type, _layout>>::DenseMatrixBase;
};

}  // namespace isvd

#endif  // ISVD_MATRIX_DENSE_MATRIX_HPP_
