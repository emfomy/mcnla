////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/blas/routine/copy_coo.hpp
/// @brief   The BLAS COPY routine for COO types.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_BLAS_ROUTINE_COPY_COO_HPP_
#define MCNLA_CORE_BLAS_ROUTINE_COPY_COO_HPP_

#include <mcnla/core/matrix.hpp>
#include <mcnla/core/blas/routine/memset0.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The BLAS namespace
//
namespace blas {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  blas1_module
/// @brief  Copies COO vector to dense vector.
///
template <typename _Scalar>
inline void copy(
    const CooVector<_Scalar> &x,
          DenseVector<_Scalar> &y
) noexcept {
  mcnla_assert_eq(x.getSizes(), y.getSizes());
  mcnla_assert_eq(y.getStride(), 1);
  blas::memset0(y);
  for ( auto tuple : x ) {
    y(tuple.template getIdx<0>()) = tuple.getValue();
  }
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Scalar>
inline void copy(
    const CooVector<_Scalar> &x,
          DenseVector<_Scalar> &&y
) noexcept {
  copy(x, y);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace blas

}  // namespace mcnla

#endif  // MCNLA_CORE_BLAS_ROUTINE_COPY_COO_HPP_
