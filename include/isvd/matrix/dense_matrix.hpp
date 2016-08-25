////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/matrix/dense_matrix.hpp
/// @brief   The dense matrix class.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_MATRIX_DENSE_MATRIX_HPP_
#define ISVD_MATRIX_DENSE_MATRIX_HPP_

#include <iostream>
#include <memory>
#include <isvd/config.hpp>
#include <isvd/matrix/dense_matrix_base.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense matrix class.
///
/// @tparam  _Scalar  The scalar type of matrix.
/// @tparam  _layout  The storage layout of matrix.
///
//@{
template <typename _Scalar, Layout _layout = Layout::COLMAJOR>
class DenseMatrix : public impl::DenseMatrixBase<DenseMatrix<_Scalar, _layout>, _Scalar> {

  friend impl::MatrixBase<DenseMatrix<_Scalar, _layout>>;
  friend impl::DenseBase<DenseMatrix<_Scalar, _layout>, _Scalar>;
  friend impl::DenseMatrixBase<DenseMatrix<_Scalar, _layout>, _Scalar>;

 protected:

  /// The number of rows.
  const index_t nrow_;

  /// The number of columns.
  const index_t ncol_;

  /// The size of major dimension.
  const index_t &dim1_ = (_layout == Layout::COLMAJOR) ? nrow_ : ncol_;

  /// The size of minor dimension.
  const index_t &dim2_ = (_layout == Layout::COLMAJOR) ? ncol_ : nrow_;

  /// The leading dimension.
  const index_t pitch_;

  /// The offset of starting position.
  const index_t offset_;

  /// The length of data array.
  const index_t capability_;

  /// The data array.
  std::shared_ptr<_Scalar> value_;

 public:

  // Constructors
  DenseMatrix() noexcept;
  DenseMatrix( const index_t nrow, const index_t ncol ) noexcept;
  DenseMatrix( const index_t nrow, const index_t ncol, const index_t pitch ) noexcept;
  DenseMatrix( const index_t nrow, const index_t ncol, const index_t pitch, _Scalar *value ) noexcept;
  DenseMatrix( const index_t nrow, const index_t ncol, const index_t pitch, _Scalar *value,
               const index_t capability, const index_t offset = 0 ) noexcept;

  // Destructor
  ~DenseMatrix() noexcept;

 protected:

  // Constructors
  DenseMatrix( const DenseMatrix &other, const index_t nrow, const index_t ncol, const index_t offset ) noexcept;

  // Operators
  template <typename __Scalar, Layout __layout>
  friend std::ostream& operator<< ( std::ostream &out, const DenseMatrix<__Scalar, __layout> &matrix );

  // Gets matrix information
  inline Layout  getLayoutImpl() const noexcept;
  inline index_t getNrowImpl() const noexcept;
  inline index_t getNcolImpl() const noexcept;
  inline index_t getPitchImpl() const noexcept;
  inline index_t getSizeImpl() const noexcept;
  inline index_t getOffsetImpl() const noexcept;
  inline index_t getCapabilityImpl() const noexcept;

  // Gets data
  inline       _Scalar* getValueImpl() noexcept;
  inline const _Scalar* getValueImpl() const noexcept;
  inline       _Scalar& getValueImpl( const index_t rowidx, const index_t colidx ) noexcept;
  inline const _Scalar& getValueImpl( const index_t rowidx, const index_t colidx ) const noexcept;

  // Gets block
  inline DenseMatrix getBlockImpl( const index_t rowidx, const index_t colidx,
                                   const index_t nrow, const index_t ncol ) noexcept;
  inline DenseMatrix getRowsImpl( const index_t rowidx, const index_t nrow ) noexcept;
  inline DenseMatrix getColsImpl( const index_t colidx, const index_t ncol ) noexcept;

};

}  // namespace isvd

#endif  // ISVD_MATRIX_DENSE_MATRIX_HPP_
