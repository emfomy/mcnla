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
#include <isvd/matrix/cube_base.hpp>
#include <isvd/matrix/dense_base.hpp>
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
  using ScalarType     = _Scalar;
  using RealScalarType = typename isvd::internal::ScalarTraits<_Scalar>::RealType;
  using VectorType     = DenseVector<ScalarType>;
  using RealVectorType = DenseVector<RealScalarType>;
  using MatrixType     = DenseMatrix<ScalarType, _layout>;
};

}  // namespace internal

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense cube class.
///
/// @tparam  _Scalar  The scalar type.
/// @tparam  _layout  The storage layout.
///
template <typename _Scalar, Layout _layout = Layout::COLMAJOR>
class DenseCube
  : public internal::CubeBase<DenseCube<_Scalar, _layout>>,
    public internal::DenseBase<DenseCube<_Scalar, _layout>>{

 public:

  static const Layout layout = _layout;
  using ScalarType     = _Scalar;
  using RealScalarType = typename isvd::internal::ScalarTraits<_Scalar>::RealType;
  using VectorType     = DenseVector<ScalarType>;
  using RealVectorType = DenseVector<RealScalarType>;
  using MatrixType     = DenseMatrix<ScalarType, _layout>;

 private:

  using CubeBaseType  = internal::CubeBase<DenseCube<_Scalar, _layout>>;
  using DenseBaseType = internal::DenseBase<DenseCube<_Scalar, _layout>>;

 protected:

  /// The leading dimension.
  index_t pitch1_;

  /// The second dimension.
  index_t pitch2_;

  using CubeBaseType::nrow_;
  using CubeBaseType::ncol_;
  using CubeBaseType::npage_;
  using CubeBaseType::dim1_;
  using CubeBaseType::dim2_;
  using DenseBaseType::offset_;
  using DenseBaseType::data_;

 public:

  // Constructors
  DenseCube() noexcept;
  DenseCube( const index_t nrow, const index_t ncol, const index_t npage ) noexcept;
  DenseCube( const std::tuple<index_t, index_t, index_t> sizes ) noexcept;
  DenseCube( const index_t nrow, const index_t ncol, const index_t npage, const index_t pitch1 ) noexcept;
  DenseCube( const index_t nrow, const index_t ncol, const index_t npage,
             const index_t pitch1, const index_t pitch2 ) noexcept;
  DenseCube( const index_t nrow, const index_t ncol, const index_t npage,
             const index_t pitch1, const index_t pitch2, std::shared_ptr<_Scalar> value ) noexcept;
  DenseCube( const index_t nrow, const index_t ncol, const index_t npage,
             const index_t pitch1, const index_t pitch2, std::shared_ptr<_Scalar> value,
             const index_t capability, const index_t offset = 0 ) noexcept;
  DenseCube( const index_t nrow, const index_t ncol, const index_t npage,
             const index_t pitch1, const index_t pitch2, const DenseData<_Scalar> &data, const index_t offset = 0 ) noexcept;
  DenseCube( const DenseCube &other ) noexcept;
  DenseCube( DenseCube &&other ) noexcept;

  // Operators
  inline DenseCube& operator=( const DenseCube &other ) noexcept;
  inline DenseCube& operator=( DenseCube &&other ) noexcept;

  // Gets information
  inline index_t getPitch1() const noexcept;
  inline index_t getPitch2() const noexcept;

  // Gets element
  inline       _Scalar& getElement( const index_t rowidx, const index_t colidx, const index_t pageidx ) noexcept;
  inline const _Scalar& getElement( const index_t rowidx, const index_t colidx, const index_t pageidx ) const noexcept;
  inline       _Scalar& operator()( const index_t rowidx, const index_t colidx, const index_t pageidx ) noexcept;
  inline const _Scalar& operator()( const index_t rowidx, const index_t colidx, const index_t pageidx ) const noexcept;

  // Resizes
  inline void resize( const index_t nrow, const index_t ncol, const index_t npage ) noexcept;

  // Gets cube block
  inline       DenseCube<_Scalar, _layout> getCube( const IndexRange rowrange, const IndexRange colrange,
                                                    const IndexRange pagerange ) noexcept;
  inline const DenseCube<_Scalar, _layout> getCube( const IndexRange rowrange, const IndexRange colrange,
                                                    const IndexRange pagerange ) const noexcept;
  inline       DenseCube<_Scalar, _layout> getTubes( const IndexRange rowrange, const IndexRange colrange ) noexcept;
  inline const DenseCube<_Scalar, _layout> getTubes( const IndexRange rowrange, const IndexRange colrange ) const noexcept;
  inline       DenseCube<_Scalar, _layout> getPages( const IndexRange pagerange ) noexcept;
  inline const DenseCube<_Scalar, _layout> getPages( const IndexRange pagerange ) const noexcept;
  inline       DenseCube<_Scalar, _layout> getColPages( const IndexRange rowrange ) noexcept;
  inline const DenseCube<_Scalar, _layout> getColPages( const IndexRange rowrange ) const noexcept;
  inline       DenseCube<_Scalar, _layout> getRowPages( const IndexRange colrange ) noexcept;
  inline const DenseCube<_Scalar, _layout> getRowPages( const IndexRange colrange ) const noexcept;

  // Gets matrix block
  inline       DenseMatrix<_Scalar, _layout> getPage( const index_t pageidx ) noexcept;
  inline const DenseMatrix<_Scalar, _layout> getPage( const index_t pageidx ) const noexcept;
  inline       DenseMatrix<_Scalar, _layout> getCols( const index_t pageidx, const IndexRange rowrange ) noexcept;
  inline const DenseMatrix<_Scalar, _layout> getCols( const index_t pageidx, const IndexRange rowrange ) const noexcept;
  inline       DenseMatrix<_Scalar, _layout> getRows( const index_t pageidx, const IndexRange colrange ) noexcept;
  inline const DenseMatrix<_Scalar, _layout> getRows( const index_t pageidx, const IndexRange colrange ) const noexcept;
  inline       DenseMatrix<_Scalar, _layout> getBlock( const index_t pageidx, const IndexRange rowrange,
                                                                              const IndexRange colrange ) noexcept;
  inline const DenseMatrix<_Scalar, _layout> getBlock( const index_t pageidx, const IndexRange rowrange,
                                                                              const IndexRange colrange ) const noexcept;
  inline       DenseMatrix<_Scalar, _layout> unfold() noexcept;
  inline const DenseMatrix<_Scalar, _layout> unfold() const noexcept;

  // Gets vector segment
  inline       DenseVector<_Scalar> getCol( const index_t colidx, const index_t pageidx ) noexcept;
  inline const DenseVector<_Scalar> getCol( const index_t colidx, const index_t pageidx ) const noexcept;
  inline       DenseVector<_Scalar> getColSegment( const index_t colidx, const index_t pageidx,
                                                   const IndexRange rowrange ) noexcept;
  inline const DenseVector<_Scalar> getColSegment( const index_t colidx, const index_t pageidx,
                                                   const IndexRange rowrange ) const noexcept;
  inline       DenseVector<_Scalar> getRow( const index_t rowidx, const index_t pageidx ) noexcept;
  inline const DenseVector<_Scalar> getRow( const index_t rowidx, const index_t pageidx ) const noexcept;
  inline       DenseVector<_Scalar> getRowSegment( const index_t rowidx, const index_t pageidx,
                                                   const IndexRange colrange ) noexcept;
  inline const DenseVector<_Scalar> getRowSegment( const index_t rowidx, const index_t pageidx,
                                                   const IndexRange colrange ) const noexcept;
  inline       DenseVector<_Scalar> getTube( const index_t rowidx, const index_t colidx ) noexcept;
  inline const DenseVector<_Scalar> getTube( const index_t rowidx, const index_t colidx ) const noexcept;
  inline       DenseVector<_Scalar> getTubeSegment( const index_t rowidx, const index_t colidx,
                                                    const IndexRange pagerange ) noexcept;
  inline const DenseVector<_Scalar> getTubeSegment( const index_t rowidx, const index_t colidx,
                                                    const IndexRange pagerange ) const noexcept;
  inline       DenseVector<_Scalar> getDiagonal( const index_t pageidx, const index_t idx ) noexcept;
  inline const DenseVector<_Scalar> getDiagonal( const index_t pageidx, const index_t idx ) const noexcept;
  inline DenseVector<_Scalar> vectorize() noexcept;
  inline const DenseVector<_Scalar> vectorize() const noexcept;

 protected:

  // Gets internal information
  inline index_t getIndexInternal( const index_t rowidx, const index_t colidx, const index_t pageidx ) const noexcept;
  inline index_t getColIncInternal() const noexcept;
  inline index_t getRowIncInternal() const noexcept;
  inline index_t getTubeIncInternal() const noexcept;

};

}  // namespace isvd

#endif  // ISVD_MATRIX_DENSE_CUBE_HPP_
