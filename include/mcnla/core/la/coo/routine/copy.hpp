////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/la/coo/routine/copy.hpp
/// @brief   The BLAS COPY routine for COO format.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_LA_COO_ROUTINE_COPY_HPP_
#define MCNLA_CORE_LA_COO_ROUTINE_COPY_HPP_

#include <mcnla/core/la/def.hpp>
#include <mcnla/core/matrix.hpp>
#include <mcnla/core/la/dense/routine/scal0.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The linear algebra namespace
//
namespace la {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  la_coo_blas1_module
/// @brief  Copies vector to another vector.
///
template <typename _Scalar>
inline void copy(
    const CooVector<_Scalar> &x,
          DenseVector<_Scalar> &y
) noexcept {
  mcnla_assert_eq(x.sizes(), y.sizes());

  scal0(y);
  for ( index_t i = 0; i < x.nnz(); ++i ) {
    y(x.idxPtr()[i]) = x.valPtr()[i];
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

}  // namespace la

}  // namespace mcnla

#endif  // MCNLA_CORE_LA_COO_ROUTINE_COPY_HPP_
