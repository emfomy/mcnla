////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/blas/routine/copy_coo.hpp
/// @brief   The BLAS COPY routine for COO types.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_BLAS_ROUTINE_COPY_COO_HPP_
#define MCNLA_BLAS_ROUTINE_COPY_COO_HPP_

#include <mcnla/matrix.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The BLAS namespace
//
namespace blas {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copies COO vector to dense vector.
///
//@{
template <typename _Scalar>
inline void copy(
    const CooVector<_Scalar> &x,
          DenseVector<_Scalar> &y
) noexcept {
  assert(x.getSizes() == y.getSizes());
  zeroize(y);
  for ( auto tuple : x ) {
    y(tuple.template getIdx<0>()) = tuple.getValue();
  }
}

template <typename _Scalar>
inline void copy(
    const CooVector<_Scalar> &x,
          DenseVector<_Scalar> &&y
) noexcept {
  copy(x, y);
}
//@}

}  // namespace blas

}  // namespace mcnla

#endif  // MCNLA_BLAS_ROUTINE_COPY_COO_HPP_
