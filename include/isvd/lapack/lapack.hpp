////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/lapack/lapack.hpp
/// @brief   The LAPACK definitions.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_LAPACK_LAPACK_HPP_
#define ISVD_LAPACK_LAPACK_HPP_

#include <isvd/isvd.hpp>
#include <isvd/blas/blas.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The LAPACK namespace
///
namespace lapack {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The internal namespace.
///
namespace internal {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  The job option.
///
using JobOption = char;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Convert transpose option to char.
///
template <TransOption _trans, typename _Scalar>
using TransChar = isvd::blas::TransChar<_trans, _Scalar>;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Convert upper/lower option to char.
///
template <UploOption _uplo, Layout _layout>
using UploChar = isvd::blas::UploChar<_uplo, _layout>;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Convert diagonal option to char.
///
template <UploOption _uplo>
using DiagChar = isvd::blas::DiagChar<_uplo>;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Convert side option to char.
///
template <SideOption _side, Layout _layout>
using SideChar = isvd::blas::SideChar<_side, _layout>;

}  // namespace lapack

}  // namespace isvd

#endif  // ISVD_LAPACK_LAPACK_HPP_
