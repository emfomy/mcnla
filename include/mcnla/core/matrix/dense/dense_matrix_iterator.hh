////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/dense/dense_matrix_iterator.hh
/// @brief   The definition of definition of dense matrix iterator class.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_DENSE_DENSE_MATRIX_ITERATOR_HH_
#define MCNLA_CORE_MATRIX_DENSE_DENSE_MATRIX_ITERATOR_HH_

#include <mcnla/core/matrix/dense/def.hpp>
#include <mcnla/core/matrix/base/iterator_base.hpp>
#include <mcnla/core/matrix/dense/dense_matrix.hpp>
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
template <typename _Val, Trans _trans, class _Matrix> class DenseMatrixIteratorBase;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace matrix

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The traits namespace.
//
namespace traits {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense matrix iterator traits.
///
/// @tparam  _Val     The value type.
/// @tparam  _trans   The transpose storage layout.
/// @tparam  _Matrix  The matrix type.
///
template <typename _Val, Trans _trans, class _Matrix>
struct Traits<matrix::DenseMatrixIteratorBase<_Val, _trans, _Matrix>> {
  static constexpr Trans trans = _trans;
  using ElemType      = _Val;
  using ElemRefType   = _Val&;
  using ElemPtrType   = _Val*;
  using ContainerType = _Matrix;
};

}  // namespace traits

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense matrix iterator.
///
/// @tparam  _Val  The value type.
/// @tparam  _trans  The storage layout.
/// @tparam  _Matrix  The matrix type.
///
/// @see  DenseMatrixIterator, DenseMatrixConstIterator
///
template <typename _Val, Trans _trans, class _Matrix>
class DenseMatrixIteratorBase : public IteratorBase<DenseMatrixIteratorBase<_Val, _trans, _Matrix>> {

 private:

  static constexpr Trans trans = _trans;
  using ValType       = _Val;
  using ElemType      = _Val;
  using ElemRefType   = _Val&;
  using ElemPtrType   = _Val*;
  using ContainerType = _Matrix;

  using BaseType      = IteratorBase<DenseMatrixIteratorBase<_Val, _trans, _Matrix>>;

 protected:

  using BaseType::itidx_;
  using BaseType::container_;

 public:

  using BaseType::IteratorBase;
  using BaseType::operator=;

  // Operators
  template <typename __Val, Trans __trans, class __Matrix>
  friend inline std::ostream& operator<<( std::ostream &os,
                                          const DenseMatrixIteratorBase<__Val, __trans, __Matrix> &it ) noexcept;

  // Gets value
  inline ValType&    val() const noexcept;
  inline index_t     rowidx() const noexcept;
  inline index_t     colidx() const noexcept;
  inline index_t     idx0() const noexcept;
  inline index_t     idx1() const noexcept;
  inline index_t     pos() const noexcept;
  inline ElemRefType elemRef() const noexcept;
  inline ElemPtrType elemPtr() const noexcept;

};

template <typename _Val, Trans _trans>
using DenseMatrixIterator = DenseMatrixIteratorBase<_Val, _trans, DenseMatrix<_Val, _trans>>;

template <typename _Val, Trans _trans>
using DenseMatrixConstIterator = DenseMatrixIteratorBase<const _Val, _trans, const DenseMatrix<_Val, _trans>>;

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_DENSE_DENSE_MATRIX_ITERATOR_HH_
