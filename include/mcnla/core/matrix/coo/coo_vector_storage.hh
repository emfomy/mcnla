////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/coo/coo_vector_storage.hh
/// @brief   The definition of COO vector storage class.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_COO_COO_VECTOR_STORAGE_HH_
#define MCNLA_CORE_MATRIX_COO_COO_VECTOR_STORAGE_HH_

#include <mcnla/core/matrix/coo/def.hpp>
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
template <class _Core, typename _Val> class CooMatrixStorage;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The coordinate list (COO) vector storage class.
///
/// @tparam  _Val     The value type.
/// @tparam  _ArrayT  The array template.
///
/// @todo  Add sorting routines.
/// @todo  Add sorting attention to routines.
///
template <class _Core, typename _Val>
class CooVectorStorage
  : public CooStorage<_Core, _Val>,
    public CooIdx0Storage<_Core, index_t> {

  friend class CooMatrixStorage<_Core, _Val>;

 private:

  using ValType           = _Val;
  using ValArrayType      = ArrI<_Core, _Val>;
  using IdxArrayType      = ArrI<_Core, index_t>;
  using DimsType          = std::tuple<index_t>;

  using VectorStorageType = CooVectorStorage<_Core, _Val>;

  using BaseType          = CooStorage<_Core, _Val>;
  using Base0Type         = CooIdx0Storage<_Core, index_t>;

 protected:

  /// The size in the first dimension.
  index_t dim0_;

  using BaseType::val_;
  using BaseType::nnz_;

 public:

  using BaseType::val;
  using BaseType::valPtr;
  using Base0Type::idx0;
  using Base0Type::idx0Ptr;

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
