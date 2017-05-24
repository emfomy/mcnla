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
#include <mcnla/core/utility/crtp.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

#ifdef DOXYGEN_SHOULD_SKIP_THIS
template <class _Core, typename _Val>
using DenseDiagonalMatrixBase = DenseDiagonalMatrixBase_<_Core, _Val>;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense diagonal matrix base class.
///
/// @tparam  _Core  The core tag.
/// @tparam  _Val    The value type.
///
template <class _Core, typename _Val>
#ifndef DOXYGEN_SHOULD_SKIP_THIS
class DenseDiagonalMatrixBase
#else  // DOXYGEN_SHOULD_SKIP_THIS
class DenseDiagonalMatrixBase_
#endif  // DOXYGEN_SHOULD_SKIP_THIS
  : public DenseVectorStorage<_Core, _Val>,
    public DenseMatrixWrapper<DiMatS<_Core, DenseTag, _Val>>,
    public InvertibleWrapper<DiMatS<_Core, DenseTag, _Val>> {

 private:

  using DerivedType = DiMatS<_Core, DenseTag, _Val>;

  friend MatrixWrapper<DerivedType>;
  friend DenseMatrixWrapper<DerivedType>;
  friend InvertibleWrapper<DerivedType>;

 public:

  using ValType       = _Val;
  using ValArrayType  = ArrS<_Core, _Val>;

  using VectorType    = GeVecS<_Core, DenseTag, _Val>;
  using MatrixType    = DiMatS<_Core, DenseTag, _Val>;

  using TransposeType = DiMatS<_Core, DenseTag, _Val>;

 private:

  using BaseType      = DenseVectorStorage<_Core, _Val>;

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
  template <typename ..._Args>
  inline void reconstruct( _Args... args ) noexcept;

  // Transpose/Conjugate
  inline       TransposeType& t() noexcept;
  inline const TransposeType& t() const noexcept;

  // Changes view
  inline       VectorType& vec() noexcept;
  inline const VectorType& vec() const noexcept;

 protected:

  // Gets information
  inline index_t nrowImpl() const noexcept;
  inline index_t ncolImpl() const noexcept;
  inline index_t mrowImpl() const noexcept;
  inline index_t mcolImpl() const noexcept;

  MCNLA_CRTP_BASE(BaseType);
  MCNLA_CRTP_DERIVED(DerivedType);

};

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_DENSE_DENSE_DIAGONAL_MATRIX_BASE_HH_
