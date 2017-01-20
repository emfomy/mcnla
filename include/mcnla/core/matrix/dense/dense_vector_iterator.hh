////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/dense/dense_vector_iterator.hh
/// @brief   The definition of dense vector iterator class.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_DENSE_DENSE_VECTOR_ITERATOR_HH_
#define MCNLA_CORE_MATRIX_DENSE_DENSE_VECTOR_ITERATOR_HH_

#include <mcnla/core/matrix/def.hpp>
#include <mcnla/core/matrix/dense/dense_vector.hpp>
#include <mcnla/core/matrix/dense/dense_iterator_base.hpp>
#include <mcnla/core/utility/traits.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Scalar> class DenseVector;
template <typename _Scalar, class _Vector> class DenseVectorIteratorBase;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace matrix

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The traits namespace.
//
namespace traits {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense vector iterator traits.
///
template <typename _Scalar, class _Vector>
struct Traits<matrix::DenseVectorIteratorBase<_Scalar, _Vector>> {
  static constexpr index_t ndim = 1;
  using ScalarType    = _Scalar;
  using ContainerType = _Vector;
};

}  // namespace traits

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  matrix_dense_module
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
  friend inline std::ostream& operator<<( std::ostream &os, const DenseVectorIteratorBase<__Scalar, __Vector> &iterator );

  // Gets value
  inline ScalarType& value() const noexcept;
  inline index_t     idx() const noexcept;
  inline index_t     pos() const noexcept;

};

/// @ingroup  matrix_dense_module
template <typename _Scalar>
using DenseVectorIterator = DenseVectorIteratorBase<_Scalar, DenseVector<_Scalar>>;

/// @ingroup  matrix_dense_module
template <typename _Scalar>
using DenseVectorConstIterator = DenseVectorIteratorBase<const _Scalar, const DenseVector<_Scalar>>;

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_DENSE_DENSE_VECTOR_ITERATOR_HH_
