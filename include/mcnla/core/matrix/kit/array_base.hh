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
#include <mcnla/core/utility/crtp.hpp>

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
/// @tparam  _Val       The value type.
/// @tparam  _DerivedT  The derived template.
///
template <class _Derived, typename _Val>
class ArrayBase
  : public std::shared_ptr<_Val>,
    public utility::CrtpBase<_Derived, ArrayBase<_Derived, _Val>> {

 private:

  using DerivedType = _Derived;
  using BaseType    = std::shared_ptr<_Val>;

 protected:

  // The size.
  index_t size_;

  // The offset.
  index_t offset_;

 public:

  // Constructors
  inline ArrayBase() noexcept;
  inline ArrayBase( const BaseType &ptr, const index_t size, const index_t offset = 0 ) noexcept;
  inline ArrayBase( const DerivedType &other ) noexcept;

  // Operators
  inline       DerivedType& operator=( const DerivedType &other ) noexcept;
  inline       DerivedType& operator>>=( const index_t offset ) noexcept;
  inline       DerivedType& operator<<=( const index_t offset ) noexcept;
  inline       DerivedType  operator>>( const index_t offset ) noexcept;
  inline const DerivedType  operator>>( const index_t offset ) const noexcept;
  inline       DerivedType  operator<<( const index_t offset ) noexcept;
  inline const DerivedType  operator<<( const index_t offset ) const noexcept;

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
