////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/la/coo/routine/copy.hpp
/// @brief   The BLAS COPY routine for COO format.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_LA_COO_ROUTINE_COPY_HPP_
#define MCNLA_CORE_LA_COO_ROUTINE_COPY_HPP_

#include <mcnla/core/la/def.hpp>
#include <mcnla/core/matrix.hpp>
#include <mcnla/core/la/dense/routine/scal0.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The linear algebra namespace
//
namespace la {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  la_coo_blas1_module
/// @brief  Copies vector to another vector.
///
template <typename _Val>
inline void copy(
    const CooVector<_Val> &x,
          DenseVector<_Val> &y
) noexcept {
  mcnla_assert_eq(x.sizes(), y.sizes());

  scal0(y);
  for ( index_t i = 0; i < x.nnz(); ++i ) {
    y(x.idxPtr()[i]) = x.valPtr()[i];
  }
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Val>
inline void copy(
    const CooVector<_Val> &x,
          DenseVector<_Val> &&y
) noexcept {
  copy(x, y);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  la_coo_blas1m_module
/// @brief  Copies matrix to another matrix.
///
template <typename _Val, Trans _transa, Trans _transb>
inline void copy(
    const CooMatrix<_Val, _transa> &a,
          DenseMatrix<_Val, _transb> &b
) noexcept {
  static_assert(!isConj(_transa), "COO COPY for conjugate matrices is not implemented!");
  static_assert(!isConj(_transb), "COO COPY for conjugate matrices is not implemented!");

  mcnla_assert_eq(a.sizes(), b.sizes());

  scal0(b);
  for ( index_t i = 0; i < a.nnz(); ++i ) {
    b(a.rowidxPtr()[i], a.colidxPtr()[i]) = a.valPtr()[i];
  }
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Val, Trans _transa, Trans _transb>
inline void copy(
    const CooMatrix<_Val, _transa> &a,
          DenseMatrix<_Val, _transb> &&b
) noexcept {
  copy(a, b);
}
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace la

}  // namespace mcnla

#endif  // MCNLA_CORE_LA_COO_ROUTINE_COPY_HPP_
