////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/dense/def.hpp
/// @brief   The dense container definitions.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_DENSE_DEF_HPP_
#define MCNLA_CORE_MATRIX_DENSE_DEF_HPP_

#include <mcnla/core/matrix/def.hpp>
#include <mcnla/core/matrix/kit/array.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <class _Core, typename _Val> class DenseStorage;
template <class _Core, typename _Val> class DenseVectorStorage;
template <class _Core, typename _Val> class DenseMatrixStorage;

template <typename _Val>
using DenseVector = GeVecI<CpuTag, DenseTag, _Val>;

template <typename _Val, Trans _trans = Trans::NORMAL>
using DenseMatrix = GeMatI<CpuTag, DenseTag, _Val, _trans>;

template <typename _Val, Trans _trans = Trans::NORMAL, Uplo _uplo = Uplo::UPPER ^ _trans>
using DenseSymmetricMatrix = SyMatI<CpuTag, DenseTag, _Val, _trans, _uplo>;

template <typename _Val, Trans _trans = Trans::NORMAL, Uplo _uplo = Uplo::UPPER ^ _trans>
using DenseTriangularMatrix = TrMatI<CpuTag, DenseTag, _Val, _trans, _uplo>;

template <typename _Val>
using DenseDiagonalMatrix = DiMatI<CpuTag, DenseTag, _Val>;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_DENSE_DEF_HPP_
