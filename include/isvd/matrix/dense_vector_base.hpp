////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/matrix/dense_vector_base.hpp
/// @brief   The dense vector interface.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_MATRIX_DENSE_VECTOR_BASE_HPP_
#define ISVD_MATRIX_DENSE_VECTOR_BASE_HPP_

#include <isvd/isvd.hpp>
#include <isvd/utility/crtp.hpp>
#include <isvd/matrix/index_range.hpp>
#include <isvd/matrix/vector_base.hpp>
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
/// The interface of dense vector.
///
/// @tparam  _Derived  The derived class type.
///
template <class _Derived>
class DenseVectorBase
  : public CrtpBase<_Derived, DenseVectorBase<_Derived>>,
    public VectorBase<_Derived>,
    public DenseBase<_Derived> {

  using CrtpBase<_Derived, DenseVectorBase<_Derived>>::derived;

 private:
  using ScalarType = typename Traits<_Derived>::ScalarType;

 public:

  // Operators
  inline ScalarType& operator()( const index_t idx ) noexcept;
  inline const ScalarType& operator()( const index_t idx ) const noexcept;

  // Gets information
  inline index_t getIncrement() const noexcept;

  // Gets vecot segment
  inline _Derived getSegment( const IndexRange range = IndexRange::FULL ) noexcept;

};

}  // namespace internal

}  // namespace isvd

#endif  // ISVD_MATRIX_DENSE_VECTOR_BASE_HPP_
