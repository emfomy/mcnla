////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/matrix/coo/coo_matrix_iterator.hpp
/// @brief   The COO matrix iterator class.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_MATRIX_COO_COO_MATRIX_ITERATOR_HPP_
#define ISVD_MATRIX_COO_COO_MATRIX_ITERATOR_HPP_

#include <isvd/isvd.hpp>
#include <isvd/matrix/coo/coo_iterator_base.hpp>
#include <isvd/matrix/coo/coo_matrix.hpp>
#include <isvd/matrix/coo/coo_tuple.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Scalar, Layout _layout> class CooMatrix;
template <typename _Scalar, typename _Index, Layout _layout, class _Matrix> class CooMatrixIteratorBase;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The detail namespace.
//
namespace detail {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The coordinate list (COO) matrix iterator traits.
///
/// @tparam  _Scalar  The scalar type.
/// @tparam  _Index   The index type.
/// @tparam  _Matrix  The matrix type.
///
template <typename _Scalar, typename _Index, Layout _layout, class _Matrix>
struct Traits<CooMatrixIteratorBase<_Scalar, _Index, _layout, _Matrix>> {
  static constexpr index_t ndim = 2;
  using ScalarType    = _Scalar;
  using IndexType     = _Index;
  using ContainerType = _Matrix;
};

}  // namespace detail

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The coordinate list (COO) matrix iterator.
///
/// @tparam  _Scalar  The scalar type.
/// @tparam  _Index   The index type.
/// @tparam  _Matrix  The matrix type.
///
template <typename _Scalar, typename _Index, Layout _layout, class _Matrix>
class CooMatrixIteratorBase : public CooIteratorBase<CooMatrixIteratorBase<_Scalar, _Index, _layout, _Matrix>> {

 private:

  static constexpr index_t ndim = 2;
  using ScalarType    = _Scalar;
  using IndexType     = _Index;
  using ContainerType = _Matrix;

  using BaseType      = CooIteratorBase<CooMatrixIteratorBase<_Scalar, _Index, _layout, _Matrix>>;

 protected:

  using BaseType::itidx_;
  using BaseType::container_;

 public:

  using BaseType::CooIteratorBase;
  using BaseType::operator=;

  // Operators
  template <typename __Scalar, typename __Index, Layout __layout, class __Matrix>
  friend inline std::ostream& operator<<( std::ostream &out,
                                          const CooMatrixIteratorBase<__Scalar, __Index, __layout, __Matrix> &iterator );

  // Gets value
  inline IndexType& getRowIdx() const noexcept;
  inline IndexType& getColIdx() const noexcept;
  inline index_t    getPos() const noexcept;

};

template <typename _Scalar, Layout _layout>
using CooMatrixIterator = CooMatrixIteratorBase<_Scalar, index_t, _layout, CooMatrix<_Scalar, _layout>>;

template <typename _Scalar, Layout _layout>
using CooMatrixConstIterator = CooMatrixIteratorBase<const _Scalar, const index_t, _layout, const CooMatrix<_Scalar, _layout>>;

}  // namespace isvd

#endif  // ISVD_MATRIX_COO_COO_MATRIX_ITERATOR_HPP_
