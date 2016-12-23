////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/dense/dense_matrix_storage.hpp
/// @brief   The dense matrix storage class.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_DENSE_DENSE_MATRIX_STORAGE_HPP_
#define MCNLA_CORE_MATRIX_DENSE_DENSE_MATRIX_STORAGE_HPP_

#include <mcnla/def.hpp>
#include <mcnla/core/def.hpp>
#include <tuple>
#include <mcnla/core/matrix/dense/dense_storage.hpp>
#include <mcnla/core/matrix/kit/idx_range.hpp>

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
/// The dense matrix storage class.
///
/// @tparam  _Scalar  The scalar type.
///
template <typename _Scalar>
class DenseMatrixStorage : public DenseStorage<_Scalar> {

 private:

  using ScalarType        = _Scalar;
  using ValueArrayType    = Array<ScalarType>;
  using DimsType          = std::tuple<index_t, index_t>;

  using VectorStorageType = DenseVectorStorage<ScalarType>;
  using MatrixStorageType = DenseMatrixStorage<ScalarType>;

  using BaseType          = DenseStorage<_Scalar>;

 protected:

  /// The size in the first dimension.
  index_t dim0_;

  /// The size in the second dimension.
  index_t dim1_;

  /// The maximum size in the first dimension.
  index_t pitch_;

  /// The stride.
  index_t stride_;

  using BaseType::value_;

 protected:

  // Constructors
  inline DenseMatrixStorage() noexcept;
  inline DenseMatrixStorage( const index_t dim0, const index_t dim1 ) noexcept;
  inline DenseMatrixStorage( const index_t dim0, const index_t dim1, const index_t pitch ) noexcept;
  inline DenseMatrixStorage( const index_t dim0, const index_t dim1, const index_t pitch, const index_t capacity ) noexcept;
  inline DenseMatrixStorage( const index_t dim0, const index_t dim1, const index_t pitch,
                             const ValueArrayType &value, const index_t offset = 0 ) noexcept;
  inline DenseMatrixStorage( const DenseMatrixStorage &other ) noexcept;
  inline DenseMatrixStorage( DenseMatrixStorage &&other ) noexcept;

  // Operators
  inline DenseMatrixStorage& operator=( const DenseMatrixStorage &other ) noexcept;
  inline DenseMatrixStorage& operator=( DenseMatrixStorage &&other ) noexcept;

 public:

  // Gets information
  inline bool     isShrunk() const noexcept;
  inline bool     isSquare() const noexcept;
  inline index_t  getDim0() const noexcept;
  inline index_t  getDim1() const noexcept;
  inline DimsType getDims() const noexcept;
  inline index_t  getPitch() const noexcept;

  // Gets internal position
  inline index_t getPos( const index_t idx0, const index_t idx1 ) const noexcept;

 protected:

  // Gets element
  inline       ScalarType& getElemImpl( const index_t idx0, const index_t idx1 ) noexcept;
  inline const ScalarType& getElemImpl( const index_t idx0, const index_t idx1 ) const noexcept;

  // Resizes
  inline void resizeImpl( const index_t nrow, const index_t ncol ) noexcept;

  // Gets matrix block
  inline       MatrixStorageType getBlockImpl( const IdxRange range0, const IdxRange range1 ) noexcept;
  inline const MatrixStorageType getBlockImpl( const IdxRange range0, const IdxRange range1 ) const noexcept;
  inline       MatrixStorageType getBlockImpl( const IdxRange range0, const IdxRange range1 ) noexcept;
  inline const MatrixStorageType getBlockImpl( const IdxRange range0, const IdxRange range1 ) const noexcept;
  inline       MatrixStorageType getColsImpl( const IdxRange range1 ) noexcept;
  inline const MatrixStorageType getColsImpl( const IdxRange range1 ) const noexcept;
  inline       MatrixStorageType getRowsImpl( const IdxRange range0 ) noexcept;
  inline const MatrixStorageType getRowsImpl( const IdxRange range0 ) const noexcept;

  // Gets vector segment
  inline       VectorStorageType getColImpl( const index_t idx1 ) noexcept;
  inline const VectorStorageType getColImpl( const index_t idx1 ) const noexcept;
  inline       VectorStorageType getColSegmentImpl( const index_t idx1, const IdxRange range0 ) noexcept;
  inline const VectorStorageType getColSegmentImpl( const index_t idx1, const IdxRange range0 ) const noexcept;
  inline       VectorStorageType getRowImpl( const index_t idx0 ) noexcept;
  inline const VectorStorageType getRowImpl( const index_t idx0 ) const noexcept;
  inline       VectorStorageType getRowSegmentImpl( const index_t idx0, const IdxRange range1 ) noexcept;
  inline const VectorStorageType getRowSegmentImpl( const index_t idx0, const IdxRange range1 ) const noexcept;
  inline       VectorStorageType getDiagonalImpl( const index_t idx = 0 ) noexcept;
  inline const VectorStorageType getDiagonalImpl( const index_t idx = 0 ) const noexcept;
  inline       VectorStorageType vectorizeImpl() noexcept;
  inline const VectorStorageType vectorizeImpl() const noexcept;

};

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_DENSE_DENSE_MATRIX_STORAGE_HPP_
