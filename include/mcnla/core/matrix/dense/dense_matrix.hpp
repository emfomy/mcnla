////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/dense/dense_matrix.hpp
/// @brief   The dense matrix class.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_DENSE_DENSE_MATRIX_HPP_
#define MCNLA_CORE_MATRIX_DENSE_DENSE_MATRIX_HPP_

#include <mcnla/def.hpp>
#include <mcnla/core/def.hpp>
#include <iostream>
#include <mcnla/core/matrix/base/matrix_wrapper.hpp>
#include <mcnla/core/matrix/base/container_wrapper.hpp>
#include <mcnla/core/matrix/dense/dense_vector.hpp>
#include <mcnla/core/matrix/dense/dense_matrix_storage.hpp>
#include <mcnla/core/matrix/dense/dense_matrix_iterator.hpp>
#include <mcnla/core/utility/traits.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Scalar, Layout _layout> class DenseMatrix;
template <typename _Scalar> class DenseVector;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace matrix

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The traits namespace.
//
namespace traits {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense matrix traits.
///
/// @tparam  _Scalar  The scalar type.
///
template <typename _Scalar, Layout _layout>
struct Traits<matrix::DenseMatrix<_Scalar, _layout>> {
  static constexpr index_t ndim = 2;

  using ScalarType        = _Scalar;
  using RealScalarType    = RealType<_Scalar>;
  using MatrixType        = matrix::DenseMatrix<_Scalar, _layout>;
  using IteratorType      = matrix::DenseMatrixIterator<_Scalar, _layout>;
  using ConstIteratorType = matrix::DenseMatrixConstIterator<_Scalar, _layout>;
};

}  // namespace traits

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  matrix_dense_module
/// The dense matrix class.
///
/// @tparam  _Scalar  The scalar type.
///
template <typename _Scalar, Layout _layout = Layout::COLMAJOR>
class DenseMatrix
  : public DenseMatrixStorage<_Scalar>,
    public MatrixWrapper<DenseMatrix<_Scalar, _layout>>,
    public ContainerWrapper<DenseMatrix<_Scalar, _layout>> {

  friend MatrixWrapper<DenseMatrix<_Scalar, _layout>>;
  friend ContainerWrapper<DenseMatrix<_Scalar, _layout>>;

 public:

  static constexpr index_t ndim = 2;

  using ScalarType        = _Scalar;
  using RealScalarType    = RealType<_Scalar>;
  using ValueArrayType    = Array<_Scalar>;
  using SizesType         = std::tuple<index_t, index_t>;

  using VectorType        = DenseVector<_Scalar>;
  using MatrixType        = DenseMatrix<_Scalar, _layout>;
  using TransposeType     = DenseMatrix<_Scalar, changeLayout(_layout)>;

  using IteratorType      = DenseMatrixIterator<_Scalar, _layout>;
  using ConstIteratorType = DenseMatrixConstIterator<_Scalar, _layout>;

 private:

  using BaseType          = DenseMatrixStorage<_Scalar>;

 public:

  // Constructors
  inline DenseMatrix() noexcept;
  inline DenseMatrix( const index_t nrow, const index_t ncol ) noexcept;
  inline DenseMatrix( const SizesType sizes ) noexcept;
  inline DenseMatrix( const index_t nrow, const index_t ncol, const index_t pitch ) noexcept;
  inline DenseMatrix( const SizesType sizes, const index_t pitch ) noexcept;
  inline DenseMatrix( const index_t nrow, const index_t ncol, const index_t pitch, const index_t capacity ) noexcept;
  inline DenseMatrix( const SizesType sizes, const index_t pitch, const index_t capacity ) noexcept;
  inline DenseMatrix( const index_t nrow, const index_t ncol, const index_t pitch,
                      const ValueArrayType &value, const index_t offset = 0 ) noexcept;
  inline DenseMatrix( const DenseMatrix &other ) noexcept;
  inline DenseMatrix( DenseMatrix &&other ) noexcept;

  // Operators
  inline DenseMatrix& operator=( const DenseMatrix &other ) noexcept;
  inline DenseMatrix& operator=( DenseMatrix &&other ) noexcept;
  template <typename __Scalar, Layout __layout>
  friend inline std::ostream& operator<<( std::ostream &out, const DenseMatrix<__Scalar, __layout> &matrix );

  // Gets information
  inline index_t getNidx() const noexcept;

  // Gets element
  inline       ScalarType& operator()( const index_t rowidx, const index_t colidx ) noexcept;
  inline const ScalarType& operator()( const index_t rowidx, const index_t colidx ) const noexcept;

  // Gets internal position
  inline index_t getPos( const index_t rowidx, const index_t colidx ) const noexcept;

  // Finds the iterator
  inline IteratorType      find( const index_t rowidx, const index_t colidx ) noexcept;
  inline ConstIteratorType find( const index_t rowidx, const index_t colidx ) const noexcept;
  inline ConstIteratorType cfind( const index_t rowidx, const index_t colidx ) const noexcept;

  // Resizes
  inline void resize( const index_t nrow, const index_t ncol ) noexcept;

  // Transpose
  inline       TransposeType& transpose() noexcept;
  inline const TransposeType& transpose() const noexcept;

  // Gets matrix block
  inline       MatrixType operator()( const IdxRange &rowrange, const IdxRange &colrange ) noexcept;
  inline const MatrixType operator()( const IdxRange &rowrange, const IdxRange &colrange ) const noexcept;
  inline       MatrixType operator()( const char*,              const IdxRange &colrange ) noexcept;
  inline const MatrixType operator()( const char*,              const IdxRange &colrange ) const noexcept;
  inline       MatrixType operator()( const IdxRange &rowrange, const char*              ) noexcept;
  inline const MatrixType operator()( const IdxRange &rowrange, const char*              ) const noexcept;

  // Gets vector segment
  inline       VectorType operator()( const IdxRange &rowrange, const index_t colidx     ) noexcept;
  inline const VectorType operator()( const IdxRange &rowrange, const index_t colidx     ) const noexcept;
  inline       VectorType operator()( const char*,              const index_t colidx     ) noexcept;
  inline const VectorType operator()( const char*,              const index_t colidx     ) const noexcept;
  inline       VectorType operator()( const index_t rowidx,     const IdxRange &colrange ) noexcept;
  inline const VectorType operator()( const index_t rowidx,     const IdxRange &colrange ) const noexcept;
  inline       VectorType operator()( const index_t rowidx,     const char*              ) noexcept;
  inline const VectorType operator()( const index_t rowidx,     const char*              ) const noexcept;

  inline       VectorType getDiagonal( const index_t idx = 0 ) noexcept;
  inline const VectorType getDiagonal( const index_t idx = 0 ) const noexcept;
  inline       VectorType vectorize() noexcept;
  inline const VectorType vectorize() const noexcept;

 protected:

  // Gets information
  inline index_t getNrowImpl() const noexcept;
  inline index_t getNcolImpl() const noexcept;

  // Convert sizes to dims
  inline index_t dim0( const SizesType sizes ) const noexcept;
  inline index_t dim0( const index_t nrow, const index_t ncol ) const noexcept;
  inline index_t dim1( const SizesType sizes ) const noexcept;
  inline index_t dim1( const index_t nrow, const index_t ncol ) const noexcept;

  // Create full index range
  inline const IdxRange colfullrange() const noexcept;
  inline const IdxRange rowfullrange() const noexcept;

  // Gets base class
  inline       BaseType& base() noexcept;
  inline const BaseType& base() const noexcept;

};

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_DENSE_DENSE_MATRIX_HPP_
