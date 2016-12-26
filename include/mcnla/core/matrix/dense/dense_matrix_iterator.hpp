////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/dense/dense_matrix_iterator.hpp
/// @brief   The dense matrix iterator class.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_DENSE_DENSE_MATRIX_ITERATOR_HPP_
#define MCNLA_CORE_MATRIX_DENSE_DENSE_MATRIX_ITERATOR_HPP_

#include <mcnla/def.hpp>
#include <mcnla/core/def.hpp>
#include <mcnla/core/matrix/dense/dense_matrix.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Scalar, Trans _trans> class DenseMatrix;
template <typename _Scalar, Trans _trans, class _Matrix> class DenseMatrixIteratorBase;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace matrix

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The traits namespace.
//
namespace traits {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense matrix iterator traits.
///
/// @tparam  _Scalar  The scalar type.
/// @tparam  _trans  The storage layout.
/// @tparam  _Matrix  The matrix type.
///
template <typename _Scalar, Trans _trans, class _Matrix>
struct Traits<matrix::DenseMatrixIteratorBase<_Scalar, _trans, _Matrix>> {

  static constexpr index_t ndim = 2;
  static constexpr Trans trans = _trans;
  using ScalarType    = _Scalar;
  using ContainerType = _Matrix;
};

}  // namespace traits

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  matrix_dense_module
/// The dense matrix iterator.
///
/// @tparam  _Scalar  The scalar type.
/// @tparam  _trans  The storage layout.
/// @tparam  _Matrix  The matrix type.
///
/// @see  DenseMatrixIterator, DenseMatrixConstIterator
///
template <typename _Scalar, Trans _trans, class _Matrix>
class DenseMatrixIteratorBase : public DenseIteratorBase<DenseMatrixIteratorBase<_Scalar, _trans, _Matrix>> {

 private:

  static constexpr index_t ndim = 2;
  static constexpr Trans trans = _trans;
  using ScalarType    = _Scalar;
  using ContainerType = _Matrix;

  using BaseType      = DenseIteratorBase<DenseMatrixIteratorBase<_Scalar, _trans, _Matrix>>;

 protected:

  using BaseType::itidx_;
  using BaseType::container_;

 public:

  using BaseType::DenseIteratorBase;
  using BaseType::operator=;

  // Operators
  template <typename __Scalar, Trans __trans, class __Matrix>
  friend inline std::ostream& operator<<( std::ostream &out,
                                          const DenseMatrixIteratorBase<__Scalar, __trans, __Matrix> &iterator );

  // Gets value
  inline ScalarType& value() const noexcept;
  inline index_t     rowidx() const noexcept;
  inline index_t     colidx() const noexcept;
  inline index_t     pos() const noexcept;

};

/// @ingroup  matrix_dense_module
template <typename _Scalar, Trans _trans>
using DenseMatrixIterator = DenseMatrixIteratorBase<_Scalar, _trans, DenseMatrix<_Scalar, _trans>>;

/// @ingroup  matrix_dense_module
template <typename _Scalar, Trans _trans>
using DenseMatrixConstIterator = DenseMatrixIteratorBase<const _Scalar, _trans, const DenseMatrix<_Scalar, _trans>>;

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_DENSE_DENSE_MATRIX_ITERATOR_HPP_
