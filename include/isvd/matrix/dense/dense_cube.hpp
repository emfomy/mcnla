////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/matrix/dense/dense_cube.hpp
/// @brief   The dense cube class.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_MATRIX_DENSE_DENSE_CUBE_HPP_
#define ISVD_MATRIX_DENSE_DENSE_CUBE_HPP_

#include <isvd/isvd.hpp>
#include <utility>
#include <tuple>
#include <isvd/matrix/cube_base.hpp>
#include <isvd/matrix/dense/dense_base.hpp>
#include <isvd/matrix/dense/dense_vector.hpp>
#include <isvd/matrix/dense/dense_matrix.hpp>
#include <isvd/matrix/dense/dense_cube_iterator.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Scalar, Layout _layout> class DenseCube;
template <typename _Scalar, Layout _layout> class DenseMatrix;
template <typename _Scalar> class DenseVector;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

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
  static constexpr Layout layout = _layout;
  using ScalarType        = _Scalar;
  using RealScalarType    = typename internal::ScalarTraits<_Scalar>::RealType;
  using VectorType        = DenseVector<ScalarType>;
  using RealVectorType    = DenseVector<RealScalarType>;
  using MatrixType        = DenseMatrix<ScalarType, _layout>;
  using RealMatrixType    = DenseMatrix<RealScalarType, _layout>;
  using CubeType          = DenseCube<ScalarType, _layout>;
  using RealCubeType      = DenseCube<RealScalarType, _layout>;
  using TransposeType     = DenseCube<ScalarType, changeLayout(_layout)>;
  using RealTransposeType = DenseCube<RealScalarType, changeLayout(_layout)>;
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

  static constexpr Layout layout = _layout;

  using ScalarType        = _Scalar;
  using RealScalarType    = typename internal::ScalarTraits<_Scalar>::RealType;
  using ValuePtrType      = std::shared_ptr<std::valarray<ScalarType>>;

  using VectorType        = DenseVector<ScalarType>;
  using RealVectorType    = DenseVector<RealScalarType>;
  using MatrixType        = DenseMatrix<ScalarType, _layout>;
  using RealMatrixType    = DenseMatrix<RealScalarType, _layout>;
  using CubeType          = DenseCube<ScalarType, _layout>;
  using RealCubeType      = DenseCube<RealScalarType, _layout>;
  using TransposeType     = DenseCube<ScalarType, changeLayout(_layout)>;
  using RealTransposeType = DenseCube<RealScalarType, changeLayout(_layout)>;

  using DataType          = DenseData<ScalarType>;
  using IteratorType      = DenseCubeIterator<ScalarType, _layout>;
  using ConstIteratorType = DenseCubeConstIterator<ScalarType, _layout>;

 private:

  using CubeBaseType      = internal::CubeBase<DenseCube<_Scalar, _layout>>;
  using DenseBaseType     = internal::DenseBase<DenseCube<_Scalar, _layout>>;

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
  DenseCube( const index_t nrow, const index_t ncol, const index_t npage, const index_t pitch1, const index_t pitch2 ) noexcept;
  DenseCube( const std::tuple<index_t, index_t, index_t> sizes, const std::pair<index_t, index_t> pitches ) noexcept;
  DenseCube( const index_t nrow, const index_t ncol, const index_t npage, const index_t pitch1, const index_t pitch2,
             const index_t capability, const index_t offset = 0 ) noexcept;
  DenseCube( const std::tuple<index_t, index_t, index_t> sizes, const std::pair<index_t, index_t> pitches,
             const index_t capability, const index_t offset = 0 ) noexcept;
  DenseCube( const index_t nrow, const index_t ncol, const index_t npage, const index_t pitch1, const index_t pitch2,
             const ValuePtrType &value, const index_t offset = 0 ) noexcept;
  DenseCube( const index_t nrow, const index_t ncol, const index_t npage, const index_t pitch1, const index_t pitch2,
             const DataType &data, const index_t offset = 0 ) noexcept;
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

  // Gets element
  inline       ScalarType& getElem( const index_t rowidx, const index_t colidx, const index_t pageidx ) noexcept;
  inline const ScalarType& getElem( const index_t rowidx, const index_t colidx, const index_t pageidx ) const noexcept;
  inline       ScalarType& operator()( const index_t rowidx, const index_t colidx, const index_t pageidx ) noexcept;
  inline const ScalarType& operator()( const index_t rowidx, const index_t colidx, const index_t pageidx ) const noexcept;

  // Gets internal position
  inline index_t getPos( const index_t rowidx, const index_t colidx, const index_t pageidx ) const noexcept;

  // Gets iterator
  inline IteratorType      begin() noexcept;
  inline ConstIteratorType begin() const noexcept;
  inline ConstIteratorType cbegin() const noexcept;
  inline IteratorType      end() noexcept;
  inline ConstIteratorType end() const noexcept;
  inline ConstIteratorType cend() const noexcept;
  inline IteratorType      getIterator( const index_t rowidx, const index_t colidx, const index_t pageidx ) noexcept;
  inline ConstIteratorType getIterator( const index_t rowidx, const index_t colidx, const index_t pageidx ) const noexcept;
  inline ConstIteratorType getConstIterator( const index_t rowidx, const index_t colidx, const index_t pageidx ) const noexcept;

  // Transpose
  inline TransposeType transpose() noexcept;

  // Resizes
  inline void resize( const index_t nrow, const index_t ncol, const index_t npage ) noexcept;

  // Gets cube block
  inline       CubeType getCube( const IdxRange rowrange, const IdxRange colrange, const IdxRange pagerange ) noexcept;
  inline const CubeType getCube( const IdxRange rowrange, const IdxRange colrange, const IdxRange pagerange ) const noexcept;
  inline       CubeType getTubes( const IdxRange rowrange, const IdxRange colrange ) noexcept;
  inline const CubeType getTubes( const IdxRange rowrange, const IdxRange colrange ) const noexcept;
  inline       CubeType getPages( const IdxRange pagerange ) noexcept;
  inline const CubeType getPages( const IdxRange pagerange ) const noexcept;
  inline       CubeType getColPages( const IdxRange rowrange ) noexcept;
  inline const CubeType getColPages( const IdxRange rowrange ) const noexcept;
  inline       CubeType getRowPages( const IdxRange colrange ) noexcept;
  inline const CubeType getRowPages( const IdxRange colrange ) const noexcept;

  // Gets matrix block
  inline       MatrixType getPage( const index_t pageidx ) noexcept;
  inline const MatrixType getPage( const index_t pageidx ) const noexcept;
  inline       MatrixType getCols( const index_t pageidx, const IdxRange rowrange ) noexcept;
  inline const MatrixType getCols( const index_t pageidx, const IdxRange rowrange ) const noexcept;
  inline       MatrixType getRows( const index_t pageidx, const IdxRange colrange ) noexcept;
  inline const MatrixType getRows( const index_t pageidx, const IdxRange colrange ) const noexcept;
  inline       MatrixType getBlock( const index_t pageidx, const IdxRange rowrange, const IdxRange colrange ) noexcept;
  inline const MatrixType getBlock( const index_t pageidx, const IdxRange rowrange, const IdxRange colrange ) const noexcept;
  inline       MatrixType unfold() noexcept;
  inline const MatrixType unfold() const noexcept;

  // Gets vector segment
  inline       VectorType getCol( const index_t colidx, const index_t pageidx ) noexcept;
  inline const VectorType getCol( const index_t colidx, const index_t pageidx ) const noexcept;
  inline       VectorType getColSegment( const index_t colidx, const index_t pageidx, const IdxRange rowrange ) noexcept;
  inline const VectorType getColSegment( const index_t colidx, const index_t pageidx, const IdxRange rowrange ) const noexcept;
  inline       VectorType getRow( const index_t rowidx, const index_t pageidx ) noexcept;
  inline const VectorType getRow( const index_t rowidx, const index_t pageidx ) const noexcept;
  inline       VectorType getRowSegment( const index_t rowidx, const index_t pageidx, const IdxRange colrange ) noexcept;
  inline const VectorType getRowSegment( const index_t rowidx, const index_t pageidx, const IdxRange colrange ) const noexcept;
  inline       VectorType getTube( const index_t rowidx, const index_t colidx ) noexcept;
  inline const VectorType getTube( const index_t rowidx, const index_t colidx ) const noexcept;
  inline       VectorType getTubeSegment( const index_t rowidx, const index_t colidx, const IdxRange pagerange ) noexcept;
  inline const VectorType getTubeSegment( const index_t rowidx, const index_t colidx, const IdxRange pagerange ) const noexcept;
  inline       VectorType getDiagonal( const index_t pageidx, const index_t idx ) noexcept;
  inline const VectorType getDiagonal( const index_t pageidx, const index_t idx ) const noexcept;
  inline       VectorType vectorize() noexcept;
  inline const VectorType vectorize() const noexcept;

 protected:

  // Gets stride
  inline index_t getColInc() const noexcept;
  inline index_t getRowInc() const noexcept;
  inline index_t getTubeInc() const noexcept;

};

}  // namespace isvd

#endif  // ISVD_MATRIX_DENSE_DENSE_CUBE_HPP_
