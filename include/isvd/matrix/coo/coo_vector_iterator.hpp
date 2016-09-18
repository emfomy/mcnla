////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/matrix/coo/coo_vector_iterator.hpp
/// @brief   The COO vector iterator class.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_MATRIX_COO_COO_VECTOR_ITERATOR_HPP_
#define ISVD_MATRIX_COO_COO_VECTOR_ITERATOR_HPP_

#include <isvd/isvd.hpp>
#include <isvd/matrix/base/iterator_base.hpp>
#include <isvd/matrix/base/value_iterator_base.hpp>
#include <isvd/matrix/base/idx_iterator_base.hpp>
#include <isvd/matrix/coo/coo_vector.hpp>

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
template <class _Derived> class CooVectorIteratorBase;
template <typename _Scalar, typename _Index, class _Vector> class CooVectorValueIteratorBase;
template <typename _Scalar, typename _Index, class _Vector> class CooVectorIdxIteratorBase;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The coordinate list (COO) vector value iterator traits.
///
/// @tparam  _Scalar  The scalar type.
/// @tparam  _Index   The index type.
/// @tparam  _Vector  The vector type.
///
template <typename _Scalar, typename _Index, class _Vector>
struct Traits<CooVectorValueIteratorBase<_Scalar, _Index, _Vector>>
  : Traits<IteratorBase<CooVectorValueIteratorBase<_Scalar, _Index, _Vector>>> {
  using ScalarType        = _Scalar;
  using IndexType         = _Index;
  using IdxTupleType      = IdxTuple<1, _Index>;
  using ContainerType     = _Vector;
  using BaseType          = CooVectorIteratorBase<CooVectorValueIteratorBase<_Scalar, _Index, _Vector>>;
  using IdxIteratorType   = CooVectorIdxIteratorBase<_Scalar, _Index, _Vector>;
  using ValueIteratorType = CooVectorValueIteratorBase<_Scalar, _Index, _Vector>;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The coordinate list (COO) vector index iterator traits.
///
/// @tparam  _Scalar  The scalar type.
/// @tparam  _Index   The index type.
/// @tparam  _Vector  The vector type.
///
template <typename _Scalar, typename _Index, class _Vector>
struct Traits<CooVectorIdxIteratorBase<_Scalar, _Index, _Vector>>
  : Traits<IteratorBase<CooVectorIdxIteratorBase<_Scalar, _Index, _Vector>>> {
  using ScalarType        = _Scalar;
  using IndexType         = _Index;
  using IdxTupleType      = IdxTuple<1, _Index>;
  using ContainerType     = _Vector;
  using BaseType          = CooVectorIteratorBase<CooVectorIdxIteratorBase<_Scalar, _Index, _Vector>>;
  using IdxIteratorType   = CooVectorIdxIteratorBase<_Scalar, _Index, _Vector>;
  using ValueIteratorType = CooVectorValueIteratorBase<_Scalar, _Index, _Vector>;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The coordinate list (COO) vector iterator.
///
/// @tparam  _Derived  The derived type.
///
template <class _Derived>
class CooVectorIteratorBase : public IteratorBase<_Derived> {

 private:

  using ScalarType        = typename Traits<_Derived>::ScalarType;
  using IndexType         = typename Traits<_Derived>::IndexType;
  using IdxTupleType      = typename Traits<_Derived>::IdxTupleType;
  using ConstIdxTupleType = typename Traits<_Derived>::ConstIdxTupleType;
  using ContainerType     = typename Traits<_Derived>::ContainerType;

 protected:

  using IteratorBase<_Derived>::itidx_;
  using IteratorBase<_Derived>::container_;

 public:

  using IteratorBase<_Derived>::IteratorBase;

  // Operators
  template <class __Derived>
  friend inline std::ostream& operator<<( std::ostream &out, const CooVectorIteratorBase<__Derived> &iterator );

  // Gets value
  inline       ScalarType&  getValue() noexcept;
  inline const ScalarType&  getValue() const noexcept;
  inline       IndexType&   getIdx() noexcept;
  inline const IndexType&   getIdx() const noexcept;
  inline       index_t      getPos() const noexcept;
  inline       IdxTupleType      getIdxs() noexcept;
  inline       ConstIdxTupleType getIdxs() const noexcept;

  // Sets to begin/end
  inline _Derived& setBegin() noexcept;
  inline _Derived& setEnd() noexcept;

};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The coordinate list (COO) vector value iterator.
///
/// @tparam  _Scalar  The scalar type.
/// @tparam  _Index   The index type.
/// @tparam  _Vector  The vector type.
///
template <typename _Scalar, typename _Index, class _Vector>
class CooVectorValueIteratorBase
  : public CooVectorIteratorBase<CooVectorValueIteratorBase<_Scalar, _Index, _Vector>>,
    public ValueIteratorBase<CooVectorValueIteratorBase<_Scalar, _Index, _Vector>> {

 public:

  using CooVectorIteratorBase<CooVectorValueIteratorBase<_Scalar, _Index, _Vector>>::CooVectorIteratorBase;

};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The coordinate list (COO) vector value iterator.
///
/// @tparam  _Scalar  The scalar type.
/// @tparam  _Index   The index type.
/// @tparam  _Vector  The vector type.
///
template <typename _Scalar, typename _Index, class _Vector>
class CooVectorIdxIteratorBase
  : public CooVectorIteratorBase<CooVectorIdxIteratorBase<_Scalar, _Index, _Vector>>,
    public IdxIteratorBase<CooVectorIdxIteratorBase<_Scalar, _Index, _Vector>> {

 public:

  using CooVectorIteratorBase<CooVectorIdxIteratorBase<_Scalar, _Index, _Vector>>::CooVectorIteratorBase;

};

}  // namespace internal

template <typename _Scalar>
using CooVectorIterator = internal::CooVectorValueIteratorBase<_Scalar, index_t, CooVector<_Scalar>>;

template <typename _Scalar>
using CooVectorConstIterator = internal::CooVectorValueIteratorBase<const _Scalar, const index_t, const CooVector<_Scalar>>;

template <typename _Scalar>
using CooVectorIdxIterator = internal::CooVectorIdxIteratorBase<_Scalar, index_t, CooVector<_Scalar>>;

template <typename _Scalar>
using CooVectorConstIdxIterator = internal::CooVectorIdxIteratorBase<const _Scalar, const index_t, const CooVector<_Scalar>>;

}  // namespace isvd

#endif  // ISVD_MATRIX_COO_COO_VECTOR_ITERATOR_HPP_
