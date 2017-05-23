////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/coo/coo_matrix_iterator.hh
/// @brief   The definition of COO matrix iterator class.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_COO_COO_MATRIX_ITERATOR_HH_
#define MCNLA_CORE_MATRIX_COO_COO_MATRIX_ITERATOR_HH_

#include <mcnla/core/matrix/coo/def.hpp>
#include <mcnla/core/matrix/base/iterator_base.hpp>
#include <mcnla/core/matrix/coo/coo_matrix.hpp>
#include <mcnla/core/matrix/coo/coo_tuple2.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Val, typename _Idx, Trans _trans, class _Matrix> class CooMatrixIteratorBase;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace matrix

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The traits namespace.
//
namespace traits {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The COO matrix iterator traits.
///
template <typename _Val, typename _Idx, Trans _trans, class _Matrix>
struct Traits<matrix::CooMatrixIteratorBase<_Val, _Idx, _trans, _Matrix>> {
  using ElemType      = std::tuple<_Idx, _Idx>;
  using ElemRefType   = matrix::CooTuple2<_Val, _Idx, _trans>;
  using ElemPtrType   = matrix::CooTuple2Ptr<_Val, _Idx, _trans>;
  using ContainerType = _Matrix;
};

}  // namespace traits

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The COO matrix iterator.
///
/// @tparam  _Val     The value type.
/// @tparam  _Idx     The index type.
/// @tparam  _trans   The transpose storage layout.
/// @tparam  _Matrix  The matrix type.
///
/// @see  CooMatrixIterator, CooMatrixConstIterator
///
template <typename _Val, typename _Idx, Trans _trans, class _Matrix>
class CooMatrixIteratorBase : public IteratorBase<CooMatrixIteratorBase<_Val, _Idx, _trans, _Matrix>> {

 private:

  using ValType       = _Val;
  using IdxType       = _Idx;
  using TupleType     = CooTuple2<_Val, _Idx, _trans>;
  using ElemType      = std::tuple<_Idx>;
  using ElemRefType   = CooTuple2<_Val, _Idx, _trans>;
  using ElemPtrType   = CooTuple2Ptr<_Val, _Idx, _trans>;
  using ContainerType = _Matrix;

  using BaseType      = IteratorBase<CooMatrixIteratorBase<_Val, _Idx, _trans, _Matrix>>;

 protected:

  using BaseType::itidx_;
  using BaseType::container_;

 public:

  using BaseType::IteratorBase;
  using BaseType::operator=;

  // Operators
  template <typename __Val, typename __Idx, Trans __trans, class __Matrix>
  friend inline std::ostream& operator<<( std::ostream &os, const CooMatrixIteratorBase<__Val, __Idx, __trans, __Matrix> &it );

  // Gets value
  inline ValType&    val() const noexcept;
  inline IdxType&    rowidx() const noexcept;
  inline IdxType&    colidx() const noexcept;
  inline IdxType&    idx0() const noexcept;
  inline IdxType&    idx1() const noexcept;
  inline TupleType   tuple() const noexcept;
  inline index_t     pos() const noexcept;
  inline ElemRefType elemRef() const noexcept;
  inline ElemPtrType elemPtr() const noexcept;

};

template <typename _Val, Trans _trans>
using CooMatrixIterator = CooMatrixIteratorBase<_Val, index_t, _trans, CooMatrix<_Val, _trans>>;

template <typename _Val, Trans _trans>
using CooMatrixConstIterator = CooMatrixIteratorBase<const _Val, const index_t, _trans, const CooMatrix<_Val, _trans>>;

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_COO_COO_MATRIX_ITERATOR_HH_
