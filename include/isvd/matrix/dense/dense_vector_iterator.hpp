////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/matrix/dense/dense_vector_iterator.hpp
/// @brief   The dense vector iterator class.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_MATRIX_DENSE_DENSE_VECTOR_ITERATOR_HPP_
#define ISVD_MATRIX_DENSE_DENSE_VECTOR_ITERATOR_HPP_

#include <isvd/isvd.hpp>
#include <isvd/matrix/dense/dense_vector.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Scalar> class DenseVector;
template <typename _Scalar, class _Vector> class DenseVectorIteratorBase;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The detail namespace.
//
namespace detail {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense vector iterator traits.
///
/// @tparam  _Scalar  The scalar type.
/// @tparam  _Vector  The vector type.
///
template <typename _Scalar, class _Vector>
struct Traits<DenseVectorIteratorBase<_Scalar, _Vector>> {
  static constexpr index_t ndim = 1;
  using ScalarType    = _Scalar;
  using ContainerType = _Vector;
};

}  // namespace detail

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense vector iterator.
///
/// @tparam  _Scalar  The scalar type.
/// @tparam  _Vector  The vector type.
///
/// @see  DenseVectorIterator, DenseVectorConstIterator
///
template <typename _Scalar, class _Vector>
class DenseVectorIteratorBase : public DenseIteratorBase<DenseVectorIteratorBase<_Scalar, _Vector>> {

 private:

  static constexpr index_t ndim = 1;
  using ScalarType    = _Scalar;
  using ContainerType = _Vector;

  using BaseType      = DenseIteratorBase<DenseVectorIteratorBase<_Scalar, _Vector>>;

 protected:

  using BaseType::itidx_;
  using BaseType::container_;

 public:

  using BaseType::DenseIteratorBase;
  using BaseType::operator=;

  // Operators
  template <typename __Scalar, class __Vector>
  friend inline std::ostream& operator<<( std::ostream &out, const DenseVectorIteratorBase<__Scalar, __Vector> &iterator );

  // Gets value
  inline ScalarType& getValue() const noexcept;
  inline index_t     getIdx() const noexcept;
  inline index_t     getPos() const noexcept;

};

template <typename _Scalar>
using DenseVectorIterator = DenseVectorIteratorBase<_Scalar, DenseVector<_Scalar>>;

template <typename _Scalar>
using DenseVectorConstIterator = DenseVectorIteratorBase<const _Scalar, const DenseVector<_Scalar>>;

}  // namespace isvd

#endif  // ISVD_MATRIX_DENSE_DENSE_VECTOR_ITERATOR_HPP_
