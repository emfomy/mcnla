////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/kit/array.hh
/// @brief   The definition of value array class.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_KIT_ARRAY_HH_
#define MCNLA_CORE_MATRIX_KIT_ARRAY_HH_

#include <mcnla/core/matrix/kit/def.hpp>
#include <mcnla/core/matrix/kit/array_base.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The traits namespace.
//
namespace traits {

MCNLA_ARR_TRAITS_DEF(CpuTag, matrix::Array)

}  // namespace traits

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  matrix_kit_module
/// The value array.
///
/// @tparam  _Val  The value type.
///
template <typename _Val>
class Array : public ArrayBase<CpuTag, _Val> {

 private:

  using BaseType = ArrayBase<CpuTag, _Val>;

 protected:

  using BaseType::size_;
  using BaseType::offset_;

 public:

  using BaseType::ArrayBase;

  // Constructors
  inline Array() noexcept;
  inline Array( const index_t size, const index_t offset = 0 ) noexcept;

  // Copy
  inline Array<_Val> copy() const noexcept;

};

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_KIT_ARRAY_HH_
