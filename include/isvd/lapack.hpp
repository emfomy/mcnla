////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/lapack.hpp
/// @brief   The LAPACK header.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_LAPACK_HPP_
#define ISVD_LAPACK_HPP_

#include <isvd/lapack/lapack.hpp>

#include <isvd/lapack/dense_syev.hpp>
#include <isvd/lapack/dense_gesvd.hpp>

#include <isvd/lapack/dense_geqrf.hpp>
#include <isvd/lapack/dense_gerqf.hpp>
#include <isvd/lapack/dense_orgqr.hpp>
#include <isvd/lapack/dense_orgrq.hpp>

#include <isvd/lapack/dense_larnv.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The iSVD namespace
///
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The LAPACK namespace
///
namespace lapack {}  // namespace lapack

}  // namespace isvd

#endif  // ISVD_LAPACK_HPP_
