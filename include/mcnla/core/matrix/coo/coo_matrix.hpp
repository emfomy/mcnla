////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/coo/coo_matrix.hpp
/// @brief   The COO matrix class.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_COO_COO_MATRIX_HPP_
#define MCNLA_CORE_MATRIX_COO_COO_MATRIX_HPP_

#include <mcnla/def.hpp>
#include <mcnla/core/def.hpp>
#include <iostream>
#include <utility>
#include <mcnla/core/matrix/base/matrix_base.hpp>
#include <mcnla/core/matrix/coo/coo_base.hpp>
#include <mcnla/core/matrix/coo/coo_vector.hpp>
#include <mcnla/core/matrix/coo/coo_matrix_iterator.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Scalar, Layout _layout> class CooMatrix;
template <typename _Scalar> class CooVector;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The traits namespace.
//
namespace traits {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The coordinate list (COO) matrix traits.
///
/// @tparam  _Scalar  The scalar type.
/// @tparam  _layout  The storage layout.
///
template <typename _Scalar, Layout _layout>
struct Traits<CooMatrix<_Scalar, _layout>> {
  static constexpr index_t ndim = 2;
  static constexpr Layout layout = _layout;

  using ScalarType        = _Scalar;
  using RealScalarType    = typename traits::ScalarTraits<_Scalar>::RealType;

  using VectorType        = CooVector<ScalarType>;
  using RealVectorType    = CooVector<RealScalarType>;
  using MatrixType        = CooMatrix<ScalarType, _layout>;
  using RealMatrixType    = CooMatrix<RealScalarType, _layout>;
  using TransposeType     = CooMatrix<ScalarType, changeLayout(_layout)>;
  using RealTransposeType = CooMatrix<RealScalarType, changeLayout(_layout)>;

  using IteratorType      = CooMatrixIterator<ScalarType, _layout>;
  using ConstIteratorType = CooMatrixConstIterator<ScalarType, _layout>;
};

}  // namespace traits

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The coordinate list (COO) matrix class.
///
/// @tparam  _Scalar  The scalar type.
/// @tparam  _layout  The storage layout.
///
/// @todo  Add sorting attention to routines.
///
template <typename _Scalar, Layout _layout = Layout::COLMAJOR>
class CooMatrix
  : public ContainerBase<CooMatrix<_Scalar, _layout>>,
    public MatrixBase<CooMatrix<_Scalar, _layout>>,
    public CooBase<CooMatrix<_Scalar, _layout>> {

 public:

  static constexpr index_t ndim = 2;
  static constexpr Layout layout = _layout;

  using ScalarType        = _Scalar;
  using RealScalarType    = typename traits::ScalarTraits<_Scalar>::RealType;
  using ValuePtrType      = std::shared_ptr<std::valarray<ScalarType>>;
  using IdxPtrType        = std::shared_ptr<std::valarray<index_t>>;

  using VectorType        = CooVector<ScalarType>;
  using RealVectorType    = CooVector<RealScalarType>;
  using MatrixType        = CooMatrix<ScalarType, _layout>;
  using RealMatrixType    = CooMatrix<RealScalarType, _layout>;
  using TransposeType     = CooMatrix<ScalarType, changeLayout(_layout)>;
  using RealTransposeType = CooMatrix<RealScalarType, changeLayout(_layout)>;

  using DataType          = CooData<ndim, ScalarType>;

  using IteratorType      = CooMatrixIterator<ScalarType, _layout>;
  using ConstIteratorType = CooMatrixConstIterator<ScalarType, _layout>;

 private:

  using ContainerBaseType = ContainerBase<CooMatrix<_Scalar, _layout>>;
  using MatrixBaseType    = MatrixBase<CooMatrix<_Scalar, _layout>>;
  using CooBaseType       = CooBase<CooMatrix<_Scalar, _layout>>;

 protected:

  using MatrixBaseType::nrow_;
  using MatrixBaseType::ncol_;
  using MatrixBaseType::size0_;
  using MatrixBaseType::size1_;
  using CooBaseType::nnz_;
  using CooBaseType::offset_;
  using CooBaseType::data_;

 public:

  // Constructors
  inline CooMatrix() noexcept;
  inline CooMatrix( const index_t ncol, const index_t nrow ) noexcept;
  inline CooMatrix( const std::pair<index_t, index_t> sizes ) noexcept;
  inline CooMatrix( const index_t ncol, const index_t nrow, const index_t capability ) noexcept;
  inline CooMatrix( const std::pair<index_t, index_t> sizes, const index_t capability ) noexcept;
  inline CooMatrix( const index_t ncol, const index_t nrow, const index_t nnz,
                    const index_t capability, const index_t offset = 0 ) noexcept;
  inline CooMatrix( const std::pair<index_t, index_t> sizes, const index_t nnz,
                    const index_t capability, const index_t offset = 0 ) noexcept;
  inline CooMatrix( const index_t ncol, const index_t nrow, const index_t nnz, const ValuePtrType &value,
                    const IdxPtrType &rowidx, const IdxPtrType &colidx, const index_t offset = 0 ) noexcept;
  inline CooMatrix( const index_t ncol, const index_t nrow, const index_t nnz,
                    const DataType &data, const index_t offset = 0 ) noexcept;
  inline CooMatrix( const CooMatrix &other ) noexcept;
  inline CooMatrix( CooMatrix &&other ) noexcept;

  // Operators
  inline CooMatrix& operator=( const CooMatrix &other ) noexcept;
  inline CooMatrix& operator=( CooMatrix &&other ) noexcept;
  template <typename __Scalar, Layout __layout>
  friend inline std::ostream& operator<<( std::ostream &out, const CooMatrix<__Scalar, __layout> &matrix );

  // Gets index array
  inline       index_t* getRowIdx() noexcept;
  inline const index_t* getRowIdx() const noexcept;
  inline       index_t* getColIdx() noexcept;
  inline const index_t* getColIdx() const noexcept;

  // Gets element
  inline ScalarType getElem( const index_t rowidx, const index_t colidx ) const noexcept;
  inline ScalarType operator()( const index_t rowidx, const index_t colidx ) const noexcept;

  // Gets the internal position
  inline index_t getPos( const index_t rowidx, const index_t colidx ) const noexcept;
  inline void getPosNnz( const IdxRange rowrange, const IdxRange colrange, index_t &pos, index_t &nnz ) const noexcept;

  // Finds the iterator
  inline IteratorType      find( const index_t rowidx, const index_t colidx ) noexcept;
  inline ConstIteratorType find( const index_t rowidx, const index_t colidx ) const noexcept;
  inline ConstIteratorType cfind( const index_t rowidx, const index_t colidx ) const noexcept;

  // Sorts
  inline void sort() noexcept;
  inline bool isSorted() const noexcept;

  // Transpose
  inline TransposeType transpose() noexcept;

  // Resizes
  inline void resize( const index_t nrow, const index_t ncol ) noexcept;

  // Gets vector segment
  inline       VectorType getCol( const index_t colidx ) noexcept;
  inline const VectorType getCol( const index_t colidx ) const noexcept;
  inline       VectorType getRow( const index_t rowidx ) noexcept;
  inline const VectorType getRow( const index_t rowidx ) const noexcept;

};

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_COO_COO_MATRIX_HPP_
