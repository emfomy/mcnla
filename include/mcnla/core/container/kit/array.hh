////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/container/kit/array.hh
/// @brief   The definition of raw array class.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_CONTAINER_KIT_ARRAY_HH_
#define MCNLA_CORE_CONTAINER_KIT_ARRAY_HH_

#include <mcnla/def.hpp>
#include <mcnla/core/def.hpp>
#include <valarray>
#include <memory>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The container namespace.
//
namespace container {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  container_module
/// The array.
///
template <typename _Type>
class Array : public std::shared_ptr<std::valarray<_Type>> {

 private:

  using BaseType = std::shared_ptr<std::valarray<_Type>>;

 protected:

  // The offset.
  index_t offset_;

  /// The empty array pointer.
  static const BaseType kNullPtr;

 public:

  // Constructors
  inline Array() noexcept;
  inline Array( const index_t size, const index_t offset = 0 ) noexcept;
  inline Array( const BaseType &ptr, const index_t offset = 0 ) noexcept;
  inline Array( const Array &other ) noexcept;
  inline Array( Array &&other ) noexcept;

  // Operators
  inline Array& operator=( const Array &other ) noexcept;
  inline Array& operator=( Array &&other ) noexcept;
  inline void operator>>=( const index_t offset ) noexcept;
  inline void operator<<=( const index_t offset ) noexcept;
  inline       Array operator>>( const index_t offset ) noexcept;
  inline const Array operator>>( const index_t offset ) const noexcept;
  inline       Array operator<<( const index_t offset ) noexcept;
  inline const Array operator<<( const index_t offset ) const noexcept;

  // Gets information
  inline bool    isEmpty() const noexcept;
  inline index_t size() const noexcept;
  inline index_t capacity() const noexcept;
  inline index_t offset() const noexcept;

  // Gets data
  inline       _Type* operator*() noexcept;
  inline const _Type* operator*() const noexcept;
  inline       _Type& operator[]( const index_t idx ) noexcept;
  inline const _Type& operator[]( const index_t idx ) const noexcept;

  // Gets Valarray
  inline       std::valarray<_Type>& valarray() noexcept;
  inline const std::valarray<_Type>& valarray() const noexcept;

};

template <typename _Type>
const typename Array<_Type>::BaseType Array<_Type>::kNullPtr = std::make_shared<std::valarray<_Type>>();

}  // namespace container

}  // namespace mcnla

#endif  // MCNLA_CORE_CONTAINER_KIT_ARRAY_HH_
