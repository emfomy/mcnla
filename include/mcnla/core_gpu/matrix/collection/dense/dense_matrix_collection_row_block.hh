////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core_gpu/matrix/collection/dense/dense_matrix_collection_row_block.hh
/// @brief   The definition of GPU dense matrix collection with dimension order (dim1, dim0, dim2).
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_GPU_MATRIX_COLLECTION_DENSE_DENSE_MATRIX_COLLECTION_ROW_BLOCK_HH_
#define MCNLA_CORE_GPU_MATRIX_COLLECTION_DENSE_DENSE_MATRIX_COLLECTION_ROW_BLOCK_HH_

#include <mcnla/core_gpu/matrix/collection/dense/def.hpp>
#include <mcnla/core/matrix/collection/dense/dense_matrix_collection_row_block.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

/// @ingroup  matrix_collection_module
/// @see  DenseMatrixCollectionRowBlockBase
template <typename _Val, Trans _trans>
using DenseMatrixCollectionGpuRowBlock = DenseMatrixCollectionRowBlockBase<GpuTag, _Val, _trans>;

/// @ingroup  matrix_collection_module
/// @see  DenseMatrixCollectionRowBlockBase
template <typename _Val>
using DenseMatrixCollectionGpuRowBlockColMajor = DenseMatrixCollectionGpuRowBlock<_Val, Trans::NORMAL>;

/// @ingroup  matrix_collection_module
/// @see  DenseMatrixCollectionRowBlockBase
template <typename _Val>
using DenseMatrixCollectionGpuRowBlockRowMajor = DenseMatrixCollectionGpuRowBlock<_Val, Trans::TRANS>;

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_GPU_MATRIX_COLLECTION_DENSE_DENSE_MATRIX_COLLECTION_ROW_BLOCK_HH_
