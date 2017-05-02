////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/kit/array_base.hh
/// @brief   The definition of base array class.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_KIT_ARRAY_BASE_HH_
#define MCNLA_CORE_MATRIX_KIT_ARRAY_BASE_HH_

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
/// The base array.
///
/// @tparam  _Val  The value type.
///
template <typename _Val>
class ArrayBase : public std::shared_ptr<_Val> {

 private:

  using BaseType = std::shared_ptr<_Val>;

 protected:

  // The size.
  index_t size_;

  // The offset.
  index_t offset_;

 protected:

  // Constructors
  inline ArrayBase() noexcept;
  inline ArrayBase( const BaseType &ptr, const index_t size, const index_t offset = 0 ) noexcept;
  inline ArrayBase( const ArrayBase &other ) noexcept;

  // Operators
  inline ArrayBase& operator=( const ArrayBase &other ) noexcept;

 public:

  // Operators
  inline void operator>>=( const index_t offset ) noexcept;
  inline void operator<<=( const index_t offset ) noexcept;
  inline       ArrayBase operator>>( const index_t offset ) noexcept;
  inline const ArrayBase operator>>( const index_t offset ) const noexcept;
  inline       ArrayBase operator<<( const index_t offset ) noexcept;
  inline const ArrayBase operator<<( const index_t offset ) const noexcept;

  // Copy
  inline ArrayBase copy() const noexcept;

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

#endif  // MCNLA_CORE_MATRIX_KIT_ARRAY_BASE_HH_
