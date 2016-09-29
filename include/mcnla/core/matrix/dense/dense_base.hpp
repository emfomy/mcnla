////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/dense/dense_base.hpp
/// @brief   The dense container interface.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_DENSE_DENSE_BASE_HPP_
#define MCNLA_CORE_MATRIX_DENSE_DENSE_BASE_HPP_

#include <mcnla/def.hpp>
#include <mcnla/core/def.hpp>
#include <mcnla/core/utility/traits.hpp>
#include <mcnla/core/matrix/dense/dense_data.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The interface of dense container.
///
/// @tparam  _Derived  The derived type.
///
template <class _Derived>
class DenseBase {

 private:

  using ScalarType   = typename traits::Traits<_Derived>::ScalarType;
  using ValuePtrType = std::shared_ptr<std::valarray<ScalarType>>;
  using DataType     = DenseData<ScalarType>;

 protected:

  /// The offset of starting position.
  index_t offset_;

  /// The data storage
  DataType data_;

 protected:

  // Constructors
  inline DenseBase() noexcept;
  inline DenseBase( const index_t capability, const index_t offset = 0 ) noexcept;
  inline DenseBase( const ValuePtrType &value, const index_t offset = 0 ) noexcept;
  inline DenseBase( const DataType &data, const index_t offset = 0 ) noexcept;
  inline DenseBase( const DenseBase &other ) noexcept;
  inline DenseBase( DenseBase &&other ) noexcept;

  // Operators
  inline DenseBase& operator=( const DenseBase &other ) noexcept;
  inline DenseBase& operator=( DenseBase &&other ) noexcept;

 public:

  // Gets information
  inline index_t getCapability() const noexcept;
  inline index_t getOffset() const noexcept;

  // Gets data storage
  inline DataType& getData() noexcept;
  inline const DataType& getData() const noexcept;

  // Gets value array
  inline ScalarType* getValue() noexcept;
  inline const ScalarType* getValue() const noexcept;

};

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_DENSE_DENSE_BASE_HPP_
