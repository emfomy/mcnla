////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/matrix/dense/dense_iterator_base.ipp
/// @brief   The implementation of dense container iterator interface.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_MATRIX_DENSE_DENSE_ITERATOR_BASE_IPP_
#define ISVD_MATRIX_DENSE_DENSE_ITERATOR_BASE_IPP_

#include <isvd/matrix/dense/dense_iterator_base.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The internal namespace.
//
namespace internal {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Default constructor.
///
template <typename _Scalar, index_t _ndim, class _Container>
DenseIteratorBase<_Scalar, _ndim, _Container>::DenseIteratorBase() noexcept
  : itidx_(0),
    container_(nullptr) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given container.
///
template <typename _Scalar, index_t _ndim, class _Container>
DenseIteratorBase<_Scalar, _ndim, _Container>::DenseIteratorBase(
    _Container *container
) noexcept
  : itidx_(0),
    container_(container) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy constructor.
///
template <typename _Scalar, index_t _ndim, class _Container>
DenseIteratorBase<_Scalar, _ndim, _Container>::DenseIteratorBase(
    const DenseIteratorBase &other
) noexcept
  : itidx_(other.itidx_),
    container_(other.container_) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy assignment operator.
///
template <typename _Scalar, index_t _ndim, class _Container>
DenseIteratorBase<_Scalar, _ndim, _Container>& DenseIteratorBase<_Scalar, _ndim, _Container>::operator=(
    const DenseIteratorBase &other
) noexcept {
  itidx_ = other.itidx_; container_ = other.container_;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Equal-to operator.
///
template <typename _Scalar, index_t _ndim, class _Container>
bool DenseIteratorBase<_Scalar, _ndim, _Container>::operator==(
    const DenseIteratorBase &other
) const noexcept {
  return (container_ == other.container_) && (itidx_ == other.itidx_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Not-equal-to operator.
///
template <typename _Scalar, index_t _ndim, class _Container>
bool DenseIteratorBase<_Scalar, _ndim, _Container>::operator!=(
    const DenseIteratorBase &other
) const noexcept {
  return !(*this == other);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Prefix increment operator.
///
template <typename _Scalar, index_t _ndim, class _Container>
DenseIteratorBase<_Scalar, _ndim, _Container>& DenseIteratorBase<_Scalar, _ndim, _Container>::operator++() noexcept {
  assert(container_ != nullptr);

  const auto nelem = container_->getNelem();
  if ( ++itidx_ >= nelem ) {
    itidx_ = nelem;
  }
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Postfix increment operator.
///
template <typename _Scalar, index_t _ndim, class _Container>
DenseIteratorBase<_Scalar, _ndim, _Container> DenseIteratorBase<_Scalar, _ndim, _Container>::operator++( int ) noexcept {
  auto retval(*this);
  ++(*this);
  return retval;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Sets the iterator to beginning.
///
template <typename _Scalar, index_t _ndim, class _Container>
DenseIteratorBase<_Scalar, _ndim, _Container>& DenseIteratorBase<_Scalar, _ndim, _Container>::setBegin() noexcept {
  itidx_ = 0;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Sets the iterator to end.
///
template <typename _Scalar, index_t _ndim, class _Container>
DenseIteratorBase<_Scalar, _ndim, _Container>& DenseIteratorBase<_Scalar, _ndim, _Container>::setEnd() noexcept {
  itidx_ = (container_ != nullptr) ? container_->getNelem() : 0;
  return *this;
}

}  // namespace internal

}  // namespace isvd

#endif  // ISVD_MATRIX_DENSE_DENSE_ITERATOR_BASE_IPP_
