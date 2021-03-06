////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/dense/dense_symmetric_matrix_base.hh
/// @brief   The definition of dense symmetric matrix base class.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_DENSE_DENSE_SYMMETRIC_BASE_MATRIX_HH_
#define MCNLA_CORE_MATRIX_DENSE_DENSE_SYMMETRIC_BASE_MATRIX_HH_

#include <mcnla/core/matrix/dense/def.hpp>
#include <mcnla/core/matrix/base/dense_matrix_wrapper.hpp>
#include <mcnla/core/matrix/base/invertible_wrapper.hpp>
#include <mcnla/core/matrix/dense/dense_matrix_storage.hpp>

#ifndef DOXYGEN_SHOULD_SKIP_THIS
  #define MCNLA_ALIAS0 DenseSymmetricMatrixBase
#else  // DOXYGEN_SHOULD_SKIP_THIS
  #define MCNLA_ALIAS0 DenseSymmetricMatrix
#endif  // DOXYGEN_SHOULD_SKIP_THIS

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
    public DenseMatrixWrapper<SyMatS<_Core, DenseTag, _Val, _trans, _uplo>>,
    public InvertibleWrapper<SyMatS<_Core, DenseTag, _Val, _trans, _uplo>> {

  static_assert(!isConj(_trans),    "Conjugate matrix is not supported!");
  static_assert(!isUnitDiag(_uplo), "Unit-diagonal symmetric matrix is not supported!");

 private:

  using DerivedType = SyMatS<_Core, DenseTag, _Val, _trans, _uplo>;

  friend MatrixWrapper<DerivedType>;
  friend DenseMatrixWrapper<DerivedType>;
  friend InvertibleWrapper<DerivedType>;

 public:

  static constexpr Trans trans = _trans;
  static constexpr Uplo uplo   = _uplo;

  using ValType       = _Val;
  using ValArrayType  = ArrS<_Core, _Val>;

  using VectorType    = GeVecS<_Core, DenseTag, _Val>;
  using MatrixType    = SyMatS<_Core, DenseTag, _Val, _trans, _uplo>;

  using TransposeType = SyMatS<_Core, DenseTag, _Val, changeTrans(_trans), changeUplo(_uplo)>;

  using GeneralType   = GeMatS<_Core, DenseTag, _Val, _trans>;

 private:

  using BaseType      = DenseMatrixStorage<_Core, _Val>;

 public:

  // Constructors
  inline MCNLA_ALIAS0() noexcept;
  inline MCNLA_ALIAS0( const index_t size ) noexcept;
  inline MCNLA_ALIAS0( const index_t size, const index_t pitch ) noexcept;
  inline MCNLA_ALIAS0( const index_t size, const index_t pitch, const index_t capacity ) noexcept;
  inline MCNLA_ALIAS0( const index_t size, const index_t pitch,
                                   const ValArrayType &val, const index_t offset = 0 ) noexcept;
  inline MCNLA_ALIAS0( const DenseSymmetricMatrixBase &other ) noexcept;

  // Operators
  inline DerivedType& operator=( const DenseSymmetricMatrixBase &other ) noexcept;

  // Copy
  inline DerivedType copy() const noexcept;

  // Gets information
  inline index_t size() const noexcept;
  inline index_t nnz() const noexcept;

  // Gets element
  inline ValType operator()( const index_t rowidx, const index_t colidx ) const noexcept;

  // Resizes
  template <typename ..._Args>
  inline void reconstruct( _Args... args ) noexcept;
  inline void resize( const index_t size ) noexcept;

  // Transpose/Conjugate
  inline       TransposeType& t() noexcept;
  inline const TransposeType& t() const noexcept;

  // Change view
  inline       GeneralType& full() noexcept;
  inline const GeneralType& full() const noexcept;

 protected:

  // Gets information
  inline index_t nrowImpl() const noexcept;
  inline index_t ncolImpl() const noexcept;
  inline index_t mrowImpl() const noexcept;
  inline index_t mcolImpl() const noexcept;

  MCNLA_CRTP_BASE(BaseType)
  MCNLA_CRTP_DERIVED(DerivedType)

};

}  // namespace matrix

}  // namespace mcnla

#undef MCNLA_ALIAS0

#endif  // MCNLA_CORE_MATRIX_DENSE_DENSE_SYMMETRIC_BASE_MATRIX_HH_
