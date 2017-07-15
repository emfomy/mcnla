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

#ifndef DOXYGEN_SHOULD_SKIP_THIS
  #define MCNLA_ALIAS  ArrS<CpuTag, _Val>
  #define MCNLA_ALIAS0 ArrS
  #define MCNLA_ALIAS1 ArrS<CpuTag, _Val>
#else  // DOXYGEN_SHOULD_SKIP_THIS
  #define MCNLA_ALIAS  Array<_Val>
  #define MCNLA_ALIAS0 Array
  #define MCNLA_ALIAS1 Array
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
/// @ingroup  matrix_kit_module
/// The value array.
///
/// @tparam  _Val  The value type.
///
template <typename _Val>
class MCNLA_ALIAS1
  : public ArrayBase<CpuTag, _Val> {

 private:

  using BaseType = ArrayBase<CpuTag, _Val>;

 protected:

  using BaseType::size_;
  using BaseType::offset_;

 public:

  using BaseType::ArrayBase;

#ifdef DOXYGEN_SHOULD_SKIP_THIS
  /// @copydoc ArrayBase::operator=
  Array& operator=( const Array &other );
#endif  // DOXYGEN_SHOULD_SKIP_THIS

  // Constructors
  inline MCNLA_ALIAS0() noexcept;
  inline MCNLA_ALIAS0( const size_t size, const index_t offset = 0 ) noexcept;

  // Copy
  inline MCNLA_ALIAS copy() const noexcept;

};

}  // namespace matrix

}  // namespace mcnla

#undef MCNLA_ALIAS
#undef MCNLA_ALIAS0
#undef MCNLA_ALIAS1

#endif  // MCNLA_CORE_MATRIX_KIT_ARRAY_HH_
