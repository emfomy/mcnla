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
template <typename _Val> class DenseVector;
template <typename _Val, Trans _trans> class DenseMatrix;
template <typename _Val, Trans _trans, Uplo _uplo> class DenseSymmetricMatrix;
template <typename _Val, Trans _trans, Uplo _uplo> class DenseTriangularMatrix;
template <typename _Val> class DenseDiagonalMatrix;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The dense types.
//
struct DenseTypes {

  template <typename _Val>
  using ArrayT = Array<_Val>;

  template <typename _Val>
  using GeVecT = DenseVector<_Val>;

  template <typename _Val, Trans _trans>
  using GeMatT = DenseMatrix<_Val, _trans>;

  template <typename _Val, Trans _trans, Uplo _uplo>
  using SyMatT = DenseSymmetricMatrix<_Val, _trans, _uplo>;

  template <typename _Val, Trans _trans, Uplo _uplo>
  using TrMatT = DenseTriangularMatrix<_Val, _trans, _uplo>;

  template <typename _Val>
  using DiMatT = DenseDiagonalMatrix<_Val>;

};

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_DENSE_DEF_HPP_
