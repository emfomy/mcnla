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
class CooMatrixIteratorBase
  : public IteratorBase<CooMatrixIteratorBase<_Val, _Idx, _trans, _Matrix>, _Matrix, std::tuple<_Idx, _Idx>,
                        CooTuple2<_Val, _Idx, _trans>, CooTuple2Ptr<_Val, _Idx, _trans>> {

 private:

  using ValType       = _Val;
  using IdxType       = _Idx;
  using TupleType     = CooTuple2<_Val, _Idx, _trans>;
  using ElemRefType   = CooTuple2<_Val, _Idx, _trans>;
  using ElemPtrType   = CooTuple2Ptr<_Val, _Idx, _trans>;
  using ContainerType = _Matrix;

  using BaseType      = IteratorBase<CooMatrixIteratorBase<_Val, _Idx, _trans, _Matrix>, _Matrix, std::tuple<_Idx, _Idx>,
                                     CooTuple2<_Val, _Idx, _trans>, CooTuple2Ptr<_Val, _Idx, _trans>>;

 protected:

  using BaseType::itidx_;
  using BaseType::container_;

 public:

  using BaseType::IteratorBase;
  using BaseType::operator=;

  // Operators
  template <typename ..._Args>
  friend inline std::ostream& operator<<( std::ostream &os, const CooMatrixIteratorBase<_Args...> &it );

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
