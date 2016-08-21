////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/matrix/dense_block.hpp
/// @brief   The dense block class.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_MATRIX_DENSE_BLOCK_HPP_
#define ISVD_MATRIX_DENSE_BLOCK_HPP_

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
/// The dense block data storage.
///
/// @tparam  _Scalar  The scalar type of matrix.
/// @tparam  _layout  The storage layout of matrix.
///
template <typename _Scalar, Layout _layout>
class DenseBlockData : public DenseMatrixData<_Scalar, _layout> {

 public:

  // Constructors
  DenseBlockData() noexcept;
  DenseBlockData( const index_t nrow, const index_t ncol, const index_t pitch, _Scalar *value ) noexcept;

  // Destructor
  ~DenseBlockData() noexcept;

};

}  // namespace impl

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense block.
///
/// @tparam  _Scalar  The type of numeric value in matrix.
/// @tparam  _layout  The storage layout of matrix.
///
template <typename _Scalar, Layout _layout = Layout::COLMAJOR>
class DenseBlock : public impl::Matrix<impl::DenseBlockData<_Scalar, _layout>> {
  using impl::Matrix<impl::DenseBlockData<_Scalar, _layout>>::Matrix;
};

}  // namespace isvd

#endif  // ISVD_MATRIX_DENSE_BLOCK_HPP_
