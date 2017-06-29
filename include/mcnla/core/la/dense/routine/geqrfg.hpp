////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/la/dense/routine/geqrfg.hpp
/// @brief   The LAPACK GEQRF+ORGQR routine.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_LA_DENSE_ROUTINE_GEQRFG_HPP_
#define MCNLA_CORE_LA_DENSE_ROUTINE_GEQRFG_HPP_

#include <mcnla/core/la/def.hpp>
#include <mcnla/core/matrix.hpp>
#include <mcnla/core/la/dense/driver/geqrfg.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The linear algebra namespace
//
namespace la {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  la_dense_lapack_le_module
/// @copydoc  mcnla::la::DenseGeqrfgDriver::compute
///
/// @see  mcnla::la::DenseGeqrfgDriver
///
template <typename _Val, Trans _trans>
inline void geqrfg(
    DenseMatrix<_Val, _trans> &a
) noexcept {
  DenseGeqrfgDriver<_Val, _trans> driver(a);
  driver(a);
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Val, Trans _trans>
inline void geqrfg(
    DenseMatrix<_Val, _trans> &&a
) noexcept {
  geqrfg(a);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace la

}  // namespace mcnla

#endif  // MCNLA_CORE_LA_DENSE_ROUTINE_GEQRFG_HPP_
