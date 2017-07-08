////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core_gpu/matrix/dense/def.hpp
/// @brief   The GPU dense container definitions.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_GPU_MATRIX_DENSE_DEF_HPP_
#define MCNLA_CORE_GPU_MATRIX_DENSE_DEF_HPP_

#include <mcnla/core_gpu/matrix/def.hpp>
#include <mcnla/core/matrix/dense/def.hpp>
#include <mcnla/core_gpu/matrix/kit/array_gpu.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Val>
using DenseVectorGpu = GeVecS<GpuTag, DenseTag, _Val>;

template <typename _Val, Trans _trans>
using DenseMatrixGpu = GeMatS<GpuTag, DenseTag, _Val, _trans>;

template <typename _Val, Trans _trans, Uplo _uplo>
using DenseSymmetricMatrixGpu = SyMatS<GpuTag, DenseTag, _Val, _trans, _uplo>;

template <typename _Val, Trans _trans, Uplo _uplo>
using DenseTriangularMatrixGpu = TrMatS<GpuTag, DenseTag, _Val, _trans, _uplo>;

template <typename _Val>
using DenseDiagonalMatrixGpu = DiMatS<GpuTag, DenseTag, _Val>;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_GPU_MATRIX_DENSE_DEF_HPP_
