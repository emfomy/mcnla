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
#include <isvd/utility/traits.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The internal namespace.
//
namespace internal {

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <class _Derived> class IteratorBase;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense container iterator interface traits.
///
/// @tparam  _Derived  The derived type.
///
template <class _Derived>
struct Traits<IteratorBase<_Derived>> {
  using IteratorTag = std::random_access_iterator_tag;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense container iterator interface.
///
/// @tparam  _Derived  The derived type.
///
template <class _Derived>
class IteratorBase {

 private:

  using ContainerType    = typename Traits<_Derived>::ContainerType;
  using BaseIteratorType = typename Traits<_Derived>::BaseType;

 protected:

  /// The iterator index.
  index_t itidx_;

  ContainerType *container_;

 public:

  // Constructors
  inline IteratorBase() noexcept;
  inline IteratorBase( ContainerType *container, const index_t itidx_ = 0 ) noexcept;
  inline IteratorBase( const IteratorBase &other ) noexcept;

  // Assignment operators
  inline _Derived& operator=( const IteratorBase &other ) noexcept;

  // Comparison operators

  inline bool operator==( const IteratorBase &other ) const noexcept;
  inline bool operator!=( const IteratorBase &other ) const noexcept;
  inline bool operator>( const IteratorBase &other ) const noexcept;
  inline bool operator<( const IteratorBase &other ) const noexcept;
  inline bool operator>=( const IteratorBase &other ) const noexcept;
  inline bool operator<=( const IteratorBase &other ) const noexcept;

  // Arithmetic operators
  inline _Derived& operator++() noexcept;
  inline _Derived& operator--() noexcept;
  inline _Derived  operator++( int ) noexcept;
  inline _Derived  operator--( int ) noexcept;
  inline _Derived& operator+=( const index_t num ) noexcept;
  inline _Derived& operator-=( const index_t num ) noexcept;
  inline _Derived  operator+( const index_t num ) const noexcept;
  inline _Derived  operator-( const index_t num ) const noexcept;

  inline index_t operator-( const IteratorBase &other ) const noexcept;
  template <class __Derived>
  friend inline __Derived operator+( const index_t num, const IteratorBase<__Derived> iterator ) noexcept;

  // Gets the data
  inline index_t        getItIdx() const noexcept;
  inline ContainerType* getContainer() const noexcept;

  // Gets the begin/end iterator
  static inline _Derived getBegin( ContainerType *container ) noexcept;
  static inline _Derived getEnd( ContainerType *container ) noexcept;

 protected:

  // Gets derived class
  inline       _Derived& derived() noexcept;
  inline const _Derived& derived() const noexcept;

};

}  // namespace internal

}  // namespace isvd

#endif  // ISVD_MATRIX_BASE_ITERATOR_BASE_HPP_
