////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/integrator.hpp
/// @brief   The iSVD integrator header.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_INTEGRATOR_HPP_
#define MCNLA_ISVD_INTEGRATOR_HPP_

// Kolmogorov-Nagumo-type
#include <mcnla/isvd/integrator/kolmogorov_nagumo_integrator.hpp>
#include <mcnla/isvd/integrator/row_block_kolmogorov_nagumo_integrator.hpp>
#include <mcnla/isvd/integrator/row_block_gramian_kolmogorov_nagumo_integrator.hpp>

// Wen-Yin line search
#include <mcnla/isvd/integrator/row_block_wen_yin_integrator.hpp>
#pragma warning
#include <mcnla/isvd/integrator/row_block_gramian_wen_yin_integrator.hpp>

// Reduce-sum
#include <mcnla/isvd/integrator/row_block_reduce_sum_integrator.hpp>

// Extrinsic mean
#include <mcnla/isvd/integrator/row_block_extrinsic_mean_integrator.hpp>

#endif  // MCNLA_ISVD_INTEGRATOR_HPP_
