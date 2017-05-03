////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/dense/dense_diagonal_matrix_base.hh
/// @brief   The definition of definition of dense diagonal matrix base class.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_DENSE_DENSE_DIAGONAL_MATRIX_BASE_HH_
#define MCNLA_CORE_MATRIX_DENSE_DENSE_DIAGONAL_MATRIX_BASE_HH_

#include <mcnla/core/matrix/dense/def.hpp>
#include <mcnla/core/matrix/base/matrix_wrapper.hpp>
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense diagonal matrix base class.
///
/// @tparam  _Val    The value type.
/// @tparam  _Types  The type templates.
///
template <typename _Val, class _Types>
class DenseDiagonalMatrixBase
  : public DenseVectorStorage<_Val, _Types::template ArrayT>,
    public MatrixWrapper<typename _Types::template DiMatT<_Val>>,
    public InvertibleWrapper<typename _Types::template DiMatT<_Val>> {

 private:

  using DerivedType = typename _Types::template DiMatT<_Val>;

  friend MatrixWrapper<DerivedType>;
  friend InvertibleWrapper<DerivedType>;

 public:

  using ValType       = _Val;
  using ValArrayType  = typename _Types::template ArrayT<_Val>;

  using RealType      = typename _Types::template DiMatT<RealValT<_Val>>;
  using ComplexType   = typename _Types::template DiMatT<ComplexValT<_Val>>;

  using VectorType    = typename _Types::template GeVecT<_Val>;
  using MatrixType    = typename _Types::template DiMatT<_Val>;

  using TransposeType = typename _Types::template DiMatT<_Val>;

 private:

  using BaseType      = DenseVectorStorage<_Val, _Types::template ArrayT>;

 public:

  // Constructors
  inline DenseDiagonalMatrixBase() noexcept;
  inline DenseDiagonalMatrixBase( const index_t size ) noexcept;
  inline DenseDiagonalMatrixBase( const index_t size, const index_t pitch ) noexcept;
  inline DenseDiagonalMatrixBase( const index_t size, const index_t pitch, const index_t capacity ) noexcept;
  inline DenseDiagonalMatrixBase( const index_t size, const index_t pitch,
                                  const ValArrayType &val, const index_t offset = 0 ) noexcept;
  inline DenseDiagonalMatrixBase( const DerivedType &other ) noexcept;

  // Operators
  inline DerivedType& operator=( const DerivedType &other ) noexcept;

  // Copy
  inline DerivedType copy() const noexcept;

  // Gets information
  inline index_t size() const noexcept;
  inline index_t nnz() const noexcept;
  inline index_t pitch() const noexcept;

  // Gets element
  inline ValType operator()( const index_t rowidx, const index_t colidx ) const noexcept;

  // Resizes
  template <typename... Args>
  inline void reconstruct( Args... args ) noexcept;

  // Transpose/Conjugate
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

#endif  // MCNLA_CORE_MATRIX_DENSE_DENSE_DIAGONAL_MATRIX_BASE_HH_
