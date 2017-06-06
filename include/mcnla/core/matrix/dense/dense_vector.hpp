////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/dense/dense_vector.hpp
/// @brief   The dense vector.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_DENSE_DENSE_VECTOR_HPP_
#define MCNLA_CORE_MATRIX_DENSE_DENSE_VECTOR_HPP_

#include <mcnla/core/matrix/dense/dense_vector.hh>

#ifndef DOXYGEN_SHOULD_SKIP_THIS
  #define MCNLA_TMP GeVecS<CpuTag, DenseTag, _Val>
#else  // DOXYGEN_SHOULD_SKIP_THIS
  #define MCNLA_TMP DenseVector<_Val>
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
template <typename _Val>
DenseVectorIterator<_Val> MCNLA_TMP::find(
    const index_t idx
) noexcept {
  mcnla_assert_gelt(idx, 0, this->len());
  return IteratorType(this, idx);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  find
///
template <typename _Val>
DenseVectorConstIterator<_Val> MCNLA_TMP::find(
    const index_t idx
) const noexcept {
  mcnla_assert_gelt(idx, 0, this->len());
  return ConstIteratorType(this, idx);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  find
///
template <typename _Val>
DenseVectorConstIterator<_Val> MCNLA_TMP::cfind(
    const index_t idx
) const noexcept {
  return find(idx);
}

}  // namespace matrix

}  // namespace mcnla

#undef MCNLA_TMP

#endif  // MCNLA_CORE_MATRIX_DENSE_DENSE_VECTOR_HPP_
