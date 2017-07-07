////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/la/dense/routine/getrfi.hpp
/// @brief   The LAPACK GETRF+GETRI routine.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_LA_DENSE_ROUTINE_GETRFI_HPP_
#define MCNLA_CORE_LA_DENSE_ROUTINE_GETRFI_HPP_

#include <mcnla/core/la/def.hpp>
#include <mcnla/core/matrix.hpp>
#include <mcnla/core/la/dense/driver/getrfi.hpp>

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
/// @copydoc  mcnla::la::DenseGetrfiDriver::compute
///
/// @see  mcnla::la::DenseGetrfiDriver
///
template <typename _Val, Trans _trans>
inline void getrfi(
    DenseMatrix<_Val, _trans> &a
) noexcept {
  DenseGetrfiDriver<_Val, _trans> driver(a);
  driver(a);
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Val, Trans _trans>
inline void getrfi(
    DenseMatrix<_Val, _trans> &&a
) noexcept {
  getrfi(a);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace la

}  // namespace mcnla

#endif  // MCNLA_CORE_LA_DENSE_ROUTINE_GETRFI_HPP_
