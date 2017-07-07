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

#ifndef DOXYGEN_SHOULD_SKIP_THIS
struct DummyConverterTag {};
template <typename _Val> using DummyConverter = Converter<DummyConverterTag, _Val>;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  isvd_converter_module
/// The dummy converter.
///
/// @tparam  _Val  The value type.
///
template <class _Val>
#ifndef DOXYGEN_SHOULD_SKIP_THIS
class Converter<DummyConverterTag, _Val>
#else  // DOXYGEN_SHOULD_SKIP_THIS
class DummyConverter
#endif  // DOXYGEN_SHOULD_SKIP_THIS
  : public StageWrapper<DummyConverter<_Val>> {

  friend StageWrapper<DummyConverter<_Val>>;

 private:

  using BaseType = StageWrapper<DummyConverter<_Val>>;

 protected:

  using BaseType::parameters_;
  using BaseType::initialized_;
  using BaseType::computed_;
  using BaseType::moments_;
  using BaseType::comm_times_;

 public:

  // Constructor
  inline Converter( const Parameters<_Val> &parameters ) noexcept;

 protected:

  // Initializes
  void initializeImpl() noexcept;

  // Converts data
  template <typename ..._Args>
  void runImpl( _Args... arg ) noexcept;

};

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_CONVERTER_DUMMY_CONVERTER_HH_
