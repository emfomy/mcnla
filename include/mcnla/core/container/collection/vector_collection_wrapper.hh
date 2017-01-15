////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/container/collection/vector_collection_wrapper.hh
/// @brief   The definition of vector collection wrapper.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_CONTAINER_COLLECTION_VECTOR_COLLECTION_WRAPPER_HH_
#define MCNLA_CORE_CONTAINER_COLLECTION_VECTOR_COLLECTION_WRAPPER_HH_

#include <mcnla/def.hpp>
#include <mcnla/core/def.hpp>
#include <tuple>
#include <mcnla/core/utility/crtp.hpp>
#include <mcnla/core/utility/traits.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The container namespace.
//
namespace container {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  container_collection_module
/// The vector collection wrapper.
///
/// @tparam  _Derived  The derived type.
///
template <class _Derived>
class VectorSetWrapper : public utility::CrtpBase<_Derived, VectorSetWrapper<_Derived>> {

 private:

  using VectorType = VectorT<_Derived>;

 protected:

  // Constructors
  inline VectorSetWrapper() noexcept;

 public:

  // Gets information
  inline index_t length() const noexcept;
  inline index_t nvec() const noexcept;
  inline std::tuple<index_t, index_t> sizes() const noexcept;

  // Gets vector
  inline       VectorType operator()( const index_t idx ) noexcept;
  inline const VectorType operator()( const index_t idx ) const noexcept;

};

}  // namespace container

}  // namespace mcnla

#endif  // MCNLA_CORE_CONTAINER_COLLECTION_VECTOR_COLLECTION_WRAPPER_HH_
