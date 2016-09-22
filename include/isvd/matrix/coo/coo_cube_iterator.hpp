////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/matrix/coo/coo_cube_iterator.hpp
/// @brief   The COO cube iterator class.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_MATRIX_COO_COO_CUBE_ITERATOR_HPP_
#define ISVD_MATRIX_COO_COO_CUBE_ITERATOR_HPP_

#include <isvd/isvd.hpp>
#include <isvd/matrix/coo/coo_iterator_base.hpp>
#include <isvd/matrix/coo/coo_cube.hpp>
#include <isvd/matrix/coo/coo_tuple.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Scalar, Layout _layout> class CooCube;
template <typename _Scalar, typename _Index, Layout _layout, class _Cube> class CooCubeIteratorBase;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The detail namespace.
//
namespace detail {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The coordinate list (COO) cube iterator traits.
///
/// @tparam  _Scalar  The scalar type.
/// @tparam  _Index   The index type.
/// @tparam  _Cube    The cube type.
///
template <typename _Scalar, typename _Index, Layout _layout, class _Cube>
struct Traits<CooCubeIteratorBase<_Scalar, _Index, _layout, _Cube>> {
  static constexpr index_t ndim = 3;
  using ScalarType    = _Scalar;
  using IndexType     = _Index;
  using ContainerType = _Cube;
};

}  // namespace detail

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The coordinate list (COO) cube iterator.
///
/// @tparam  _Scalar  The scalar type.
/// @tparam  _Index   The index type.
/// @tparam  _Cube    The cube type.
///
template <typename _Scalar, typename _Index, Layout _layout, class _Cube>
class CooCubeIteratorBase : public CooIteratorBase<CooCubeIteratorBase<_Scalar, _Index, _layout, _Cube>> {

 private:

  static constexpr index_t ndim = 3;
  using ScalarType    = _Scalar;
  using IndexType     = _Index;
  using ContainerType = _Cube;

  using BaseType      = CooIteratorBase<CooCubeIteratorBase<_Scalar, _Index, _layout, _Cube>>;

 protected:

  using BaseType::itidx_;
  using BaseType::container_;

 public:

  using BaseType::CooIteratorBase;
  using BaseType::operator=;

  // Operators
  template <typename __Scalar, typename __Index, Layout __layout, class __Cube>
  friend inline std::ostream& operator<<( std::ostream &out,
                                          const CooCubeIteratorBase<__Scalar, __Index, __layout, __Cube> &iterator );

  // Gets value
  inline IndexType& getRowIdx() const noexcept;
  inline IndexType& getColIdx() const noexcept;
  inline IndexType& getPageIdx() const noexcept;
  inline index_t    getPos() const noexcept;

};

template <typename _Scalar, Layout _layout>
using CooCubeIterator = CooCubeIteratorBase<_Scalar, index_t, _layout, CooCube<_Scalar, _layout>>;

template <typename _Scalar, Layout _layout>
using CooCubeConstIterator = CooCubeIteratorBase<const _Scalar, const index_t, _layout, const CooCube<_Scalar, _layout>>;

}  // namespace isvd

#endif  // ISVD_MATRIX_COO_COO_CUBE_ITERATOR_HPP_
