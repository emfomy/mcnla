////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/matrix/dense_vector_base.hpp
/// @brief   The dense vector interface.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_MATRIX_DENSE_VECTOR_BASE_HPP_
#define ISVD_MATRIX_DENSE_VECTOR_BASE_HPP_

#include <memory>
#include <isvd/isvd.hpp>
#include <isvd/utility/crtp.hpp>
#include <isvd/matrix/vector_base.hpp>
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

  // Gets information
  inline index_t getIncrement() const noexcept;
  inline index_t getOffset() const noexcept;

  // Gets data
  inline ScalarType& getValue( const index_t idx ) noexcept;
  inline const ScalarType& getValue( const index_t idx ) const noexcept;

  // Gets vecot segment
  inline _Derived getSegment( const index_t idx, const index_t length ) noexcept;

};

}  // namespace impl

}  // namespace isvd

#endif  // ISVD_MATRIX_DENSE_VECTOR_BASE_HPP_
