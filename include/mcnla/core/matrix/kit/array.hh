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
  #define MCNLA_TMP  ArrS<CpuTag, _Val>
  #define MCNLA_TMP0 ArrS
  #define MCNLA_TMP1 ArrS<CpuTag, _Val>
#else  // DOXYGEN_SHOULD_SKIP_THIS
  #define MCNLA_TMP  Array<_Val>
  #define MCNLA_TMP0 Array
  #define MCNLA_TMP1 Array
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
class MCNLA_TMP1
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
  inline MCNLA_TMP0() noexcept;
  inline MCNLA_TMP0( const size_t size, const index_t offset = 0 ) noexcept;

  // Copy
  inline MCNLA_TMP copy() const noexcept;

};

}  // namespace matrix

}  // namespace mcnla

#undef MCNLA_TMP
#undef MCNLA_TMP0
#undef MCNLA_TMP1

#endif  // MCNLA_CORE_MATRIX_KIT_ARRAY_HH_
