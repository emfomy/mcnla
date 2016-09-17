////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/matrix/dense/dense_vector_iterator.hpp
/// @brief   The dense vector iterator class.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_MATRIX_DENSE_DENSE_VECTOR_ITERATOR_HPP_
#define ISVD_MATRIX_DENSE_DENSE_VECTOR_ITERATOR_HPP_

#include <isvd/isvd.hpp>
#include <isvd/matrix/base/iterator_base.hpp>
#include <isvd/matrix/base/value_iterator_base.hpp>
#include <isvd/matrix/base/idx_iterator_base.hpp>
#include <isvd/matrix/dense/dense_vector.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Scalar> class DenseVector;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The internal namespace.
//
namespace internal {

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Scalar, class _Vector> class DenseVectorIteratorBase;
template <typename _Scalar, class _Vector> class DenseVectorValueIteratorBase;
template <typename _Scalar, class _Vector> class DenseVectorIdxIteratorBase;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense vector iterator traits.
///
/// @tparam  _Scalar  The scalar type.
/// @tparam  _Vector  The vector type.
///
template <typename _Scalar, class _Vector>
struct Traits<DenseVectorIteratorBase<_Scalar, _Vector>> : Traits<IteratorBase<DenseVectorIteratorBase<_Scalar, _Vector>>> {
  using ScalarType        = _Scalar;
  using IdxTupleType      = IdxTuple<1>;
  using ContainerType     = _Vector;
  using BaseType          = DenseVectorIteratorBase<_Scalar, _Vector>;
  using ValueIteratorType = DenseVectorValueIteratorBase<_Scalar, _Vector>;
  using IdxIteratorType   = DenseVectorIdxIteratorBase<_Scalar, _Vector>;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense vector value iterator traits.
///
/// @tparam  _Scalar  The scalar type.
/// @tparam  _Vector  The vector type.
///
template <typename _Scalar, class _Vector>
struct Traits<DenseVectorValueIteratorBase<_Scalar, _Vector>> : Traits<DenseVectorIteratorBase<_Scalar, _Vector>> {};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense vector index iterator traits.
///
/// @tparam  _Scalar  The scalar type.
/// @tparam  _Vector  The vector type.
///
template <typename _Scalar, class _Vector>
struct Traits<DenseVectorIdxIteratorBase<_Scalar, _Vector>> : Traits<DenseVectorIteratorBase<_Scalar, _Vector>> {};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense vector iterator.
///
/// @tparam  _Scalar  The scalar type.
/// @tparam  _Vector  The vector type.
///
template <typename _Scalar, class _Vector>
class DenseVectorIteratorBase : public IteratorBase<DenseVectorIteratorBase<_Scalar, _Vector>> {

 protected:

  using IteratorBase<DenseVectorIteratorBase<_Scalar, _Vector>>::itidx_;
  using IteratorBase<DenseVectorIteratorBase<_Scalar, _Vector>>::container_;

 public:

  using IteratorBase<DenseVectorIteratorBase<_Scalar, _Vector>>::IteratorBase;

  // Operators
  template <typename __Scalar, class __Vector>
  friend inline std::ostream& operator<<( std::ostream &out, const DenseVectorIteratorBase<__Scalar, __Vector> &iterator );

  // Gets value
  inline       _Scalar&    getValue() noexcept;
  inline const _Scalar&    getValue() const noexcept;
  inline       IdxTuple<1> getIdxs() const noexcept;
  inline       index_t     getIdx() const noexcept;
  inline       index_t     getPos() const noexcept;

};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense vector value iterator.
///
/// @tparam  _Scalar  The scalar type.
/// @tparam  _Vector  The vector type.
///
template <typename _Scalar, class _Vector>
class DenseVectorValueIteratorBase
  : public DenseVectorIteratorBase<_Scalar, _Vector>,
    public ValueIteratorBase<DenseVectorValueIteratorBase<_Scalar, _Vector>> {

 public:

  using DenseVectorIteratorBase<_Scalar, _Vector>::DenseVectorIteratorBase;

};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense vector value iterator.
///
/// @tparam  _Scalar  The scalar type.
/// @tparam  _Vector  The vector type.
///
template <typename _Scalar, class _Vector>
class DenseVectorIdxIteratorBase
  : public DenseVectorIteratorBase<_Scalar, _Vector>,
    public IdxIteratorBase<DenseVectorIdxIteratorBase<_Scalar, _Vector>> {

 public:

  using DenseVectorIteratorBase<_Scalar, _Vector>::DenseVectorIteratorBase;

};

}  // namespace internal

template <typename _Scalar>
using DenseVectorIterator = internal::DenseVectorValueIteratorBase<_Scalar, DenseVector<_Scalar>>;

template <typename _Scalar>
using DenseVectorConstIterator = internal::DenseVectorValueIteratorBase<const _Scalar, const DenseVector<_Scalar>>;

template <typename _Scalar>
using DenseVectorIdxIterator = internal::DenseVectorIdxIteratorBase<_Scalar, DenseVector<_Scalar>>;

template <typename _Scalar>
using DenseVectorConstIdxIterator = internal::DenseVectorIdxIteratorBase<const _Scalar, const DenseVector<_Scalar>>;

}  // namespace isvd

#endif  // ISVD_MATRIX_DENSE_DENSE_VECTOR_ITERATOR_HPP_
