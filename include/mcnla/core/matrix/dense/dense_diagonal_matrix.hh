////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/dense/dense_diagonal_matrix.hh
/// @brief   The definition of definition of dense diagonal matrix class.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_DENSE_DENSE_DIAGONAL_MATRIX_HH_
#define MCNLA_CORE_MATRIX_DENSE_DENSE_DIAGONAL_MATRIX_HH_

#include <mcnla/core/matrix/def.hpp>
#include <mcnla/core/matrix/base/dense_matrix_wrapper.hpp>
#include <mcnla/core/matrix/base/iterable_wrapper.hpp>
#include <mcnla/core/matrix/base/invertible_wrapper.hpp>
#include <mcnla/core/matrix/dense/dense_vector_storage.hpp>
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
template <typename _Val> class DenseDiagonalMatrix;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace matrix

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The traits namespace.
//
namespace traits {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense diagonal matrix traits.
///
template <typename _Val>
struct Traits<matrix::DenseDiagonalMatrix<_Val>> {

  static constexpr index_t ndim = 2;

  using ValType     = _Val;
  using RealType    = matrix::DenseDiagonalMatrix<RealValT<_Val>>;
  using ComplexType = matrix::DenseDiagonalMatrix<ComplexValT<_Val>>;
  using VectorType  = matrix::DenseVector<_Val>;
  using MatrixType  = matrix::DenseDiagonalMatrix<_Val>;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense diagonal matrix instantiation type traits.
///
template <typename _Type>
struct IsDenseDiagonalMatrix : std::false_type {};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc IsDenseDiagonalMatrix
///
template <typename _Val>
struct IsDenseDiagonalMatrix<matrix::DenseDiagonalMatrix<_Val>> : std::true_type {};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense diagonal matrix assert.
///
#define assertDenseDiagonalMatrix( Type ) \
    static_assert(traits::IsDenseDiagonalMatrix<Type>::value, "'"#Type"' is not a dense diagonal matrix!")

}  // namespace traits

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  matrix_dense_module
/// The dense diagonal matrix class.
///
/// @tparam  _Val  The value type.
///
template <typename _Val>
class DenseDiagonalMatrix
  : public DenseVectorStorage<_Val>,
    public DenseMatrixWrapper<DenseDiagonalMatrix<_Val>>,
    public InvertibleWrapper<DenseDiagonalMatrix<_Val>> {

  friend MatrixWrapper<DenseDiagonalMatrix<_Val>>;
  friend DenseMatrixWrapper<DenseDiagonalMatrix<_Val>>;
  friend InvertibleWrapper<DenseDiagonalMatrix<_Val>>;

 public:

  static constexpr index_t ndim = 2;

  using ValType       = _Val;
  using ValArrayType  = Array<_Val>;

  using RealType      = DenseDiagonalMatrix<RealValT<_Val>>;
  using ComplexType   = DenseDiagonalMatrix<ComplexValT<_Val>>;

  using VectorType    = DenseVector<_Val>;
  using MatrixType    = DenseDiagonalMatrix<_Val>;

  using TransposeType = DenseDiagonalMatrix<_Val>;

 private:

  using BaseType      = DenseVectorStorage<_Val>;

 public:

  // Constructors
  inline DenseDiagonalMatrix() noexcept;
  inline DenseDiagonalMatrix( const index_t size ) noexcept;
  inline DenseDiagonalMatrix( const index_t size, const index_t pitch ) noexcept;
  inline DenseDiagonalMatrix( const index_t size, const index_t pitch, const index_t capacity ) noexcept;
  inline DenseDiagonalMatrix( const index_t size, const index_t pitch,
                              const ValArrayType &val, const index_t offset = 0 ) noexcept;
  inline DenseDiagonalMatrix( const DenseDiagonalMatrix &other ) noexcept;
  inline DenseDiagonalMatrix( DenseDiagonalMatrix &&other ) noexcept;

  // Operators
  inline DenseDiagonalMatrix& operator=( const DenseDiagonalMatrix &other ) noexcept;
  inline DenseDiagonalMatrix& operator=( DenseDiagonalMatrix &&other ) noexcept;

  // Copy
  inline DenseDiagonalMatrix copy() const noexcept;

  // Gets information
  inline index_t size() const noexcept;
  inline index_t nnz() const noexcept;
  inline index_t pitch() const noexcept;

  // Gets element
  inline ValType operator()( const index_t rowidx, const index_t colidx ) const noexcept;

  // Resizes
  template <typename... Args>
  inline void reconstruct( Args... args ) noexcept;

  // Transpose
  inline       TransposeType& t() noexcept;
  inline const TransposeType& t() const noexcept;

  // Changes view
  inline       VectorType& viewVector() noexcept;
  inline const VectorType& viewVector() const noexcept;

  // Gets vector
  inline       VectorType& vectorize() noexcept;
  inline const VectorType& vectorize() const noexcept;

 protected:

  // Gets information
  inline index_t nrowImpl() const noexcept;
  inline index_t ncolImpl() const noexcept;

  // Gets base class
  inline       BaseType& base() noexcept;
  inline const BaseType& base() const noexcept;

};

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_DENSE_DENSE_DIAGONAL_MATRIX_HH_
