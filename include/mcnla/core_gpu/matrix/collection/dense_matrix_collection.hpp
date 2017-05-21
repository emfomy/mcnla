////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core_gpu/matrix/collection/dense_matrix_collection.hpp
/// @brief   The GPU dense matrix collections.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_GPU_MATRIX_COLLECTION_DENSE_MATRIX_COLLECTION_HPP_
#define MCNLA_CORE_GPU_MATRIX_COLLECTION_DENSE_MATRIX_COLLECTION_HPP_

#include <mcnla/core_gpu/matrix/def.hpp>
#include <mcnla/core/matrix/collection/dense_matrix_collection_012.hpp>
#include <mcnla/core/matrix/collection/dense_matrix_collection_102.hpp>
#include <mcnla/core/matrix/collection/dense_matrix_collection_201.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

/// @ingroup  matrix_collection_gpu_module
template <typename _Val>
using DenseMatrixCollection012Gpu = DenseMatrixCollection<DenseMatrixCollection012Tag, GpuTag, _Val, Trans::NORMAL>;

/// @ingroup  matrix_collection_gpu_module
template <typename _Val>
using DenseMatrixCollection102Gpu = DenseMatrixCollection<DenseMatrixCollection102Tag, GpuTag, _Val, Trans::NORMAL>;

/// @ingroup  matrix_collection_gpu_module
template <typename _Val>
using DenseMatrixCollection201Gpu = DenseMatrixCollection<DenseMatrixCollection201Tag, GpuTag, _Val, Trans::NORMAL>;

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_GPU_MATRIX_COLLECTION_DENSE_MATRIX_COLLECTION_HPP_
