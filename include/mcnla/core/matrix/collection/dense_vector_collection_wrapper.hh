////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/collection/dense_vector_collection_wrapper.hh
/// @brief   The definition of dense vector collection wrapper.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_COLLECTION_DENSE_VECTOR_COLLECTION_WRAPPER_HH_
#define MCNLA_CORE_MATRIX_COLLECTION_DENSE_VECTOR_COLLECTION_WRAPPER_HH_

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
/// @ingroup  matrix_collection_module
/// The dense vector collection wrapper.
///
/// @tparam  _Derived  The derived type.
///
template <class _Derived>
class DenseVectorCollectionWrapper : public utility::CrtpBase<_Derived, DenseVectorCollectionWrapper<_Derived>> {

  assertDenseMatrix(VectorT<_Derived>);

 private:

  using VectorType = VectorT<_Derived>;

 protected:

  // Constructors
  inline DenseVectorCollectionWrapper() noexcept;

 public:

  // Gets information
  inline index_t length() const noexcept;
  inline index_t nvec() const noexcept;
  inline std::tuple<index_t, index_t> sizes() const noexcept;

  // Gets vector
  inline       VectorType operator()( const index_t idx ) noexcept;
  inline const VectorType operator()( const index_t idx ) const noexcept;

};

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_COLLECTION_DENSE_VECTOR_COLLECTION_WRAPPER_HH_
