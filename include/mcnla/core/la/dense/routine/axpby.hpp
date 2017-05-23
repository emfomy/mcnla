////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/la/dense/routine/axpby.hpp
/// @brief   The BLAS AXPBY routine.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_LA_DENSE_ROUTINE_AXPBY_HPP_
#define MCNLA_CORE_LA_DENSE_ROUTINE_AXPBY_HPP_

#include <mcnla/core/la/def.hpp>
#include <mcnla/core/matrix.hpp>
#include <mcnla/core/la/raw/blas/axpby.hpp>
#include <mcnla/core/la/dense/routine/copy.hpp>
#include <mcnla/core/la/dense/routine/scal.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The linear algebra namespace
//
namespace la {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  la_dense_blas1_module
/// @brief  Scales two vectors, adds them to one another and stores result in the vector.
///
template <typename _Val>
inline void axpby(
    const DenseVector<_Val> &x,
          DenseVector<_Val> &y,
    const ValT<DenseVector<_Val>> alpha = 1,
    const ValT<DenseVector<_Val>> beta  = 1
) noexcept {
  if ( beta == 0.0 ) {
    copy(x, y);
    scal(y, alpha);
  } else {
    detail::axpby(x.length(), alpha, x.valPtr(), x.stride(), beta, y.valPtr(), y.stride());
  }
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Val>
inline void axpby(
    const DenseVector<_Val> &x,
          DenseVector<_Val> &&y,
    const ValT<DenseVector<_Val>> alpha = 1,
    const ValT<DenseVector<_Val>> beta  = 1
) noexcept {
  axpby(x, y, alpha, beta);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace la

}  // namespace mcnla

#endif  // MCNLA_CORE_LA_DENSE_ROUTINE_AXPBY_HPP_
