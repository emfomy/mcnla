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
  #define MCNLA_TMP ArrS<CpuTag, _Val>
#else  // DOXYGEN_SHOULD_SKIP_THIS
  #define MCNLA_TMP Array<_Val>
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
MCNLA_TMP::ArrS() noexcept
  : BaseType() {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Val>
MCNLA_TMP::ArrS(
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
ArrS<CpuTag, _Val> MCNLA_TMP::copy() const noexcept {
  ArrS retval(size_, offset_);
  utility::memcpy(*retval, **this, size_);
  return retval;
}

}  // namespace matrix

}  // namespace mcnla

#undef MCNLA_TMP

#endif  // MCNLA_CORE_MATRIX_KIT_ARRAY_HPP_
