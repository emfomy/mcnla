////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core_gpu/matrix/dense/def.hpp
/// @brief   The dense GPU container definitions.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_GPU_MATRIX_DENSE_DEF_HPP_
#define MCNLA_CORE_GPU_MATRIX_DENSE_DEF_HPP_

#include <mcnla/core_gpu/matrix/def.hpp>
#include <mcnla/core_gpu/matrix/kit/gpu_array.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Val> class DenseGpuVector;
template <typename _Val, Trans _trans> class DenseGpuMatrix;
template <typename _Val, Trans _trans, Uplo _uplo> class DenseSymmetricGpuMatrix;
template <typename _Val, Trans _trans, Uplo _uplo> class DenseTriangularGpuMatrix;
template <typename _Val> class DenseDiagonalGpuMatrix;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The dense GPU types.
//
struct DenseGpuTypes {

  template <typename _Val>
  using ArrayT = GpuArray<_Val>;

  template <typename _Val>
  using GeVecT = DenseGpuVector<_Val>;

  template <typename _Val, Trans _trans>
  using GeMatT = DenseGpuMatrix<_Val, _trans>;

  template <typename _Val, Trans _trans, Uplo _uplo>
  using SyMatT = DenseSymmetricGpuMatrix<_Val, _trans, _uplo>;

  template <typename _Val, Trans _trans, Uplo _uplo>
  using TrMatT = DenseTriangularGpuMatrix<_Val, _trans, _uplo>;

  template <typename _Val>
  using DiMatT = DenseDiagonalGpuMatrix<_Val>;

};

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_GPU_MATRIX_DENSE_DEF_HPP_
