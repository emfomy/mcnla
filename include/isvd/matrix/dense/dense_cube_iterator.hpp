////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/matrix/dense/dense_cube_iterator.hpp
/// @brief   The dense cube iterator class.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_MATRIX_DENSE_DENSE_CUBE_ITERATOR_HPP_
#define ISVD_MATRIX_DENSE_DENSE_CUBE_ITERATOR_HPP_

#include <iterator>
#include <isvd/isvd.hpp>
#include <isvd/matrix/dense/dense_cube.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

template <typename _Scalar, Layout _layout> class DenseCube;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The internal namespace.
//
namespace internal {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense cube iterator.
///
/// @tparam  _Scalar  The scalar type.
/// @tparam  _layout  The storage layout.
///
template <typename _Scalar, Layout _layout>
class DenseCubeIterator : public std::iterator<std::forward_iterator_tag, _Scalar> {

 protected:

  /// The leading index.
  index_t idx1_;

  /// The second index.
  index_t idx2_;

  /// The page index.
  index_t idx3_;

  /// The row index.
  index_t &rowidx_ = isColMajor(_layout) ? idx1_ : idx2_;

  /// The column index.
  index_t &colidx_ = isColMajor(_layout) ? idx2_ : idx1_;

  /// The cube.
  DenseCube<_Scalar, _layout> *cube_;

 public:

  // Constructors
  DenseCubeIterator() noexcept;
  DenseCubeIterator( DenseCube<_Scalar, _layout> *cube ) noexcept;
  DenseCubeIterator( const DenseCubeIterator &other ) noexcept;

  // Operators
  inline DenseCubeIterator& operator=( const DenseCubeIterator &other ) noexcept;
  inline bool operator==( const DenseCubeIterator &other ) const noexcept;
  inline bool operator!=( const DenseCubeIterator &other ) const noexcept;
  inline DenseCubeIterator& operator++() noexcept;
  inline DenseCubeIterator& operator++( int ) noexcept;
  inline       _Scalar& operator*() noexcept;
  inline const _Scalar& operator*() const noexcept;
  inline       _Scalar* operator->() noexcept;
  inline const _Scalar* operator->() const noexcept;

  // Gets value
  inline       _Scalar& getValue() noexcept;
  inline const _Scalar& getValue() const noexcept;
  inline       index_t getRowIdx() noexcept;
  inline       index_t getColIdx() noexcept;
  inline       index_t getPageIdx() noexcept;
  inline       index_t getIdx1() noexcept;
  inline       index_t getIdx2() noexcept;

  // Sets to begin & end
  inline DenseCubeIterator& setBegin() noexcept;
  inline DenseCubeIterator& setEnd() noexcept;

};

}  // namespace internal

}  // namespace isvd

#endif  // ISVD_MATRIX_DENSE_DENSE_CUBE_ITERATOR_HPP_
