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
#ifndef DOXYGEN_SHOULD_SKIP_THIS
class ArrS<CpuTag, _Val>
  : public ArrayBase<CpuTag, _Val> {
#else  // DOXYGEN_SHOULD_SKIP_THIS
class Array
  : public ArrayBase_<CpuTag, _Val> {
#endif  // DOXYGEN_SHOULD_SKIP_THIS

 private:

  using BaseType = ArrayBase<CpuTag, _Val>;

 protected:

  using BaseType::size_;
  using BaseType::offset_;

 public:

  using BaseType::ArrayBase;

#ifdef DOXYGEN_SHOULD_SKIP_THIS
  /// @copydoc ArrayBase_::operator=
  Array& operator=( const Array &other );
#endif  // DOXYGEN_SHOULD_SKIP_THIS

  // Constructors
  inline ArrS() noexcept;
  inline ArrS( const size_t size, const index_t offset = 0 ) noexcept;

  // Copy
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  inline Array<_Val> copy() const noexcept;
#else  // DOXYGEN_SHOULD_SKIP_THIS
  inline Array copy() const noexcept;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

};

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_KIT_ARRAY_HH_
