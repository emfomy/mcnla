////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/coo/coo_vector_iterator.hpp
/// @brief   The COO vector iterator class.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_COO_COO_VECTOR_ITERATOR_HPP_
#define MCNLA_CORE_MATRIX_COO_COO_VECTOR_ITERATOR_HPP_

#include <mcnla/def.hpp>
#include <mcnla/core/def.hpp>
#include <mcnla/core/matrix/coo/coo_iterator_base.hpp>
#include <mcnla/core/matrix/coo/coo_vector.hpp>
#include <mcnla/core/matrix/coo/coo_tuple.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Scalar> class CooVector;
template <typename _Scalar, typename _Index, class _Vector> class CooVectorIteratorBase;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The traits namespace.
//
namespace traits {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The coordinate list (COO) vector iterator traits.
///
/// @tparam  _Scalar  The scalar type.
/// @tparam  _Index   The index type.
/// @tparam  _Vector  The vector type.
///
template <typename _Scalar, typename _Index, class _Vector>
struct Traits<CooVectorIteratorBase<_Scalar, _Index, _Vector>> {
  static constexpr index_t ndim = 1;
  using ScalarType    = _Scalar;
  using IndexType     = _Index;
  using ContainerType = _Vector;
};

}  // namespace traits

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The coordinate list (COO) vector iterator.
///
/// @tparam  _Scalar  The scalar type.
/// @tparam  _Index   The index type.
/// @tparam  _Vector  The vector type.
///
/// @see  CooVectorIterator, CooVectorConstIterator
///
template <typename _Scalar, typename _Index, class _Vector>
class CooVectorIteratorBase : public CooIteratorBase<CooVectorIteratorBase<_Scalar, _Index, _Vector>> {

 private:

  static constexpr index_t ndim = 1;
  using ScalarType    = _Scalar;
  using IndexType     = _Index;
  using ContainerType = _Vector;

  using BaseType      = CooIteratorBase<CooVectorIteratorBase<_Scalar, _Index, _Vector>>;

 protected:

  using BaseType::itidx_;
  using BaseType::container_;

 public:

  using BaseType::CooIteratorBase;
  using BaseType::operator=;

  // Operators
  template <typename __Scalar, typename __Index, class __Vector>
  friend inline std::ostream& operator<<( std::ostream &out,
                                          const CooVectorIteratorBase<__Scalar, __Index, __Vector> &iterator );

  // Gets value
  using BaseType::getIdx;
  inline IndexType& getIdx() const noexcept;
  inline index_t    getPos() const noexcept;

};

template <typename _Scalar>
using CooVectorIterator = CooVectorIteratorBase<_Scalar, index_t, CooVector<_Scalar>>;

template <typename _Scalar>
using CooVectorConstIterator = CooVectorIteratorBase<const _Scalar, const index_t, const CooVector<_Scalar>>;

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_COO_COO_VECTOR_ITERATOR_HPP_
