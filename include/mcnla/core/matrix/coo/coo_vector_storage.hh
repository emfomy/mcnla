////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/coo/coo_vector_storage.hh
/// @brief   The definition of COO vector storage class.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_COO_COO_VECTOR_STORAGE_HH_
#define MCNLA_CORE_MATRIX_COO_COO_VECTOR_STORAGE_HH_

#include <mcnla/core/matrix/def.hpp>
#include <tuple>
#include <mcnla/core/matrix/coo/coo_storage.hpp>
#include <mcnla/core/matrix/coo/coo_idx0_storage.hpp>
#include <mcnla/core/matrix/kit/idx_range.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Val, template <typename> class _Array> class CooMatrixStorage;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The coordinate list (COO) vector storage class.
///
/// @tparam  _Val    The value type.
/// @tparam  _Array  The array template.
///
/// @todo  Add sorting routines.
/// @todo  Add sorting attention to routines.
///
template <typename _Val, template <typename> class _Array = Array>
class CooVectorStorage
  : public CooStorage<_Val, _Array>,
    public CooIdx0Storage<index_t, _Array> {

  friend class CooMatrixStorage<_Val, _Array>;

 private:

  using ValType           = _Val;
  using ValArrayType      = _Array<_Val>;
  using IdxArrayType      = _Array<index_t>;
  using DimsType          = std::tuple<index_t>;

  using VectorStorageType = CooVectorStorage<_Val, _Array>;

  using BaseType          = CooStorage<_Val, _Array>;
  using Base0Type         = CooIdx0Storage<index_t, _Array>;

 protected:

  /// The size in the first dimension.
  index_t dim0_;

  using BaseType::val_;
  using BaseType::nnz_;

 public:

  using BaseType::val;
  using BaseType::idx0;
  using BaseType::valPtr;
  using BaseType::idx0Ptr;

 protected:

  // Constructors
  inline CooVectorStorage() noexcept;
  inline CooVectorStorage( const index_t dim0, const index_t nnz = 0 ) noexcept;
  inline CooVectorStorage( const index_t dim0, const index_t nnz, const index_t capacity ) noexcept;
  inline CooVectorStorage( const index_t dim0, const index_t nnz,
                           const ValArrayType &val, const IdxArrayType &idx0, const index_t offset = 0 ) noexcept;
  inline CooVectorStorage( const CooVectorStorage &other ) noexcept;

  // Operators
  inline CooVectorStorage& operator=( const CooVectorStorage &other ) noexcept;

 public:

  // Gets information
  inline bool     isEmpty() const noexcept;
  inline index_t  dim0() const noexcept;
  inline DimsType dims() const noexcept;

 protected:

  // Gets element
  inline       ValType elemImpl( const index_t idx0 ) noexcept;
  inline const ValType elemImpl( const index_t idx0 ) const noexcept;

  // Gets internal position
  inline index_t posImpl( const index_t idx0 ) const noexcept;

  // Resizes
  inline void resizeImpl( const index_t dim0, const index_t nnz = 0 ) noexcept;

};

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_COO_COO_VECTOR_STORAGE_HH_
