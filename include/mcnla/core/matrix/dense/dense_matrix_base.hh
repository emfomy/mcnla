////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/dense/dense_matrix_base.hh
/// @brief   The definition of definition of dense matrix base class.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_DENSE_DENSE_MATRIX_BASE_HH_
#define MCNLA_CORE_MATRIX_DENSE_DENSE_MATRIX_BASE_HH_

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

#ifdef DOXYGEN_SHOULD_SKIP_THIS
template <class _Core, typename _Val, Trans _trans>
using DenseMatrixBase = DenseMatrixBase_<_Core, _Val, _trans>;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense matrix base class.
///
/// @tparam  _Core   The core tag.
/// @tparam  _Val    The value type.
/// @tparam  _trans  The transpose storage layout.
///
template <class _Core, typename _Val, Trans _trans>
#ifndef DOXYGEN_SHOULD_SKIP_THIS
class DenseMatrixBase
#else  // DOXYGEN_SHOULD_SKIP_THIS
class DenseMatrixBase_
#endif  // DOXYGEN_SHOULD_SKIP_THIS
  : public DenseMatrixStorage<_Core, _Val>,
    public DenseMatrixWrapper<GeMatT<_Core, DenseTag, _Val, _trans>>,
    public InvertibleWrapper<GeMatT<_Core, DenseTag, _Val, _trans>> {

  static_assert(!isConj(_trans), "Conjugate matrix is not supported!");

 private:

  using DerivedType = GeMatT<_Core, DenseTag, _Val, _trans>;

  friend MatrixWrapper<DerivedType>;
  friend DenseMatrixWrapper<DerivedType>;
  friend InvertibleWrapper<DerivedType>;

 public:

  static constexpr Trans trans = _trans;

  using ValType        = _Val;
  using ValArrayType   = ArrT<_Core, _Val>;
  using SizesType      = std::tuple<index_t, index_t>;

  using RealType       = GeMatT<_Core, DenseTag, RealValT<_Val>, _trans>;
  using ComplexType    = GeMatT<_Core, DenseTag, ComplexValT<_Val>, _trans>;

  using VectorType     = GeVecT<_Core, DenseTag, _Val>;
  using MatrixType     = GeMatT<_Core, DenseTag, _Val, _trans>;

  using TransposeType  = GeMatT<_Core, DenseTag, _Val, changeTrans(_trans)>;
  using ConjugateType  = GeMatT<_Core, DenseTag, _Val, changeConj(_trans)>;
  using HermitianType  = GeMatT<_Core, DenseTag, _Val, changeHerm(_trans)>;

  template <Uplo _uplo>
  using SymmetricType  = SyMatT<_Core, DenseTag, _Val, _trans, _uplo>;

  template <Uplo _uplo>
  using TriangularType = TrMatT<_Core, DenseTag, _Val, _trans, _uplo>;

  using DiagonalType   = DiMatT<_Core, DenseTag, _Val>;

 private:

  using BaseType       = DenseMatrixStorage<_Core, _Val>;

 public:

  // Constructors
  inline DenseMatrixBase() noexcept;
  inline DenseMatrixBase( const index_t nrow, const index_t ncol ) noexcept;
  inline DenseMatrixBase( const SizesType sizes ) noexcept;
  inline DenseMatrixBase( const index_t nrow, const index_t ncol, const index_t pitch ) noexcept;
  inline DenseMatrixBase( const SizesType sizes, const index_t pitch ) noexcept;
  inline DenseMatrixBase( const index_t nrow, const index_t ncol, const index_t pitch, const index_t capacity ) noexcept;
  inline DenseMatrixBase( const SizesType sizes, const index_t pitch, const index_t capacity ) noexcept;
  inline DenseMatrixBase( const index_t nrow, const index_t ncol, const index_t pitch,
                          const ValArrayType &val, const index_t offset = 0 ) noexcept;
  inline DenseMatrixBase( const DerivedType &other ) noexcept;

  // Operators
  inline DerivedType& operator=( const DerivedType &other ) noexcept;

  // Copy
  inline DerivedType copy() const noexcept;

  // Gets information
  inline index_t nnz() const noexcept;

  // Gets element
  inline       ValType& operator()( const index_t rowidx, const index_t colidx ) noexcept;
  inline const ValType& operator()( const index_t rowidx, const index_t colidx ) const noexcept;

  // Gets internal position
  inline index_t pos( const index_t rowidx, const index_t colidx ) const noexcept;

  // Resizes
  template <typename ..._Args>
  inline void reconstruct( _Args... args ) noexcept;
  inline void resize( const index_t nrow, const index_t ncol ) noexcept;
  inline void resize( const index_t nrow, const FullRange ) noexcept;
  inline void resize( const FullRange, const index_t ncol ) noexcept;

  // Transpose/Conjugate
  inline       TransposeType& t() noexcept;
  inline const TransposeType& t() const noexcept;
  inline       ConjugateType& c() noexcept;
  inline const ConjugateType& c() const noexcept;
  inline       HermitianType& h() noexcept;
  inline const HermitianType& h() const noexcept;

  // Change view
  template <Uplo _uplo = Uplo::UPPER ^ _trans>
  inline       SymmetricType<_uplo>& sym() noexcept;
  template <Uplo _uplo = Uplo::UPPER ^ _trans>
  inline const SymmetricType<_uplo>& sym() const noexcept;
  inline       SymmetricType<Uplo::UPPER>& symu() noexcept;
  inline const SymmetricType<Uplo::UPPER>& symu() const noexcept;
  inline       SymmetricType<Uplo::LOWER>& syml() noexcept;
  inline const SymmetricType<Uplo::LOWER>& syml() const noexcept;

  template <Uplo _uplo = Uplo::UPPER ^ _trans>
  inline       TriangularType<_uplo>& tri() noexcept;
  template <Uplo _uplo = Uplo::UPPER ^ _trans>
  inline const TriangularType<_uplo>& tri() const noexcept;
  inline       TriangularType<Uplo::UPPER>& triu() noexcept;
  inline const TriangularType<Uplo::UPPER>& triu() const noexcept;
  inline       TriangularType<Uplo::LOWER>& tril() noexcept;
  inline const TriangularType<Uplo::LOWER>& tril() const noexcept;

  inline       DiagonalType diag() noexcept;
  inline const DiagonalType diag() const noexcept;

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

  inline       VectorType getDiag( const index_t idx = 0 ) noexcept;
  inline const VectorType getDiag( const index_t idx = 0 ) const noexcept;
  inline       VectorType vec() noexcept;
  inline const VectorType vec() const noexcept;

 protected:

  // Gets information
  inline index_t nrowImpl() const noexcept;
  inline index_t ncolImpl() const noexcept;
  inline index_t mrowImpl() const noexcept;
  inline index_t mcolImpl() const noexcept;

  // Convert sizes to dims
  inline index_t toDim0( const SizesType sizes ) const noexcept;
  inline index_t toDim0( const index_t nrow, const index_t ncol ) const noexcept;
  inline index_t toDim1( const SizesType sizes ) const noexcept;
  inline index_t toDim1( const index_t nrow, const index_t ncol ) const noexcept;

  // Create full index range
  inline const IdxRange colfullrange() const noexcept;
  inline const IdxRange rowfullrange() const noexcept;

  MCNLA_CRTP_BASE(BaseType)
  MCNLA_CRTP_DERIVED(DerivedType)

};

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_DENSE_DENSE_MATRIX_BASE_HH_
