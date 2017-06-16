////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/la/dense/routine.hpp
/// @brief   The dense linear algebra routine header.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_LA_DENSE_ROUTINE_HPP_
#define MCNLA_CORE_LA_DENSE_ROUTINE_HPP_

// BLAS 1
#include <mcnla/core/la/dense/routine/copy.hpp>
#include <mcnla/core/la/dense/routine/scal.hpp>
#include <mcnla/core/la/dense/routine/scal0.hpp>
#include <mcnla/core/la/dense/routine/axpy.hpp>
#include <mcnla/core/la/dense/routine/axpby.hpp>
#include <mcnla/core/la/dense/routine/dot.hpp>
#include <mcnla/core/la/dense/routine/nrm2.hpp>
#include <mcnla/core/la/dense/routine/asum.hpp>
#include <mcnla/core/la/dense/routine/iamax.hpp>
#include <mcnla/core/la/dense/routine/iamin.hpp>

// BLAS 2

// BLAS 3
#include <mcnla/core/la/dense/routine/gemm.hpp>
#include <mcnla/core/la/dense/routine/gemmt.hpp>
#include <mcnla/core/la/dense/routine/symm.hpp>
#include <mcnla/core/la/dense/routine/syrk.hpp>
#include <mcnla/core/la/dense/routine/syr2k.hpp>
#include <mcnla/core/la/dense/routine/dimm.hpp>
#include <mcnla/core/la/dense/routine/dism.hpp>

// BLAS-like
#include <mcnla/core/la/dense/routine/omatcopy.hpp>
#include <mcnla/core/la/dense/routine/memset0.hpp>
#include <mcnla/core/la/dense/routine/nrmf.hpp>

// LAPACK linear equation
#include <mcnla/core/la/dense/routine/getrfi.hpp>

// LAPACK least squares
#include <mcnla/core/la/dense/routine/gesvd.hpp>
#include <mcnla/core/la/dense/routine/syev.hpp>

// LAPACK auxiliary
#include <mcnla/core/la/dense/routine/larnv.hpp>

#endif  // MCNLA_CORE_LA_DENSE_ROUTINE_HPP_
