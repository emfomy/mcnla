////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/def.hpp
/// @brief   The matrix definitions.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_DEF_HPP_
#define MCNLA_CORE_MATRIX_DEF_HPP_

#include <mcnla/def.hpp>
#include <mcnla/core/def.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @defgroup  matrix_module  Matrix Module
/// @ingroup   core_module
/// @brief     The matrix Module
///

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @defgroup  matrix_base_module  Base Container Module
/// @ingroup   matrix_module
/// @brief     The Base Container Module
///

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @defgroup  matrix_dense_module  Dense Matrix Module
/// @ingroup   matrix_module
/// @brief     The Dense Container Module
///

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @defgroup  matrix_coo_module  COO Matrix Module
/// @ingroup   matrix_module
/// @brief     The Coordinate List (COO) Container Module
///

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The matrix namespace.
/// @ingroup  matrix_module
///
namespace matrix {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The matrix detail namespace.
///
namespace detail {}

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_DEF_HPP_
