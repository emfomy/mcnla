////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/dense/dense_vector_iterator.hh
/// @brief   The definition of dense vector iterator class.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_DENSE_DENSE_VECTOR_ITERATOR_HH_
#define MCNLA_CORE_MATRIX_DENSE_DENSE_VECTOR_ITERATOR_HH_

#include <mcnla/core/matrix/dense/def.hpp>
#include <mcnla/core/matrix/base/iterator_base.hpp>
#include <mcnla/core/matrix/dense/dense_vector.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense vector iterator.
///
/// @tparam  _Val     The value type.
/// @tparam  _Vector  The vector type.
///
/// @see  DenseVectorIterator, DenseVectorConstIterator
///
template <typename _Val, class _Vector>
class DenseVectorIteratorBase : public IteratorBase<DenseVectorIteratorBase<_Val, _Vector>, _Vector, _Val> {

 private:

  using ValType       = _Val;
  using ElemRefType   = _Val&;
  using ElemPtrType   = _Val*;
  using ContainerType = _Vector;

  using BaseType      = IteratorBase<DenseVectorIteratorBase<_Val, _Vector>, _Vector, _Val>;

 protected:

  using BaseType::itidx_;
  using BaseType::container_;

 public:

  using BaseType::IteratorBase;
  using BaseType::operator=;

  // Operators
  template <typename ..._Args>
  friend inline std::ostream& operator<<( std::ostream &os, const DenseVectorIteratorBase<_Args...> &it ) noexcept;

  // Gets value
  inline ValType&    val() const noexcept;
  inline index_t     idx() const noexcept;
  inline index_t     idx0() const noexcept;
  inline index_t     pos() const noexcept;
  inline ElemRefType elemRef() const noexcept;
  inline ElemPtrType elemPtr() const noexcept;

};

template <typename _Val>
using DenseVectorIterator = DenseVectorIteratorBase<_Val, DenseVector<_Val>>;

template <typename _Val>
using DenseVectorConstIterator = DenseVectorIteratorBase<const _Val, const DenseVector<_Val>>;

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_DENSE_DENSE_VECTOR_ITERATOR_HH_
