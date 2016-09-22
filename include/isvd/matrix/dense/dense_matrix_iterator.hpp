////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/matrix/dense/dense_matrix_iterator.hpp
/// @brief   The dense matrix iterator class.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_MATRIX_DENSE_DENSE_MATRIX_ITERATOR_HPP_
#define ISVD_MATRIX_DENSE_DENSE_MATRIX_ITERATOR_HPP_

#include <isvd/isvd.hpp>
#include <isvd/matrix/dense/dense_matrix.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Scalar, Layout _layout> class DenseMatrix;
template <typename _Scalar, Layout _layout, class _Matrix> class DenseMatrixIteratorBase;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The detail namespace.
//
namespace detail {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense matrix iterator traits.
///
/// @tparam  _Scalar  The scalar type.
/// @tparam  _layout  The storage layout.
/// @tparam  _Matrix  The matrix type.
///
template <typename _Scalar, Layout _layout, class _Matrix>
struct Traits<DenseMatrixIteratorBase<_Scalar, _layout, _Matrix>> {
  static constexpr index_t ndim = 2;
  using ScalarType    = _Scalar;
  using ContainerType = _Matrix;
};

}  // namespace detail

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense matrix iterator.
///
/// @tparam  _Scalar  The scalar type.
/// @tparam  _layout  The storage layout.
/// @tparam  _Matrix  The matrix type.
///
template <typename _Scalar, Layout _layout, class _Matrix>
class DenseMatrixIteratorBase : public DenseIteratorBase<DenseMatrixIteratorBase<_Scalar, _layout, _Matrix>> {

 private:

  static constexpr index_t ndim = 2;
  using ScalarType    = _Scalar;
  using ContainerType = _Matrix;

  using BaseType      = DenseIteratorBase<DenseMatrixIteratorBase<_Scalar, _layout, _Matrix>>;

 protected:

  using BaseType::itidx_;
  using BaseType::container_;

 public:

  using BaseType::DenseIteratorBase;
  using BaseType::operator=;

  // Operators
  template <typename __Scalar, Layout __layout, class __Matrix>
  friend inline std::ostream& operator<<( std::ostream &out,
                                          const DenseMatrixIteratorBase<__Scalar, __layout, __Matrix> &iterator );

  // Gets value
  inline ScalarType& getValue() const noexcept;
  inline index_t     getRowIdx() const noexcept;
  inline index_t     getColIdx() const noexcept;
  inline index_t     getPos() const noexcept;

};

template <typename _Scalar, Layout _layout>
using DenseMatrixIterator = DenseMatrixIteratorBase<_Scalar, _layout, DenseMatrix<_Scalar, _layout>>;

template <typename _Scalar, Layout _layout>
using DenseMatrixConstIterator = DenseMatrixIteratorBase<const _Scalar, _layout, const DenseMatrix<_Scalar, _layout>>;

}  // namespace isvd

#endif  // ISVD_MATRIX_DENSE_DENSE_MATRIX_ITERATOR_HPP_
