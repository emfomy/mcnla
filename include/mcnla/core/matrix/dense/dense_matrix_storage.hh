////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/dense/dense_matrix_storage.hh
/// @brief   The definition of dense matrix storage class.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_DENSE_DENSE_MATRIX_STORAGE_HH_
#define MCNLA_CORE_MATRIX_DENSE_DENSE_MATRIX_STORAGE_HH_

#include <mcnla/core/matrix/dense/def.hpp>
#include <tuple>
#include <mcnla/core/matrix/dense/dense_storage.hpp>
#include <mcnla/core/matrix/dense/dense_vector_storage.hpp>
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
/// The dense matrix storage class.
///
/// @tparam  _Core  The core tag.
/// @tparam  _Val   The value type.
///
template <class _Core, typename _Val>
class DenseMatrixStorage : public DenseStorage<_Core, _Val> {

 private:

  using ValType           = _Val;
  using ValArrayType      = ArrS<_Core, _Val>;
  using DimsType          = std::tuple<index_t, index_t>;

  using VectorStorageType = DenseVectorStorage<_Core, _Val>;
  using MatrixStorageType = DenseMatrixStorage<_Core, _Val>;

  using VectorType        = GeVecS<_Core, DenseTag, _Val>;

  using BaseType          = DenseStorage<_Core, _Val>;

 protected:

  /// The size in the first dimension.
  index_t dim0_;

  /// The size in the second dimension.
  index_t dim1_;

  /// The maximum size in the first dimension.
  index_t pitch_;

  using BaseType::val_;

 protected:

  // Constructors
  inline DenseMatrixStorage() noexcept;
  inline DenseMatrixStorage( const index_t dim0, const index_t dim1 ) noexcept;
  inline DenseMatrixStorage( const index_t dim0, const index_t dim1, const index_t pitch ) noexcept;
  inline DenseMatrixStorage( const index_t dim0, const index_t dim1, const index_t pitch, const index_t capacity ) noexcept;
  inline DenseMatrixStorage( const index_t dim0, const index_t dim1, const index_t pitch,
                             const ValArrayType &val, const index_t offset = 0 ) noexcept;
  inline DenseMatrixStorage( const DenseMatrixStorage &other ) noexcept;

  // Operators
  inline DenseMatrixStorage& operator=( const DenseMatrixStorage &other ) noexcept;

 public:

  // Gets information
  inline bool     isShrunk() const noexcept;
  inline bool     isSquare() const noexcept;
  inline index_t  dim0() const noexcept;
  inline index_t  dim1() const noexcept;
  inline index_t  mdim0() const noexcept;
  inline index_t  mdim1() const noexcept;
  inline DimsType dims() const noexcept;
  inline DimsType mdims() const noexcept;
  inline index_t  pitch() const noexcept;

  // Gets the storage vector
  inline       VectorType unfold() noexcept;
  inline const VectorType unfold() const noexcept;

 protected:

  // Gets element
  inline       ValType& elemImpl( const index_t idx0, const index_t idx1 ) noexcept;
  inline const ValType& elemImpl( const index_t idx0, const index_t idx1 ) const noexcept;

  // Gets internal position
  inline index_t posImpl( const index_t idx0, const index_t idx1 ) const noexcept;

  // Resizes
  inline void resizeImpl( const index_t nrow, const index_t ncol ) noexcept;

  // Gets matrix block
  inline       MatrixStorageType getMatrixImpl( const IdxRange &range0, const IdxRange &range1 ) noexcept;
  inline const MatrixStorageType getMatrixImpl( const IdxRange &range0, const IdxRange &range1 ) const noexcept;

  // Gets vector segment
  inline       VectorStorageType getVector0Impl( const IdxRange &range0, const index_t idx1 ) noexcept;
  inline const VectorStorageType getVector0Impl( const IdxRange &range0, const index_t idx1 ) const noexcept;
  inline       VectorStorageType getVector1Impl( const index_t idx0, const IdxRange &range1 ) noexcept;
  inline const VectorStorageType getVector1Impl( const index_t idx0, const IdxRange &range1 ) const noexcept;
  inline       VectorStorageType getDiagImpl( const index_t idx ) noexcept;
  inline const VectorStorageType getDiagImpl( const index_t idx ) const noexcept;
  inline       VectorStorageType vecImpl() noexcept;
  inline const VectorStorageType vecImpl() const noexcept;

};

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_DENSE_DENSE_MATRIX_STORAGE_HH_
