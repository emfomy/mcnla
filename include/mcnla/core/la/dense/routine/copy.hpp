////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/la/dense/routine/copy.hpp
/// @brief   The BLAS COPY routine.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_LA_DENSE_ROUTINE_COPY_HPP_
#define MCNLA_CORE_LA_DENSE_ROUTINE_COPY_HPP_

#include <mcnla/core/la/def.hpp>
#include <mcnla/core/matrix.hpp>
#include <mcnla/core/la/raw/blas/copy.hpp>

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
/// @brief  Copies vector to another vector.
///
template <typename _Val>
inline void copy(
    const DenseVector<_Val> &x,
          DenseVector<_Val> &y
) noexcept {
  mcnla_assert_eq(x.sizes(), y.sizes());
  detail::copy(x.length(), x.valPtr(), x.stride(), y.valPtr(), y.stride());
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Val>
inline void copy(
    const DenseVector<_Val> &x,
          DenseVector<_Val> &&y
) noexcept {
  copy(x, y);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace la

}  // namespace mcnla

#endif  // MCNLA_CORE_LA_DENSE_ROUTINE_COPY_HPP_
