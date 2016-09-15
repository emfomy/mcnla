////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/matrix/dense/dense_cube_iterator.hpp
/// @brief   The dense cube iterator class.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_MATRIX_DENSE_DENSE_CUBE_ITERATOR_HPP_
#define ISVD_MATRIX_DENSE_DENSE_CUBE_ITERATOR_HPP_

#include <isvd/isvd.hpp>
#include <iterator>
#include <isvd/matrix/dense/dense_cube.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Scalar, Layout _layout> class DenseCube;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

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
template <typename _Scalar, Layout _layout, class _Cube>
class DenseCubeIteratorBase : public std::iterator<std::forward_iterator_tag, _Scalar> {

 protected:

  /// The row index.
  index_t rowidx_;

  /// The column index.
  index_t colidx_;

  /// The page index.
  index_t pageidx_;

  /// The leading index.
  index_t &idx1_ = isColMajor(_layout) ? rowidx_ : colidx_;

  /// The second index.
  index_t &idx2_ = isColMajor(_layout) ? colidx_ : rowidx_;

  /// The cube.
  _Cube *cube_;

 public:

  // Constructors
  inline DenseCubeIteratorBase() noexcept;
  inline DenseCubeIteratorBase( _Cube *cube ) noexcept;
  inline DenseCubeIteratorBase( _Cube *cube, const index_t rowidx, const index_t colidx, const index_t pageidx ) noexcept;
  inline DenseCubeIteratorBase( const DenseCubeIteratorBase &other ) noexcept;

  // Operators
  inline DenseCubeIteratorBase& operator=( const DenseCubeIteratorBase &other ) noexcept;
  inline bool operator==( const DenseCubeIteratorBase &other ) const noexcept;
  inline bool operator!=( const DenseCubeIteratorBase &other ) const noexcept;
  inline DenseCubeIteratorBase& operator++() noexcept;
  inline DenseCubeIteratorBase  operator++( int ) noexcept;
  inline       _Scalar& operator*() noexcept;
  inline const _Scalar& operator*() const noexcept;
  inline       _Scalar* operator->() noexcept;
  inline const _Scalar* operator->() const noexcept;

  // Gets value
  inline       _Scalar& getValue() noexcept;
  inline const _Scalar& getValue() const noexcept;
  inline       index_t getRowIdx() const noexcept;
  inline       index_t getColIdx() const noexcept;
  inline       index_t getPageIdx() const noexcept;
  inline       index_t getIdx1() const noexcept;
  inline       index_t getIdx2() const noexcept;
  inline       index_t getPos() const noexcept;

  // Sets to begin/end
  inline DenseCubeIteratorBase& setBegin() noexcept;
  inline DenseCubeIteratorBase& setEnd() noexcept;

  // Gets the begin/end iterator
  static inline DenseCubeIteratorBase getBegin( _Cube *cube ) noexcept;
  static inline DenseCubeIteratorBase getEnd( _Cube *cube ) noexcept;

};

}  // namespace internal

template <typename _Scalar, Layout _layout>
using DenseCubeIterator = internal::DenseCubeIteratorBase<_Scalar, _layout, DenseCube<_Scalar, _layout>>;

template <typename _Scalar, Layout _layout>
using DenseCubeConstIterator = internal::DenseCubeIteratorBase<const _Scalar, _layout, const DenseCube<_Scalar, _layout>>;

}  // namespace isvd

#endif  // ISVD_MATRIX_DENSE_DENSE_CUBE_ITERATOR_HPP_
