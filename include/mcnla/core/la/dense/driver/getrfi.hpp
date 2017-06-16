////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/la/dense/driver/getrfi.hpp
/// @brief   The LAPACK GETRF+GETRI driver.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_LA_DENSE_DRIVER_GETRFI_HPP_
#define MCNLA_CORE_LA_DENSE_DRIVER_GETRFI_HPP_

#include <mcnla/core/la/dense/driver/getrfi.hh>
#include <mcnla/core/la/raw/lapack/getrf.hpp>
#include <mcnla/core/la/raw/lapack/getri.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The linear algebra namespace
//
namespace la {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Default constructor.
///
template <class _Matrix>
GetrfiDriver<_Matrix>::GetrfiDriver() noexcept
  : size_(0),
    ipiv_(),
    work_() {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <class _Matrix>
GetrfiDriver<_Matrix>::GetrfiDriver(
    const index_t size
) noexcept
  : size_(size),
    ipiv_(size),
    work_(query(size)) {
  mcnla_assert_gt(size_, 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <class _Matrix>
GetrfiDriver<_Matrix>::GetrfiDriver(
    const MatrixType &a
) noexcept
  : GetrfiDriver(a.nrow()) {
  mcnla_assert_true(a.isSquare());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  compute
///
template <class _Matrix>
void GetrfiDriver<_Matrix>::operator()(
    MatrixType &a
) noexcept {
  compute(a);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  compute
///
template <class _Matrix>
void GetrfiDriver<_Matrix>::operator()(
    MatrixType &&a
) noexcept {
  compute(a);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Reconstruct the driver.
///
template <class _Matrix> template <typename ..._Args>
void GetrfiDriver<_Matrix>::reconstruct(
    _Args... args
) noexcept {
  *this = GetrfiDriver<_Matrix>(args...);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the sizes.
///
template <class _Matrix>
std::tuple<index_t> GetrfiDriver<_Matrix>::sizes() const noexcept {
  return std::make_tuple(size_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the workspace
///
template <class _Matrix>
VectorT<_Matrix>& GetrfiDriver<_Matrix>::getWork() noexcept {
  return work_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getWork
///
template <class _Matrix>
const VectorT<_Matrix>& GetrfiDriver<_Matrix>::getWork() const noexcept {
  return work_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Computes the inverse of an general matrix using LU factorization.
///
/// @attention  Matrix @a a will be destroyed!
///
template <class _Matrix>
void GetrfiDriver<_Matrix>::compute(
    MatrixType &a
) noexcept {
  mcnla_assert_eq(a.sizes(), std::make_tuple(size_, size_));

  mcnla_assert_pass(detail::getrf(size_, size_, a.valPtr(), a.pitch(), ipiv_.valPtr()));
  mcnla_assert_pass(detail::getri(size_, a.valPtr(), a.pitch(), ipiv_.valPtr(), work_.valPtr(), work_.len()));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Query the optimal workspace size.
///
template <class _Matrix>
index_t GetrfiDriver<_Matrix>::query(
    const index_t size
) noexcept {
  ValType lwork;
  mcnla_assert_pass(detail::getri(size, nullptr, size, nullptr, &lwork, -1));
  return lwork;
}

}  // namespace la

}  // namespace mcnla

#endif  // MCNLA_CORE_LA_DENSE_DRIVER_GETRFI_HPP_
