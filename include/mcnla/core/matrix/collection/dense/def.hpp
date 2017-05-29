////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/collection/def.hpp
/// @brief   The container collection definitions.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_COLLECTION_DENSE_DEF_HPP_
#define MCNLA_CORE_MATRIX_COLLECTION_DENSE_DEF_HPP_

#include <mcnla/core/matrix/collection/def.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace
//
namespace matrix {

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <class _Tag, typename _Val>
using DenseVectorCollection = GeVecCollS<_Tag, CpuTag, DenseTag, _Val>;

template <class _Tag, typename _Val, Trans _trans>
using DenseMatrixCollection = GeMatCollS<_Tag, CpuTag, DenseTag, _Val, _trans>;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_COLLECTION_DENSE_DEF_HPP_
