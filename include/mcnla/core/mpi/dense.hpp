////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/dense.hpp
/// @brief   The dense MPI header.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_MPI_DENSE_HPP_
#define MCNLA_CORE_MATRIX_MPI_DENSE_HPP_

#include <mcnla/core/mpi/dense/allreduce.hpp>
#include <mcnla/core/mpi/dense/alltoall.hpp>
#include <mcnla/core/mpi/dense/bcast.hpp>
#include <mcnla/core/mpi/dense/gather.hpp>
#include <mcnla/core/mpi/dense/recv.hpp>
#include <mcnla/core/mpi/dense/reduce.hpp>
#include <mcnla/core/mpi/dense/reduce_scatter_block.hpp>
#include <mcnla/core/mpi/dense/scatter.hpp>
#include <mcnla/core/mpi/dense/scatterv.hpp>
#include <mcnla/core/mpi/dense/send.hpp>

#endif  // MCNLA_CORE_MATRIX_MPI_DENSE_HPP_
