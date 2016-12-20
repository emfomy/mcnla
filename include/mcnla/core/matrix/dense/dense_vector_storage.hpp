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
#include <mcnla/core/matrix/dense/dense_storage.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  matrix_dense_module
/// The dense vector storage class.
///
/// @tparam  _Scalar  The scalar type.
///
template <typename _Scalar>
class DenseVectorStorage : public DenseStorage<_Scalar> {

 private:

  using ScalarType     = _Scalar;
  using ValueArrayType = Array<ScalarType>;

 private:

  using BaseType       = DenseStorage<_Scalar>;

 protected:

  /// The size of the first dimension.
  index_t size0_;

  /// The stride.
  index_t stride_;

  using BaseType::value_;

 public:

  // Constructors
  inline DenseVectorStorage() noexcept;
  inline DenseVectorStorage( const index_t size0, const index_t stride = 1 ) noexcept;
  inline DenseVectorStorage( const index_t size0, const index_t stride, const index_t capacity ) noexcept;
  inline DenseVectorStorage( const index_t size0, const index_t stride,
                             const ValueArrayType &value, const index_t offset = 0 ) noexcept;
  inline DenseVectorStorage( const DenseVectorStorage &other ) noexcept;
  inline DenseVectorStorage( DenseVectorStorage &&other ) noexcept;

  // Operators
  inline DenseVectorStorage& operator=( const DenseVectorStorage &other ) noexcept;
  inline DenseVectorStorage& operator=( DenseVectorStorage &&other ) noexcept;

  // Gets information
  inline bool    isShrunk() const noexcept;
  inline index_t getSize0() const noexcept;
  inline index_t getStride() const noexcept;

  // Gets element
  inline       ScalarType& getElem( const index_t idx0 ) noexcept;
  inline const ScalarType& getElem( const index_t idx0 ) const noexcept;
  inline       ScalarType& operator()( const index_t idx0 ) noexcept;
  inline const ScalarType& operator()( const index_t idx0 ) const noexcept;

  // Gets internal position
  inline index_t getPos( const index_t idx0 ) const noexcept;

};

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_DENSE_DENSE_VECTOR_STORAGE_HPP_
