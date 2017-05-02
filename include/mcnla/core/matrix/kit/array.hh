////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/kit/array.hh
/// @brief   The definition of value array class.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_KIT_ARRAY_HH_
#define MCNLA_CORE_MATRIX_KIT_ARRAY_HH_

#include <mcnla/core/matrix/def.hpp>
#include <mcnla/core/matrix/kit/array_base.hpp>

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
/// The value array.
///
/// @tparam  _Val  The value type.
///
template <typename _Val>
class Array : public ArrayBase<_Val> {

 private:

  using BaseType = ArrayBase<_Val>;

 protected:

  using BaseType::size_;
  using BaseType::offset_;

 public:

  // Constructors
  inline Array() noexcept;
  inline Array( const index_t size, const index_t offset = 0 ) noexcept;
  inline Array( const BaseType &ptr, const index_t size, const index_t offset = 0 ) noexcept;
  inline Array( const Array &other ) noexcept;

  // Operators
  inline Array& operator=( const Array &other ) noexcept;

  // Copy
  inline Array copy() const noexcept;

};

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_KIT_ARRAY_HH_
