////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/dense/dense_data.hpp
/// @brief   The dense data storage.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_DENSE_DENSE_DATA_HPP_
#define MCNLA_CORE_MATRIX_DENSE_DENSE_DATA_HPP_

#include <mcnla/def.hpp>
#include <mcnla/core/def.hpp>
#include <valarray>
#include <memory>
#include <mcnla/core/matrix/kit/array.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense data storage.
///
/// @tparam  _Scalar  The scalar type.
///
template <typename _Scalar>
class DenseData {

 private:

  using ValueArrayType    = Array<_Scalar>;
  using ValueValarrayType = std::valarray<_Scalar>;

 protected:

  /// The value array.
  ValueArrayType value_;

 public:

  // Constructors
  inline DenseData() noexcept;
  inline DenseData( const index_t capability ) noexcept;
  inline DenseData( const ValueArrayType &value ) noexcept;
  inline DenseData( const DenseData &other ) noexcept;
  inline DenseData( DenseData &&other ) noexcept;

  // Operators
  inline DenseData& operator=( const DenseData &other ) noexcept;
  inline DenseData& operator=( DenseData &&other ) noexcept;
  inline void operator>>=( const index_t offset ) noexcept;
  inline void operator<<=( const index_t offset ) noexcept;
  inline       DenseData operator>>( const index_t offset ) noexcept;
  inline const DenseData operator>>( const index_t offset ) const noexcept;
  inline       DenseData operator<<( const index_t offset ) noexcept;
  inline const DenseData operator<<( const index_t offset ) const noexcept;

  // Gets data
  inline       index_t  getCapability() const noexcept;
  inline       index_t  getOffset() const noexcept;
  inline       _Scalar* getValue() noexcept;
  inline const _Scalar* getValue() const noexcept;
  inline       ValueArrayType& getValueArray() noexcept;
  inline const ValueArrayType& getValueArray() const noexcept;
  inline       ValueValarrayType& getValueValarray() noexcept;
  inline const ValueValarrayType& getValueValarray() const noexcept;

};

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_DENSE_DENSE_DATA_HPP_
