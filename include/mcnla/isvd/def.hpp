////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/def.hpp
/// @brief   The iSVD definitions.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_DEF_HPP_
#define MCNLA_ISVD_DEF_HPP_

#include <mcnla/def.hpp>
#include <mcnla/core/matrix/def.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @defgroup  isvd_module  iSVD Module
/// @brief     The iSVD Module
///

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @defgroup  isvd_solver_module  Solver Module
/// @ingroup   isvd_module
/// @brief     The Solver Module
///

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @defgroup  isvd_sketcher_module  Sketcher Module
/// @ingroup   isvd_module
/// @brief     The Sketcher Module
///

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @defgroup  isvd_orthogonalizer_module  Orthogonalizer Module
/// @ingroup   isvd_module
/// @brief     The Orthogonalizer Module
///

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @defgroup  isvd_integrator_module  Integrator Module
/// @ingroup   isvd_module
/// @brief     The Integrator Module
///

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @defgroup  isvd_former_module  Former Module
/// @ingroup   isvd_module
/// @brief     The Former Module
///

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  isvd_module
/// The iSVD namespace.
///
namespace isvd {

using namespace matrix;

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_DEF_HPP_
