////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/dense/dense_matrix_storage.hpp
/// @brief   The dense matrix storage class.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_DENSE_DENSE_MATRIX_STORAGE_HPP_
#define MCNLA_CORE_MATRIX_DENSE_DENSE_MATRIX_STORAGE_HPP_

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
/// The dense matrix storage class.
///
/// @tparam  _Scalar  The scalar type.
///
template <typename _Scalar>
class DenseMatrixStorage : public DenseStorage<_Scalar> {

 private:

  using ScalarType     = _Scalar;
  using ValueArrayType = Array<ScalarType>;

 private:

  using BaseType       = DenseStorage<_Scalar>;

 protected:

  /// The size of the first dimension.
  index_t size0_;

  /// The size of the second dimension.
  index_t size1_;

  /// The leading dimension.
  index_t pitch0_;

  /// The stride.
  index_t stride_;

  using BaseType::value_;

 public:

  // Constructors
  inline DenseMatrixStorage() noexcept;
  inline DenseMatrixStorage( const index_t size0, const index_t size1 ) noexcept;
  inline DenseMatrixStorage( const index_t size0, const index_t size1, const index_t pitch0 ) noexcept;
  inline DenseMatrixStorage( const index_t size0, const index_t size1, const index_t pitch0, const index_t capacity ) noexcept;
  inline DenseMatrixStorage( const index_t size0, const index_t size1, const index_t pitch0,
                             const ValueArrayType &value, const index_t offset = 0 ) noexcept;
  inline DenseMatrixStorage( const DenseMatrixStorage &other ) noexcept;
  inline DenseMatrixStorage( DenseMatrixStorage &&other ) noexcept;

  // Operators
  inline DenseMatrixStorage& operator=( const DenseMatrixStorage &other ) noexcept;
  inline DenseMatrixStorage& operator=( DenseMatrixStorage &&other ) noexcept;

  // Gets information
  inline bool    isShrunk() const noexcept;
  inline bool    isSquare() const noexcept;
  inline index_t getSize0() const noexcept;
  inline index_t getSize1() const noexcept;
  inline index_t getPitch0() const noexcept;

  // Gets element
  inline       ScalarType& getElem( const index_t idx0, const index_t idx1 ) noexcept;
  inline const ScalarType& getElem( const index_t idx0, const index_t idx1 ) const noexcept;
  inline       ScalarType& operator()( const index_t idx0, const index_t idx1 ) noexcept;
  inline const ScalarType& operator()( const index_t idx0, const index_t idx1 ) const noexcept;

  // Gets internal position
  inline index_t getPos( const index_t idx0, const index_t idx1 ) const noexcept;

};

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_DENSE_DENSE_MATRIX_STORAGE_HPP_
