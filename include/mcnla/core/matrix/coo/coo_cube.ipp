////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/coo/coo_cube.ipp
/// @brief   The implementation of COO cube.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_COO_COO_CUBE_IPP_
#define MCNLA_CORE_MATRIX_COO_COO_CUBE_IPP_

#include <mcnla/core/matrix/coo/coo_cube.hpp>
#include <iomanip>

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
template <typename _Scalar, Layout _layout>
CooCube<_Scalar, _layout>::CooCube() noexcept
  : CubeBaseType(),
    CooBaseType() {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Scalar, Layout _layout>
CooCube<_Scalar, _layout>::CooCube(
    const index_t nrow,
    const index_t ncol,
    const index_t npage
) noexcept
  : CubeBaseType(nrow, ncol, npage),
    CooBaseType(size0_ * size1_ * size2_) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Scalar, Layout _layout>
CooCube<_Scalar, _layout>::CooCube(
    const std::tuple<index_t, index_t, index_t> sizes
) noexcept
  : CooCube(std::get<0>(sizes), std::get<1>(sizes), std::get<2>(sizes)) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Scalar, Layout _layout>
CooCube<_Scalar, _layout>::CooCube(
    const index_t nrow,
    const index_t ncol,
    const index_t npage,
    const index_t capacity
) noexcept
  : CubeBaseType(nrow, ncol, npage),
    CooBaseType(capacity) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Scalar, Layout _layout>
CooCube<_Scalar, _layout>::CooCube(
    const std::tuple<index_t, index_t, index_t> sizes,
    const index_t capacity
) noexcept
  : CooCube(std::get<0>(sizes), std::get<1>(sizes), std::get<2>(sizes), capacity) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Scalar, Layout _layout>
CooCube<_Scalar, _layout>::CooCube(
    const index_t nrow,
    const index_t ncol,
    const index_t npage,
    const index_t nnz,
    const index_t capacity,
    const index_t offset
) noexcept
  : CubeBaseType(nrow, ncol, npage),
    CooBaseType(nnz, capacity, offset) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Scalar, Layout _layout>
CooCube<_Scalar, _layout>::CooCube(
    const std::tuple<index_t, index_t, index_t> sizes,
    const index_t nnz,
    const index_t capacity,
    const index_t offset
) noexcept
  : CooCube(std::get<0>(sizes), std::get<1>(sizes), std::get<2>(sizes), nnz, capacity, offset) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given raw data.
///
template <typename _Scalar, Layout _layout>
CooCube<_Scalar, _layout>::CooCube(
    const index_t nrow,
    const index_t ncol,
    const index_t npage,
    const index_t nnz,
    const ValuePtrType &value,
    const IdxPtrType &rowidx,
    const IdxPtrType &colidx,
    const IdxPtrType &pageidx,
    const index_t offset
) noexcept
  : CubeBaseType(nrow, ncol, npage),
    CooBaseType(nnz, value, {isColMajor(_layout) ? rowidx : colidx, isColMajor(_layout) ? colidx : rowidx, pageidx}, offset) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct from data storage.
///
template <typename _Scalar, Layout _layout>
CooCube<_Scalar, _layout>::CooCube(
    const index_t nrow,
    const index_t ncol,
    const index_t npage,
    const index_t nnz,
    const DataType &data,
    const index_t offset
) noexcept
  : CubeBaseType(nrow, ncol, npage),
    CooBaseType(nnz, data, offset) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy constructor.
///
/// @attention  It is shallow copy. For deep copy, uses mcnla::blas::copy.
///
template <typename _Scalar, Layout _layout>
CooCube<_Scalar, _layout>::CooCube( const CooCube &other ) noexcept
  : CubeBaseType(other),
    CooBaseType(other) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Move constructor.
///
template <typename _Scalar, Layout _layout>
CooCube<_Scalar, _layout>::CooCube( CooCube &&other ) noexcept
  : CubeBaseType(std::move(other)),
    CooBaseType(std::move(other)) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy assignment operator.
///
/// @attention  It is shallow copy. For deep copy, uses mcnla::blas::copy.
///
template <typename _Scalar, Layout _layout>
CooCube<_Scalar, _layout>& CooCube<_Scalar, _layout>::operator=( const CooCube &other ) noexcept {
  CubeBaseType::operator=(other); CooBaseType::operator=(other);
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Move assignment operator.
///
template <typename _Scalar, Layout _layout>
CooCube<_Scalar, _layout>& CooCube<_Scalar, _layout>::operator=( CooCube &&other ) noexcept {
  CubeBaseType::operator=(std::move(other)); CooBaseType::operator=(std::move(other));
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Print to stream.
///
template <typename __Scalar, Layout __layout>
std::ostream& operator<< ( std::ostream &out, const CooCube<__Scalar, __layout> &cube ) {
  for ( auto it = cube.begin(); it != cube.end(); ++it ) {
    out << it;
  }
  return out;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the row index array.
///
template <typename _Scalar, Layout _layout>
index_t* CooCube<_Scalar, _layout>::getRowIdx() noexcept {
  return CooBaseType::template getIdx<isColMajor(_layout) ? 0 : 1>();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getRowIdx
///
template <typename _Scalar, Layout _layout>
const index_t* CooCube<_Scalar, _layout>::getRowIdx() const noexcept {
  return CooBaseType::template getIdx<isColMajor(_layout) ? 0 : 1>();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the column index array.
///
template <typename _Scalar, Layout _layout>
index_t* CooCube<_Scalar, _layout>::getColIdx() noexcept {
  return CooBaseType::template getIdx<isColMajor(_layout) ? 1 : 0>();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getColIdx
///
template <typename _Scalar, Layout _layout>
const index_t* CooCube<_Scalar, _layout>::getColIdx() const noexcept {
  return CooBaseType::template getIdx<isColMajor(_layout) ? 1 : 0>();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the page index array.
///
template <typename _Scalar, Layout _layout>
index_t* CooCube<_Scalar, _layout>::getPageIdx() noexcept {
  return CooBaseType::template getIdx<2>();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getPageIdx
///
template <typename _Scalar, Layout _layout>
const index_t* CooCube<_Scalar, _layout>::getPageIdx() const noexcept {
  return CooBaseType::template getIdx<2>();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the element of given index.
///
template <typename _Scalar, Layout _layout>
_Scalar CooCube<_Scalar, _layout>::getElem(
    const index_t rowidx,
    const index_t colidx,
    const index_t pageidx
) const noexcept {
  assert(rowidx >= 0 && rowidx < nrow_);
  assert(colidx >= 0 && colidx < ncol_);
  assert(pageidx >= 0 && pageidx < npage_);
  auto it = find(rowidx, colidx, pageidx);
  return (it != this->end()) ? it.getValue() : 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getElem
///
template <typename _Scalar, Layout _layout>
_Scalar CooCube<_Scalar, _layout>::operator()(
    const index_t rowidx,
    const index_t colidx,
    const index_t pageidx
) const noexcept { return getElem(rowidx, colidx, pageidx); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the internal position of given index.
//
/// @attention  Returns `-1` if the index does not exist!
///
template <typename _Scalar, Layout _layout>
index_t CooCube<_Scalar, _layout>::getPos(
    const index_t rowidx,
    const index_t colidx,
    const index_t pageidx
) const noexcept {
  assert(rowidx >= 0 && rowidx < nrow_);
  assert(colidx >= 0 && colidx < ncol_);
  assert(pageidx >= 0 && pageidx < npage_);
  auto it = find(rowidx, colidx, pageidx);
  return (it != this->end()) ? it.getPos() : -1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the internal position and nonzero elements of given index range.
///
template <typename _Scalar, Layout _layout>
void CooCube<_Scalar, _layout>::getPosNnz(
    const IdxRange rowrange,
    const IdxRange colrange,
    const IdxRange pagerange,
          index_t &pos,
          index_t &nnz
) const noexcept {
  assert(rowrange.begin >= 0 && rowrange.end <= nrow_ && rowrange.getLength() >= 0);
  assert(colrange.begin >= 0 && colrange.end <= ncol_ && colrange.getLength() >= 0);
  assert(pagerange.begin >= 0 && pagerange.end <= npage_ && pagerange.getLength() >= 0);
  assert(isSorted());
  auto begintuple = isColMajor(_layout) ? makeCooTuple(rowrange.begin, colrange.begin, pagerange.begin)
                                        : makeCooTuple(colrange.begin, rowrange.begin, pagerange.begin);
  auto endtuple   = isColMajor(_layout) ? makeCooTuple(rowrange.end, colrange.end, pagerange.end)
                                        : makeCooTuple(colrange.end, rowrange.end, pagerange.end);
  auto it0 = std::lower_bound(this->begin(), this->end(), begintuple);
  auto it1 = std::lower_bound(it0, this->end(), endtuple);
  pos = it0.getPos();
  nnz = it1.getPos() - pos;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Finds the iterator to element
///
template <typename _Scalar, Layout _layout>
typename CooCube<_Scalar, _layout>::IteratorType CooCube<_Scalar, _layout>::find(
    const index_t rowidx,
    const index_t colidx,
    const index_t pageidx
) noexcept {
  assert(rowidx >= 0 && rowidx < nrow_);
  assert(colidx >= 0 && colidx < ncol_);
  assert(pageidx >= 0 && pageidx < npage_);
  assert(isSorted());
  auto tuple = isColMajor(_layout) ? makeCooTuple(rowidx, colidx, pageidx) : makeCooTuple(colidx, rowidx, pageidx);
  auto it = std::lower_bound(this->begin(), this->end(), tuple);
  return (it == this->end() || *it == tuple) ? it : this->end();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  find
///
template <typename _Scalar, Layout _layout>
typename CooCube<_Scalar, _layout>::ConstIteratorType CooCube<_Scalar, _layout>::find(
    const index_t rowidx,
    const index_t colidx,
    const index_t pageidx
) const noexcept {
  assert(rowidx >= 0 && rowidx < nrow_);
  assert(colidx >= 0 && colidx < ncol_);
  assert(pageidx >= 0 && pageidx < npage_);
  assert(isSorted());
  auto tuple = isColMajor(_layout) ? makeCooTuple(rowidx, colidx, pageidx) : makeCooTuple(colidx, rowidx, pageidx);
  auto it = std::lower_bound(this->begin(), this->end(), tuple);
  return (it == this->end() || *it == tuple) ? it : this->end();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  find
///
template <typename _Scalar, Layout _layout>
typename CooCube<_Scalar, _layout>::ConstIteratorType CooCube<_Scalar, _layout>::cfind(
    const index_t rowidx,
    const index_t colidx,
    const index_t pageidx
) const noexcept {
  return find(rowidx, colidx, pageidx);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Sorts the cube.
///
template <typename _Scalar, Layout _layout>
void CooCube<_Scalar, _layout>::sort() noexcept {
  std::sort(this->begin(), this->end());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Check if the cube is sorted.
///
template <typename _Scalar, Layout _layout>
bool CooCube<_Scalar, _layout>::isSorted() const noexcept {
  return std::is_sorted(this->begin(), this->end());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the transpose of the cube.
///
/// @attention  The storage layout is also changed.
///
template <typename _Scalar, Layout _layout>
CooCube<_Scalar, changeLayout(_layout)> CooCube<_Scalar, _layout>::transpose() noexcept {
  return CooCube<_Scalar, changeLayout(_layout)>(ncol_, nrow_, npage_, nnz_, data_, offset_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Resizes the cube.
///
/// @attention  The new space is not initialized.
///
template <typename _Scalar, Layout _layout>
void CooCube<_Scalar, _layout>::resize(
    const index_t nrow,
    const index_t ncol,
    const index_t npage
) noexcept {
  assert(nrow >= 0 && ncol >= 0 && npage >= 0);
  nrow_ = nrow;
  ncol_ = ncol;
  npage_ = npage;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets a matrix block.
///
template <typename _Scalar, Layout _layout>
CooMatrix<_Scalar, _layout> CooCube<_Scalar, _layout>::getPage(
    const index_t pageidx
) noexcept {
  assert(pageidx >= 0 && pageidx < npage_);
  index_t pos, nnz; getPosNnz({0, nrow_}, {0, ncol_}, {pageidx, pageidx}, pos, nnz);
  return CooMatrix<_Scalar, _layout>(nrow_, ncol_, nnz, data_.template getReduced<0, 1>(), pos + offset_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getPage
///
template <typename _Scalar, Layout _layout>
const CooMatrix<_Scalar, _layout> CooCube<_Scalar, _layout>::getPage(
    const index_t pageidx
) const noexcept {
  assert(pageidx >= 0 && pageidx < npage_);
  index_t pos, nnz; getPosNnz({0, nrow_}, {0, ncol_}, {pageidx, pageidx}, pos, nnz);
  return CooMatrix<_Scalar, _layout>(nrow_, ncol_, nnz, data_.template getReduced<0, 1>(), pos + offset_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets a vector segment.
///
/// @attention  This routine is only available in column-major matrices.
///
template <typename _Scalar, Layout _layout>
CooVector<_Scalar> CooCube<_Scalar, _layout>::getCol(
    const index_t colidx,
    const index_t pageidx
) noexcept {
  static_assert(isColMajor(_layout), "This routine is only available in column-major matrices.");
  assert(colidx >= 0 && colidx < ncol_);
  assert(pageidx >= 0 && pageidx < npage_);
  index_t pos, nnz; getPosNnz({0, nrow_}, {colidx, colidx}, {pageidx, pageidx}, pos, nnz);
  return CooVector<_Scalar>(nrow_, nnz, data_.template getReduced<0>(), pos + offset_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getCol
///
template <typename _Scalar, Layout _layout>
const CooVector<_Scalar> CooCube<_Scalar, _layout>::getCol(
    const index_t colidx,
    const index_t pageidx
) const noexcept {
  static_assert(isColMajor(_layout), "This routine is only available in column-major matrices.");
  assert(colidx >= 0 && colidx < ncol_);
  assert(pageidx >= 0 && pageidx < npage_);
  index_t pos, nnz; getPosNnz({0, nrow_}, {colidx, colidx}, {pageidx, pageidx}, pos, nnz);
  return CooVector<_Scalar>(nrow_, nnz, data_.template getReduced<0>(), pos + offset_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets a vector segment.
///
/// @attention  This routine is only available in row-major matrices.
///
template <typename _Scalar, Layout _layout>
CooVector<_Scalar> CooCube<_Scalar, _layout>::getRow(
    const index_t rowidx,
    const index_t pageidx
) noexcept {
  static_assert(isRowMajor(_layout), "This routine is only available in row-major matrices.");
  assert(rowidx >= 0 && rowidx < nrow_);
  assert(pageidx >= 0 && pageidx < npage_);
  index_t pos, nnz; getPosNnz({rowidx, rowidx}, {0, ncol_}, {pageidx, pageidx}, pos, nnz);
  return CooVector<_Scalar>(ncol_, nnz, data_.template getReduced<1>(), pos + offset_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getRow
///
template <typename _Scalar, Layout _layout>
const CooVector<_Scalar> CooCube<_Scalar, _layout>::getRow(
    const index_t rowidx,
    const index_t pageidx
) const noexcept {
  static_assert(isRowMajor(_layout), "This routine is only available in row-major matrices.");
  assert(rowidx >= 0 && rowidx < nrow_);
  assert(pageidx >= 0 && pageidx < npage_);
  index_t pos, nnz; getPosNnz({rowidx, rowidx}, {0, ncol_}, {pageidx, pageidx}, pos, nnz);
  return CooVector<_Scalar>(ncol_, nnz, data_.template getReduced<1>(), pos + offset_);
}

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_COO_COO_CUBE_IPP_
