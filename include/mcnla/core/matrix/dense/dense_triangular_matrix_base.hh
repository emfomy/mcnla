////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/dense/dense_triangular_matrix_base.hh
/// @brief   The definition of dense triangular matrix base class.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_DENSE_DENSE_TRIANGULAR_BASE_MATRIX_HH_
#define MCNLA_CORE_MATRIX_DENSE_DENSE_TRIANGULAR_BASE_MATRIX_HH_

#include <mcnla/core/matrix/dense/def.hpp>
#include <mcnla/core/matrix/base/matrix_wrapper.hpp>
#include <mcnla/core/matrix/base/invertible_wrapper.hpp>
#include <mcnla/core/matrix/dense/dense_matrix_storage.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense triangular matrix base class.
///
/// @tparam  _Val    The value type.
/// @tparam  _trans  The transpose storage layout.
/// @tparam  _uplo   The triangular storage layout.
/// @tparam  _Types  The type templates.
///
template <typename _Val, Trans _trans, Uplo _uplo, class _Types>
class DenseTriangularMatrixBase
  : public DenseMatrixStorage<_Val, _Types::template ArrayT>,
    public MatrixWrapper<typename _Types::template TrMatT<_Val, _trans, _uplo>>,
    public InvertibleWrapper<typename _Types::template TrMatT<_Val, _trans, _uplo>> {

  static_assert(!isConj(_trans), "Conjugate matrix is not supported!");

 private:

  using DerivedType = typename _Types::template TrMatT<_Val, _trans, _uplo>;

  friend MatrixWrapper<DerivedType>;
  friend InvertibleWrapper<DerivedType>;

 public:

  static constexpr Trans trans = _trans;
  static constexpr Uplo uplo   = _uplo;

  using ValType       = _Val;
  using ValArrayType  = typename _Types::template ArrayT<_Val>;

  using RealType      = typename _Types::template TrMatT<RealValT<_Val>, _trans, _uplo>;
  using ComplexType   = typename _Types::template TrMatT<ComplexValT<_Val>, _trans, _uplo>;

  using VectorType    = typename _Types::template GeVecT<_Val>;
  using MatrixType    = typename _Types::template TrMatT<_Val, _trans, _uplo>;

  using TransposeType = typename _Types::template TrMatT<_Val, changeTrans(_trans), changeUplo(_uplo)>;

  using GeneralType   = typename _Types::template GeMatT<_Val, _trans>;

 private:

  using BaseType      = DenseMatrixStorage<_Val, _Types::template ArrayT>;

 public:

  // Constructors
  inline DenseTriangularMatrixBase() noexcept;
  inline DenseTriangularMatrixBase( const index_t size ) noexcept;
  inline DenseTriangularMatrixBase( const index_t size, const index_t pitch ) noexcept;
  inline DenseTriangularMatrixBase( const index_t size, const index_t pitch, const index_t capacity ) noexcept;
  inline DenseTriangularMatrixBase( const index_t size, const index_t pitch,
                                   const ValArrayType &val, const index_t offset = 0 ) noexcept;
  inline DenseTriangularMatrixBase( const DerivedType &other ) noexcept;

  // Operators
  inline DerivedType& operator=( const DerivedType &other ) noexcept;

  // Copy
  inline DerivedType copy() const noexcept;

  // Gets information
  inline index_t size() const noexcept;
  inline index_t nnz() const noexcept;

  // Gets element
  inline ValType operator()( const index_t rowidx, const index_t colidx ) const noexcept;

  // Resizes
  template <typename... Args>
  inline void reconstruct( Args... args ) noexcept;
  inline void resize( const index_t size ) noexcept;

  // Transpose/Conjugate
  inline       TransposeType& t() noexcept;
  inline const TransposeType& t() const noexcept;

  // Change view
  inline       GeneralType& viewGeneral() noexcept;
  inline const GeneralType& viewGeneral() const noexcept;

 protected:

  // Gets information
  inline index_t nrowImpl() const noexcept;
  inline index_t ncolImpl() const noexcept;

#ifndef DOXYGEN_SHOULD_SKIP_THIS
  CRTP_BASE(BaseType);
  CRTP_DERIVED(DerivedType);
#endif  // DOXYGEN_SHOULD_SKIP_THIS

};

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_DENSE_DENSE_TRIANGULAR_BASE_MATRIX_HH_
