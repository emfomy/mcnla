////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/base/cube_base.ipp
/// @brief   The implementation of cube interface.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_BASE_CUBE_BASE_IPP_
#define MCNLA_CORE_MATRIX_BASE_CUBE_BASE_IPP_

#include <mcnla/core/matrix/base/cube_base.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Default constructor.
///
template <class _Derived>
CubeBase<_Derived>::CubeBase() noexcept
  : nrow_(0),
    ncol_(0),
    npage_(0) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <class _Derived>
CubeBase<_Derived>::CubeBase(
    const index_t nrow,
    const index_t ncol,
    const index_t npage
) noexcept
  : nrow_(nrow),
    ncol_(ncol),
    npage_(npage) {
  assert(nrow_ >= 0 && ncol_ >= 0 && npage >= 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <class _Derived>
CubeBase<_Derived>::CubeBase(
    const std::tuple<index_t, index_t, index_t> sizes
) noexcept
  : CubeBase(std::get<0>(sizes), std::get<1>(sizes), std::get<2>(sizes)) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy constructor.
///
/// @attention  It is shallow copy. For deep copy, uses mcnla::blas::copy.
///
template <class _Derived>
CubeBase<_Derived>::CubeBase( const CubeBase &other ) noexcept
  : nrow_(other.nrow_),
    ncol_(other.ncol_),
    npage_(other.npage_) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Move constructor.
///
template <class _Derived>
CubeBase<_Derived>::CubeBase( CubeBase &&other ) noexcept
  : nrow_(other.nrow_),
    ncol_(other.ncol_),
    npage_(other.npage_) {
  other.nrow_ = 0;
  other.ncol_ = 0;
  other.npage_ = 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy assignment operator.
///
/// @attention  It is shallow copy. For deep copy, uses mcnla::blas::copy.
///
template <class _Derived>
CubeBase<_Derived>& CubeBase<_Derived>::operator=( const CubeBase &other ) noexcept {
  nrow_ = other.nrow_; ncol_ = other.ncol_; npage_ = other.npage_;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Move assignment operator.
///
template <class _Derived>
CubeBase<_Derived>& CubeBase<_Derived>::operator=( CubeBase &&other ) noexcept {
  nrow_ = other.nrow_; ncol_ = other.ncol_; npage_ = other.npage_;
  other.nrow_ = 0;     other.ncol_ = 0;     other.npage_ = 0;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the number of rows.
///
template <class _Derived> template <TransOption _trans>
index_t CubeBase<_Derived>::getNrow() const noexcept {
  return !isTranspose(_trans) ? nrow_ : ncol_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the number of columns.
///
template <class _Derived> template <TransOption _trans>
index_t CubeBase<_Derived>::getNcol() const noexcept {
  return !isTranspose(_trans) ? ncol_ : nrow_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the number of pages.
///
template <class _Derived>
index_t CubeBase<_Derived>::getNpage() const noexcept { return npage_; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the size.
///
template <class _Derived> template <index_t _dim>
index_t CubeBase<_Derived>::getSize() const noexcept {
  static_assert(_dim >= 0 && _dim < 3, "Invalid dimension!");
  return (_dim == 0) ? size0_ :
        ((_dim == 1) ? size1_ : size2_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the number of elements.
///
template <class _Derived>
index_t CubeBase<_Derived>::getNelem() const noexcept { return size0_ * size1_ * size2_; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the sizes.
///
template <class _Derived>
std::tuple<index_t, index_t, index_t> CubeBase<_Derived>::getSizes() const noexcept {
  return std::make_tuple(nrow_, ncol_, npage_);
}

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_BASE_CUBE_BASE_IPP_
