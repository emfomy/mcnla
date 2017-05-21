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
/// @ingroup  matrix_kit_module
/// The value array.
///
/// @tparam  _Val  The value type.
///
template <typename _Val>
class ArrI<CpuTag, _Val> : public ArrayBase<CpuTag, _Val> {

 private:

  using BaseType = ArrayBase<CpuTag, _Val>;

 protected:

  using BaseType::size_;
  using BaseType::offset_;

 public:

  using BaseType::ArrayBase;

  // Constructors
  inline ArrI() noexcept;
  inline ArrI( const index_t size, const index_t offset = 0 ) noexcept;

  // Copy
  inline ArrI copy() const noexcept;

};

/// @ingroup  matrix_kit_module
template <typename _Val> using Array = ArrI<CpuTag, _Val>;

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_KIT_ARRAY_HH_
