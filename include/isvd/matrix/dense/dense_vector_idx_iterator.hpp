////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/matrix/dense/dense_vector_idx_iterator.hpp
/// @brief   The dense vector index iterator class.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_MATRIX_DENSE_DENSE_VECTOR_IDX_ITERATOR_HPP_
#define ISVD_MATRIX_DENSE_DENSE_VECTOR_IDX_ITERATOR_HPP_

#include <isvd/isvd.hpp>
#include <isvd/matrix/dense/dense_vector_iterator.hpp>
#include <isvd/matrix/kit/idx_tuple.hpp>

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
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense vector iterator for index comparison.
///
/// @tparam  _Scalar  The scalar type.
///
template <typename _Scalar, class _Vector>
class DenseVectorIdxIteratorBase : public DenseVectorIteratorBase<_Scalar, _Vector> {

 private:

  using IdxTupleType = IdxTuple<typename std::remove_const<_Scalar>::type, 1>;

 public:

  using DenseVectorIteratorBase<_Scalar, _Vector>::DenseVectorIteratorBase;

  // Operators
  inline IdxTupleType operator*() const noexcept;

  // Sets to begin/end
  inline DenseVectorIdxIteratorBase& setBegin() noexcept;
  inline DenseVectorIdxIteratorBase& setEnd() noexcept;

  // Gets the value iterator
  inline DenseVectorIteratorBase<_Scalar, _Vector>& getValueIterator() noexcept;

  // Gets the begin/end iterator
  static inline DenseVectorIdxIteratorBase getBegin( _Vector *vector ) noexcept;
  static inline DenseVectorIdxIteratorBase getEnd( _Vector *vector ) noexcept;


 private:

  using DenseVectorIteratorBase<_Scalar, _Vector>::getIdxIterator;

  // Operators
  inline void operator->() const noexcept;

};

}  // namespace internal

template <typename _Scalar>
using DenseVectorIdxIterator = internal::DenseVectorIdxIteratorBase<_Scalar, DenseVector<_Scalar>>;

template <typename _Scalar>
using DenseVectorConstIdxIterator = internal::DenseVectorIdxIteratorBase<const _Scalar, const DenseVector<_Scalar>>;

}  // namespace isvd

#endif  // ISVD_MATRIX_DENSE_DENSE_VECTOR_IDX_ITERATOR_HPP_
