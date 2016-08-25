////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/matrix/dense_matrix_base.hpp
/// @brief   The dense matrix interface.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_MATRIX_DENSE_MATRIX_BASE_HPP_
#define ISVD_MATRIX_DENSE_MATRIX_BASE_HPP_

#include <memory>
#include <isvd/config.hpp>
#include <isvd/utility/crtp.hpp>
#include <isvd/matrix/matrix_base.hpp>
#include <isvd/matrix/dense_base.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The implementation namespace.
//
namespace impl {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The interface of matrix.
///
/// @tparam  _Derived  The derived class type.
/// @tparam  _Scalar   The scalar type of matrix.
///
template <class _Derived, typename _Scalar>
class DenseMatrixBase
  : public CrtpBase<_Derived, DenseMatrixBase<_Derived, _Scalar>>,
    public MatrixBase<_Derived>,
    public DenseBase<_Derived, _Scalar> {

  using CrtpBase<_Derived, DenseMatrixBase<_Derived, _Scalar>>::derived;

 public:

  // Gets matrix information
  inline Layout  getLayout() const noexcept;
  inline index_t getPitch() const noexcept;
  inline index_t getOffset() const noexcept;

  // Gets data
  inline _Scalar& getValue( const index_t rowid, const index_t colid ) noexcept;
  inline const _Scalar& getValue( const index_t rowid, const index_t colid ) const noexcept;

  // Gets block
  inline _Derived getBlock( const index_t rowid, const index_t colid, const index_t nrow, const index_t ncol ) noexcept;
  inline _Derived getRows( const index_t rowid, const index_t nrow ) noexcept;
  inline _Derived getCols( const index_t colid, const index_t ncol ) noexcept;

};

}  // namespace impl

}  // namespace isvd

#endif  // ISVD_MATRIX_DENSE_MATRIX_BASE_HPP_
