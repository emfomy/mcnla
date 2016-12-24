////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/dense/dense_vector_storage.hpp
/// @brief   The dense vector storage class.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_DENSE_DENSE_VECTOR_STORAGE_HPP_
#define MCNLA_CORE_MATRIX_DENSE_DENSE_VECTOR_STORAGE_HPP_

#include <mcnla/def.hpp>
#include <mcnla/core/def.hpp>
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

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Scalar> class DenseMatrixStorage;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  matrix_dense_module
/// The dense vector storage class.
///
/// @tparam  _Scalar  The scalar type.
///
template <typename _Scalar>
class DenseVectorStorage : public DenseStorage<_Scalar> {

  friend class DenseMatrixStorage<_Scalar>;

 private:

  using ScalarType        = _Scalar;
  using ValueArrayType    = Array<_Scalar>;
  using DimsType          = std::tuple<index_t>;

  using VectorStorageType = DenseVectorStorage<_Scalar>;

  using BaseType          = DenseStorage<_Scalar>;

 protected:

  /// The size in the first dimension.
  index_t dim0_;

  /// The stride.
  index_t stride_;

  using BaseType::value_;

 protected:

  // Constructors
  inline DenseVectorStorage() noexcept;
  inline DenseVectorStorage( const index_t idx0, const index_t stride = 1 ) noexcept;
  inline DenseVectorStorage( const index_t idx0, const index_t stride, const index_t capacity ) noexcept;
  inline DenseVectorStorage( const index_t idx0, const index_t stride,
                             const ValueArrayType &value, const index_t offset = 0 ) noexcept;
  inline DenseVectorStorage( const DenseVectorStorage &other ) noexcept;
  inline DenseVectorStorage( DenseVectorStorage &&other ) noexcept;

  // Operators
  inline DenseVectorStorage& operator=( const DenseVectorStorage &other ) noexcept;
  inline DenseVectorStorage& operator=( DenseVectorStorage &&other ) noexcept;

 public:

  // Gets information
  inline bool     isShrunk() const noexcept;
  inline index_t  getDim0() const noexcept;
  inline DimsType getDims() const noexcept;
  inline index_t  getStride() const noexcept;

 protected:

  // Gets element
  inline       ScalarType& getElemImpl( const index_t idx0 ) noexcept;
  inline const ScalarType& getElemImpl( const index_t idx0 ) const noexcept;

  // Gets internal position
  inline index_t getPosImpl( const index_t idx0 ) const noexcept;

  // Resizes
  inline void resizeImpl( const index_t dim0, const index_t stride ) noexcept;

  // Gets segment
  inline       VectorStorageType getVectorImpl( const IdxRange range0 ) noexcept;
  inline const VectorStorageType getVectorImpl( const IdxRange range0 ) const noexcept;

};

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_DENSE_DENSE_VECTOR_STORAGE_HPP_
