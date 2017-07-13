////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/kit/array.hpp
/// @brief   The value array.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_KIT_ARRAY_HPP_
#define MCNLA_CORE_MATRIX_KIT_ARRAY_HPP_

#include <mcnla/core/matrix/kit/array.hh>
#include <mcnla/core/utility/memory.hpp>

#ifndef DOXYGEN_SHOULD_SKIP_THIS
  #define MCNLA_TMP  ArrS<CpuTag, _Val>
  #define MCNLA_TMP0 ArrS
#else  // DOXYGEN_SHOULD_SKIP_THIS
  #define MCNLA_TMP  Array<_Val>
  #define MCNLA_TMP0 Array
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
/// @brief  Default constructor.
///
template <typename _Val>
MCNLA_TMP::MCNLA_TMP0() noexcept
  : BaseType() {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Val>
MCNLA_TMP::MCNLA_TMP0(
    const size_t size,
    const index_t offset
) noexcept
  : BaseType(std::shared_ptr<_Val>(utility::malloc<_Val>(size), utility::free<_Val>), size, offset) {
  mcnla_assert_eq(bool(size), bool(**this));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copies the array.
///
template <typename _Val>
MCNLA_TMP MCNLA_TMP::copy() const noexcept {
  MCNLA_TMP0 retval(size_, offset_);
  utility::memcpy(*retval, **this, size_);
  return retval;
}

}  // namespace matrix

}  // namespace mcnla

#undef MCNLA_TMP
#undef MCNLA_TMP0

#endif  // MCNLA_CORE_MATRIX_KIT_ARRAY_HPP_
