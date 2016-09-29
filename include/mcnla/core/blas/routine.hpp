////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/blas/routine.hpp
/// @brief   The BLAS routines header.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_BLAS_ROUTINE_HPP_
#define MCNLA_CORE_BLAS_ROUTINE_HPP_

#include <mcnla/core/blas/routine/copy.hpp>
#include <mcnla/core/blas/routine/copy_coo.hpp>
#include <mcnla/core/blas/routine/scal.hpp>
#include <mcnla/core/blas/routine/axpy.hpp>
#include <mcnla/core/blas/routine/axpby.hpp>
#include <mcnla/core/blas/routine/asum.hpp>
#include <mcnla/core/blas/routine/iamax.hpp>
#include <mcnla/core/blas/routine/iamin.hpp>

#include <mcnla/core/blas/routine/gemm.hpp>
#include <mcnla/core/blas/routine/gemm_coo.hpp>
#include <mcnla/core/blas/routine/symm.hpp>
#include <mcnla/core/blas/routine/syrk.hpp>

#endif  // MCNLA_CORE_BLAS_ROUTINE_HPP_