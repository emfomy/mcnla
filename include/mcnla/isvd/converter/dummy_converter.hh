////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/converter/dummy_converter.hh
/// @brief   The definition of dummy converter.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_CONVERTER_DUMMY_CONVERTER_HH_
#define MCNLA_ISVD_CONVERTER_DUMMY_CONVERTER_HH_

#include <mcnla/isvd/def.hpp>
#include <mcnla/isvd/converter/converter.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  isvd_converter_module_detail
/// The tag of dummy converter.
///
struct DummyConverterTag {};

/// @ingroup  isvd_converter_module
template <typename _Val>
using DummyConverter = Converter<DummyConverterTag, _Val>;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  isvd_converter_module
/// The dummy converter.
///
/// @tparam  _Val  The value type.
///
template <class _Val>
class Converter<DummyConverterTag, _Val>
  : public ComponentWrapper<Converter<DummyConverterTag, _Val>> {

  friend ComponentWrapper<Converter<DummyConverterTag, _Val>>;

 private:

  using BaseType = ComponentWrapper<Converter<DummyConverterTag, _Val>>;

 public:

  using ValType = _Val;

 protected:

  using BaseType::parameters_;
  using BaseType::initialized_;
  using BaseType::computed_;
  using BaseType::moments_;

 public:

  // Constructor
  inline Converter( const Parameters<ValType> &parameters ) noexcept;

 protected:

  // Initializes
  void initializeImpl() noexcept;

  // Converts data
  template <typename... Args>
  void runImpl( Args... arg ) noexcept;

};

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_CONVERTER_DUMMY_CONVERTER_HH_
