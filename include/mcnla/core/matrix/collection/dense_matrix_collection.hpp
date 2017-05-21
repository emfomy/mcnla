////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/collection/dense_matrix_collection.hpp
/// @brief   The dense matrix collection interface.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_COLLECTION_DENSE_MATRIX_COLLECTION_HPP_
#define MCNLA_CORE_MATRIX_COLLECTION_DENSE_MATRIX_COLLECTION_HPP_

#include <mcnla/core/matrix/def.hpp>
#include <mcnla/core/matrix/collection/matrix_collection_wrapper.hpp>
#include <mcnla/core/matrix/dense/dense_matrix.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <class _Tag, class _Core, typename _Val, Trans _trans> class DenseMatrixCollection;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace matrix

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The traits namespace.
//
namespace traits {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense matrix collection traits.
///
template <class _Tag, class _Core, typename _Val, Trans _trans>
struct Traits<matrix::DenseMatrixCollection<_Tag, _Core, _Val, _trans>> {

  using ValType        = _Val;
  using CollectionType = matrix::DenseMatrixCollection<_Tag, _Core, _Val, _trans>;
  using MatrixType     = matrix::GeMatI<_Core, DenseTag, _Val, _trans>;

};

}  // namespace traits

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The interface of dense matrix collection.
///
/// @tparam  _Tag    The collection tag.
/// @tparam  _Core   The core tag.
/// @tparam  _Val    The value type.
/// @tparam  _trans  The transpose storage layout.
///
template <class _Tag, class _Core, typename _Val, Trans _trans>
class DenseMatrixCollection : public MatrixCollectionWrapper<DenseMatrixCollection<_Tag, _Core, _Val, _trans>> {
  static_assert(traits::FalseType<_Tag>::value, "Error using non-specialized dense matrix collection!");
};

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_COLLECTION_DENSE_MATRIX_COLLECTION_HPP_
