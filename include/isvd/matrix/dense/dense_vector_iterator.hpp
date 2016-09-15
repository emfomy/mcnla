////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/matrix/dense/dense_vector_iterator.hpp
/// @brief   The dense vector iterator class.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_MATRIX_DENSE_DENSE_VECTOR_ITERATOR_HPP_
#define ISVD_MATRIX_DENSE_DENSE_VECTOR_ITERATOR_HPP_

#include <isvd/isvd.hpp>
#include <iterator>
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
struct Traits<DenseVectorIteratorBase<_Scalar, _Vector>> {
  using ScalarType        = _Scalar;
  using IdxTupleType      = IdxTuple<typename std::remove_const<_Scalar>::type, 1>;
  using ContainerType     = _Vector;
  using BaseType          = DenseVectorIteratorBase<_Scalar, _Vector>;
  using ValueIteratorType = DenseVectorValueIteratorBase<_Scalar, _Vector>;
  using IdxIteratorType   = DenseVectorIdxIteratorBase<_Scalar, _Vector>;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense vector iterator traits.
///
/// @tparam  _Scalar  The scalar type.
/// @tparam  _Vector  The vector type.
///
template <typename _Scalar, class _Vector>
struct Traits<DenseVectorValueIteratorBase<_Scalar, _Vector>> : Traits<DenseVectorIteratorBase<_Scalar, _Vector>> {
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense vector iterator traits.
///
/// @tparam  _Scalar  The scalar type.
/// @tparam  _Vector  The vector type.
///
template <typename _Scalar, class _Vector>
struct Traits<DenseVectorIdxIteratorBase<_Scalar, _Vector>> : Traits<DenseVectorIteratorBase<_Scalar, _Vector>> {
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense vector iterator.
///
/// @tparam  _Scalar  The scalar type.
/// @tparam  _Vector  The vector type.
///
template <typename _Scalar, class _Vector>
class DenseVectorIteratorBase {

 public:

  using ValueIteratorType = DenseVectorValueIteratorBase<_Scalar, _Vector>;
  using IdxIteratorType   = DenseVectorIdxIteratorBase<_Scalar, _Vector>;

 private:

  using ScalarType    = _Scalar;
  using IdxTupleType  = IdxTuple<typename std::remove_const<_Scalar>::type, 1>;
  using ContainerType = _Vector;

 protected:

  /// The index.
  index_t idx_;

  /// The vector.
  _Vector *vector_;

 public:

  // Constructors
  inline DenseVectorIteratorBase() noexcept;
  inline DenseVectorIteratorBase( ContainerType *vector, const index_t idx = 0 ) noexcept;
  inline DenseVectorIteratorBase( const DenseVectorIteratorBase &other ) noexcept;

  // Operators
  inline DenseVectorIteratorBase& operator=( const DenseVectorIteratorBase &other ) noexcept;
  inline bool operator==( const DenseVectorIteratorBase &other ) const noexcept;
  inline bool operator!=( const DenseVectorIteratorBase &other ) const noexcept;
  inline DenseVectorIteratorBase& operator++() noexcept;
  inline DenseVectorIteratorBase  operator++( int ) noexcept;

  // Gets value
  inline       ScalarType& getValue() noexcept;
  inline const ScalarType& getValue() const noexcept;
  inline       IdxTupleType getIdxs() const noexcept;
  inline       index_t getIdx() const noexcept;
  inline       index_t getPos() const noexcept;

  // Sets to begin/end
  inline DenseVectorIteratorBase& setBegin() noexcept;
  inline DenseVectorIteratorBase& setEnd() noexcept;

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
