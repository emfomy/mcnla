////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/dense/dense_matrix.hh
/// @brief   The definition of definition of dense matrix class.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_DENSE_DENSE_MATRIX_HH_
#define MCNLA_CORE_MATRIX_DENSE_DENSE_MATRIX_HH_

#include <mcnla/core/matrix/def.hpp>
#include <mcnla/core/matrix/base/container_wrapper.hpp>
#include <mcnla/core/matrix/base/invertible_wrapper.hpp>
#include <mcnla/core/matrix/base/matrix_wrapper.hpp>
#include <mcnla/core/matrix/dense/dense_matrix_storage.hpp>
#include <mcnla/core/matrix/dense/dense_matrix_iterator.hpp>
#include <mcnla/core/matrix/dense/dense_vector.hpp>
#include <mcnla/core/matrix/dense/dense_symmetric_matrix.hpp>
#include <mcnla/core/matrix/dense/dense_triangular_matrix.hpp>
#include <mcnla/core/matrix/dense/dense_diagonal_matrix.hpp>
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
template <typename _Scalar, Trans _trans> class DenseMatrix;
template <typename _Scalar> class DenseVector;
template <typename _Scalar, Trans _trans, Uplo _uplo> class DenseSymmetricMatrix;
template <typename _Scalar, Trans _trans, Uplo _uplo> class DenseTriangularMatrix;
template <typename _Scalar> class DenseDiagonalMatrix;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace matrix

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The traits namespace.
//
namespace traits {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense matrix traits.
///
template <typename _Scalar, Trans _trans>
struct Traits<matrix::DenseMatrix<_Scalar, _trans>> {

  static constexpr index_t ndim = 2;
  static constexpr Trans trans = _trans;

  using ScalarType        = _Scalar;

  using RealType          = matrix::DenseMatrix<RealScalarT<_Scalar>, _trans>;
  using ComplexType       = matrix::DenseMatrix<ComplexScalarT<_Scalar>, _trans>;

  using VectorType        = matrix::DenseVector<_Scalar>;
  using MatrixType        = matrix::DenseMatrix<_Scalar, _trans>;

  using IteratorType      = matrix::DenseMatrixIterator<_Scalar, _trans>;
  using ConstIteratorType = matrix::DenseMatrixConstIterator<_Scalar, _trans>;
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
/// @tparam  _trans   The transpose storage layout.
///
template <typename _Scalar, Trans _trans = Trans::NORMAL>
class DenseMatrix
  : public DenseMatrixStorage<_Scalar>,
    public MatrixWrapper<DenseMatrix<_Scalar, _trans>>,
    public ContainerWrapper<DenseMatrix<_Scalar, _trans>>,
    public InvertibleWrapper<DenseMatrix<_Scalar, _trans>> {

  static_assert(!isConj(_trans), "Conjugate matrix is not supported!");

  friend MatrixWrapper<DenseMatrix<_Scalar, _trans>>;
  friend ContainerWrapper<DenseMatrix<_Scalar, _trans>>;
  friend InvertibleWrapper<DenseMatrix<_Scalar, _trans>>;

 public:

  static constexpr index_t ndim = 2;
  static constexpr Trans trans = _trans;

  using ScalarType        = _Scalar;
  using ValueArrayType    = Array<_Scalar>;
  using SizesType         = std::tuple<index_t, index_t>;

  using RealType          = DenseMatrix<RealScalarT<_Scalar>, _trans>;
  using ComplexType       = DenseMatrix<ComplexScalarT<_Scalar>, _trans>;

  using VectorType        = DenseVector<_Scalar>;
  using MatrixType        = DenseMatrix<_Scalar, _trans>;

  using TransposeType     = DenseMatrix<_Scalar, changeTrans(_trans)>;
  using ConjugateType     = DenseMatrix<_Scalar, changeConj(_trans)>;
  using HermitianType     = DenseMatrix<_Scalar, changeHerm(_trans)>;

  template <Uplo _uplo>
  using SymmetricType     = DenseSymmetricMatrix<_Scalar, _trans, _uplo>;

  template <Uplo _uplo>
  using TriangularType    = DenseTriangularMatrix<_Scalar, _trans, _uplo>;

  using DiagonalType      = DenseDiagonalMatrix<_Scalar>;

  using IteratorType      = DenseMatrixIterator<_Scalar, _trans>;
  using ConstIteratorType = DenseMatrixConstIterator<_Scalar, _trans>;

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

  // Gets information
  inline index_t nidx() const noexcept;

  // Gets element
  inline       ScalarType& operator()( const index_t rowidx, const index_t colidx ) noexcept;
  inline const ScalarType& operator()( const index_t rowidx, const index_t colidx ) const noexcept;

  // Gets internal position
  inline index_t pos( const index_t rowidx, const index_t colidx ) const noexcept;

  // Finds the iterator
  inline IteratorType      find( const index_t rowidx, const index_t colidx ) noexcept;
  inline ConstIteratorType find( const index_t rowidx, const index_t colidx ) const noexcept;
  inline ConstIteratorType cfind( const index_t rowidx, const index_t colidx ) const noexcept;

  // Resizes
  template <typename... Args>
  inline void reconstruct( Args... args ) noexcept;
  inline void resize( const index_t nrow, const index_t ncol ) noexcept;

  // Transpose
  inline       TransposeType& t() noexcept;
  inline const TransposeType& t() const noexcept;
  inline       ConjugateType& c() noexcept;
  inline const ConjugateType& c() const noexcept;
  inline       HermitianType& h() noexcept;
  inline const HermitianType& h() const noexcept;

  // Change view
  template <Uplo _uplo = Uplo::UPPER ^ _trans>
  inline       SymmetricType<_uplo>& viewSymmetric() noexcept;
  template <Uplo _uplo = Uplo::UPPER ^ _trans>
  inline const SymmetricType<_uplo>& viewSymmetric() const noexcept;

  template <Uplo _uplo = Uplo::UPPER ^ _trans>
  inline       TriangularType<_uplo>& viewTriangular() noexcept;
  template <Uplo _uplo = Uplo::UPPER ^ _trans>
  inline const TriangularType<_uplo>& viewTriangular() const noexcept;

  inline       DiagonalType viewDiagonal() noexcept;
  inline const DiagonalType viewDiagonal() const noexcept;

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
  inline index_t nrowImpl() const noexcept;
  inline index_t ncolImpl() const noexcept;

  // Convert sizes to dims
  inline index_t toDim0( const SizesType sizes ) const noexcept;
  inline index_t toDim0( const index_t nrow, const index_t ncol ) const noexcept;
  inline index_t toDim1( const SizesType sizes ) const noexcept;
  inline index_t toDim1( const index_t nrow, const index_t ncol ) const noexcept;

  // Create full index range
  inline const IdxRange colfullrange() const noexcept;
  inline const IdxRange rowfullrange() const noexcept;

  // Gets base class
  inline       BaseType& base() noexcept;
  inline const BaseType& base() const noexcept;

};

/// @ingroup  matrix_dense_module
template <typename _Scalar>
using DenseMatrixColMajor = DenseMatrix<_Scalar, Trans::NORMAL>;

/// @ingroup  matrix_dense_module
template <typename _Scalar>
using DenseMatrixRowMajor = DenseMatrix<_Scalar, Trans::TRANS>;

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_DENSE_DENSE_MATRIX_HH_
