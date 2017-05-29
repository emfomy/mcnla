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

template <class _Tag, class _Core, typename _Val, Trans _trans>
MCNLA_TRAITS_DEF(Val, matrix::DenseMatrixCollection<_Tag MCNLA_COMMA _Core MCNLA_COMMA _Val MCNLA_COMMA _trans>, _Val)

template <class _Tag, class _Core, typename _Val, Trans _trans>
MCNLA_TRAITS_DEF(Matrix, matrix::DenseMatrixCollection<_Tag MCNLA_COMMA _Core MCNLA_COMMA _Val MCNLA_COMMA _trans>,
                         matrix::DenseMatrix<_Val MCNLA_COMMA _trans>)

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
class DenseMatrixCollection : public MatrixCollectionWrapper<DenseMatrixCollection<_Tag, _Core, _Val, _trans>>;

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_COLLECTION_DENSE_MATRIX_COLLECTION_HPP_
