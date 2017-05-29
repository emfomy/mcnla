////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/dense/dense_matrix.hpp
/// @brief   The dense matrix.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_DENSE_DENSE_MATRIX_HPP_
#define MCNLA_CORE_MATRIX_DENSE_DENSE_MATRIX_HPP_

#include <mcnla/core/matrix/dense/dense_matrix.hh>

#ifndef DOXYGEN_SHOULD_SKIP_THIS
  #define MCNLA_TEP GeMatS<CpuTag, DenseTag, _Val, _trans>
#else  // DOXYGEN_SHOULD_SKIP_THIS
  #define MCNLA_TEP DenseMatrix<_Val, _trans>
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Finds the iterator to element
///
template <typename _Val, Trans _trans>
DenseMatrixIterator<_Val, _trans> MCNLA_TEP::find(
    const index_t rowidx,
    const index_t colidx
) noexcept {
  mcnla_assert_gelt(rowidx, 0, this->nrow());
  mcnla_assert_gelt(colidx, 0, this->ncol());
  auto itidx = this->toDim0(rowidx, colidx) + this->toDim1(rowidx, colidx) * this->dim0();
  return IteratorType(this, itidx);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  find
///
template <typename _Val, Trans _trans>
DenseMatrixConstIterator<_Val, _trans> MCNLA_TEP::find(
    const index_t rowidx,
    const index_t colidx
) const noexcept {
  mcnla_assert_gelt(rowidx, 0, this->nrow());
  mcnla_assert_gelt(colidx, 0, this->ncol());
  auto itidx = this->toDim0(rowidx, colidx) + this->toDim1(rowidx, colidx) * this->dim0();
  return ConstIteratorType(this, itidx);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  find
///
template <typename _Val, Trans _trans>
DenseMatrixConstIterator<_Val, _trans> MCNLA_TEP::cfind(
    const index_t rowidx,
    const index_t colidx
) const noexcept {
  return find(rowidx, colidx);
}

}  // namespace matrix

}  // namespace mcnla

#undef MCNLA_TEP

#endif  // MCNLA_CORE_MATRIX_DENSE_DENSE_MATRIX_HPP_
