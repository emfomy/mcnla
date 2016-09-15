////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/matrix/coo/coo_matrix.hpp
/// @brief   The COO matrix class.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_MATRIX_COO_COO_MATRIX_HPP_
#define ISVD_MATRIX_COO_COO_MATRIX_HPP_

#include <isvd/isvd.hpp>
#include <iostream>
#include <utility>
#include <isvd/matrix/base/matrix_base.hpp>
#include <isvd/matrix/coo/coo_base.hpp>
#include <isvd/matrix/coo/coo_vector.hpp>
// #include <isvd/matrix/coo/coo_matrix_iterator.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Scalar, Layout _layout> class CooMatrix;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The internal namespace.
//
namespace internal {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The coordinate list (COO) matrix traits.
///
/// @tparam  _Scalar  The scalar type.
/// @tparam  _layout  The storage layout.
///
template <typename _Scalar, Layout _layout>
struct Traits<CooMatrix<_Scalar, _layout>> {
  static constexpr index_t ndim = 2;
  using ScalarType        = _Scalar;
  using RealScalarType    = typename internal::ScalarTraits<_Scalar>::RealType;
  using VectorType        = CooVector<ScalarType>;
  using RealVectorType    = CooVector<RealScalarType>;
  using MatrixType        = CooMatrix<ScalarType, _layout>;
  using RealMatrixType    = CooMatrix<RealScalarType, _layout>;
  using TransposeType     = CooMatrix<ScalarType, changeLayout(_layout)>;
  using RealTransposeType = CooMatrix<RealScalarType, changeLayout(_layout)>;
};

}  // namespace internal

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The coordinate list (COO) matrix class.
///
/// @tparam  _Scalar  The scalar type.
/// @tparam  _layout  The storage layout.
///
template <typename _Scalar, Layout _layout = Layout::COLMAJOR>
class CooMatrix
  : public internal::MatrixBase<CooMatrix<_Scalar, _layout>>,
    public internal::CooBase<CooMatrix<_Scalar, _layout>> {

 public:

  using ScalarType        = _Scalar;
  using RealScalarType    = typename internal::ScalarTraits<_Scalar>::RealType;

  using VectorType        = CooVector<ScalarType>;
  using RealVectorType    = CooVector<RealScalarType>;
  using MatrixType        = CooMatrix<ScalarType, _layout>;
  using RealMatrixType    = CooMatrix<RealScalarType, _layout>;
  using TransposeType     = CooMatrix<ScalarType, changeLayout(_layout)>;
  using RealTransposeType = CooMatrix<RealScalarType, changeLayout(_layout)>;

  using DataType          = CooData<ScalarType, 2>;
  // using IteratorType      = CooMatrixIterator<ScalarType>;
  // using ConstIteratorType = CooMatrixConstIterator<ScalarType>;

 private:

  using MatrixBaseType    = internal::MatrixBase<CooMatrix<_Scalar, _layout>>;
  using CooBaseType       = internal::CooBase<CooMatrix<_Scalar, _layout>>;

  template <class _Type> using EnableIfColMajor = typename std::enable_if<isColMajor(_layout), _Type>::type;
  template <class _Type> using EnableIfRowMajor = typename std::enable_if<isRowMajor(_layout), _Type>::type;

 protected:

  using MatrixBaseType::nrow_;
  using MatrixBaseType::ncol_;
  using MatrixBaseType::size1_;
  using MatrixBaseType::size2_;
  using CooBaseType::nnz_;
  using CooBaseType::offset_;
  using CooBaseType::data_;

 public:

  // Constructors
  CooMatrix() noexcept;
  CooMatrix( const index_t ncol, const index_t nrow ) noexcept;
  CooMatrix( const std::pair<index_t, index_t> sizes ) noexcept;
  CooMatrix( const index_t ncol, const index_t nrow, const index_t capability, const index_t offset = 0 ) noexcept;
  CooMatrix( const std::pair<index_t, index_t> sizes, const index_t capability, const index_t offset = 0 ) noexcept;
  CooMatrix( const index_t ncol, const index_t nrow, const index_t nnz,
             const ValuePtrType &value, IdxPtrType rowidx, IdxPtrType colidx, const index_t offset = 0 ) noexcept;
  CooMatrix( const index_t ncol, const index_t nrow, const index_t nnz,
             const DataType &data, const index_t offset = 0 ) noexcept;
  CooMatrix( const CooMatrix &other ) noexcept;
  CooMatrix( CooMatrix &&other ) noexcept;

  // Operators
  inline CooMatrix& operator=( const CooMatrix &other ) noexcept;
  inline CooMatrix& operator=( CooMatrix &&other ) noexcept;
  template <typename __Scalar, Layout __layout>
  friend std::ostream& operator<<( std::ostream &out, const CooMatrix<__Scalar, __layout> &matrix );

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

  // Gets iterator
  // inline IteratorType      begin() noexcept;
  // inline ConstIteratorType begin() const noexcept;
  // inline ConstIteratorType cbegin() const noexcept;
  // inline IteratorType      end() noexcept;
  // inline ConstIteratorType end() const noexcept;
  // inline ConstIteratorType cend() const noexcept;
  // inline IteratorType      getIterator( const index_t idx ) noexcept;
  // inline ConstIteratorType getIterator( const index_t idx ) const noexcept;
  // inline ConstIteratorType getConstIterator( const index_t idx ) const noexcept;

  // Transpose
  inline TransposeType transpose() noexcept;

  // Resizes
  inline void resize( const index_t nrow, const index_t ncol ) noexcept;

  // Gets matrix block
  template <typename _MatrixType = MatrixType>
  inline       EnableIfColMajor<_MatrixType> getCols( const IdxRange rowrange ) noexcept;
  template <typename _MatrixType = MatrixType>
  inline const EnableIfColMajor<_MatrixType> getCols( const IdxRange rowrange ) const noexcept;
  template <typename _MatrixType = MatrixType>
  inline       EnableIfRowMajor<_MatrixType> getRows( const IdxRange colrange ) noexcept;
  template <typename _MatrixType = MatrixType>
  inline const EnableIfRowMajor<_MatrixType> getRows( const IdxRange colrange ) const noexcept;

  // Gets vector segment
  template <typename _VectorType = VectorType>
  inline       EnableIfColMajor<_VectorType> getCol( const index_t colidx ) noexcept;
  template <typename _VectorType = VectorType>
  inline const EnableIfColMajor<_VectorType> getCol( const index_t colidx ) const noexcept;
  template <typename _VectorType = VectorType>
  inline       EnableIfColMajor<_VectorType> getColSegment( const index_t colidx, const IdxRange rowrange ) noexcept;
  template <typename _VectorType = VectorType>
  inline const EnableIfColMajor<_VectorType> getColSegment( const index_t colidx, const IdxRange rowrange ) const noexcept;
  template <typename _VectorType = VectorType>
  inline       EnableIfRowMajor<_VectorType> getRow( const index_t rowidx ) noexcept;
  template <typename _VectorType = VectorType>
  inline const EnableIfRowMajor<_VectorType> getRow( const index_t rowidx ) const noexcept;
  template <typename _VectorType = VectorType>
  inline       EnableIfRowMajor<_VectorType> getRowSegment( const index_t rowidx, const IdxRange colrange ) noexcept;
  template <typename _VectorType = VectorType>
  inline const EnableIfRowMajor<_VectorType> getRowSegment( const index_t rowidx, const IdxRange colrange ) const noexcept;

};

}  // namespace isvd

#endif  // ISVD_MATRIX_COO_COO_MATRIX_HPP_
