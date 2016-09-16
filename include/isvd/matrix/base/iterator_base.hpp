////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/matrix/base/iterator_base.hpp
/// @brief   The iterator interface.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_MATRIX_BASE_ITERATOR_BASE_HPP_
#define ISVD_MATRIX_BASE_ITERATOR_BASE_HPP_

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
template <class _Container> class IteratorBase;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense container iterator interface traits.
///
/// @tparam  _Container  The container type.
///
template <class _Container>
struct Traits<IteratorBase<_Container>> {
  using IteratorTag       = std::random_access_iterator_tag;
  using ContainerType     = _Container;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense container iterator interface.
///
/// @tparam  _Container  The container type.
///
template <class _Container>
class IteratorBase {

 protected:

  /// The iterator index.
  index_t itidx_;

  _Container *container_;

 public:

  // Constructors
  inline IteratorBase() noexcept;
  inline IteratorBase( _Container *matrix ) noexcept;
  inline IteratorBase( const IteratorBase &other ) noexcept;

  // Assignment operators
  inline IteratorBase& operator=( const IteratorBase &other ) noexcept;

  // Comparison operators

  inline bool operator==( const IteratorBase &other ) const noexcept;
  inline bool operator!=( const IteratorBase &other ) const noexcept;
  inline bool operator>( const IteratorBase &other ) const noexcept;
  inline bool operator<( const IteratorBase &other ) const noexcept;
  inline bool operator>=( const IteratorBase &other ) const noexcept;
  inline bool operator<=( const IteratorBase &other ) const noexcept;

  // Arithmetic operators
  inline IteratorBase& operator++() noexcept;
  inline IteratorBase& operator--() noexcept;
  inline IteratorBase  operator++( int ) noexcept;
  inline IteratorBase  operator--( int ) noexcept;
  inline IteratorBase& operator+=( const index_t num ) noexcept;
  inline IteratorBase& operator-=( const index_t num ) noexcept;
  inline IteratorBase  operator+( const index_t num ) const noexcept;
  inline IteratorBase  operator-( const index_t num ) const noexcept;

  inline index_t operator-( const IteratorBase &other ) const noexcept;
  template <class __Container>
  friend inline IteratorBase operator+( const index_t num, const IteratorBase<__Container> iterator ) noexcept;

  // Sets to begin/end
  inline IteratorBase& setBegin() noexcept;
  inline IteratorBase& setEnd() noexcept;

};

}  // namespace internal

}  // namespace isvd

#endif  // ISVD_MATRIX_BASE_ITERATOR_BASE_HPP_
