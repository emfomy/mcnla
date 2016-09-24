////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/lapack/routine/larnv.hpp
/// @brief   The LAPACK LARNV routine.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_LAPACK_ROUTINE_LARNV_HPP_
#define ISVD_LAPACK_ROUTINE_LARNV_HPP_

#include <isvd/isvd.hpp>
#include <isvd/matrix.hpp>
#include <isvd/lapack/lapack.hpp>
#include <isvd/lapack/lapack/larnv.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The LAPACK namespace
//
namespace lapack {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Returns a vector of random numbers from a uniform or normal distribution.
///
//@{
template <index_t idist, typename _Scalar>
inline void larnv(
    DenseVector<_Scalar> &x,
    index_t iseed[4]
) noexcept {
  static_assert(isvd::detail::ScalarTraits<_Scalar>::is_real ? (1 <= idist && idist <= 3) : (1 <= idist && idist <= 5),
                "The value of 'idist' is invalid!");
  detail::larnv(idist, iseed, x.getLength(), x.getValue());
}

template <index_t idist, typename _Scalar>
inline void larnv(
    DenseVector<_Scalar> &&x,
    index_t iseed[4]
) noexcept {
  larnv<idist>(x, iseed);
}
//@}

}  // namespace lapack

}  // namespace isvd

#endif  // ISVD_LAPACK_ROUTINE_LARNV_HPP_
