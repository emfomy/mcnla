////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/dense/dense_cube.hpp
/// @brief   The dense cube class.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_DENSE_DENSE_CUBE_HPP_
#define MCNLA_CORE_MATRIX_DENSE_DENSE_CUBE_HPP_

#include <mcnla/def.hpp>
#include <mcnla/core/def.hpp>
#include <iostream>
#include <utility>
#include <tuple>
#include <mcnla/core/matrix/base/container_base.hpp>
#include <mcnla/core/matrix/base/cube_base.hpp>
#include <mcnla/core/matrix/dense/dense_base.hpp>
#include <mcnla/core/matrix/dense/dense_vector.hpp>
#include <mcnla/core/matrix/dense/dense_matrix.hpp>
#include <mcnla/core/matrix/dense/dense_cube_iterator.hpp>
#include <mcnla/core/matrix/kit/idx_range.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Scalar, Layout _layout> class DenseCube;
template <typename _Scalar, Layout _layout> class DenseMatrix;
template <typename _Scalar> class DenseVector;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace matrix

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The traits namespace.
//
namespace traits {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense cube traits.
///
/// @tparam  _Scalar  The scalar type.
/// @tparam  _layout  The storage layout.
///
template <typename _Scalar, Layout _layout>
struct Traits<matrix::DenseCube<_Scalar, _layout>> {
  static constexpr index_t ndim = 3;
  static constexpr Layout layout = _layout;

  using ScalarType        = _Scalar;
  using RealScalarType    = RealType<_Scalar>;

  using VectorType        = matrix::DenseVector<ScalarType>;
  using RealVectorType    = matrix::DenseVector<RealScalarType>;
  using MatrixType        = matrix::DenseMatrix<ScalarType, _layout>;
  using RealMatrixType    = matrix::DenseMatrix<RealScalarType, _layout>;
  using CubeType          = matrix::DenseCube<ScalarType, _layout>;
  using RealCubeType      = matrix::DenseCube<RealScalarType, _layout>;
  using TransposeType     = matrix::DenseCube<ScalarType, changeLayout(_layout)>;
  using RealTransposeType = matrix::DenseCube<RealScalarType, changeLayout(_layout)>;

  using IteratorType      = matrix::DenseCubeIterator<ScalarType, _layout>;
  using ConstIteratorType = matrix::DenseCubeConstIterator<ScalarType, _layout>;
};

}  // namespace traits

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  matrix_dense_module
/// The dense cube class.
///
/// @tparam  _Scalar  The scalar type.
/// @tparam  _layout  The storage layout.
///
template <typename _Scalar, Layout _layout = Layout::COLMAJOR>
class DenseCube
  : public ContainerBase<DenseCube<_Scalar, _layout>>,
    public CubeBase<DenseCube<_Scalar, _layout>>,
    public DenseBase<DenseCube<_Scalar, _layout>>{

 public:

  static constexpr index_t ndim = 3;
  static constexpr Layout layout = _layout;

  using ScalarType        = _Scalar;
  using RealScalarType    = RealType<_Scalar>;
  using ValueArrayType    = Array<ScalarType>;

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

  using ContainerBaseType = ContainerBase<DenseCube<_Scalar, _layout>>;
  using CubeBaseType      = CubeBase<DenseCube<_Scalar, _layout>>;
  using DenseBaseType     = DenseBase<DenseCube<_Scalar, _layout>>;

 protected:

  /// The leading dimension.
  index_t pitch0_;

  /// The second dimension.
  index_t pitch1_;

  using CubeBaseType::nrow_;
  using CubeBaseType::ncol_;
  using CubeBaseType::npage_;
  using CubeBaseType::size0_;
  using CubeBaseType::size1_;
  using CubeBaseType::size2_;
  using DenseBaseType::data_;

 public:

  // Constructors
  inline DenseCube() noexcept;
  inline DenseCube( const index_t nrow, const index_t ncol, const index_t npage ) noexcept;
  inline DenseCube( const std::tuple<index_t, index_t, index_t> sizes ) noexcept;
  inline DenseCube( const index_t nrow, const index_t ncol, const index_t npage, const index_t pitch0 ) noexcept;
  inline DenseCube( const index_t nrow, const index_t ncol, const index_t npage,
                    const index_t pitch0, const index_t pitch1 ) noexcept;
  inline DenseCube( const std::tuple<index_t, index_t, index_t> sizes, const std::pair<index_t, index_t> pitches ) noexcept;
  inline DenseCube( const index_t nrow, const index_t ncol, const index_t npage,
                    const index_t pitch0, const index_t pitch1, const index_t capacity ) noexcept;
  inline DenseCube( const std::tuple<index_t, index_t, index_t> sizes,
                    const std::pair<index_t, index_t> pitches, const index_t capacity ) noexcept;
  inline DenseCube( const index_t nrow, const index_t ncol, const index_t npage,
                    const index_t pitch0, const index_t pitch1, const ValueArrayType &value ) noexcept;
  inline DenseCube( const index_t nrow, const index_t ncol, const index_t npage,
                    const index_t pitch0, const index_t pitch1, const DataType &data, const index_t offset = 0 ) noexcept;
  inline DenseCube( const DenseCube &other ) noexcept;
  inline DenseCube( DenseCube &&other ) noexcept;

  // Operators
  inline DenseCube& operator=( const DenseCube &other ) noexcept;
  inline DenseCube& operator=( DenseCube &&other ) noexcept;
  template <typename __Scalar, Layout __layout>
  friend inline std::ostream& operator<<( std::ostream &out, const DenseCube<__Scalar, __layout> &cube );

  // Gets information
  inline index_t getPitch0() const noexcept;
  inline index_t getPitch1() const noexcept;
  inline std::pair<index_t, index_t> getPitches() const noexcept;
  inline bool isShrunk() const noexcept;

  // Gets element
  inline       ScalarType& getElem( const index_t rowidx, const index_t colidx, const index_t pageidx ) noexcept;
  inline const ScalarType& getElem( const index_t rowidx, const index_t colidx, const index_t pageidx ) const noexcept;
  inline       ScalarType& operator()( const index_t rowidx, const index_t colidx, const index_t pageidx ) noexcept;
  inline const ScalarType& operator()( const index_t rowidx, const index_t colidx, const index_t pageidx ) const noexcept;

  // Gets mask
  inline const std::gslice getValueMask() const noexcept;

  // Gets internal position
  inline index_t getPos( const index_t rowidx, const index_t colidx, const index_t pageidx ) const noexcept;

  // Transpose
  inline TransposeType transpose() noexcept;

  // Finds the iterator
  inline IteratorType      find( const index_t rowidx, const index_t colidx, const index_t pageidx ) noexcept;
  inline ConstIteratorType find( const index_t rowidx, const index_t colidx, const index_t pageidx ) const noexcept;
  inline ConstIteratorType cfind( const index_t rowidx, const index_t colidx, const index_t pageidx ) const noexcept;

  // Resizes
  inline void resize( const index_t nrow, const index_t ncol, const index_t npage ) noexcept;

  // Gets cube block
  inline       CubeType getSubcube( const IdxRange rowrange, const IdxRange colrange, const IdxRange pagerange ) noexcept;
  inline const CubeType getSubcube( const IdxRange rowrange, const IdxRange colrange, const IdxRange pagerange ) const noexcept;
  inline       CubeType getTubes( const IdxRange rowrange, const IdxRange colrange ) noexcept;
  inline const CubeType getTubes( const IdxRange rowrange, const IdxRange colrange ) const noexcept;
  inline       CubeType getPages( const IdxRange pagerange ) noexcept;
  inline const CubeType getPages( const IdxRange pagerange ) const noexcept;
  inline       CubeType getColPages( const IdxRange colrange ) noexcept;
  inline const CubeType getColPages( const IdxRange colrange ) const noexcept;
  inline       CubeType getRowPages( const IdxRange rowrange ) noexcept;
  inline const CubeType getRowPages( const IdxRange rowrange ) const noexcept;

  // Gets matrix block
  inline       MatrixType getPage( const index_t pageidx ) noexcept;
  inline const MatrixType getPage( const index_t pageidx ) const noexcept;
  inline       MatrixType getCols( const index_t pageidx, const IdxRange colrange ) noexcept;
  inline const MatrixType getCols( const index_t pageidx, const IdxRange colrange ) const noexcept;
  inline       MatrixType getRows( const index_t pageidx, const IdxRange rowrange ) noexcept;
  inline const MatrixType getRows( const index_t pageidx, const IdxRange rowrange ) const noexcept;
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
  inline       VectorType getDiagonal( const index_t pageidx, const index_t idx = 0 ) noexcept;
  inline const VectorType getDiagonal( const index_t pageidx, const index_t idx = 0 ) const noexcept;
  inline       VectorType vectorize() noexcept;
  inline const VectorType vectorize() const noexcept;

 protected:

  // Gets stride
  inline index_t getColStride() const noexcept;
  inline index_t getRowStride() const noexcept;
  inline index_t getTubeStride() const noexcept;

};

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_DENSE_DENSE_CUBE_HPP_
