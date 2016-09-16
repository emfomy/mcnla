////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/matrix/dense/dense_iterator_base.hpp
/// @brief   The dense container iterator interface.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_MATRIX_DENSE_DENSE_ITERATOR_BASE_HPP_
#define ISVD_MATRIX_DENSE_DENSE_ITERATOR_BASE_HPP_

#include <isvd/isvd.hpp>
#include <iterator>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The internal namespace.
//
namespace internal {

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Scalar, index_t _ndim, class _Container> class DenseIteratorBase;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense container iterator interface traits.
///
/// @tparam  _Scalar     The scalar type.
/// @tparam  _ndim       The dimension.
/// @tparam  _Container  The container type.
///
template <typename _Scalar, index_t _ndim, class _Container>
struct Traits<DenseIteratorBase<_Scalar, _ndim, _Container>> {
  using IteratorTag       = std::forward_iterator_tag;
  using ScalarType        = _Scalar;
  using IdxTupleType      = IdxTuple<_ndim>;
  using ContainerType     = _Container;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense container iterator interface.
///
/// @tparam  _Scalar     The scalar type.
/// @tparam  _ndim       The dimension.
/// @tparam  _Container  The container type.
///
template <typename _Scalar, index_t _ndim, class _Container>
class DenseIteratorBase {

 protected:

  /// The iterator index.
  index_t itidx_;

  _Container *container_;

 public:

  // Constructors
  inline DenseIteratorBase() noexcept;
  inline DenseIteratorBase( _Container *matrix ) noexcept;
  inline DenseIteratorBase( const DenseIteratorBase &other ) noexcept;

  // Operators
  inline DenseIteratorBase& operator=( const DenseIteratorBase &other ) noexcept;
  inline bool operator==( const DenseIteratorBase &other ) const noexcept;
  inline bool operator!=( const DenseIteratorBase &other ) const noexcept;
  inline DenseIteratorBase& operator++() noexcept;
  inline DenseIteratorBase  operator++( int ) noexcept;

  // Sets to begin/end
  inline DenseIteratorBase& setBegin() noexcept;
  inline DenseIteratorBase& setEnd() noexcept;

};

}  // namespace internal

}  // namespace isvd

#endif  // ISVD_MATRIX_DENSE_DENSE_ITERATOR_BASE_HPP_
