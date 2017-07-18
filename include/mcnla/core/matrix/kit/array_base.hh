////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/kit/array_base.hh
/// @brief   The definition of base array class.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_KIT_ARRAY_BASE_HH_
#define MCNLA_CORE_MATRIX_KIT_ARRAY_BASE_HH_

#include <mcnla/core/matrix/kit/def.hpp>
#include <memory>
#include <mcnla/core/utility/crtp.hpp>

#ifndef DOXYGEN_SHOULD_SKIP_THIS
  #define MCNLA_ALIAS0 ArrayBase
#else  // DOXYGEN_SHOULD_SKIP_THIS
  #define MCNLA_ALIAS0 Array
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The base array.
///
/// @tparam  _Core  The core tag.
/// @tparam  _Val   The value type.
///
template <class _Core, typename _Val>
class ArrayBase
  : public std::shared_ptr<_Val> {

 private:

  using DerivedType = ArrS<_Core, _Val>;
  using BaseType    = std::shared_ptr<_Val>;

 protected:

  // The size.
  index_t size_;

  // The offset.
  index_t offset_;

 public:

  // Constructors
  inline MCNLA_ALIAS0() noexcept;
  inline MCNLA_ALIAS0( const BaseType &ptr, const index_t size, const index_t offset = 0 ) noexcept;
  inline MCNLA_ALIAS0( const ArrayBase &other ) noexcept;

  // Operators
  inline       DerivedType& operator=( const ArrayBase &other ) noexcept;
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

 protected:

  MCNLA_CRTP_DERIVED(DerivedType)

};

}  // namespace matrix

}  // namespace mcnla

#undef MCNLA_ALIAS0

#endif  // MCNLA_CORE_MATRIX_KIT_ARRAY_BASE_HH_
