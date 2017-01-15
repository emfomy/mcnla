////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/container/collection/matrix_collection_wrapper.hh
/// @brief   The definition of matrix collection wrapper.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_CONTAINER_COLLECTION_MATRIX_COLLECTION_WRAPPER_HH_
#define MCNLA_CORE_CONTAINER_COLLECTION_MATRIX_COLLECTION_WRAPPER_HH_

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
/// The matrix collection wrapper.
///
/// @tparam  _Derived  The derived type.
///
template <class _Derived>
class MatrixSetWrapper : public utility::CrtpBase<_Derived, MatrixSetWrapper<_Derived>> {

 private:

  using MatrixType = MatrixT<_Derived>;

 protected:

  // Constructors
  inline MatrixSetWrapper() noexcept;

 public:

  // Gets information
  inline index_t nrow() const noexcept;
  inline index_t ncol() const noexcept;
  inline index_t nmat() const noexcept;
  inline std::tuple<index_t, index_t, index_t> sizes() const noexcept;

  // Gets matrix
  inline       MatrixType operator()( const index_t idx ) noexcept;
  inline const MatrixType operator()( const index_t idx ) const noexcept;

};

}  // namespace container

}  // namespace mcnla

#endif  // MCNLA_CORE_CONTAINER_COLLECTION_MATRIX_COLLECTION_WRAPPER_HH_
