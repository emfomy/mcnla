////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/la/functor/mm_functor.hpp
/// @brief   The MM functor.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_LA_FUNCTIR_MM_FUNCTOR_HPP_
#define MCNLA_CORE_LA_FUNCTIR_MM_FUNCTOR_HPP_

#include <mcnla/core/la/functor/mm_functor.hh>
#include <mcnla/core/la.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The la namespace.
//
namespace la {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::la::MmFunctorWrapper::MmFunctorWrapper
///
template <class _Matrix, Trans _transb, Trans _transc>
MmFunctor<_Matrix, _transb, _transc>::MmFunctor(
    const AType &matrix
) noexcept
  : matrix_(matrix) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
template <class _Matrix, Trans _transb, Trans _transc>
MmFunctor<_Matrix, _transb, _transc>::~MmFunctor() noexcept {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
template <class _Matrix, Trans _transb, Trans _transc>
void MmFunctor<_Matrix, _transb, _transc>::operator()(
    const BType &b,
          CType &c,
    const ValType alpha,
    const ValType beta
) const noexcept {
  la::mm(matrix_, b, c, alpha, beta);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::MatrixWrapper::nrow
///
template <class _Matrix, Trans _transb, Trans _transc>
index_t MmFunctor<_Matrix, _transb, _transc>::nrowImpl() const noexcept {
  return matrix_.nrow();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::matrix::MatrixWrapper::ncol
///
template <class _Matrix, Trans _transb, Trans _transc>
index_t MmFunctor<_Matrix, _transb, _transc>::ncolImpl() const noexcept {
  return matrix_.ncol();
}

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_LA_FUNCTIR_MM_FUNCTOR_HPP_
