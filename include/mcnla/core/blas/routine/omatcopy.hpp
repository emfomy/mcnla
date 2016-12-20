////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/blas/routine/omatcopy.hpp
/// @brief   The BLAS OMATCOPY routine.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_BLAS_ROUTINE_OMATCOPY_HPP_
#define MCNLA_CORE_BLAS_ROUTINE_OMATCOPY_HPP_

#include <mcnla/core/matrix.hpp>
#include <mcnla/core/blas/blas/omatcopy.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The BLAS namespace
//
namespace blas {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  blas0_module
/// @brief  Performs scaling and out-place transposition/copying of matrices.
///
template <TransOption _trans = TransOption::NORMAL, typename _Scalar, Layout _layout>
inline void omatcopy(
    const typename DenseMatrix<_Scalar, _layout>::ScalarType alpha,
    const DenseMatrix<_Scalar, _layout> &a,
          DenseMatrix<_Scalar, _layout> &b
) noexcept {
#ifdef MCNLA_USE_MKL
  detail::omatcopy(toLayoutChar(_layout), toTransChar<_Scalar>(_trans), a.getNrow(), a.getNcol(),
                   alpha, a.getValue(), a.getPitch(), b.getValue(), b.getPitch());
#else  // MCNLA_USE_MKL
  for ( auto ait = a.cbegin(), bit = b.begin(); ait != a.cend(); ++ait, ++bit ) {
    *bit = alpha * *ait;
  }
#endif  // MCNLA_USE_MKL
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <TransOption _trans = TransOption::NORMAL, typename _Scalar, Layout _layout>
inline void omatcopy(
    const typename DenseMatrix<_Scalar, _layout>::ScalarType alpha,
    const DenseMatrix<_Scalar, _layout> &a,
          DenseMatrix<_Scalar, _layout> &&b
) noexcept {
  omatcopy<_trans>(alpha, a, b);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace blas

}  // namespace mcnla

#endif  // MCNLA_CORE_BLAS_ROUTINE_OMATCOPY_HPP_
