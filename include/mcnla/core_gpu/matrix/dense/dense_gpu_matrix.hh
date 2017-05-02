////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core_gpu/matrix/dense/dense_gpu_matrix.hh
/// @brief   The definition of definition of dense GPU matrix class.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_GPU_MATRIX_DENSE_DENSE_GPU_MATRIX_HH_
#define MCNLA_CORE_GPU_MATRIX_DENSE_DENSE_GPU_MATRIX_HH_

#include <mcnla/core_gpu/matrix/def.hpp>
#include <mcnla/core/matrix/base/matrix_wrapper.hpp>
#include <mcnla/core/matrix/base/invertible_wrapper.hpp>
#include <mcnla/core/matrix/dense/dense_matrix_storage.hpp>
#include <mcnla/core_gpu/matrix/dense/dense_gpu_vector.hpp>
#pragma warning
// #include <mcnla/core_gpu/matrix/dense/dense_symmetric_gpu_matrix.hpp>
// #include <mcnla/core_gpu/matrix/dense/dense_triangular_gpu_matrix.hpp>
#include <mcnla/core_gpu/matrix/dense/dense_diagonal_gpu_matrix.hpp>
#include <mcnla/core_gpu/matrix/kit/gpu_array.hpp>
#include <mcnla/core/utility/traits.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Val> class DenseGpuVector;
template <typename _Val, Trans _trans> class DenseGpuMatrix;
template <typename _Val, Trans _trans, Uplo _uplo> class DenseSymmetricGpuMatrix;
template <typename _Val, Trans _trans, Uplo _uplo> class DenseTriangularGpuMatrix;
template <typename _Val> class DenseDiagonalGpuMatrix;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace matrix

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The traits namespace.
//
namespace traits {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense GPU matrix traits.
///
template <typename _Val, Trans _trans>
struct Traits<matrix::DenseGpuMatrix<_Val, _trans>> {

  static constexpr Trans trans = _trans;

  using ValType     = _Val;

  using RealType    = matrix::DenseGpuMatrix<RealValT<_Val>, _trans>;
  using ComplexType = matrix::DenseGpuMatrix<ComplexValT<_Val>, _trans>;

  using VectorType  = matrix::DenseGpuVector<_Val>;
  using MatrixType  = matrix::DenseGpuMatrix<_Val, _trans>;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense GPU matrix instantiation type traits.
///
template <typename _Type>
struct IsDenseGpuMatrix : std::false_type {};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc IsDenseGpuMatrix
///
template <typename _Val, Trans _trans>
struct IsDenseGpuMatrix<matrix::DenseGpuMatrix<_Val, _trans>> : std::true_type {};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense GPU matrix assert.
///
#define assertDenseGpuMatrix( Type ) \
    static_assert(traits::IsDenseGpuMatrix<Type>::value, "'"#Type"' is not a dense GPU matrix!")

}  // namespace traits

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  gpu_matrix_dense_module
/// The dense GPU matrix class.
///
/// @tparam  _Val    The value type.
/// @tparam  _trans  The transpose storage layout.
///
template <typename _Val, Trans _trans = Trans::NORMAL>
class DenseMatrix
  : public DenseMatrixStorage<_Val, GpuArray>,
    public MatrixWrapper<DenseGpuMatrix<_Val, _trans>>
    public InvertibleWrapper<DenseGpuMatrix<_Val, _trans>> {

  static_assert(!isConj(_trans), "Conjugate matrix is not supported!");

  friend MatrixWrapper<DenseGpuMatrix<_Val, _trans>>;
  friend InvertibleWrapper<DenseGpuMatrix<_Val, _trans>>;

 public:

  static constexpr Trans trans = _trans;

  using ValType           = _Val;
  using ValArrayType      = GpuArray<_Val>;
  using SizesType         = std::tuple<index_t, index_t>;

  using RealType          = DenseGpuMatrix<RealValT<_Val>, _trans>;
  using ComplexType       = DenseGpuMatrix<ComplexValT<_Val>, _trans>;

  using VectorType        = DenseGpuVector<_Val>;
  using MatrixType        = DenseGpuMatrix<_Val, _trans>;

  using TransposeType     = DenseGpuMatrix<_Val, changeTrans(_trans)>;
  using ConjugateType     = DenseGpuMatrix<_Val, changeConj(_trans)>;
  using HermitianType     = DenseGpuMatrix<_Val, changeHerm(_trans)>;

  template <Uplo _uplo>
  using SymmetricType     = DenseSymmetricGpuMatrix<_Val, _trans, _uplo>;

  template <Uplo _uplo>
  using TriangularType    = DenseTriangularGpuMatrix<_Val, _trans, _uplo>;

  using DiagonalType      = DenseDiagonalMatrix<_Val>;

 private:

  using BaseType          = DenseMatrixStorage<_Val, GpuArray>;

 public:

  // Constructors
  inline DenseMatrix() noexcept;
  inline DenseMatrix( const index_t nrow, const index_t ncol ) noexcept;
  inline DenseMatrix( const SizesType sizes ) noexcept;
  inline DenseMatrix( const index_t nrow, const index_t ncol, const index_t pitch ) noexcept;
  inline DenseMatrix( const SizesType sizes, const index_t pitch ) noexcept;
  inline DenseMatrix( const index_t nrow, const index_t ncol, const index_t pitch, const index_t capacity ) noexcept;
  inline DenseMatrix( const SizesType sizes, const index_t pitch, const index_t capacity ) noexcept;
  inline DenseMatrix( const index_t nrow, const index_t ncol, const index_t pitch,
                      const ValArrayType &val, const index_t offset = 0 ) noexcept;
  inline DenseMatrix( const DenseMatrix &other ) noexcept;

  // Operators
  inline DenseMatrix& operator=( const DenseMatrix &other ) noexcept;

  // Gets information
  inline index_t nnz() const noexcept;

  // Gets internal position
  inline index_t pos( const index_t rowidx, const index_t colidx ) const noexcept;

  // Finds the iterator
  inline IteratorType      find( const index_t rowidx, const index_t colidx ) noexcept;
  inline ConstIteratorType find( const index_t rowidx, const index_t colidx ) const noexcept;
  inline ConstIteratorType cfind( const index_t rowidx, const index_t colidx ) const noexcept;

  // Resizes
  template <typename... Args>
  inline void reconstruct( Args... args ) noexcept;
  inline void resize( const index_t nrow, const index_t ncol ) noexcept;
  inline void resize( const index_t nrow, const FullRange ) noexcept;
  inline void resize( const FullRange, const index_t ncol ) noexcept;

  // Transpose/Conjugate
  inline       TransposeType& t() noexcept;
  inline const TransposeType& t() const noexcept;
  inline       ConjugateType& c() noexcept;
  inline const ConjugateType& c() const noexcept;
  inline       HermitianType& h() noexcept;
  inline const HermitianType& h() const noexcept;

  // Change view
  template <Uplo _uplo = Uplo::UPPER ^ _trans>
  inline       SymmetricType<_uplo>& viewSymmetric() noexcept;
  template <Uplo _uplo = Uplo::UPPER ^ _trans>
  inline const SymmetricType<_uplo>& viewSymmetric() const noexcept;

  template <Uplo _uplo = Uplo::UPPER ^ _trans>
  inline       TriangularType<_uplo>& viewTriangular() noexcept;
  template <Uplo _uplo = Uplo::UPPER ^ _trans>
  inline const TriangularType<_uplo>& viewTriangular() const noexcept;

  inline       DiagonalType viewDiagonal() noexcept;
  inline const DiagonalType viewDiagonal() const noexcept;

  // Gets matrix block
  inline       MatrixType operator()( const IdxRange &rowrange, const IdxRange &colrange ) noexcept;
  inline const MatrixType operator()( const IdxRange &rowrange, const IdxRange &colrange ) const noexcept;
  inline       MatrixType operator()( const FullRange, const IdxRange &colrange ) noexcept;
  inline const MatrixType operator()( const FullRange, const IdxRange &colrange ) const noexcept;
  inline       MatrixType operator()( const IdxRange &rowrange, const FullRange ) noexcept;
  inline const MatrixType operator()( const IdxRange &rowrange, const FullRange ) const noexcept;

  // Gets vector segment
  inline       VectorType operator()( const IdxRange &rowrange, const index_t colidx ) noexcept;
  inline const VectorType operator()( const IdxRange &rowrange, const index_t colidx ) const noexcept;
  inline       VectorType operator()( const FullRange, const index_t colidx ) noexcept;
  inline const VectorType operator()( const FullRange, const index_t colidx ) const noexcept;
  inline       VectorType operator()( const index_t rowidx, const IdxRange &colrange ) noexcept;
  inline const VectorType operator()( const index_t rowidx, const IdxRange &colrange ) const noexcept;
  inline       VectorType operator()( const index_t rowidx, const FullRange ) noexcept;
  inline const VectorType operator()( const index_t rowidx, const FullRange ) const noexcept;

  inline       VectorType getDiagonal( const index_t idx = 0 ) noexcept;
  inline const VectorType getDiagonal( const index_t idx = 0 ) const noexcept;
  inline       VectorType vectorize() noexcept;
  inline const VectorType vectorize() const noexcept;

 protected:

  // Gets information
  inline index_t nrowImpl() const noexcept;
  inline index_t ncolImpl() const noexcept;

  // Convert sizes to dims
  inline index_t toDim0( const SizesType sizes ) const noexcept;
  inline index_t toDim0( const index_t nrow, const index_t ncol ) const noexcept;
  inline index_t toDim1( const SizesType sizes ) const noexcept;
  inline index_t toDim1( const index_t nrow, const index_t ncol ) const noexcept;

  // Create full index range
  inline const IdxRange colfullrange() const noexcept;
  inline const IdxRange rowfullrange() const noexcept;

  // Gets base class
  inline       BaseType& base() noexcept;
  inline const BaseType& base() const noexcept;

};

/// @ingroup  gpu_matrix_dense_module
template <typename _Val>
using DenseGpuMatrixColMajor = DenseGpuMatrix<_Val, Trans::NORMAL>;

/// @ingroup  gpu_matrix_dense_module
template <typename _Val>
using DenseGpuMatrixRowMajor = DenseGpuMatrix<_Val, Trans::TRANS>;

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_GPU_MATRIX_DENSE_DENSE_GPU_MATRIX_HH_
