////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/matrix/dense_cube.hpp
/// @brief   The dense cube class.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_MATRIX_DENSE_CUBE_HPP_
#define ISVD_MATRIX_DENSE_CUBE_HPP_

#include <iostream>
#include <isvd/isvd.hpp>
#include <isvd/matrix/dense_cube_base.hpp>
#include <isvd/matrix/dense_matrix.hpp>
#include <isvd/matrix/dense_vector.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

template <typename _Scalar, Layout _layout> class DenseCube;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The internal namespace.
//
namespace internal {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense cube traits.
///
/// @tparam  _Scalar  The scalar type.
/// @tparam  _layout  The storage layout.
///
template <typename _Scalar, Layout _layout>
struct Traits<DenseCube<_Scalar, _layout>> {
  static const Layout layout = _layout;
  using ScalarType = _Scalar;
  using VectorType = DenseVector<_Scalar>;
  using MatrixType = DenseMatrix<_Scalar, _layout>;
};

}  // namespace internal

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense cube class.
///
/// @tparam  _Scalar  The scalar type.
/// @tparam  _layout  The storage layout.
///
template <typename _Scalar, Layout _layout = Layout::COLMAJOR>
class DenseCube : public internal::DenseCubeBase<DenseCube<_Scalar, _layout>> {

  friend internal::CubeBase<DenseCube<_Scalar, _layout>>;
  friend internal::DenseBase<DenseCube<_Scalar, _layout>>;
  friend internal::DenseCubeBase<DenseCube<_Scalar, _layout>>;

 protected:

  /// The number of rows.
  index_t nrow_;

  /// The number of columns.
  index_t ncol_;

  /// The number of pages.
  index_t npage_;

  /// The size of major dimension.
  index_t &dim1_ = isColMajor(_layout) ? nrow_ : ncol_;

  /// The size of minor dimension.
  index_t &dim2_ = isColMajor(_layout) ? ncol_ : nrow_;

  /// The leading dimension.
  const index_t pitch_;

  /// The page dimension.
  const index_t page_pitch_;

  /// The offset of starting position.
  const index_t offset_;

  /// The data storage
  DenseData<_Scalar> data_;

 public:

  // Constructors
  DenseCube() noexcept;
  DenseCube( const index_t nrow, const index_t ncol, const index_t npage ) noexcept;
  DenseCube( const index_t nrow, const index_t ncol, const index_t npage, const index_t pitch ) noexcept;
  DenseCube( const index_t nrow, const index_t ncol, const index_t npage,
             const index_t pitch, const index_t page_pitch ) noexcept;
  DenseCube( const index_t nrow, const index_t ncol, const index_t npage,
             const index_t pitch, const index_t page_pitch, _Scalar *value ) noexcept;
  DenseCube( const index_t nrow, const index_t ncol, const index_t npage, const index_t pitch, const index_t page_pitch,
             _Scalar *value, const index_t capability, const index_t offset = 0 ) noexcept;
  DenseCube( const index_t nrow, const index_t ncol, const index_t npage, const index_t pitch, const index_t page_pitch,
             const DenseData<_Scalar> &data, const index_t offset = 0 ) noexcept;

  // Destructor
  ~DenseCube() noexcept;

 protected:

  // Gets information
  inline Layout getLayoutImpl() const noexcept;
  inline index_t getNrowImpl() const noexcept;
  inline index_t getNcolImpl() const noexcept;
  inline index_t getNpageImpl() const noexcept;
  inline index_t getPitchImpl() const noexcept;
  inline index_t getPagePitchImpl() const noexcept;
  inline index_t getOffsetImpl() const noexcept;

  // Gets data storage
  inline DenseData<_Scalar>& getDataImpl() noexcept;
  inline const DenseData<_Scalar>& getDataImpl() const noexcept;

  // Gets element
  inline       _Scalar& getElementImpl( const index_t rowidx, const index_t colidx, const index_t pageidx ) noexcept;
  inline const _Scalar& getElementImpl( const index_t rowidx, const index_t colidx, const index_t pageidx ) const noexcept;

  // Resizes
  inline void resizeImpl( const index_t nrow, const index_t ncol, const index_t npage ) noexcept;

  // Gets cube block
  inline DenseCube getBlockImpl( const IndexRange rowrange, const IndexRange colrange, const IndexRange pagerange ) noexcept;

  // Gets matrix block
  inline DenseMatrix<_Scalar, _layout> getPageImpl( const index_t pageidx,
                                                    const IndexRange rowrange, const IndexRange colrange ) noexcept;

  // Gets vector segment
  inline DenseVector<_Scalar> getColImpl( const index_t colidx, const index_t pageidx, const IndexRange rowrange ) noexcept;
  inline DenseVector<_Scalar> getRowImpl( const index_t rowidx, const index_t pageidx, const IndexRange colrange ) noexcept;
  inline DenseVector<_Scalar> getTubeImpl( const index_t rowidx, const index_t colidx, const IndexRange pagerange ) noexcept;
  inline DenseVector<_Scalar> getDiagonalImpl( const index_t pageidx, const index_t idx ) noexcept;

  // Gets internal information
  inline index_t getIndexInternal( const index_t rowidx, const index_t colidx, const index_t pageidx ) const noexcept;
  inline index_t getColIncInternal() const noexcept;
  inline index_t getRowIncInternal() const noexcept;
  inline index_t getTubeIncInternal() const noexcept;

};

}  // namespace isvd

#endif  // ISVD_MATRIX_DENSE_CUBE_HPP_
