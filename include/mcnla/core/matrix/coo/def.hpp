////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/coo/def.hpp
/// @brief   The COO container definitions.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_COO_DEF_HPP_
#define MCNLA_CORE_MATRIX_COO_DEF_HPP_

#include <mcnla/core/matrix/def.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Val> class CooVector;
template <typename _Val> class CooDiagonalMatrix;
template <typename _Val, Trans _trans> class CooMatrix;
template <typename _Val, Trans _trans, Uplo _uplo> class CooSymmetricMatrix;
template <typename _Val, Trans _trans, Uplo _uplo> class CooTriangularMatrix;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_COO_DEF_HPP_
