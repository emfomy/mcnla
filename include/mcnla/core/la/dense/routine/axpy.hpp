////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/la/dense/routine/axpy.hpp
/// @brief   The BLAS AXPY routine.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_LA_DENSE_ROUTINE_AXPY_HPP_
#define MCNLA_CORE_LA_DENSE_ROUTINE_AXPY_HPP_

#include <mcnla/core/la/def.hpp>
#include <mcnla/core/matrix.hpp>
#include <mcnla/core/la/raw/blas/axpy.hpp>

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
/// @brief  Computes a vector-scalar product and adds the result to a vector.
///
template <typename _Val>
inline void axpy(
    const DenseVector<_Val> &x,
          DenseVector<_Val> &y,
    const ValT<DenseVector<_Val>> alpha = 1
) noexcept {
  detail::axpy(x.len(), alpha, x.valPtr(), x.stride(), y.valPtr(), y.stride());
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Val>
inline void axpy(
    const DenseVector<_Val> &x,
          DenseVector<_Val> &&y,
    const ValT<DenseVector<_Val>> alpha = 1
) noexcept {
  axpy(x, y, alpha);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace la

}  // namespace mcnla

#endif  // MCNLA_CORE_LA_DENSE_ROUTINE_AXPY_HPP_
