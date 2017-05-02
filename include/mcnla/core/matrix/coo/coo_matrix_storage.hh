////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/coo/coo_matrix_storage.hh
/// @brief   The definition of COO matrix storage class.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_COO_COO_MATRIX_STORAGE_HH_
#define MCNLA_CORE_MATRIX_COO_COO_MATRIX_STORAGE_HH_

#include <mcnla/core/matrix/def.hpp>
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
/// @tparam  _Val  The value type.
///
/// @todo  Add sorting routines.
/// @todo  Add sorting attention to routines.
///
template <typename _Val, template <typename> class _Array = Array>
class CooMatrixStorage
  : public CooStorage<_Val, _Array>,
    public CooIdx0Storage<index_t, _Array>,
    public CooIdx1Storage<index_t, _Array> {

 private:

  using ValType           = _Val;
  using ValArrayType      = _Array<_Val>;
  using IdxArrayType      = _Array<index_t>;
  using DimsType          = std::tuple<index_t, index_t>;

  using VectorStorageType = CooVectorStorage<_Val, _Array>;
  using MatrixStorageType = CooMatrixStorage<_Val, _Array>;

  using BaseType          = CooStorage<_Val, _Array>;
  using Base0Type         = CooIdx0Storage<index_t, _Array>;
  using Base1Type         = CooIdx1Storage<index_t, _Array>;

 protected:

  /// The size in the first dimension.
  index_t dim0_;

  /// The size in the second dimension.
  index_t dim1_;

  using BaseType::val_;
  using BaseType::nnz_;

 public:

  using BaseType::val;
  using BaseType::idx0;
  using BaseType::idx1;
  using BaseType::valPtr;
  using BaseType::idx0Ptr;
  using BaseType::idx1Ptr;

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
