////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core_gpu/matrix/collection/def.hpp
/// @brief   The GPU container collection definitions.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_GPU_MATRIX_COLLECTION_DENSE_DEF_HPP_
#define MCNLA_CORE_GPU_MATRIX_COLLECTION_DENSE_DEF_HPP_

#include <mcnla/core_gpu/matrix/collection/def.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace
//
namespace matrix {

/// @ingroup  matrix_collection_gpu_module
template <class _Tag, typename _Val>
using DenseVectorCollectionGpu = GeVecCollS<_Tag, GpuTag, DenseTag, _Val>;

/// @ingroup  matrix_collection_gpu_module
/// @see  DenseMatrixCollectionGpuColBlock, DenseMatrixCollectionGpuRowBlock
template <class _Tag, typename _Val, Trans _trans>
using DenseMatrixCollectionGpu = GeMatCollS<_Tag, GpuTag, DenseTag, _Val, _trans>;

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_GPU_MATRIX_COLLECTION_DENSE_DEF_HPP_
