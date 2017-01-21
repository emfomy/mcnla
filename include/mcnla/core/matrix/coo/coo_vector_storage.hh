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
template <typename _Scalar> class CooMatrixStorage;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  matrix_coo_module
/// The coordinate list (COO) vector storage class.
///
/// @tparam  _Scalar  The scalar type.
///
/// @todo  Add sorting routines.
/// @todo  Add sorting attention to routines.
///
template <typename _Scalar>
class CooVectorStorage
  : public CooStorage<_Scalar>,
    public CooIdx0Storage<index_t> {

  friend class CooMatrixStorage<_Scalar>;

 private:

  using ScalarType        = _Scalar;
  using ValArrayType      = Array<_Scalar>;
  using IdxArrayType      = Array<index_t>;
  using DimsType          = std::tuple<index_t>;

  using VectorStorageType = CooVectorStorage<_Scalar>;

  using BaseType          = CooStorage<_Scalar>;
  using Base0Type      = CooIdx0Storage<index_t>;

 protected:

  /// The size in the first dimension.
  index_t dim0_;

  using BaseType::val_;
  using BaseType::nnz_;

 public:

  using BaseType::val;
  using BaseType::valPtr;

 protected:

  // Constructors
  inline CooVectorStorage() noexcept;
  inline CooVectorStorage( const index_t dim0, const index_t nnz = 0 ) noexcept;
  inline CooVectorStorage( const index_t dim0, const index_t nnz, const index_t capacity ) noexcept;
  inline CooVectorStorage( const index_t dim0, const index_t nnz,
                           const ValArrayType &val, const IdxArrayType &idx0, const index_t offset = 0 ) noexcept;
  inline CooVectorStorage( const CooVectorStorage &other ) noexcept;
  inline CooVectorStorage( CooVectorStorage &&other ) noexcept;

  // Operators
  inline CooVectorStorage& operator=( const CooVectorStorage &other ) noexcept;
  inline CooVectorStorage& operator=( CooVectorStorage &&other ) noexcept;

 public:

  // Gets information
  inline bool     isEmpty() const noexcept;
  inline index_t  dim0() const noexcept;
  inline DimsType dims() const noexcept;

 protected:

  // Gets element
  inline       ScalarType elemImpl( const index_t idx0 ) noexcept;
  inline const ScalarType elemImpl( const index_t idx0 ) const noexcept;

  // Gets internal position
  inline index_t posImpl( const index_t idx0 ) const noexcept;

  // Resizes
  inline void resizeImpl( const index_t dim0, const index_t nnz = 0 ) noexcept;

};

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_COO_COO_VECTOR_STORAGE_HH_
