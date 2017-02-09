////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/collection/dense_vector_collection.hpp
/// @brief   The dense vector collection interface.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_COLLECTION_DENSE_VECTOR_COLLECTION_HPP_
#define MCNLA_CORE_MATRIX_COLLECTION_DENSE_VECTOR_COLLECTION_HPP_

#include <mcnla/core/matrix/def.hpp>
#include <mcnla/core/matrix/collection/vector_collection_wrapper.hpp>
#include <mcnla/core/matrix/dense/dense_vector.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <class _Tag, typename _Scalar> class DenseVectorCollection;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace matrix

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The traits namespace.
//
namespace traits {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense vector collection traits.
///
template <class _Tag, typename _Scalar>
struct Traits<matrix::DenseVectorCollection<_Tag, _Scalar>> {

  using ScalarType     = _Scalar;
  using CollectionType = matrix::DenseVectorCollection<_Tag, _Scalar>;
  using VectorType     = matrix::DenseVector<_Scalar>;

};

}  // namespace traits

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  matrix_collection_module_detail
/// The interface of dense vector collection.
///
/// @tparam  _Tag     The collection tag.
/// @tparam  _Scalar  The scalar type.
///
template <class _Tag, typename _Scalar>
class DenseVectorCollection : public VectorCollectionWrapper<DenseVectorCollection<_Tag, _Scalar>> {
  static_assert(traits::False<_Tag>::value, "Error using non-specialized dense vector collection!");
};

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_COLLECTION_DENSE_VECTOR_COLLECTION_HPP_
