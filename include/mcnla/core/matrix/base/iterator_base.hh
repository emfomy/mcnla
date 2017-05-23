////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/base/iterator_base.hh
/// @brief   The definition of iterator interface.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_BASE_ITERATOR_BASE_HH_
#define MCNLA_CORE_MATRIX_BASE_ITERATOR_BASE_HH_

#include <mcnla/core/matrix/def.hpp>
#include <iterator>
#include <mcnla/core/utility/crtp.hpp>
#include <mcnla/core/utility/traits.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The iterator interface.
///
/// @tparam  _Derived    The derived type.
///
template <class _Derived>
class IteratorBase
  : public std::iterator<std::random_access_iterator_tag, typename traits::Traits<_Derived>::ElemType> {

 private:

  using ElemType      = typename traits::Traits<_Derived>::ElemType;
  using ElemRefType   = typename traits::Traits<_Derived>::ElemRefType;
  using ElemPtrType   = typename traits::Traits<_Derived>::ElemPtrType;
  using ContainerType = typename traits::Traits<_Derived>::ContainerType;

 protected:

  /// The container.
  ContainerType *container_;

  /// The iterator index.
  index_t itidx_;

 public:

  // Constructors
  inline IteratorBase() noexcept;
  inline IteratorBase( ContainerType *container, const index_t itidx = 0 ) noexcept;
  inline IteratorBase( const IteratorBase &other ) noexcept;

  // Assignment operators
  inline _Derived& operator=( const IteratorBase &other ) noexcept;

  // Member access operators
  inline ElemRefType operator*() const noexcept;
  inline ElemPtrType operator->() const noexcept;

  // Comparison operators
  inline bool operator==( const IteratorBase &other ) const noexcept;
  inline bool operator!=( const IteratorBase &other ) const noexcept;
  inline bool operator>(  const IteratorBase &other ) const noexcept;
  inline bool operator<(  const IteratorBase &other ) const noexcept;
  inline bool operator>=( const IteratorBase &other ) const noexcept;
  inline bool operator<=( const IteratorBase &other ) const noexcept;

  // Arithmetic operators
  inline _Derived& operator++() noexcept;
  inline _Derived& operator--() noexcept;
  inline _Derived  operator++( int ) noexcept;
  inline _Derived  operator--( int ) noexcept;
  inline _Derived& operator+=( const index_t num ) noexcept;
  inline _Derived& operator-=( const index_t num ) noexcept;
  inline _Derived  operator+(  const index_t num ) const noexcept;
  inline _Derived  operator-(  const index_t num ) const noexcept;

  inline index_t operator-( const IteratorBase &other ) const noexcept;
  template <class __Derived>
  friend inline __Derived operator+( const index_t num, const IteratorBase<__Derived> iterator ) noexcept;

  // Gets data
  inline ContainerType* container() const noexcept;
  inline index_t        itidx() const noexcept;

  // Sets to begin/end
  inline _Derived& setBegin() noexcept;
  inline _Derived& setEnd() noexcept;

  // Gets the begin/end iterator
  static inline _Derived beginImpl( ContainerType *container ) noexcept;
  static inline _Derived endImpl( ContainerType *container ) noexcept;

 protected:

  MCNLA_CRTP_DERIVED(_Derived)

};

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_BASE_ITERATOR_BASE_HH_
