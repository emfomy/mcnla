////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/dense/dense_vector_storage.hh
/// @brief   The definition of dense vector storage class.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_DENSE_DENSE_VECTOR_STORAGE_HH_
#define MCNLA_CORE_MATRIX_DENSE_DENSE_VECTOR_STORAGE_HH_

#include <mcnla/core/matrix/dense/def.hpp>
#include <tuple>
#include <mcnla/core/matrix/dense/dense_storage.hpp>
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
/// The dense vector storage class.
///
/// @tparam  _Core  The core tag.
/// @tparam  _Val   The value type.
///
template <class _Core, typename _Val>
class DenseVectorStorage : public DenseStorage<_Core, _Val> {

  friend DenseMatrixStorage<_Core, _Val>;

 private:

  using ValType           = _Val;
  using ValArrayType      = ArrS<_Core, _Val>;
  using DimsType          = std::tuple<index_t>;

  using VectorStorageType = DenseVectorStorage<_Core, _Val>;

  using BaseType          = DenseStorage<_Core, _Val>;

 protected:

  /// The size in the first dimension.
  index_t dim0_;

  /// The number of positions between successive elements
  index_t stride_;

  using BaseType::val_;

 protected:

  // Constructors
  inline DenseVectorStorage() noexcept;
  inline DenseVectorStorage( const index_t dim0, const index_t stride = 1 ) noexcept;
  inline DenseVectorStorage( const index_t dim0, const index_t stride, const index_t capacity ) noexcept;
  inline DenseVectorStorage( const index_t dim0, const index_t stride,
                             const ValArrayType &val, const index_t offset = 0 ) noexcept;
  inline DenseVectorStorage( const DenseVectorStorage &other ) noexcept;

  // Operators
  inline DenseVectorStorage& operator=( const DenseVectorStorage &other ) noexcept;

 public:

  // Gets information
  inline bool     isShrunk() const noexcept;
  inline index_t  dim0() const noexcept;
  inline index_t  mdim0() const noexcept;
  inline DimsType dims() const noexcept;
  inline DimsType mdims() const noexcept;
  inline index_t  stride() const noexcept;

 protected:

  // Gets element
  inline       ValType& elemImpl( const index_t idx0 ) noexcept;
  inline const ValType& elemImpl( const index_t idx0 ) const noexcept;

  // Gets internal position
  inline index_t posImpl( const index_t idx0 ) const noexcept;

  // Resizes
  inline void resizeImpl( const index_t dim0 ) noexcept;

  // Gets segment
  inline       VectorStorageType getVectorImpl( const IdxRange &range0 ) noexcept;
  inline const VectorStorageType getVectorImpl( const IdxRange &range0 ) const noexcept;

};

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_DENSE_DENSE_VECTOR_STORAGE_HH_
