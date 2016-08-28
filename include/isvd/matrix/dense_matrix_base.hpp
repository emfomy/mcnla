////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/matrix/dense_matrix_base.hpp
/// @brief   The dense matrix interface.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_MATRIX_DENSE_MATRIX_BASE_HPP_
#define ISVD_MATRIX_DENSE_MATRIX_BASE_HPP_

#include <isvd/isvd.hpp>
#include <isvd/utility/crtp.hpp>
#include <isvd/matrix/index_range.hpp>
#include <isvd/matrix/matrix_base.hpp>
#include <isvd/matrix/dense_base.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The internal namespace.
//
namespace internal {

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
  using VectorType = typename Traits<_Derived>::VectorType;

 public:

  // Gets information
  inline Layout getLayout() const noexcept;
  inline index_t getPitch() const noexcept;

  // Gets matrix block
  inline _Derived getBlock( const IndexRange rowrange = IndexRange::FULL,
                            const IndexRange colrange = IndexRange::FULL ) noexcept;

  // Gets vector segment
  inline VectorType getCol( const index_t colidx, const IndexRange rowrange = IndexRange::FULL ) noexcept;
  inline VectorType getRow( const index_t rowidx, const IndexRange colrange = IndexRange::FULL ) noexcept;
  inline VectorType getDiagonal( const index_t idx = 0 ) noexcept;
  inline VectorType vectorize() noexcept;

};

}  // namespace internal

}  // namespace isvd

#endif  // ISVD_MATRIX_DENSE_MATRIX_BASE_HPP_
