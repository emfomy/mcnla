////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/dense/dense_matrix.hh
/// @brief   The definition of definition of dense matrix class.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_DENSE_DENSE_MATRIX_HH_
#define MCNLA_CORE_MATRIX_DENSE_DENSE_MATRIX_HH_

#include <mcnla/core/matrix/def.hpp>
#include <mcnla/core/matrix/base/dense_matrix_wrapper.hpp>
#include <mcnla/core/matrix/base/iterable_wrapper.hpp>
#include <mcnla/core/matrix/base/invertible_wrapper.hpp>
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
template <typename _Val, Trans _trans> class DenseMatrix;
template <typename _Val> class DenseVector;
template <typename _Val, Trans _trans, Uplo _uplo> class DenseSymmetricMatrix;
template <typename _Val, Trans _trans, Uplo _uplo> class DenseTriangularMatrix;
template <typename _Val> class DenseDiagonalMatrix;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace matrix

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The traits namespace.
//
namespace traits {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense matrix traits.
///
template <typename _Val, Trans _trans>
struct Traits<matrix::DenseMatrix<_Val, _trans>> {

  static constexpr index_t ndim = 2;
  static constexpr Trans trans = _trans;

  using ValType           = _Val;

  using RealType          = matrix::DenseMatrix<RealValT<_Val>, _trans>;
  using ComplexType       = matrix::DenseMatrix<ComplexValT<_Val>, _trans>;

  using VectorType        = matrix::DenseVector<_Val>;
  using MatrixType        = matrix::DenseMatrix<_Val, _trans>;

  using IteratorType      = matrix::DenseMatrixIterator<_Val, _trans>;
  using ConstIteratorType = matrix::DenseMatrixConstIterator<_Val, _trans>;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense matrix instantiation type traits.
///
template <typename _Type>
struct IsDenseMatrix : std::false_type {};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc IsDenseMatrix
///
template <typename _Val, Trans _trans>
struct IsDenseMatrix<matrix::DenseMatrix<_Val, _trans>> : std::true_type {};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense matrix assert.
///
#define assertDenseMatrix( Type ) \
    static_assert(traits::IsDenseMatrix<Type>::value, "'"#Type"' is not a dense matrix!")

}  // namespace traits

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  matrix_dense_module
/// The dense matrix class.
///
/// @tparam  _Val    The value type.
/// @tparam  _trans  The transpose storage layout.
///
template <typename _Val, Trans _trans = Trans::NORMAL>
class DenseMatrix
  : public DenseMatrixStorage<_Val>,
    public DenseMatrixWrapper<DenseMatrix<_Val, _trans>>,
    public IterableWrapper<DenseMatrix<_Val, _trans>>,
    public InvertibleWrapper<DenseMatrix<_Val, _trans>> {

  static_assert(!isConj(_trans), "Conjugate matrix is not supported!");

  friend MatrixWrapper<DenseMatrix<_Val, _trans>>;
  friend DenseMatrixWrapper<DenseMatrix<_Val, _trans>>;
  friend IterableWrapper<DenseMatrix<_Val, _trans>>;
  friend InvertibleWrapper<DenseMatrix<_Val, _trans>>;

 public:

  static constexpr index_t ndim = 2;
  static constexpr Trans trans = _trans;

  using ValType           = _Val;
  using ValArrayType      = Array<_Val>;
  using SizesType         = std::tuple<index_t, index_t>;

  using RealType          = DenseMatrix<RealValT<_Val>, _trans>;
  using ComplexType       = DenseMatrix<ComplexValT<_Val>, _trans>;

  using VectorType        = DenseVector<_Val>;
  using MatrixType        = DenseMatrix<_Val, _trans>;

  using TransposeType     = DenseMatrix<_Val, changeTrans(_trans)>;
  using ConjugateType     = DenseMatrix<_Val, changeConj(_trans)>;
  using HermitianType     = DenseMatrix<_Val, changeHerm(_trans)>;

  template <Uplo _uplo>
  using SymmetricType     = DenseSymmetricMatrix<_Val, _trans, _uplo>;

  template <Uplo _uplo>
  using TriangularType    = DenseTriangularMatrix<_Val, _trans, _uplo>;

  using DiagonalType      = DenseDiagonalMatrix<_Val>;

  using IteratorType      = DenseMatrixIterator<_Val, _trans>;
  using ConstIteratorType = DenseMatrixConstIterator<_Val, _trans>;

 private:

  using BaseType          = DenseMatrixStorage<_Val>;

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
                      const ValArrayType &val, const index_t offset = 0 ) noexcept;
  inline DenseMatrix( const DenseMatrix &other ) noexcept;
  inline DenseMatrix( DenseMatrix &&other ) noexcept;

  // Operators
  inline DenseMatrix& operator=( const DenseMatrix &other ) noexcept;
  inline DenseMatrix& operator=( DenseMatrix &&other ) noexcept;

  // Copy
  inline DenseMatrix copy() const noexcept;

  // Gets information
  inline index_t nnz() const noexcept;

  // Gets element
  inline       ValType& operator()( const index_t rowidx, const index_t colidx ) noexcept;
  inline const ValType& operator()( const index_t rowidx, const index_t colidx ) const noexcept;

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
  inline void resize( const index_t nrow, const FullRange ) noexcept;
  inline void resize( const FullRange, const index_t ncol ) noexcept;

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
  inline       MatrixType operator()( const FullRange, const IdxRange &colrange ) noexcept;
  inline const MatrixType operator()( const FullRange, const IdxRange &colrange ) const noexcept;
  inline       MatrixType operator()( const IdxRange &rowrange, const FullRange ) noexcept;
  inline const MatrixType operator()( const IdxRange &rowrange, const FullRange ) const noexcept;

  // Gets vector segment
  inline       VectorType operator()( const IdxRange &rowrange, const index_t colidx ) noexcept;
  inline const VectorType operator()( const IdxRange &rowrange, const index_t colidx ) const noexcept;
  inline       VectorType operator()( const FullRange, const index_t colidx ) noexcept;
  inline const VectorType operator()( const FullRange, const index_t colidx ) const noexcept;
  inline       VectorType operator()( const index_t rowidx, const IdxRange &colrange ) noexcept;
  inline const VectorType operator()( const index_t rowidx, const IdxRange &colrange ) const noexcept;
  inline       VectorType operator()( const index_t rowidx, const FullRange ) noexcept;
  inline const VectorType operator()( const index_t rowidx, const FullRange ) const noexcept;

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
template <typename _Val>
using DenseMatrixColMajor = DenseMatrix<_Val, Trans::NORMAL>;

/// @ingroup  matrix_dense_module
template <typename _Val>
using DenseMatrixRowMajor = DenseMatrix<_Val, Trans::TRANS>;

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_DENSE_DENSE_MATRIX_HH_
