////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/matrix/dense_matrix_base.hpp
/// @brief   The dense matrix interface.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_MATRIX_DENSE_MATRIX_BASE_HPP_
#define ISVD_MATRIX_DENSE_MATRIX_BASE_HPP_

#include <memory>
#include <isvd/isvd.hpp>
#include <isvd/utility/crtp.hpp>
#include <isvd/matrix/enum.hpp>
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
/// The interface of dense matrix.
///
/// @tparam  _Derived  The derived class type.
///
template <class _Derived>
class DenseMatrixBase
  : public CrtpBase<_Derived, DenseMatrixBase<_Derived>>,
    public MatrixBase<_Derived>,
    public DenseBase<_Derived> {

  using CrtpBase<_Derived, DenseMatrixBase<_Derived>>::derived;

 private:
  using ScalarType = typename Traits<_Derived>::ScalarType;
  using VectorType = typename Traits<_Derived>::VectorType;

 public:

  // Gets information
  inline Layout  getLayout() const noexcept;
  inline index_t getPitch() const noexcept;
  inline index_t getOffset() const noexcept;

  // Gets data
  inline ScalarType& getValue( const index_t rowidx, const index_t colidx ) noexcept;
  inline const ScalarType& getValue( const index_t rowidx, const index_t colidx ) const noexcept;

  // Gets matrix block
  inline _Derived getBlock( const index_t rowidx, const index_t colidx, const index_t nrow, const index_t ncol ) noexcept;
  inline _Derived getRows( const index_t rowidx, const index_t nrow ) noexcept;
  inline _Derived getCols( const index_t colidx, const index_t ncol ) noexcept;

  // Gets vector segment
  inline VectorType getRow( const index_t rowidx ) noexcept;
  inline VectorType getRow( const index_t rowidx, const index_t colidx, const index_t ncol ) noexcept;
  inline VectorType getCol( const index_t colidx ) noexcept;
  inline VectorType getCol( const index_t colidx, const index_t rowidx, const index_t nrow ) noexcept;

};

}  // namespace impl

}  // namespace isvd

#endif  // ISVD_MATRIX_DENSE_MATRIX_BASE_HPP_
