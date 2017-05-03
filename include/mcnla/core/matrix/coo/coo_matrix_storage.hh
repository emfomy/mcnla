////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/coo/coo_matrix_storage.hh
/// @brief   The definition of COO matrix storage class.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_COO_COO_MATRIX_STORAGE_HH_
#define MCNLA_CORE_MATRIX_COO_COO_MATRIX_STORAGE_HH_

#include <mcnla/core/matrix/coo/def.hpp>
#include <tuple>
#include <mcnla/core/matrix/coo/coo_storage.hpp>
#include <mcnla/core/matrix/coo/coo_idx0_storage.hpp>
#include <mcnla/core/matrix/coo/coo_idx1_storage.hpp>
#include <mcnla/core/matrix/coo/coo_vector_storage.hpp>
#include <mcnla/core/matrix/kit/idx_range.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The The coordinate list (COO) matrix storage class.
///
/// @tparam  _Val     The value type.
/// @tparam  _ArrayT  The array template.
///
/// @todo  Add sorting routines.
/// @todo  Add sorting attention to routines.
///
template <typename _Val, template <typename> class _ArrayT>
class CooMatrixStorage
  : public CooStorage<_Val, _ArrayT>,
    public CooIdx0Storage<index_t, _ArrayT>,
    public CooIdx1Storage<index_t, _ArrayT> {

 private:

  using ValType           = _Val;
  using ValArrayType      = _ArrayT<_Val>;
  using IdxArrayType      = _ArrayT<index_t>;
  using DimsType          = std::tuple<index_t, index_t>;

  using VectorStorageType = CooVectorStorage<_Val, _ArrayT>;
  using MatrixStorageType = CooMatrixStorage<_Val, _ArrayT>;

  using BaseType          = CooStorage<_Val, _ArrayT>;
  using Base0Type         = CooIdx0Storage<index_t, _ArrayT>;
  using Base1Type         = CooIdx1Storage<index_t, _ArrayT>;

 protected:

  /// The size in the first dimension.
  index_t dim0_;

  /// The size in the second dimension.
  index_t dim1_;

  using BaseType::val_;
  using BaseType::nnz_;

 public:

  using BaseType::val;
  using BaseType::valPtr;
  using Base0Type::idx0;
  using Base0Type::idx0Ptr;
  using Base1Type::idx1;
  using Base1Type::idx1Ptr;

 protected:

  // Constructors
  inline CooMatrixStorage() noexcept;
  inline CooMatrixStorage( const index_t dim0, const index_t dim1, const index_t nnz = 0 ) noexcept;
  inline CooMatrixStorage( const index_t dim0, const index_t dim1, const index_t nnz, const index_t capacity ) noexcept;
  inline CooMatrixStorage( const index_t dim0, const index_t dim1, const index_t nnz, const ValArrayType &val,
                           const IdxArrayType &idx0, const IdxArrayType &idx1, const index_t offset = 0 ) noexcept;
  inline CooMatrixStorage( const CooMatrixStorage &other ) noexcept;

  // Operators
  inline CooMatrixStorage& operator=( const CooMatrixStorage &other ) noexcept;

 public:

  // Gets information
  inline bool     isEmpty() const noexcept;
  inline bool     isSquare() const noexcept;
  inline index_t  dim0() const noexcept;
  inline index_t  dim1() const noexcept;
  inline DimsType dims() const noexcept;

 protected:

  // Gets element
  inline       ValType elemImpl( const index_t idx0, const index_t idx1 ) noexcept;
  inline const ValType elemImpl( const index_t idx0, const index_t idx1 ) const noexcept;

  // Gets internal position
  inline index_t posImpl( const index_t idx0, const index_t idx1 ) const noexcept;
  inline void posImpl( const index_t idx1, index_t &pos, index_t &nnz ) const noexcept;

  // Resizes
  inline void resizeImpl( const index_t dim0, const index_t dim1, const index_t nnz ) noexcept;

  // Gets vector segment
  inline       VectorStorageType getVector0Impl( const index_t idx1 ) noexcept;
  inline const VectorStorageType getVector0Impl( const index_t idx1 ) const noexcept;

};

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_COO_COO_MATRIX_STORAGE_HH_
