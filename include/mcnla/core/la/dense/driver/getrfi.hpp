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
template <typename _Val, Trans _trans>
DenseGetrfiDriver<_Val, _trans>::DenseGetrfiDriver() noexcept
  : size_(0),
    ipiv_(),
    work_() {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Val, Trans _trans>
DenseGetrfiDriver<_Val, _trans>::DenseGetrfiDriver(
    const index_t size
) noexcept
  : size_(size),
    ipiv_(size),
    work_(query()) {
  mcnla_assert_gt(size_, 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Val, Trans _trans>
DenseGetrfiDriver<_Val, _trans>::DenseGetrfiDriver(
    const MatrixType &a
) noexcept
  : DenseGetrfiDriver(a.nrow()) {
  mcnla_assert_true(a.isSquare());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  compute
///
template <typename _Val, Trans _trans>
void DenseGetrfiDriver<_Val, _trans>::operator()(
    MatrixType &a
) noexcept {
  compute(a);
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Val, Trans _trans>
void DenseGetrfiDriver<_Val, _trans>::operator()(
    MatrixType &&a
) noexcept {
  compute(a);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Reconstruct the driver.
///
template <typename _Val, Trans _trans> template <typename ..._Args>
void DenseGetrfiDriver<_Val, _trans>::reconstruct(
    _Args... args
) noexcept {
  *this = DenseGetrfiDriver<_Val, _trans>(args...);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the sizes.
///
template <typename _Val, Trans _trans>
std::tuple<index_t, index_t> DenseGetrfiDriver<_Val, _trans>::sizes() const noexcept {
  return std::make_tuple(size_, size_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the workspace
///
template <typename _Val, Trans _trans>
DenseVector<_Val>& DenseGetrfiDriver<_Val, _trans>::getWork() noexcept {
  return work_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getWork
///
template <typename _Val, Trans _trans>
const DenseVector<_Val>& DenseGetrfiDriver<_Val, _trans>::getWork() const noexcept {
  return work_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Computes the inverse of a general matrix using LU factorization.
///
/// @attention  Matrix @a a will be destroyed!
///
template <typename _Val, Trans _trans>
void DenseGetrfiDriver<_Val, _trans>::compute(
    MatrixType &a
) noexcept {
  mcnla_assert_eq(a.sizes(), this->sizes());

  mcnla_assert_pass(detail::getrf(size_, size_, a.valPtr(), a.pitch(), ipiv_.valPtr()));
  mcnla_assert_pass(detail::getri(size_, a.valPtr(), a.pitch(), ipiv_.valPtr(), work_.valPtr(), work_.len()));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Query the optimal workspace size.
///
template <typename _Val, Trans _trans>
index_t DenseGetrfiDriver<_Val, _trans>::query() noexcept {
  ValType lwork;
  mcnla_assert_pass(detail::getri(size_, nullptr, size_, nullptr, &lwork, -1));
  return lwork;
}

}  // namespace la

}  // namespace mcnla

#endif  // MCNLA_CORE_LA_DENSE_DRIVER_GETRFI_HPP_
