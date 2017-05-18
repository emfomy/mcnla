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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense diagonal matrix base class.
///
/// @tparam  _Core  The core tag.
/// @tparam  _Val    The value type.
///
template <class _Core, typename _Val>
class DenseDiagonalMatrixBase
  : public DenseVectorStorage<_Core, _Val>,
    public MatrixWrapper<DiMatI<_Core, DenseTag, _Val>>,
    public InvertibleWrapper<DiMatI<_Core, DenseTag, _Val>> {

 private:

  using DerivedType = DiMatI<_Core, DenseTag, _Val>;

  friend MatrixWrapper<DerivedType>;
  friend InvertibleWrapper<DerivedType>;

 public:

  using ValType       = _Val;
  using ValArrayType  = ArrI<_Core, _Val>;

  using RealType      = DiMatI<_Core, DenseTag, RealValT<_Val>>;
  using ComplexType   = DiMatI<_Core, DenseTag, ComplexValT<_Val>>;

  using VectorType    = GeVecI<_Core, DenseTag, _Val>;
  using MatrixType    = DiMatI<_Core, DenseTag, _Val>;

  using TransposeType = DiMatI<_Core, DenseTag, _Val>;

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

#ifndef DOXYGEN_SHOULD_SKIP_THIS
  CRTP_BASE(BaseType);
  CRTP_DERIVED(DerivedType);
#endif  // DOXYGEN_SHOULD_SKIP_THIS

};

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_DENSE_DENSE_DIAGONAL_MATRIX_BASE_HH_
