////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/matrix/coo/coo_vector_iterator.hpp
/// @brief   The COO vector iterator class.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_MATRIX_COO_COO_VECTOR_ITERATOR_HPP_
#define ISVD_MATRIX_COO_COO_VECTOR_ITERATOR_HPP_

#include <isvd/isvd.hpp>
#include <isvd/matrix/base/iterator_base.hpp>
#include <isvd/matrix/base/value_iterator_base.hpp>
#include <isvd/matrix/base/idx_iterator_base.hpp>
#include <isvd/matrix/coo/coo_vector.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Scalar> class CooVector;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The internal namespace.
//
namespace internal {

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Scalar, typename _Index, class _Vector> class CooVectorIteratorBase;
template <typename _Scalar, typename _Index, class _Vector> class CooVectorValueIteratorBase;
template <typename _Scalar, typename _Index, class _Vector> class CooVectorIdxIteratorBase;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The coordinate list (COO) vector iterator traits.
///
/// @tparam  _Scalar  The scalar type.
  /// @tparam  _Index   The index type.
/// @tparam  _Vector  The vector type.
///
template <typename _Scalar, typename _Index, class _Vector>
struct Traits<CooVectorIteratorBase<_Scalar, _Index, _Vector>> : Traits<IteratorBase<_Vector>> {
  using ScalarType        = _Scalar;
  using IdxTupleType      = IdxTuple<1>;
  using BaseType          = CooVectorIteratorBase<_Scalar, _Index, _Vector>;
  using ValueIteratorType = CooVectorValueIteratorBase<_Scalar, _Index, _Vector>;
  using IdxIteratorType   = CooVectorIdxIteratorBase<_Scalar, _Index, _Vector>;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The coordinate list (COO) vector value iterator traits.
///
/// @tparam  _Scalar  The scalar type.
/// @tparam  _Index   The index type.
/// @tparam  _Vector  The vector type.
///
template <typename _Scalar, typename _Index, class _Vector>
struct Traits<CooVectorValueIteratorBase<_Scalar, _Index, _Vector>>
  : Traits<CooVectorIteratorBase<_Scalar, _Index, _Vector>> {};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The coordinate list (COO) vector index iterator traits.
///
/// @tparam  _Scalar  The scalar type.
/// @tparam  _Index   The index type.
/// @tparam  _Vector  The vector type.
///
template <typename _Scalar, typename _Index, class _Vector>
struct Traits<CooVectorIdxIteratorBase<_Scalar, _Index, _Vector>>
  : Traits<CooVectorIteratorBase<_Scalar, _Index, _Vector>> {};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The coordinate list (COO) vector iterator.
///
/// @tparam  _Scalar  The scalar type.
/// @tparam  _Index   The index type.
/// @tparam  _Vector  The vector type.
///
template <typename _Scalar, typename _Index, class _Vector>
class CooVectorIteratorBase : public IteratorBase<_Vector> {

 protected:

  using IteratorBase<_Vector>::itidx_;
  using IteratorBase<_Vector>::container_;

 public:

  using IteratorBase<_Vector>::IteratorBase;

  // Operators
  template <typename __Scalar, typename __Matrix, class __Vector>
  friend inline std::ostream& operator<<( std::ostream &out,
                                          const CooVectorIteratorBase<__Scalar, __Matrix, __Vector> &iterator );

  // Gets value
  inline       _Scalar&    getValue() noexcept;
  inline const _Scalar&    getValue() const noexcept;
  inline       IdxTuple<1> getIdxs() const noexcept;
  inline       _Index&     getIdx() noexcept;
  inline const _Index&     getIdx() const noexcept;
  inline       index_t     getPos() const noexcept;

};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The coordinate list (COO) vector value iterator.
///
/// @tparam  _Scalar  The scalar type.
/// @tparam  _Index   The index type.
/// @tparam  _Vector  The vector type.
///
template <typename _Scalar, typename _Index, class _Vector>
class CooVectorValueIteratorBase
  : public CooVectorIteratorBase<_Scalar, _Index, _Vector>,
    public ValueIteratorBase<CooVectorValueIteratorBase<_Scalar, _Index, _Vector>> {

 public:

  using CooVectorIteratorBase<_Scalar, _Index, _Vector>::CooVectorIteratorBase;

};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The coordinate list (COO) vector value iterator.
///
/// @tparam  _Scalar  The scalar type.
/// @tparam  _Index   The index type.
/// @tparam  _Vector  The vector type.
///
template <typename _Scalar, typename _Index, class _Vector>
class CooVectorIdxIteratorBase
  : public CooVectorIteratorBase<_Scalar, _Index, _Vector>,
    public IdxIteratorBase<CooVectorIdxIteratorBase<_Scalar, _Index, _Vector>> {

 public:

  using CooVectorIteratorBase<_Scalar, _Index, _Vector>::CooVectorIteratorBase;

};

}  // namespace internal

template <typename _Scalar>
using CooVectorIterator = internal::CooVectorValueIteratorBase<_Scalar, index_t, CooVector<_Scalar>>;

template <typename _Scalar>
using CooVectorConstIterator = internal::CooVectorValueIteratorBase<const _Scalar, const index_t, const CooVector<_Scalar>>;

template <typename _Scalar>
using CooVectorIdxIterator = internal::CooVectorIdxIteratorBase<_Scalar, index_t, CooVector<_Scalar>>;

template <typename _Scalar>
using CooVectorConstIdxIterator = internal::CooVectorIdxIteratorBase<const _Scalar, const index_t, const CooVector<_Scalar>>;

}  // namespace isvd

#endif  // ISVD_MATRIX_COO_COO_VECTOR_ITERATOR_HPP_
