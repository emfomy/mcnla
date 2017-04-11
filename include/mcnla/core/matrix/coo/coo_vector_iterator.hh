////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/coo/coo_vector_iterator.hh
/// @brief   The definition of COO vector iterator class.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_COO_COO_VECTOR_ITERATOR_HH_
#define MCNLA_CORE_MATRIX_COO_COO_VECTOR_ITERATOR_HH_

#include <mcnla/core/matrix/def.hpp>
#include <mcnla/core/matrix/base/iterator_base.hpp>
#include <mcnla/core/matrix/coo/coo_vector.hpp>
#include <mcnla/core/matrix/coo/coo_tuple1.hpp>
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
template <typename _Val> class CooVector;
template <typename _Val, typename _Idx, class _Vector> class CooVectorIteratorBase;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace matrix

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The traits namespace.
//
namespace traits {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The COO vector iterator traits.
///
template <typename _Val, typename _Idx, class _Vector>
struct Traits<matrix::CooVectorIteratorBase<_Val, _Idx, _Vector>> {
  static constexpr index_t ndim = 1;
  using ElemType      = std::tuple<_Idx>;
  using ElemRefType   = matrix::CooTuple1<_Val, _Idx>;
  using ElemPtrType   = matrix::CooTuple1Ptr<_Val, _Idx>;
  using ContainerType = _Vector;
};

}  // namespace traits

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The COO vector iterator.
///
/// @tparam  _Val     The value type.
/// @tparam  _Idx     The index type.
/// @tparam  _Vector  The vector type.
///
/// @see  CooVectorIterator, CooVectorConstIterator
///
template <typename _Val, typename _Idx, class _Vector>
class CooVectorIteratorBase : public IteratorBase<CooVectorIteratorBase<_Val, _Idx, _Vector>> {

 private:

  static constexpr index_t ndim = 1;
  using ValType       = _Val;
  using IdxType       = _Idx;
  using TupleType     = CooTuple1<_Val, _Idx>;
  using ElemType      = std::tuple<_Idx>;
  using ElemRefType   = CooTuple1<_Val, _Idx>;
  using ElemPtrType   = CooTuple1Ptr<_Val, _Idx>;
  using ContainerType = _Vector;

  using BaseType      = IteratorBase<CooVectorIteratorBase<_Val, _Idx, _Vector>>;

 protected:

  using BaseType::itidx_;
  using BaseType::container_;

 public:

  using BaseType::IteratorBase;
  using BaseType::operator=;

  // Operators
  template <typename __Val, typename __Idx, class __Vector>
  friend inline std::ostream& operator<<( std::ostream &os, const CooVectorIteratorBase<__Val, __Idx, __Vector> &it );

  // Gets value
  inline ValType&    val() const noexcept;
  inline IdxType&    idx() const noexcept;
  inline IdxType&    idx0() const noexcept;
  inline TupleType   tuple() const noexcept;
  inline index_t     pos() const noexcept;
  inline ElemRefType elemRef() const noexcept;
  inline ElemPtrType elemPtr() const noexcept;

};

template <typename _Val>
using CooVectorIterator = CooVectorIteratorBase<_Val, index_t, CooVector<_Val>>;

template <typename _Val>
using CooVectorConstIterator = CooVectorIteratorBase<const _Val, const index_t, const CooVector<_Val>>;

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_COO_COO_VECTOR_ITERATOR_HH_
