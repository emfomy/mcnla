////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/kit/array.hh
/// @brief   The definition of raw array class.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_KIT_ARRAY_HH_
#define MCNLA_CORE_MATRIX_KIT_ARRAY_HH_

#include <mcnla/core/matrix/def.hpp>
#include <memory>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  matrix_module
/// The array.
///
/// @tparam  _Val  The value type.
///
template <typename _Val>
class Array : public std::shared_ptr<_Val> {

 private:

  using BaseType = std::shared_ptr<_Val>;

 protected:

  // The size.
  index_t size_;

  // The offset.
  index_t offset_;

 public:

  // Constructors
  inline Array() noexcept;
  inline Array( const index_t size, const index_t offset = 0 ) noexcept;
  inline Array( const BaseType &ptr, const index_t size, const index_t offset = 0 ) noexcept;
  inline Array( const Array &other ) noexcept;

  // Operators
  inline Array& operator=( const Array &other ) noexcept;
  inline void operator>>=( const index_t offset ) noexcept;
  inline void operator<<=( const index_t offset ) noexcept;
  inline       Array operator>>( const index_t offset ) noexcept;
  inline const Array operator>>( const index_t offset ) const noexcept;
  inline       Array operator<<( const index_t offset ) noexcept;
  inline const Array operator<<( const index_t offset ) const noexcept;

  // Copy
  inline Array copy() const noexcept;

  // Gets information
  inline bool    isEmpty() const noexcept;
  inline index_t size() const noexcept;
  inline index_t capacity() const noexcept;
  inline index_t offset() const noexcept;

  // Gets data
  inline       _Val* operator*() noexcept;
  inline const _Val* operator*() const noexcept;
  inline       _Val& operator[]( const index_t idx ) noexcept;
  inline const _Val& operator[]( const index_t idx ) const noexcept;

};

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_KIT_ARRAY_HH_
