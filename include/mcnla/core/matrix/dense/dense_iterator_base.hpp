////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/dense/dense_iterator_base.hpp
/// @brief   The dense iterator interface.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_DENSE_DENSE_ITERATOR_BASE_HPP_
#define MCNLA_CORE_MATRIX_DENSE_DENSE_ITERATOR_BASE_HPP_

#include <mcnla/def.hpp>
#include <mcnla/core/def.hpp>
#include <iterator>
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
/// @ingroup  matrix_dense_module
/// The dense iterator interface.
///
/// @tparam  _Derived  The derived type.
///
template <class _Derived>
class DenseIteratorBase
  : public std::iterator<std::random_access_iterator_tag, typename traits::Traits<_Derived>::ScalarType> {

 private:

  static constexpr index_t ndim = traits::Traits<_Derived>::ndim;
  using ScalarType    = typename traits::Traits<_Derived>::ScalarType;
  using ContainerType = typename traits::Traits<_Derived>::ContainerType;

 protected:

  /// The container.
  ContainerType *container_;

  /// The iterator index.
  index_t itidx_;

 public:

  // Constructors
  inline DenseIteratorBase() noexcept;
  inline DenseIteratorBase( ContainerType *container, const index_t itidx = 0 ) noexcept;
  inline DenseIteratorBase( const DenseIteratorBase &other ) noexcept;

  // Assignment operators
  inline _Derived& operator=( const DenseIteratorBase &other ) noexcept;

  // Member access operators
  inline ScalarType& operator*() const noexcept;
  inline ScalarType* operator->() const noexcept;

  // Comparison operators
  inline bool operator==( const DenseIteratorBase &other ) const noexcept;
  inline bool operator!=( const DenseIteratorBase &other ) const noexcept;
  inline bool operator>(  const DenseIteratorBase &other ) const noexcept;
  inline bool operator<(  const DenseIteratorBase &other ) const noexcept;
  inline bool operator>=( const DenseIteratorBase &other ) const noexcept;
  inline bool operator<=( const DenseIteratorBase &other ) const noexcept;

  // Arithmetic operators
  inline _Derived& operator++() noexcept;
  inline _Derived& operator--() noexcept;
  inline _Derived  operator++( int ) noexcept;
  inline _Derived  operator--( int ) noexcept;
  inline _Derived& operator+=( const index_t num ) noexcept;
  inline _Derived& operator-=( const index_t num ) noexcept;
  inline _Derived  operator+(  const index_t num ) const noexcept;
  inline _Derived  operator-(  const index_t num ) const noexcept;

  inline index_t operator-( const DenseIteratorBase &other ) const noexcept;
  template <class __Derived>
  friend inline __Derived operator+( const index_t num, const DenseIteratorBase<__Derived> iterator ) noexcept;

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

  // Gets derived class
  inline       _Derived& derived() noexcept;
  inline const _Derived& derived() const noexcept;

};

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_DENSE_DENSE_ITERATOR_BASE_HPP_
