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
template <class _Tag, typename _Scalar, Trans _trans> class DenseMatrixCollection;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace matrix

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The traits namespace.
//
namespace traits {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense matrix collection traits.
///
template <class _Tag, typename _Scalar, Trans _trans>
struct Traits<matrix::DenseMatrixCollection<_Tag, _Scalar, _trans>> {

  using ScalarType     = _Scalar;
  using CollectionType = matrix::DenseMatrixCollection<_Tag, _Scalar, _trans>;
  using MatrixType     = matrix::DenseMatrix<_Scalar, _trans>;

};

}  // namespace traits

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  matrix_collection_module_detail
/// The interface of dense matrix collection.
///
/// @tparam  _Tag     The collection tag.
/// @tparam  _Scalar  The scalar type.
/// @tparam  _trans   The transpose storage layout.
///
template <class _Tag, typename _Scalar, Trans _trans>
class DenseMatrixCollection : public MatrixCollectionWrapper<DenseMatrixCollection<_Tag, _Scalar, _trans>> {
  static_assert(traits::False<_Tag>::value, "Error using non-specialized dense matrix collection!");
};

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_COLLECTION_DENSE_MATRIX_COLLECTION_HPP_
