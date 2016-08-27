////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/matrix/dense_cube_base.hpp
/// @brief   The dense cube interface.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_MATRIX_DENSE_CUBE_BASE_HPP_
#define ISVD_MATRIX_DENSE_CUBE_BASE_HPP_

#include <isvd/isvd.hpp>
#include <isvd/utility/crtp.hpp>
#include <isvd/matrix/enum.hpp>
#include <isvd/matrix/index_range.hpp>
#include <isvd/matrix/cube_base.hpp>
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
/// The interface of dense cube.
///
/// @tparam  _Derived  The derived class type.
///
template <class _Derived>
class DenseCubeBase
  : public CrtpBase<_Derived, DenseCubeBase<_Derived>>,
    public CubeBase<_Derived>,
    public DenseBase<_Derived> {

  using CrtpBase<_Derived, DenseCubeBase<_Derived>>::derived;

 private:
  using ScalarType = typename Traits<_Derived>::ScalarType;
  using MatrixType = typename Traits<_Derived>::MatrixType;
  using VectorType = typename Traits<_Derived>::VectorType;

 public:

  // Operators
  inline ScalarType& operator()( const index_t rowidx, const index_t colidx, const index_t pageidx ) noexcept;
  inline const ScalarType& operator()( const index_t rowidx, const index_t colidx, const index_t pageidx ) const noexcept;

  // Gets information
  inline Layout  getLayout() const noexcept;
  inline index_t getPitch() const noexcept;
  inline index_t getPagePitch() const noexcept;

  // Gets cube block
  inline _Derived getBlock( const IndexRange rowrange = IndexRange::FULL, const IndexRange colrange = IndexRange::FULL,
                            const IndexRange pagerange = IndexRange::FULL ) noexcept;

  // Gets matrix block
  inline MatrixType getPage( const index_t pageidx, const IndexRange rowrange = IndexRange::FULL,
                             const IndexRange colrange = IndexRange::FULL ) noexcept;

  // Gets vector segment
  inline VectorType getCol( const index_t colidx, const index_t pageidx,
                            const IndexRange rowrange = IndexRange::FULL ) noexcept;
  inline VectorType getRow( const index_t rowidx, const index_t pageidx,
                            const IndexRange colrange = IndexRange::FULL ) noexcept;
  inline VectorType getTube( const index_t rowidx, const index_t colidx,
                             const IndexRange pagerange = IndexRange::FULL ) noexcept;
  inline VectorType getDiagonal( const index_t pageidx, const index_t idx = 0 ) noexcept;

};

}  // namespace internal

}  // namespace isvd

#endif  // ISVD_MATRIX_DENSE_CUBE_BASE_HPP_
