////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/matrix/coo/coo_cube.hpp
/// @brief   The COO cube class.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_MATRIX_COO_COO_CUBE_HPP_
#define ISVD_MATRIX_COO_COO_CUBE_HPP_

#include <isvd/isvd.hpp>
#include <iostream>
#include <utility>
#include <isvd/matrix/base/cube_base.hpp>
#include <isvd/matrix/coo/coo_base.hpp>
#include <isvd/matrix/coo/coo_vector.hpp>
#include <isvd/matrix/coo/coo_matrix.hpp>
#include <isvd/matrix/coo/coo_cube_iterator.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Scalar, Layout _layout> class CooCube;
template <typename _Scalar, Layout _layout> class CooMatrix;
template <typename _Scalar> class CooVector;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The detail namespace.
//
namespace detail {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The coordinate list (COO) cube traits.
///
/// @tparam  _Scalar  The scalar type.
/// @tparam  _layout  The storage layout.
///
template <typename _Scalar, Layout _layout>
struct Traits<CooCube<_Scalar, _layout>> {
  static constexpr index_t ndim = 3;
  static constexpr Layout layout = _layout;

  using ScalarType        = _Scalar;
  using RealScalarType    = typename detail::ScalarTraits<_Scalar>::RealType;

  using VectorType        = CooVector<ScalarType>;
  using RealVectorType    = CooVector<RealScalarType>;
  using MatrixType        = CooMatrix<ScalarType, _layout>;
  using RealMatrixType    = CooMatrix<RealScalarType, _layout>;
  using CubeType          = CooCube<ScalarType, _layout>;
  using RealCubeType      = CooCube<RealScalarType, _layout>;
  using TransposeType     = CooCube<ScalarType, changeLayout(_layout)>;
  using RealTransposeType = CooCube<RealScalarType, changeLayout(_layout)>;

  using IteratorType      = CooCubeIterator<ScalarType, _layout>;
  using ConstIteratorType = CooCubeConstIterator<ScalarType, _layout>;
};

}  // namespace detail

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The coordinate list (COO) cube class.
///
/// @tparam  _Scalar  The scalar type.
/// @tparam  _layout  The storage layout.
///
/// @todo  Add sorting attention to routines.
///
template <typename _Scalar, Layout _layout = Layout::COLMAJOR>
class CooCube
  : public ContainerBase<CooCube<_Scalar, _layout>>,
    public CubeBase<CooCube<_Scalar, _layout>>,
    public CooBase<CooCube<_Scalar, _layout>> {

 public:

  static constexpr index_t ndim = 3;
  static constexpr Layout layout = _layout;

  using ScalarType        = _Scalar;
  using RealScalarType    = typename detail::ScalarTraits<_Scalar>::RealType;
  using ValuePtrType      = std::shared_ptr<std::valarray<ScalarType>>;
  using IdxPtrType        = std::shared_ptr<std::valarray<index_t>>;

  using VectorType        = CooVector<ScalarType>;
  using RealVectorType    = CooVector<RealScalarType>;
  using MatrixType        = CooMatrix<ScalarType, _layout>;
  using RealMatrixType    = CooMatrix<RealScalarType, _layout>;
  using CubeType          = CooCube<ScalarType, _layout>;
  using RealCubeType      = CooCube<RealScalarType, _layout>;
  using TransposeType     = CooCube<ScalarType, changeLayout(_layout)>;
  using RealTransposeType = CooCube<RealScalarType, changeLayout(_layout)>;

  using DataType          = CooData<ndim, ScalarType>;

  using IteratorType      = CooCubeIterator<ScalarType, _layout>;
  using ConstIteratorType = CooCubeConstIterator<ScalarType, _layout>;

 private:

  using ContainerBaseType = ContainerBase<CooCube<_Scalar, _layout>>;
  using CubeBaseType      = CubeBase<CooCube<_Scalar, _layout>>;
  using CooBaseType       = CooBase<CooCube<_Scalar, _layout>>;

 protected:

  using CubeBaseType::nrow_;
  using CubeBaseType::ncol_;
  using CubeBaseType::npage_;
  using CubeBaseType::size0_;
  using CubeBaseType::size1_;
  using CubeBaseType::size2_;
  using CooBaseType::nnz_;
  using CooBaseType::offset_;
  using CooBaseType::data_;

 public:

  // Constructors
  inline CooCube() noexcept;
  inline CooCube( const index_t ncol, const index_t nrow, const index_t npage ) noexcept;
  inline CooCube( const std::tuple<index_t, index_t, index_t> sizes ) noexcept;
  inline CooCube( const index_t ncol, const index_t nrow, const index_t npage, const index_t capability ) noexcept;
  inline CooCube( const std::tuple<index_t, index_t, index_t> sizes, const index_t capability ) noexcept;
  inline CooCube( const index_t ncol, const index_t nrow, const index_t npage,
                  const index_t nnz, const index_t capability, const index_t offset = 0 ) noexcept;
  inline CooCube( const std::tuple<index_t, index_t, index_t> sizes,
                  const index_t nnz, const index_t capability, const index_t offset = 0 ) noexcept;
  inline CooCube( const index_t ncol, const index_t nrow, const index_t npage, const index_t nnz,
                  const ValuePtrType &value, const IdxPtrType &rowidx, const IdxPtrType &colidx, const IdxPtrType &pageidx,
                  const index_t offset = 0 ) noexcept;
  inline CooCube( const index_t ncol, const index_t nrow, const index_t npage, const index_t nnz,
                  const DataType &data, const index_t offset = 0 ) noexcept;
  inline CooCube( const CooCube &other ) noexcept;
  inline CooCube( CooCube &&other ) noexcept;

  // Operators
  inline CooCube& operator=( const CooCube &other ) noexcept;
  inline CooCube& operator=( CooCube &&other ) noexcept;
  template <typename __Scalar, Layout __layout>
  friend inline std::ostream& operator<<( std::ostream &out, const CooCube<__Scalar, __layout> &cube );

  // Gets index array
  template <TransOption _trans = TransOption::NORMAL> inline       index_t* getRowIdx() noexcept;
  template <TransOption _trans = TransOption::NORMAL> inline const index_t* getRowIdx() const noexcept;
  template <TransOption _trans = TransOption::NORMAL> inline       index_t* getColIdx() noexcept;
  template <TransOption _trans = TransOption::NORMAL> inline const index_t* getColIdx() const noexcept;
  inline       index_t* getPageIdx() noexcept;
  inline const index_t* getPageIdx() const noexcept;

  // Gets element
  inline ScalarType getElem( const index_t rowidx, const index_t colidx, const index_t pageidx ) const noexcept;
  inline ScalarType operator()( const index_t rowidx, const index_t colidx, const index_t pageidx ) const noexcept;

  // Gets the internal position
  inline index_t getPos( const index_t rowidx, const index_t colidx, const index_t pageidx ) const noexcept;
  inline void getPosNnz( const IdxRange rowrange, const IdxRange colrange, const IdxRange pagerange,
                         index_t &pos, index_t &nnz ) const noexcept;

  // Finds the iterator
  inline IteratorType      find( const index_t rowidx, const index_t colidx, const index_t pageidx ) noexcept;
  inline ConstIteratorType find( const index_t rowidx, const index_t colidx, const index_t pageidx ) const noexcept;
  inline ConstIteratorType cfind( const index_t rowidx, const index_t colidx, const index_t pageidx ) const noexcept;

  // Sorts
  inline void sort() noexcept;
  inline bool isSorted() const noexcept;

  // Transpose
  inline TransposeType transpose() noexcept;

  // Resizes
  inline void resize( const index_t nrow, const index_t ncol, const index_t npage ) noexcept;

  // Gets matrix block
  inline       MatrixType getPage( const index_t pageidx ) noexcept;
  inline const MatrixType getPage( const index_t pageidx ) const noexcept;

  // Gets vector segment
  inline       VectorType getCol( const index_t colidx, const index_t pageidx ) noexcept;
  inline const VectorType getCol( const index_t colidx, const index_t pageidx ) const noexcept;
  inline       VectorType getRow( const index_t rowidx, const index_t pageidx ) noexcept;
  inline const VectorType getRow( const index_t rowidx, const index_t pageidx ) const noexcept;

};

}  // namespace isvd

#endif  // ISVD_MATRIX_COO_COO_CUBE_HPP_
