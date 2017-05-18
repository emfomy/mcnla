////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/dense/dense_symmetric_matrix_base.hh
/// @brief   The definition of dense symmetric matrix base class.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_DENSE_DENSE_SYMMETRIC_BASE_MATRIX_HH_
#define MCNLA_CORE_MATRIX_DENSE_DENSE_SYMMETRIC_BASE_MATRIX_HH_

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
/// The dense symmetric matrix base class.
///
/// @tparam  _Core   The core tag.
/// @tparam  _Val    The value type.
/// @tparam  _trans  The transpose storage layout.
/// @tparam  _uplo   The triangular storage layout.
///
template <class _Core, typename _Val, Trans _trans, Uplo _uplo>
class DenseSymmetricMatrixBase
  : public DenseMatrixStorage<_Core, _Val>,
    public MatrixWrapper<SyMatI<_Core, DenseTag, _Val, _trans, _uplo>>,
    public InvertibleWrapper<SyMatI<_Core, DenseTag, _Val, _trans, _uplo>> {

  static_assert(!isConj(_trans),    "Conjugate matrix is not supported!");
  static_assert(!isUnitDiag(_uplo), "Unit-diagonal symmetric matrix is not supported!");

 private:

  using DerivedType = SyMatI<_Core, DenseTag, _Val, _trans, _uplo>;

  friend MatrixWrapper<DerivedType>;
  friend InvertibleWrapper<DerivedType>;

 public:

  static constexpr Trans trans = _trans;
  static constexpr Uplo uplo   = _uplo;

  using ValType       = _Val;
  using ValArrayType  = ArrI<_Core, _Val>;

  using RealType      = SyMatI<_Core, DenseTag, RealValT<_Val>, _trans, _uplo>;
  using ComplexType   = SyMatI<_Core, DenseTag, ComplexValT<_Val>, _trans, _uplo>;

  using VectorType    = GeVecI<_Core, DenseTag, _Val>;
  using MatrixType    = SyMatI<_Core, DenseTag, _Val, _trans, _uplo>;

  using TransposeType = SyMatI<_Core, DenseTag, _Val, changeTrans(_trans), changeUplo(_uplo)>;

  using GeneralType   = GeMatI<_Core, DenseTag, _Val, _trans>;

 private:

  using BaseType      = DenseMatrixStorage<_Core, _Val>;

 public:

  // Constructors
  inline DenseSymmetricMatrixBase() noexcept;
  inline DenseSymmetricMatrixBase( const index_t size ) noexcept;
  inline DenseSymmetricMatrixBase( const index_t size, const index_t pitch ) noexcept;
  inline DenseSymmetricMatrixBase( const index_t size, const index_t pitch, const index_t capacity ) noexcept;
  inline DenseSymmetricMatrixBase( const index_t size, const index_t pitch,
                                   const ValArrayType &val, const index_t offset = 0 ) noexcept;
  inline DenseSymmetricMatrixBase( const DerivedType &other ) noexcept;

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

#endif  // MCNLA_CORE_MATRIX_DENSE_DENSE_SYMMETRIC_BASE_MATRIX_HH_
