////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/coo/coo_matrix.hpp
/// @brief   The COO matrix.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_COO_COO_MATRIX_HPP_
#define MCNLA_CORE_MATRIX_COO_COO_MATRIX_HPP_

#include <mcnla/core/matrix/coo/coo_matrix.hh>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Default constructor.
///
template <typename _Val, Trans _trans>
CooMatrix<_Val, _trans>::CooMatrix() noexcept
  : BaseType() {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Val, Trans _trans>
CooMatrix<_Val, _trans>::CooMatrix(
    const index_t nrow,
    const index_t ncol,
    const index_t nnz
) noexcept
  : BaseType(toDim0(nrow, ncol), toDim1(nrow, ncol), nnz) {
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Val, Trans _trans>
CooMatrix<_Val, _trans>::CooMatrix(
    const SizesType sizes,
    const index_t nnz
) noexcept
  : BaseType(toDim0(sizes), toDim1(sizes), nnz) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Val, Trans _trans>
CooMatrix<_Val, _trans>::CooMatrix(
    const index_t nrow,
    const index_t ncol,
    const index_t nnz,
    const index_t capacity
) noexcept
  : BaseType(toDim0(nrow, ncol), toDim1(nrow, ncol), nnz, capacity) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Val, Trans _trans>
CooMatrix<_Val, _trans>::CooMatrix(
    const SizesType sizes,
    const index_t nnz,
    const index_t capacity
) noexcept
  : BaseType(toDim0(sizes), toDim1(sizes), nnz, capacity) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given raw data.
///
template <typename _Val, Trans _trans>
CooMatrix<_Val, _trans>::CooMatrix(
    const index_t nrow,
    const index_t ncol,
    const index_t nnz,
    const ValArrayType &val,
    const IdxArrayType &colidx,
    const IdxArrayType &rowidx,
    const index_t offset
) noexcept
  : BaseType(toDim0(nrow, ncol), toDim1(nrow, ncol), nnz, val, toIdx0(colidx, rowidx), toIdx1(colidx, rowidx), offset) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy constructor.
///
/// @attention  It is shallow copy (creates an alias).
///
template <typename _Val, Trans _trans>
CooMatrix<_Val, _trans>::CooMatrix(
    const CooMatrix &other
) noexcept
  : BaseType(other) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Move constructor.
///
template <typename _Val, Trans _trans>
CooMatrix<_Val, _trans>::CooMatrix(
    CooMatrix &&other
) noexcept
  : BaseType(std::move(other)) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy assignment operator.
///
/// @attention  It is shallow copy (creates an alias).
///
template <typename _Val, Trans _trans>
CooMatrix<_Val, _trans>& CooMatrix<_Val, _trans>::operator=(
    const CooMatrix &other
) noexcept {
  BaseType::operator=(other);
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Move assignment operator.
///
template <typename _Val, Trans _trans>
CooMatrix<_Val, _trans>& CooMatrix<_Val, _trans>::operator=(
    CooMatrix &&other
) noexcept {
  BaseType::operator=(std::move(other));
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copies the matrix.
///
template <typename _Val, Trans _trans>
CooMatrix<_Val, _trans> CooMatrix<_Val, _trans>::copy() const noexcept {
  CooMatrix retval(this->sizes(), this->nnz(), this->capacity());
  retval.val().valarray() = this->val().valarray();
  return retval;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the capacity of the row index array.
///
template <typename _Val, Trans _trans>
index_t CooMatrix<_Val, _trans>::rowidxCapacity() const noexcept {
  return !isTrans(_trans) ? this->idx0Capacity() : this->idx1Capacity();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the capacity of the index array.
///
template <typename _Val, Trans _trans>
index_t CooMatrix<_Val, _trans>::colidxCapacity() const noexcept {
  return !isTrans(_trans) ? this->idx1Capacity() : this->idx0Capacity();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the offset of the row index array.
///
template <typename _Val, Trans _trans>
index_t CooMatrix<_Val, _trans>::rowidxOffset() const noexcept {
  return !isTrans(_trans) ? this->idx0Offset() : this->idx1Offset();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the offset of the index array.
///
template <typename _Val, Trans _trans>
index_t CooMatrix<_Val, _trans>::colidxOffset() const noexcept {
  return !isTrans(_trans) ? this->idx1Offset() : this->idx0Offset();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the row index array.
///
template <typename _Val, Trans _trans>
Array<index_t>& CooMatrix<_Val, _trans>::rowidx() noexcept {
  return !isTrans(_trans) ? this->idx0() : this->idx1();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  rowidx
///
template <typename _Val, Trans _trans>
const Array<index_t>& CooMatrix<_Val, _trans>::rowidx() const noexcept {
  return !isTrans(_trans) ? this->idx0() : this->idx1();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the index array.
///
template <typename _Val, Trans _trans>
Array<index_t>& CooMatrix<_Val, _trans>::colidx() noexcept {
  return !isTrans(_trans) ? this->idx1() : this->idx0();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  colidx
///
template <typename _Val, Trans _trans>
const Array<index_t>& CooMatrix<_Val, _trans>::colidx() const noexcept {
  return !isTrans(_trans) ? this->idx1() : this->idx0();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the raw index pointer.
///
template <typename _Val, Trans _trans>
index_t* CooMatrix<_Val, _trans>::rowidxPtr() noexcept {
  return !isTrans(_trans) ? this->idx0Ptr() : this->idx1Ptr();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  rowidxPtr
///
template <typename _Val, Trans _trans>
const index_t* CooMatrix<_Val, _trans>::rowidxPtr() const noexcept {
  return !isTrans(_trans) ? this->idx0Ptr() : this->idx1Ptr();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the raw index pointer.
///
template <typename _Val, Trans _trans>
index_t* CooMatrix<_Val, _trans>::colidxPtr() noexcept {
  return !isTrans(_trans) ? this->idx1Ptr() : this->idx0Ptr();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  colidxPtr
///
template <typename _Val, Trans _trans>
const index_t* CooMatrix<_Val, _trans>::colidxPtr() const noexcept {
  return !isTrans(_trans) ? this->idx1Ptr() : this->idx0Ptr();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::CooMatrixStorage::elemImpl
///
template <typename _Val, Trans _trans>
_Val CooMatrix<_Val, _trans>::operator()(
    const index_t rowidx,
    const index_t colidx
) noexcept {
  return !isTrans(_trans) ? this->elemImpl(rowidx, colidx) : this->elemImpl(colidx, rowidx);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::CooMatrixStorage::elemImpl
///
template <typename _Val, Trans _trans>
const _Val CooMatrix<_Val, _trans>::operator()(
    const index_t rowidx,
    const index_t colidx
) const noexcept {
  return !isTrans(_trans) ? this->elemImpl(rowidx, colidx) : this->elemImpl(colidx, rowidx);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::CooMatrixStorage::posImpl
///
template <typename _Val, Trans _trans>
index_t CooMatrix<_Val, _trans>::pos(
    const index_t rowidx,
    const index_t colidx
) const noexcept {
  return !isTrans(_trans) ? this->posImpl(rowidx, colidx) : this->posImpl(colidx, rowidx);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Reconstruct the matrix.
///
/// @attention  The data is also reallocated.
///
template <typename _Val, Trans _trans> template <typename... Args>
void CooMatrix<_Val, _trans>::reconstruct(
    Args... args
) noexcept {
  *this = CooMatrix<_Val, _trans>(args...);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::CooMatrixStorage::resizeImpl
///
template <typename _Val, Trans _trans>
void CooMatrix<_Val, _trans>::resize(
    const index_t nrow,
    const index_t ncol,
    const index_t nnz
) noexcept {
  this->resizeImpl(toDim0(nrow, ncol), toDim1(nrow, ncol), nnz);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the transpose of the matrix.
///
/// @attention  The storage layout is also changed.
///
template <typename _Val, Trans _trans>
CooMatrix<_Val, changeTrans(_trans)>& CooMatrix<_Val, _trans>::t() noexcept {
  return static_cast<TransposeType&>(base());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  t
///
template <typename _Val, Trans _trans>
const CooMatrix<_Val, changeTrans(_trans)>& CooMatrix<_Val, _trans>::t() const noexcept {
  return static_cast<const TransposeType&>(base());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the conjugate of the matrix.
///
template <typename _Val, Trans _trans>
CooMatrix<_Val, changeConj(_trans)>& CooMatrix<_Val, _trans>::c() noexcept {
  return static_cast<ConjugateType&>(base());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  c
///
template <typename _Val, Trans _trans>
const CooMatrix<_Val, changeConj(_trans)>& CooMatrix<_Val, _trans>::c() const noexcept {
  return static_cast<const ConjugateType&>(base());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the conjugate transpose of the matrix.
///
/// @attention  The storage layout is also changed.
///
template <typename _Val, Trans _trans>
CooMatrix<_Val, changeHerm(_trans)>& CooMatrix<_Val, _trans>::h() noexcept {
  return static_cast<HermitianType&>(base());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  t
///
template <typename _Val, Trans _trans>
const CooMatrix<_Val, changeHerm(_trans)>& CooMatrix<_Val, _trans>::h() const noexcept {
  return static_cast<const HermitianType&>(base());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets a column vector segment.
///
template <typename _Val, Trans _trans>
CooVector<_Val> CooMatrix<_Val, _trans>::operator()(
    const FullRange,
    const index_t colidx
) noexcept {
  static_assert(!isTrans(_trans), "This routine is only available in column-major matrices.");
  return static_cast<VectorType&&>(this->getVector0Impl(colidx));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  operator()( const FullRange, const index_t )
///
template <typename _Val, Trans _trans>
const CooVector<_Val> CooMatrix<_Val, _trans>::operator()(
    const FullRange,
    const index_t colidx
) const noexcept {
  static_assert(!isTrans(_trans), "This routine is only available in column-major matrices.");
  return static_cast<VectorType&&>(this->getVector0Impl(colidx));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets a row vector segment.
///
template <typename _Val, Trans _trans>
CooVector<_Val> CooMatrix<_Val, _trans>::operator()(
    const index_t rowidx,
    const FullRange
) noexcept {
  static_assert(isTrans(_trans), "This routine is only available in row-major matrices.");
  return static_cast<VectorType&&>(this->getVector0Impl(rowidx));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  operator()( const index_t, const FullRange )
///
template <typename _Val, Trans _trans>
const CooVector<_Val> CooMatrix<_Val, _trans>::operator()(
    const index_t rowidx,
    const FullRange
) const noexcept {
  static_assert(isTrans(_trans), "This routine is only available in row-major matrices.");
  return static_cast<VectorType&&>(this->getVector0Impl(rowidx));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::MatrixWrapper::nrow
///
template <typename _Val, Trans _trans>
index_t CooMatrix<_Val, _trans>::nrowImpl() const noexcept {
  return !isTrans(_trans) ? this->dim0() : this->dim1();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::MatrixWrapper::ncol
///
template <typename _Val, Trans _trans>
index_t CooMatrix<_Val, _trans>::ncolImpl() const noexcept {
  return !isTrans(_trans) ? this->dim1() : this->dim0();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Gets the first dimension from sizes.
///
template <typename _Val, Trans _trans>
index_t CooMatrix<_Val, _trans>::toDim0(
    const SizesType sizes
) const noexcept {
  return !isTrans(_trans) ? std::get<0>(sizes) : std::get<1>(sizes);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  toDim0
///
template <typename _Val, Trans _trans>
index_t CooMatrix<_Val, _trans>::toDim0(
    const index_t nrow,
    const index_t ncol
) const noexcept {
  return !isTrans(_trans) ? nrow : ncol;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Gets the second dimension from sizes.
///
template <typename _Val, Trans _trans>
index_t CooMatrix<_Val, _trans>::toDim1(
    const SizesType sizes
) const noexcept {
  return !isTrans(_trans) ? std::get<1>(sizes) : std::get<0>(sizes);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  toDim1
///
template <typename _Val, Trans _trans>
index_t CooMatrix<_Val, _trans>::toDim1(
    const index_t nrow,
    const index_t ncol
) const noexcept {
  return !isTrans(_trans) ? ncol : nrow;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Gets the first dimension index array.
///
template <typename _Val, Trans _trans>
Array<index_t>& CooMatrix<_Val, _trans>::toIdx0(
    IdxArrayType &rowidx,
    IdxArrayType &colidx
) const noexcept {
  return !isTrans(_trans) ? rowidx : colidx;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  toIdx0
///
template <typename _Val, Trans _trans>
const Array<index_t>& CooMatrix<_Val, _trans>::toIdx0(
    const IdxArrayType &rowidx,
    const IdxArrayType &colidx
) const noexcept {
  return !isTrans(_trans) ? rowidx : colidx;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Gets the second dimension index array.
///
template <typename _Val, Trans _trans>
Array<index_t>& CooMatrix<_Val, _trans>::toIdx1(
    IdxArrayType &rowidx,
    IdxArrayType &colidx
) const noexcept {
  return !isTrans(_trans) ? colidx : rowidx;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  toIdx1
///
template <typename _Val, Trans _trans>
const Array<index_t>& CooMatrix<_Val, _trans>::toIdx1(
    const IdxArrayType &rowidx,
    const IdxArrayType &colidx
) const noexcept {
  return !isTrans(_trans) ? colidx : rowidx;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Convert to base class.
///
template <typename _Val, Trans _trans>
CooMatrixStorage<_Val>& CooMatrix<_Val, _trans>::base() noexcept {
  return static_cast<BaseType&>(*this);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  base
///
template <typename _Val, Trans _trans>
const CooMatrixStorage<_Val>& CooMatrix<_Val, _trans>::base() const noexcept {
  return static_cast<const BaseType&>(*this);
}

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_COO_COO_MATRIX_HPP_
