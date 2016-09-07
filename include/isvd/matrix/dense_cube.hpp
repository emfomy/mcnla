////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/matrix/dense_cube.hpp
/// @brief   The dense cube class.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_MATRIX_DENSE_CUBE_HPP_
#define ISVD_MATRIX_DENSE_CUBE_HPP_

#include <iostream>
#include <utility>
#include <tuple>
#include <isvd/isvd.hpp>
#include <isvd/matrix/cube_base.hpp>
#include <isvd/matrix/dense_base.hpp>
#include <isvd/matrix/dense_vector.hpp>
#include <isvd/matrix/dense_matrix.hpp>
#include <isvd/matrix/dense_cube_iterator.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

template <typename _Scalar> class DenseVector;
template <typename _Scalar, Layout _layout> class DenseMatrix;
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
  using RealScalarType = typename internal::ScalarTraits<_Scalar>::RealType;
  using VectorType     = DenseVector<ScalarType>;
  using RealVectorType = DenseVector<RealScalarType>;
  using MatrixType     = DenseMatrix<ScalarType, _layout>;
  using TransposeType  = DenseCube<ScalarType, changeLayout(_layout)>;
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
  using RealScalarType = typename internal::ScalarTraits<_Scalar>::RealType;

  using VectorType     = DenseVector<ScalarType>;
  using RealVectorType = DenseVector<RealScalarType>;
  using MatrixType     = DenseMatrix<ScalarType, _layout>;
  using TransposeType  = DenseCube<ScalarType, changeLayout(_layout)>;

  using DataType       = DenseData<ScalarType>;
  using IteratorType   = internal::DenseCubeIterator<ScalarType, _layout>;

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
  using CubeBaseType::size1_;
  using CubeBaseType::size2_;
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
  DenseCube( const std::tuple<index_t, index_t, index_t> sizes, const std::pair<index_t, index_t> pitches ) noexcept;
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
  inline std::pair<index_t, index_t> getPitches() const noexcept;
  inline bool isShrunk() const noexcept;

  // Gets iterator
  inline       IteratorType begin() noexcept;
  inline const IteratorType begin() const noexcept;
  inline       IteratorType end() noexcept;
  inline const IteratorType end() const noexcept;

  // Gets element
  inline       _Scalar& getElem( const index_t rowidx, const index_t colidx, const index_t pageidx ) noexcept;
  inline const _Scalar& getElem( const index_t rowidx, const index_t colidx, const index_t pageidx ) const noexcept;
  inline       _Scalar& operator()( const index_t rowidx, const index_t colidx, const index_t pageidx ) noexcept;
  inline const _Scalar& operator()( const index_t rowidx, const index_t colidx, const index_t pageidx ) const noexcept;

  // Transpose
  inline TransposeType transpose() noexcept;

  // Resizes
  inline void resize( const index_t nrow, const index_t ncol, const index_t npage ) noexcept;

  // Gets cube block
  inline       DenseCube getCube( const IndexRange rowrange, const IndexRange colrange,
                                                    const IndexRange pagerange ) noexcept;
  inline const DenseCube getCube( const IndexRange rowrange, const IndexRange colrange,
                                                    const IndexRange pagerange ) const noexcept;
  inline       DenseCube getTubes( const IndexRange rowrange, const IndexRange colrange ) noexcept;
  inline const DenseCube getTubes( const IndexRange rowrange, const IndexRange colrange ) const noexcept;
  inline       DenseCube getPages( const IndexRange pagerange ) noexcept;
  inline const DenseCube getPages( const IndexRange pagerange ) const noexcept;
  inline       DenseCube getColPages( const IndexRange rowrange ) noexcept;
  inline const DenseCube getColPages( const IndexRange rowrange ) const noexcept;
  inline       DenseCube getRowPages( const IndexRange colrange ) noexcept;
  inline const DenseCube getRowPages( const IndexRange colrange ) const noexcept;

  // Gets matrix block
  inline       MatrixType getPage( const index_t pageidx ) noexcept;
  inline const MatrixType getPage( const index_t pageidx ) const noexcept;
  inline       MatrixType getCols( const index_t pageidx, const IndexRange rowrange ) noexcept;
  inline const MatrixType getCols( const index_t pageidx, const IndexRange rowrange ) const noexcept;
  inline       MatrixType getRows( const index_t pageidx, const IndexRange colrange ) noexcept;
  inline const MatrixType getRows( const index_t pageidx, const IndexRange colrange ) const noexcept;
  inline       MatrixType getBlock( const index_t pageidx, const IndexRange rowrange,
                                                                              const IndexRange colrange ) noexcept;
  inline const MatrixType getBlock( const index_t pageidx, const IndexRange rowrange,
                                                                              const IndexRange colrange ) const noexcept;
  inline       MatrixType unfold() noexcept;
  inline const MatrixType unfold() const noexcept;

  // Gets vector segment
  inline       VectorType getCol( const index_t colidx, const index_t pageidx ) noexcept;
  inline const VectorType getCol( const index_t colidx, const index_t pageidx ) const noexcept;
  inline       VectorType getColSegment( const index_t colidx, const index_t pageidx,
                                                   const IndexRange rowrange ) noexcept;
  inline const VectorType getColSegment( const index_t colidx, const index_t pageidx,
                                                   const IndexRange rowrange ) const noexcept;
  inline       VectorType getRow( const index_t rowidx, const index_t pageidx ) noexcept;
  inline const VectorType getRow( const index_t rowidx, const index_t pageidx ) const noexcept;
  inline       VectorType getRowSegment( const index_t rowidx, const index_t pageidx,
                                                   const IndexRange colrange ) noexcept;
  inline const VectorType getRowSegment( const index_t rowidx, const index_t pageidx,
                                                   const IndexRange colrange ) const noexcept;
  inline       VectorType getTube( const index_t rowidx, const index_t colidx ) noexcept;
  inline const VectorType getTube( const index_t rowidx, const index_t colidx ) const noexcept;
  inline       VectorType getTubeSegment( const index_t rowidx, const index_t colidx,
                                                    const IndexRange pagerange ) noexcept;
  inline const VectorType getTubeSegment( const index_t rowidx, const index_t colidx,
                                                    const IndexRange pagerange ) const noexcept;
  inline       VectorType getDiagonal( const index_t pageidx, const index_t idx ) noexcept;
  inline const VectorType getDiagonal( const index_t pageidx, const index_t idx ) const noexcept;
  inline       VectorType vectorize() noexcept;
  inline const VectorType vectorize() const noexcept;

 protected:

  // Gets internal information
  inline index_t getIndexInternal( const index_t rowidx, const index_t colidx, const index_t pageidx ) const noexcept;
  inline index_t getColIncInternal() const noexcept;
  inline index_t getRowIncInternal() const noexcept;
  inline index_t getTubeIncInternal() const noexcept;

};

}  // namespace isvd

#endif  // ISVD_MATRIX_DENSE_CUBE_HPP_
