////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/matrix/coo/coo_vector_iterator.hpp
/// @brief   The COO vector iterator class.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_MATRIX_COO_COO_VECTOR_ITERATOR_HPP_
#define ISVD_MATRIX_COO_COO_VECTOR_ITERATOR_HPP_

#include <isvd/isvd.hpp>
#include <isvd/matrix/coo/coo_iterator_base.hpp>
#include <isvd/matrix/coo/coo_vector.hpp>
#include <isvd/matrix/coo/coo_tuple.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Scalar> class CooVector;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The internal namespace.
//
namespace internal {

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Scalar, typename _Index, class _Vector> class CooVectorIteratorBase;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The coordinate list (COO) vector iterator traits.
///
/// @tparam  _Scalar  The scalar type.
/// @tparam  _Index   The index type.
/// @tparam  _Vector  The vector type.
///
template <typename _Scalar, typename _Index, class _Vector>
struct Traits<CooVectorIteratorBase<_Scalar, _Index, _Vector>>
  : Traits<CooIteratorBase<CooVectorIteratorBase<_Scalar, _Index, _Vector>>> {
  static constexpr index_t ndim = 1;
  using ScalarType    = _Scalar;
  using IndexType     = _Index;
  using ContainerType = _Vector;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The coordinate list (COO) vector iterator.
///
/// @tparam  _Derived  The derived type.
///
template <typename _Scalar, typename _Index, class _Vector>
class CooVectorIteratorBase : public CooIteratorBase<CooVectorIteratorBase<_Scalar, _Index, _Vector>> {

 private:

  static constexpr index_t ndim = 1;
  using ScalarType    = _Scalar;
  using IndexType     = _Index;
  using ContainerType = _Vector;

  using BaseType      = CooIteratorBase<CooVectorIteratorBase<_Scalar, _Index, _Vector>>;

 protected:

  using BaseType::itidx_;
  using BaseType::container_;

 public:

  using BaseType::CooIteratorBase;
  using BaseType::operator=;

  // Operators
  template <typename __Scalar, typename __Index, class __Vector>
  friend inline std::ostream& operator<<( std::ostream &out,
                                          const CooVectorIteratorBase<__Scalar, __Index, __Vector> &iterator );

  // Gets value
  template <index_t _dim = 0> inline IndexType& getIdx() const noexcept;
  inline index_t    getPos() const noexcept;

};

}  // namespace internal

template <typename _Scalar>
using CooVectorIterator = internal::CooVectorIteratorBase<_Scalar, index_t, CooVector<_Scalar>>;

template <typename _Scalar>
using CooVectorConstIterator = internal::CooVectorIteratorBase<const _Scalar, const index_t, const CooVector<_Scalar>>;

}  // namespace isvd

#endif  // ISVD_MATRIX_COO_COO_VECTOR_ITERATOR_HPP_
