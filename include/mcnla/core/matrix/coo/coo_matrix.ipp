////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/coo/coo_matrix.ipp
/// @brief   The implementation of COO matrix.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_COO_COO_MATRIX_IPP_
#define MCNLA_CORE_MATRIX_COO_COO_MATRIX_IPP_

#include <mcnla/core/matrix/coo/coo_matrix.hpp>
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
CooMatrix<_Scalar, _layout>::CooMatrix() noexcept
  : MatrixBaseType(),
    CooBaseType() {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Scalar, Layout _layout>
CooMatrix<_Scalar, _layout>::CooMatrix(
    const index_t nrow,
    const index_t ncol
) noexcept
  : MatrixBaseType(nrow, ncol),
    CooBaseType(size0_ * size1_) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Scalar, Layout _layout>
CooMatrix<_Scalar, _layout>::CooMatrix(
    const std::pair<index_t, index_t> sizes
) noexcept
  : CooMatrix(sizes.first, sizes.second) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Scalar, Layout _layout>
CooMatrix<_Scalar, _layout>::CooMatrix(
    const index_t nrow,
    const index_t ncol,
    const index_t capacity
) noexcept
  : MatrixBaseType(nrow, ncol),
    CooBaseType(capacity) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Scalar, Layout _layout>
CooMatrix<_Scalar, _layout>::CooMatrix(
    const std::pair<index_t, index_t> sizes,
    const index_t capacity
) noexcept
  : CooMatrix(sizes.first, sizes.second, capacity) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Scalar, Layout _layout>
CooMatrix<_Scalar, _layout>::CooMatrix(
    const index_t nrow,
    const index_t ncol,
    const index_t nnz,
    const index_t capacity
) noexcept
  : MatrixBaseType(nrow, ncol),
    CooBaseType(nnz, capacity) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given size information.
///
template <typename _Scalar, Layout _layout>
CooMatrix<_Scalar, _layout>::CooMatrix(
    const std::pair<index_t, index_t> sizes,
    const index_t nnz,
    const index_t capacity
) noexcept
  : CooMatrix(sizes.first, sizes.second, nnz, capacity) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given raw data.
///
template <typename _Scalar, Layout _layout>
CooMatrix<_Scalar, _layout>::CooMatrix(
    const index_t nrow,
    const index_t ncol,
    const index_t nnz,
    const ValueArrayType &value,
    const IdxArrayType &rowidx,
    const IdxArrayType &colidx
) noexcept
  : MatrixBaseType(nrow, ncol),
    CooBaseType(nnz, value, {isColMajor(_layout) ? rowidx : colidx, isColMajor(_layout) ? colidx : rowidx}) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct from data storage.
///
template <typename _Scalar, Layout _layout>
CooMatrix<_Scalar, _layout>::CooMatrix(
    const index_t nrow,
    const index_t ncol,
    const index_t nnz,
    const DataType &data,
    const index_t offset
) noexcept
  : MatrixBaseType(nrow, ncol),
    CooBaseType(nnz, data >> offset) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy constructor.
///
/// @attention  It is shallow copy. For deep copy, uses mcnla::blas::copy.
///
template <typename _Scalar, Layout _layout>
CooMatrix<_Scalar, _layout>::CooMatrix( const CooMatrix &other ) noexcept
  : MatrixBaseType(other),
    CooBaseType(other) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Move constructor.
///
template <typename _Scalar, Layout _layout>
CooMatrix<_Scalar, _layout>::CooMatrix( CooMatrix &&other ) noexcept
  : MatrixBaseType(std::move(other)),
    CooBaseType(std::move(other)) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Copy assignment operator.
///
/// @attention  It is shallow copy. For deep copy, uses mcnla::blas::copy.
///
template <typename _Scalar, Layout _layout>
CooMatrix<_Scalar, _layout>& CooMatrix<_Scalar, _layout>::operator=( const CooMatrix &other ) noexcept {
  MatrixBaseType::operator=(other); CooBaseType::operator=(other);
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Move assignment operator.
///
template <typename _Scalar, Layout _layout>
CooMatrix<_Scalar, _layout>& CooMatrix<_Scalar, _layout>::operator=( CooMatrix &&other ) noexcept {
  MatrixBaseType::operator=(std::move(other)); CooBaseType::operator=(std::move(other));
  return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Print to stream.
///
template <typename __Scalar, Layout __layout>
std::ostream& operator<< ( std::ostream &out, const CooMatrix<__Scalar, __layout> &matrix ) {
  for ( auto it = matrix.begin(); it != matrix.end(); ++it ) {
    out << it;
  }
  return out;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the row index array.
///
template <typename _Scalar, Layout _layout>
index_t* CooMatrix<_Scalar, _layout>::getRowIdx() noexcept {
  return CooBaseType::template getIdx<isColMajor(_layout) ? 0 : 1>();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getRowIdx
///
template <typename _Scalar, Layout _layout>
const index_t* CooMatrix<_Scalar, _layout>::getRowIdx() const noexcept {
  return CooBaseType::template getIdx<isColMajor(_layout) ? 0 : 1>();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the column index array.
///
template <typename _Scalar, Layout _layout>
index_t* CooMatrix<_Scalar, _layout>::getColIdx() noexcept {
  return CooBaseType::template getIdx<isColMajor(_layout) ? 1 : 0>();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getColIdx
///
template <typename _Scalar, Layout _layout>
const index_t* CooMatrix<_Scalar, _layout>::getColIdx() const noexcept {
  return CooBaseType::template getIdx<isColMajor(_layout) ? 1 : 0>();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the element of given index.
///
template <typename _Scalar, Layout _layout>
_Scalar CooMatrix<_Scalar, _layout>::getElem(
    const index_t rowidx,
    const index_t colidx
) const noexcept {
  assert(rowidx >= 0 && rowidx < nrow_);
  assert(colidx >= 0 && colidx < ncol_);
  auto it = find(rowidx, colidx);
  return (it != this->end()) ? it.getValue() : 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getElem
///
template <typename _Scalar, Layout _layout>
_Scalar CooMatrix<_Scalar, _layout>::operator()(
    const index_t rowidx,
    const index_t colidx
) const noexcept { return getElem(rowidx, colidx); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the internal position of given index.
//
/// @attention  Returns `-1` if the index does not exist!
///
template <typename _Scalar, Layout _layout>
index_t CooMatrix<_Scalar, _layout>::getPos(
    const index_t rowidx,
    const index_t colidx
) const noexcept {
  assert(rowidx >= 0 && rowidx < nrow_);
  assert(colidx >= 0 && colidx < ncol_);
  auto it = find(rowidx, colidx);
  return (it != this->end()) ? it.getPos() : -1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the internal position and nonzero elements of given index range.
///
template <typename _Scalar, Layout _layout>
void CooMatrix<_Scalar, _layout>::getPosNnz(
    const IdxRange rowrange,
    const IdxRange colrange,
          index_t &pos,
          index_t &nnz
) const noexcept {
  assert(rowrange.begin >= 0 && rowrange.end <= nrow_ && rowrange.getLength() >= 0);
  assert(colrange.begin >= 0 && colrange.end <= ncol_ && colrange.getLength() >= 0);
  assert(isSorted());
  auto begintuple = isColMajor(_layout) ? makeCooTuple(rowrange.begin, colrange.begin)
                                        : makeCooTuple(colrange.begin, rowrange.begin);
  auto endtuple   = isColMajor(_layout) ? makeCooTuple(rowrange.end, colrange.end)
                                        : makeCooTuple(colrange.end, rowrange.end);
  auto it0 = std::lower_bound(this->begin(), this->end(), begintuple);
  auto it1 = std::lower_bound(it0, this->end(), endtuple);
  pos = it0.getPos();
  nnz = it1.getPos() - pos;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Finds the iterator to element
///
template <typename _Scalar, Layout _layout>
typename CooMatrix<_Scalar, _layout>::IteratorType CooMatrix<_Scalar, _layout>::find(
    const index_t rowidx,
    const index_t colidx
) noexcept {
  assert(rowidx >= 0 && rowidx < nrow_);
  assert(colidx >= 0 && colidx < ncol_);
  assert(isSorted());
  auto tuple = isColMajor(_layout) ? makeCooTuple(rowidx, colidx) : makeCooTuple(colidx, rowidx);
  auto it = std::lower_bound(this->begin(), this->end(), tuple);
  return (it == this->end() || *it == tuple) ? it : this->end();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  find
///
template <typename _Scalar, Layout _layout>
typename CooMatrix<_Scalar, _layout>::ConstIteratorType CooMatrix<_Scalar, _layout>::find(
    const index_t rowidx,
    const index_t colidx
) const noexcept {
  assert(rowidx >= 0 && rowidx < nrow_);
  assert(colidx >= 0 && colidx < ncol_);
  assert(isSorted());
  auto tuple = isColMajor(_layout) ? makeCooTuple(rowidx, colidx) : makeCooTuple(colidx, rowidx);
  auto it = std::lower_bound(this->begin(), this->end(), tuple);
  return (it == this->end() || *it == tuple) ? it : this->end();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  find
///
template <typename _Scalar, Layout _layout>
typename CooMatrix<_Scalar, _layout>::ConstIteratorType CooMatrix<_Scalar, _layout>::cfind(
    const index_t rowidx,
    const index_t colidx
) const noexcept {
  return find(rowidx, colidx);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Sorts the matrix.
///
template <typename _Scalar, Layout _layout>
void CooMatrix<_Scalar, _layout>::sort() noexcept {
  std::sort(this->begin(), this->end());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Check if the matrix is sorted.
///
template <typename _Scalar, Layout _layout>
bool CooMatrix<_Scalar, _layout>::isSorted() const noexcept {
  return std::is_sorted(this->begin(), this->end());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the transpose of the matrix.
///
/// @attention  The storage layout is also changed.
///
template <typename _Scalar, Layout _layout>
CooMatrix<_Scalar, changeLayout(_layout)> CooMatrix<_Scalar, _layout>::transpose() noexcept {
  return CooMatrix<_Scalar, changeLayout(_layout)>(ncol_, nrow_, nnz_, data_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Resizes the matrix.
///
/// @attention  The new space is not initialized.
///
template <typename _Scalar, Layout _layout>
void CooMatrix<_Scalar, _layout>::resize(
    const index_t nrow,
    const index_t ncol
) noexcept {
  assert(nrow >= 0 && ncol >= 0);
  nrow_ = nrow;
  ncol_ = ncol;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets a vector segment.
///
/// @attention  This routine is only available in column-major matrices.
///
template <typename _Scalar, Layout _layout>
CooVector<_Scalar> CooMatrix<_Scalar, _layout>::getCol(
    const index_t colidx
) noexcept {
  static_assert(isColMajor(_layout), "This routine is only available in column-major matrices.");
  assert(colidx >= 0 && colidx < ncol_);
  index_t pos, nnz; getPosNnz({0, nrow_}, {colidx, colidx}, pos, nnz);
  return CooVector<_Scalar>(nrow_, nnz, data_.template getReduced<0>(), pos);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getCol
///
template <typename _Scalar, Layout _layout>
const CooVector<_Scalar> CooMatrix<_Scalar, _layout>::getCol(
    const index_t colidx
) const noexcept {
  static_assert(isColMajor(_layout), "This routine is only available in column-major matrices.");
  assert(colidx >= 0 && colidx < ncol_);
  index_t pos, nnz; getPosNnz({0, nrow_}, {colidx, colidx}, pos, nnz);
  return CooVector<_Scalar>(nrow_, nnz, data_.template getReduced<0>(), pos);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets a vector segment.
///
/// @attention  This routine is only available in row-major matrices.
///
template <typename _Scalar, Layout _layout>
CooVector<_Scalar> CooMatrix<_Scalar, _layout>::getRow(
    const index_t rowidx
) noexcept {
  static_assert(isRowMajor(_layout), "This routine is only available in row-major matrices.");
  assert(rowidx >= 0 && rowidx < nrow_);
  index_t pos, nnz; getPosNnz({rowidx, rowidx+1}, {0, ncol_}, pos, nnz);
  return CooVector<_Scalar>(ncol_, nnz, data_.template getReduced<1>(), pos);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  getRow
///
template <typename _Scalar, Layout _layout>
const CooVector<_Scalar> CooMatrix<_Scalar, _layout>::getRow(
    const index_t rowidx
) const noexcept {
  static_assert(isRowMajor(_layout), "This routine is only available in row-major matrices.");
  assert(rowidx >= 0 && rowidx < nrow_);
  index_t pos, nnz; getPosNnz({rowidx, rowidx+1}, {0, ncol_}, pos, nnz);
  return CooVector<_Scalar>(ncol_, nnz, data_.template getReduced<1>(), pos);
}

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_COO_COO_MATRIX_IPP_
