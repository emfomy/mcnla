////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/matrix/dense_submatrix.hpp
/// @brief   The dense submatrix class.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_MATRIX_DENSE_SUBMATRIX_HPP_
#define ISVD_MATRIX_DENSE_SUBMATRIX_HPP_

#include <isvd/config.hpp>
#include <isvd/matrix/dense_matrix.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The implementation namespace.
//
namespace impl {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense submatrix data storage.
///
/// @tparam _Type   The type of numeric value in matrix.
/// @tparam _layout The storage layout of matrix.
///
//@{
template <typename _Type, Layout _layout>
class DenseSubmatrixData : public DenseMatrixData<_Type, _layout> {

  using DenseMatrixData<_Type, _layout>::DenseMatrixData;

 public:

  // Destructor
  ~DenseSubmatrixData() noexcept;
};

}  // namespace impl

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense submatrix.
///
/// @tparam _Type  The type of numeric value in matrix.
/// @tparam _layout The storage layout of matrix.
///
template <typename _Type, Layout _layout = Layout::COLMAJOR>
class DenseSubmatrix : public impl::DenseMatrixBase<impl::DenseSubmatrixData<_Type, _layout>> {
  using impl::DenseMatrixBase<impl::DenseSubmatrixData<_Type, _layout>>::DenseMatrixBase;
};

}  // namespace isvd

#endif  // ISVD_MATRIX_DENSE_SUBMATRIX_HPP_
