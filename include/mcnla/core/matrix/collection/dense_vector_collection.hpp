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
template <class _Tag, class _Core, typename _Val> class DenseVectorCollection;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace matrix

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The traits namespace.
//
namespace traits {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense vector collection traits.
///
template <class _Tag, class _Core, typename _Val>
struct Traits<matrix::DenseVectorCollection<_Tag, _Core, _Val>> {

  using ValType        = _Val;
  using CollectionType = matrix::DenseVectorCollection<_Tag, _Core, _Val>;
  using VectorType     = matrix::GeVecI<_Core, DenseTag, _Val>;

};

}  // namespace traits

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The interface of dense vector collection.
///
/// @tparam  _Tag   The collection tag.
/// @tparam  _Core  The core tag.
/// @tparam  _Val   The value type.
///
template <class _Tag, class _Core, typename _Val>
class DenseVectorCollection : public VectorCollectionWrapper<DenseVectorCollection<_Tag, _Core, _Val>> {
  static_assert(traits::FalseType<_Tag>::value, "Error using non-specialized dense vector collection!");
};

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_COLLECTION_DENSE_VECTOR_COLLECTION_HPP_
