////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/io/binary/def.hpp
/// @brief   The binary I/O definitions.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_BINARY_IO_DEF_HPP_
#define MCNLA_CORE_BINARY_IO_DEF_HPP_

#include <mcnla/core/io/def.hpp>
#include <cstring>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The traits namespace.
//
namespace traits {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The I/O data type traits.
///
/// @tparam  _Val  The value type.
///
template <typename _Val>
struct IoValTraits;

#define MCNLA_IO_VAL_TRAITS_DEF( _Type, _value ) \
  template <> struct IoValTraits<_Type> { static constexpr const char *str = _value; };

MCNLA_IO_VAL_TRAITS_DEF(void,                 "")
MCNLA_IO_VAL_TRAITS_DEF(char,                 "I1")
MCNLA_IO_VAL_TRAITS_DEF(int8_t,               "I1")
MCNLA_IO_VAL_TRAITS_DEF(int16_t,              "I2")
MCNLA_IO_VAL_TRAITS_DEF(int32_t,              "I4")
MCNLA_IO_VAL_TRAITS_DEF(int64_t,              "I8")
MCNLA_IO_VAL_TRAITS_DEF(float,                "R4")
MCNLA_IO_VAL_TRAITS_DEF(double,               "R8")
MCNLA_IO_VAL_TRAITS_DEF(std::complex<float>,  "C8")
MCNLA_IO_VAL_TRAITS_DEF(std::complex<double>, "C16")

#undef MCNLA_IO_VAL_TRAITS_DEF

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The I/O core traits.
///
/// @tparam  _Core  The core tag.
///
template <typename _Val>
struct IoCoreTraits;

#define MCNLA_IO_CORE_TRAITS_DEF( _Type, _value ) \
  template <> struct IoCoreTraits<_Type> { static constexpr const char *str = _value; };

MCNLA_IO_CORE_TRAITS_DEF(DenseTag, "DEN")
MCNLA_IO_CORE_TRAITS_DEF(CooTag,   "COO")

#undef MCNLA_IO_VAL_TRAITS_DEF

}  // namespace traits

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  io_module
/// The I/O namespace.
///
namespace io {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The detail namespace
//
namespace detail {

static constexpr index_t kHeaderLen = 32;
static constexpr index_t kCommentLen = 64;
static constexpr index_t kStorageLen = 8;
static constexpr index_t kTypeLen = 8;

template <typename _Core, typename _Val>
void writeHeader(
    std::ostream &fout,
    const char *comment
) noexcept {

  mcnla_assert_le(strlen(comment), kCommentLen-3);

  // Write header
  fout << std::setw(kHeaderLen-1) << std::left << "##MCNLABinaryFileFormat" << '\n';

  // Write comment
  fout << "# " << std::setw(kCommentLen-3) << comment << '\n';

  // Write storage
  fout << std::setw(kStorageLen) << std::left << traits::IoCoreTraits<_Core>::str;

  // Write value type
  fout << std::setw(kTypeLen) << std::left << traits::IoValTraits<_Val>::str;

  // Write index type
  if ( std::is_same<_Core, DenseTag>::value ) {
    fout << std::setw(kTypeLen) << "";
  } else {
    fout << std::setw(kTypeLen) << std::left << traits::IoValTraits<index_t>::str;
  }

  // Write spaces
  fout << std::setw(kTypeLen-1) << "" << '\n';
}

template <typename _Core, typename _Val>
void checkHeader(
    std::istream &fin
) noexcept {

  const char* str0;
  static_cast<void>(str0);

  // Skip header & comment & storage
  fin.seekg(kHeaderLen + kCommentLen, std::ios_base::cur);

  // Check storage type
  {
    char str[kStorageLen];
    str0 = traits::IoCoreTraits<_Core>::str;
    fin.read(str, kStorageLen);
    mcnla_assert_false(strncmp(str, str0, strlen(str0)));
  }

  // Check value type
  if ( !std::is_same<_Val, void>::value ) {
    char str[kTypeLen];
    str0 = traits::IoValTraits<_Val>::str;
    fin.read(str, kTypeLen);
    mcnla_assert_false(strncmp(str, str0, strlen(str0)));
  } else {
    fin.seekg(kTypeLen, std::ios_base::cur);
  }

  // Check index type
  if ( !std::is_same<_Core, DenseTag>::value ) {
    char str[kTypeLen];
    str0 = traits::IoValTraits<index_t>::str;
    fin.read(str, kTypeLen);
    mcnla_assert_false(strncmp(str, str0, strlen(str0)));
  } else {
    fin.seekg(kTypeLen, std::ios_base::cur);
  }

  // Skip spaces
  fin.seekg(kTypeLen, std::ios_base::cur);
}

}  // namespace detail

}  // namespace io

}  // namespace mcnla

#endif  // MCNLA_CORE_BINARY_IO_DEF_HPP_
