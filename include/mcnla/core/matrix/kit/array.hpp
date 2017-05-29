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
ArrS<CpuTag, _Val>::ArrS() noexcept
  : BaseType() {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Val>
ArrS<CpuTag, _Val>::ArrS(
    const index_t size,
    const index_t offset
) noexcept
  : BaseType(std::shared_ptr<_Val>(utility::malloc<_Val>(size), utility::free<_Val>), size, offset) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copies the array.
///
template <typename _Val>
ArrS<CpuTag, _Val> ArrS<CpuTag, _Val>::copy() const noexcept {
  ArrS retval(size_, offset_);
  utility::memcpy(*retval, **this, size_);
  return retval;
}

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_KIT_ARRAY_HPP_
