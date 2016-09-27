////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/matrix/base/sparse_base.ipp
/// @brief   The implementation of sparse container interface.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef ISVD_MATRIX_BASE_SPARSE_BASE_IPP_
#define ISVD_MATRIX_BASE_SPARSE_BASE_IPP_

#include <isvd/matrix/base/sparse_base.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Default constructor.
///
template <typename _Derived>
SparseBase<_Derived>::SparseBase() noexcept
  : nnz_(0) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Derived>
SparseBase<_Derived>::SparseBase(
    const index_t nnz
) noexcept
  : nnz_(nnz) {
  assert(nnz_ >= 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy constructor.
///
/// @attention  It is shallow copy. For deep copy, uses isvd::blas::copy.
///
template <typename _Derived>
SparseBase<_Derived>::SparseBase( const SparseBase &other ) noexcept
  : nnz_(other.nnz_) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Move constructor.
///
template <typename _Derived>
SparseBase<_Derived>::SparseBase( SparseBase &&other ) noexcept
  : nnz_(other.nnz_) {
  other.nnz_ = 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy assignment operator.
///
/// @attention  It is shallow copy. For deep copy, uses isvd::blas::copy.
///
template <typename _Derived>
SparseBase<_Derived>& SparseBase<_Derived>::operator=( const SparseBase &other ) noexcept {
  nnz_ = other.nnz_;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Move assignment operator.
///
template <typename _Derived>
SparseBase<_Derived>& SparseBase<_Derived>::operator=( SparseBase &&other ) noexcept {
  nnz_ = other.nnz_; other.nnz_ = 0;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the number of nonzero elements.
///
template <typename _Derived>
index_t SparseBase<_Derived>::getNnz() const noexcept { return nnz_; }

}  // namespace isvd

#endif  // ISVD_MATRIX_BASE_SPARSE_BASE_IPP_
