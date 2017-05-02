////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/coo/coo_matrix.hh
/// @brief   The definition of definition of COO matrix class.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_COO_COO_MATRIX_HH_
#define MCNLA_CORE_MATRIX_COO_COO_MATRIX_HH_

#include <mcnla/core/matrix/def.hpp>
#include <mcnla/core/matrix/base/matrix_wrapper.hpp>
#include <mcnla/core/matrix/base/sparse_wrapper.hpp>
#include <mcnla/core/matrix/base/iterable_wrapper.hpp>
#include <mcnla/core/matrix/base/invertible_wrapper.hpp>
#include <mcnla/core/matrix/coo/coo_matrix_storage.hpp>
#include <mcnla/core/matrix/coo/coo_matrix_iterator.hpp>
#include <mcnla/core/matrix/coo/coo_vector.hpp>
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
template <typename _Val, Trans _trans> class CooMatrix;
template <typename _Val> class CooVector;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace matrix

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The traits namespace.
//
namespace traits {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The COO matrix traits.
///
template <typename _Val, Trans _trans>
struct Traits<matrix::CooMatrix<_Val, _trans>> {

  static constexpr Trans trans = _trans;

  using ValType           = _Val;

  using RealType          = matrix::CooMatrix<RealValT<_Val>, _trans>;
  using ComplexType       = matrix::CooMatrix<ComplexValT<_Val>, _trans>;

  using VectorType        = matrix::CooVector<_Val>;
  using MatrixType        = matrix::CooMatrix<_Val, _trans>;

  using IteratorType      = matrix::CooMatrixIterator<_Val, _trans>;
  using ConstIteratorType = matrix::CooMatrixConstIterator<_Val, _trans>;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The COO matrix instantiation type traits.
///
template <typename _Type>
struct IsCooMatrix : std::false_type {};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc IsCooMatrix
///
template <typename _Val, Trans _trans>
struct IsCooMatrix<matrix::CooMatrix<_Val, _trans>> : std::true_type {};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The COO matrix assert.
///
#define assertCooMatrix( Type ) \
    static_assert(traits::IsCooMatrix<Type>::value, "'"#Type"' is not a COO matrix!")

}  // namespace traits

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  matrix_coo_module
/// The coordinate list (COO) matrix class.
///
/// @tparam  _Val    The value type.
/// @tparam  _trans  The transpose storage layout.
///
template <typename _Val, Trans _trans = Trans::NORMAL>
class CooMatrix
  : public CooMatrixStorage<_Val>,
    public MatrixWrapper<CooMatrix<_Val, _trans>>,
    public SparseWrapper<CooMatrix<_Val, _trans>>,
    public IterableWrapper<CooMatrix<_Val, _trans>>,
    public InvertibleWrapper<CooMatrix<_Val, _trans>> {

  static_assert(!isConj(_trans), "Conjugate matrix is not supported!");

  friend MatrixWrapper<CooMatrix<_Val, _trans>>;
  friend SparseWrapper<CooMatrix<_Val, _trans>>;
  friend IterableWrapper<CooMatrix<_Val, _trans>>;
  friend InvertibleWrapper<CooMatrix<_Val, _trans>>;

 public:

  static constexpr Trans trans = _trans;

  using ValType           = _Val;
  using ValArrayType      = Array<_Val>;
  using IdxArrayType      = Array<index_t>;
  using SizesType         = std::tuple<index_t, index_t>;

  using RealType          = CooMatrix<RealValT<_Val>, _trans>;
  using ComplexType       = CooMatrix<ComplexValT<_Val>, _trans>;

  using VectorType        = CooVector<_Val>;
  using MatrixType        = CooMatrix<_Val, _trans>;

  using TransposeType     = CooMatrix<_Val, changeTrans(_trans)>;
  using ConjugateType     = CooMatrix<_Val, changeConj(_trans)>;
  using HermitianType     = CooMatrix<_Val, changeHerm(_trans)>;

  using IteratorType      = CooMatrixIterator<_Val, _trans>;
  using ConstIteratorType = CooMatrixConstIterator<_Val, _trans>;

 private:

  using BaseType          = CooMatrixStorage<_Val>;

 public:

  // Constructors
  inline CooMatrix() noexcept;
  inline CooMatrix( const index_t nrow, const index_t ncol, const index_t nnz = 0 ) noexcept;
  inline CooMatrix( const SizesType sizes, const index_t nnz = 0 ) noexcept;
  inline CooMatrix( const index_t nrow, const index_t ncol, const index_t nnz, const index_t capacity ) noexcept;
  inline CooMatrix( const SizesType sizes, const index_t nnz, const index_t capacity ) noexcept;
  inline CooMatrix( const index_t nrow, const index_t ncol, const index_t nnz, const ValArrayType &val,
                    const IdxArrayType &idx0, const IdxArrayType &idx1, const index_t offset = 0 ) noexcept;
  inline CooMatrix( const CooMatrix &other ) noexcept;

  // Operators
  inline CooMatrix& operator=( const CooMatrix &other ) noexcept;

  // Copy
  inline CooMatrix copy() const noexcept;

  // Gets information
  inline index_t rowidxCapacity() const noexcept;
  inline index_t colidxCapacity() const noexcept;
  inline index_t rowidxOffset() const noexcept;
  inline index_t colidxOffset() const noexcept;

  // Gets array
  inline       IdxArrayType& rowidx() noexcept;
  inline const IdxArrayType& rowidx() const noexcept;
  inline       IdxArrayType& colidx() noexcept;
  inline const IdxArrayType& colidx() const noexcept;
  inline       index_t* rowidxPtr() noexcept;
  inline const index_t* rowidxPtr() const noexcept;
  inline       index_t* colidxPtr() noexcept;
  inline const index_t* colidxPtr() const noexcept;

  // Gets element
  inline       ValType operator()( const index_t rowidx, const index_t colidx ) noexcept;
  inline const ValType operator()( const index_t rowidx, const index_t colidx ) const noexcept;

  // Gets internal position
  inline index_t pos( const index_t rowidx, const index_t colidx ) const noexcept;

  // Resizes
  template <typename... Args>
  inline void reconstruct( Args... args ) noexcept;
  inline void resize( const index_t nrow, const index_t ncol, const index_t nnz ) noexcept;

  // Transpose/Conjugate
  inline       TransposeType& t() noexcept;
  inline const TransposeType& t() const noexcept;
  inline       ConjugateType& c() noexcept;
  inline const ConjugateType& c() const noexcept;
  inline       HermitianType& h() noexcept;
  inline const HermitianType& h() const noexcept;

  // Gets vector segment
  inline       VectorType operator()( const FullRange, const index_t colidx ) noexcept;
  inline const VectorType operator()( const FullRange, const index_t colidx ) const noexcept;
  inline       VectorType operator()( const index_t rowidx, const FullRange ) noexcept;
  inline const VectorType operator()( const index_t rowidx, const FullRange ) const noexcept;

 protected:

  // Gets information
  inline index_t nrowImpl() const noexcept;
  inline index_t ncolImpl() const noexcept;

  // Convert sizes to dims
  inline index_t toDim0( const SizesType sizes ) const noexcept;
  inline index_t toDim0( const index_t nrow, const index_t ncol ) const noexcept;
  inline index_t toDim1( const SizesType sizes ) const noexcept;
  inline index_t toDim1( const index_t nrow, const index_t ncol ) const noexcept;

  // Convert index array
  inline       IdxArrayType& toIdx0(       IdxArrayType &rowidx,       IdxArrayType &colidx ) const noexcept;
  inline const IdxArrayType& toIdx0( const IdxArrayType &rowidx, const IdxArrayType &colidx ) const noexcept;
  inline       IdxArrayType& toIdx1(       IdxArrayType &rowidx,       IdxArrayType &colidx ) const noexcept;
  inline const IdxArrayType& toIdx1( const IdxArrayType &rowidx, const IdxArrayType &colidx ) const noexcept;

  // Gets base class
  inline       BaseType& base() noexcept;
  inline const BaseType& base() const noexcept;

};

/// @ingroup  matrix_coo_module
template <typename _Val>
using CooMatrixColMajor = CooMatrix<_Val, Trans::NORMAL>;

/// @ingroup  matrix_coo_module
template <typename _Val>
using CooMatrixRowMajor = CooMatrix<_Val, Trans::TRANS>;

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_COO_COO_MATRIX_HH_
