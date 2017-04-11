////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/collection/vector_collection_wrapper.hh
/// @brief   The definition of vector collection wrapper.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_COLLECTION_VECTOR_COLLECTION_WRAPPER_HH_
#define MCNLA_CORE_MATRIX_COLLECTION_VECTOR_COLLECTION_WRAPPER_HH_

#include <mcnla/core/matrix/def.hpp>
#include <tuple>
#include <mcnla/core/matrix/dense.hpp>
#include <mcnla/core/utility/crtp.hpp>
#include <mcnla/core/utility/traits.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The vector collection wrapper.
///
/// @tparam  _Derived  The derived type.
///
template <class _Derived>
class VectorCollectionWrapper : public utility::CrtpBase<_Derived, VectorCollectionWrapper<_Derived>> {

 private:

  using VectorType = VectorT<_Derived>;

 protected:

  // Constructors
  inline VectorCollectionWrapper() noexcept = default;

 public:

  // Gets information
  inline bool    isEmpty() const noexcept;
  inline index_t length() const noexcept;
  inline index_t nvec() const noexcept;
  inline std::tuple<index_t, index_t> sizes() const noexcept;

  // Gets vector
  inline       VectorType operator()( const index_t idx ) noexcept;
  inline const VectorType operator()( const index_t idx ) const noexcept;

};

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_COLLECTION_VECTOR_COLLECTION_WRAPPER_HH_
