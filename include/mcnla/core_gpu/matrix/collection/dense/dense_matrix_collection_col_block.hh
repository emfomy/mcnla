////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core_gpu/matrix/collection/dense/dense_matrix_collection_col_block.hh
/// @brief   The definition of GPU dense matrix collection of column-blocks.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_GPU_MATRIX_COLLECTION_DENSE_DENSE_MATRIX_COLLECTION_COL_BLOCK_HH_
#define MCNLA_CORE_GPU_MATRIX_COLLECTION_DENSE_DENSE_MATRIX_COLLECTION_COL_BLOCK_HH_

#include <mcnla/core_gpu/matrix/collection/dense/def.hpp>
#include <mcnla/core/matrix/collection/dense/dense_matrix_collection_col_block.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

/// @ingroup  matrix_collection_module
/// @see  DenseMatrixCollectionColBlockBase
template <typename _Val, Trans _trans>
using DenseMatrixCollectionGpuColBlock = DenseMatrixCollectionColBlockBase<GpuTag, _Val, _trans>;

/// @ingroup  matrix_collection_module
/// @see  DenseMatrixCollectionColBlockBase
template <typename _Val>
using DenseMatrixCollectionGpuColBlockColMajor = DenseMatrixCollectionGpuColBlock<_Val, Trans::NORMAL>;

/// @ingroup  matrix_collection_module
/// @see  DenseMatrixCollectionColBlockBase
template <typename _Val>
using DenseMatrixCollectionGpuColBlockRowMajor = DenseMatrixCollectionGpuColBlock<_Val, Trans::TRANS>;

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_GPU_MATRIX_COLLECTION_DENSE_DENSE_MATRIX_COLLECTION_COL_BLOCK_HH_
