////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/matrix/coo/coo_iterator_base.hpp
/// @brief   The COO iterator interface.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_MATRIX_COO_COO_ITERATOR_BASE_HPP_
#define ISVD_MATRIX_COO_COO_ITERATOR_BASE_HPP_

#include <isvd/isvd.hpp>
#include <iterator>
#include <isvd/utility/traits.hpp>
#include <isvd/matrix/coo/coo_tuple.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The internal namespace.
//
namespace internal {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The The coordinate list (COO) iterator interface.
///
/// @tparam  _Derived  The derived type.
///
template <class _Derived>
class CooIteratorBase
  : public std::iterator<std::random_access_iterator_tag,
               CooTuple<Traits<_Derived>::ndim, typename Traits<_Derived>::ScalarType, typename Traits<_Derived>::IndexType>> {

 private:

  static constexpr index_t ndim =   Traits<_Derived>::ndim;
  using ScalarType       = typename Traits<_Derived>::ScalarType;
  using IndexType        = typename Traits<_Derived>::IndexType;
  using TupleType        = CooTuple<ndim, ScalarType, IndexType>;
  using ContainerType    = typename Traits<_Derived>::ContainerType;

 protected:

  /// The container.
  ContainerType *container_;

  /// The iterator index.
  index_t itidx_;

 public:

  // Constructors
  inline CooIteratorBase() noexcept;
  inline CooIteratorBase( ContainerType *container, const index_t itidx_ = 0 ) noexcept;
  inline CooIteratorBase( const CooIteratorBase &other ) noexcept;

  // Assignment operators
  inline _Derived& operator=( const CooIteratorBase &other ) noexcept;

  // Member access operators
  inline TupleType  operator*() const noexcept;
  inline TupleType* operator->() = delete;

  // Comparison operators
  inline bool operator==( const CooIteratorBase &other ) const noexcept;
  inline bool operator!=( const CooIteratorBase &other ) const noexcept;
  inline bool operator>(  const CooIteratorBase &other ) const noexcept;
  inline bool operator<(  const CooIteratorBase &other ) const noexcept;
  inline bool operator>=( const CooIteratorBase &other ) const noexcept;
  inline bool operator<=( const CooIteratorBase &other ) const noexcept;

  // Arithmetic operators
  inline _Derived& operator++() noexcept;
  inline _Derived& operator--() noexcept;
  inline _Derived  operator++( int ) noexcept;
  inline _Derived  operator--( int ) noexcept;
  inline _Derived& operator+=( const index_t num ) noexcept;
  inline _Derived& operator-=( const index_t num ) noexcept;
  inline _Derived  operator+(  const index_t num ) const noexcept;
  inline _Derived  operator-(  const index_t num ) const noexcept;

  inline index_t operator-( const CooIteratorBase &other ) const noexcept;
  template <class __Derived>
  friend inline __Derived operator+( const index_t num, const CooIteratorBase<__Derived> iterator ) noexcept;

  // Gets data
  inline ContainerType* getContainer() const noexcept;
  inline index_t        getItIdx() const noexcept;
  inline ScalarType&    getValue() const noexcept;
  template <index_t _dim> inline IndexType& getIdx() const noexcept;
  inline TupleType      getTuple() const noexcept;

  // Sets to begin/end
  inline _Derived& setBegin() noexcept;
  inline _Derived& setEnd() noexcept;

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

#endif  // ISVD_MATRIX_COO_COO_ITERATOR_BASE_HPP_
