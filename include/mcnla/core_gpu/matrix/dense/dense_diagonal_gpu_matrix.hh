////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core_gpu/matrix/dense/dense_diagonal_gpu_matrix.hh
/// @brief   The definition of definition of dense diagonal GPU matrix class.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_GPU_MATRIX_DENSE_DENSE_DIAGONAL_GPU_MATRIX_HH_
#define MCNLA_CORE_GPU_MATRIX_DENSE_DENSE_DIAGONAL_GPU_MATRIX_HH_

#include <mcnla/core_gpu/matrix/def.hpp>
#include <mcnla/core/matrix/base/matrix_wrapper.hpp>
#include <mcnla/core/matrix/base/invertible_wrapper.hpp>
#include <mcnla/core/matrix/dense/dense_vector_storage.hpp>
#include <mcnla/core_gpu/matrix/dense/dense_gpu_vector.hpp>
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
template <typename _Val> class DenseDiagonalGpuMatrix;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace matrix

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The traits namespace.
//
namespace traits {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense diagonal matrix traits.
///
template <typename _Val>
struct Traits<matrix::DenseDiagonalGpuMatrix<_Val>> {


  using ValType     = _Val;
  using RealType    = matrix::DenseDiagonalGpuMatrix<RealValT<_Val>>;
  using ComplexType = matrix::DenseDiagonalGpuMatrix<ComplexValT<_Val>>;
  using VectorType  = matrix::DenseGpuVector<_Val>;
  using MatrixType  = matrix::DenseDiagonalGpuMatrix<_Val>;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense diagonal matrix instantiation type traits.
///
template <typename _Type>
struct IsDenseDiagonalGpuMatrix : std::false_type {};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc IsDenseDiagonalGpuMatrix
///
template <typename _Val>
struct IsDenseDiagonalGpuMatrix<matrix::DenseDiagonalGpuMatrix<_Val>> : std::true_type {};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense diagonal matrix assert.
///
#define assertDenseDiagonalGpuMatrix( Type ) \
    static_assert(traits::IsDenseDiagonalGpuMatrix<Type>::value, "'"#Type"' is not a dense diagonal matrix!")

}  // namespace traits

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  gpu_matrix_dense_module
/// The dense diagonal matrix class.
///
/// @tparam  _Val  The value type.
///
template <typename _Val>
class DenseDiagonalGpuMatrix
  : public DenseVectorStorage<_Val, GpuArray>,
    public MatrixWrapper<DenseDiagonalGpuMatrix<_Val>>,
    public InvertibleWrapper<DenseDiagonalGpuMatrix<_Val>> {

  friend MatrixWrapper<DenseDiagonalGpuMatrix<_Val>>;
  friend InvertibleWrapper<DenseDiagonalGpuMatrix<_Val>>;

 public:

  using ValType       = _Val;
  using ValArrayType  = GpuArray<_Val>;

  using RealType      = DenseDiagonalGpuMatrix<RealValT<_Val>>;
  using ComplexType   = DenseDiagonalGpuMatrix<ComplexValT<_Val>>;

  using VectorType    = DenseGpuVector<_Val>;
  using MatrixType    = DenseDiagonalGpuMatrix<_Val>;

  using TransposeType = DenseDiagonalGpuMatrix<_Val>;

 private:

  using BaseType      = DenseVectorStorage<_Val, GpuArray>;

 public:

  // Constructors
  inline DenseDiagonalGpuMatrix() noexcept;
  inline DenseDiagonalGpuMatrix( const index_t size ) noexcept;
  inline DenseDiagonalGpuMatrix( const index_t size, const index_t pitch ) noexcept;
  inline DenseDiagonalGpuMatrix( const index_t size, const index_t pitch, const index_t capacity ) noexcept;
  inline DenseDiagonalGpuMatrix( const index_t size, const index_t pitch,
                                 const ValArrayType &val, const index_t offset = 0 ) noexcept;
  inline DenseDiagonalGpuMatrix( const DenseDiagonalGpuMatrix &other ) noexcept;

  // Operators
  inline DenseDiagonalGpuMatrix& operator=( const DenseDiagonalGpuMatrix &other ) noexcept;

  // Gets information
  inline index_t size() const noexcept;
  inline index_t nnz() const noexcept;
  inline index_t pitch() const noexcept;

  // Resizes
  template <typename... Args>
  inline void reconstruct( Args... args ) noexcept;

  // Transpose/Conjugate
  inline       TransposeType& t() noexcept;
  inline const TransposeType& t() const noexcept;

  // Changes view
  inline       VectorType& viewVector() noexcept;
  inline const VectorType& viewVector() const noexcept;

  // Gets vector
  inline       VectorType& vectorize() noexcept;
  inline const VectorType& vectorize() const noexcept;

 protected:

  // Gets information
  inline index_t nrowImpl() const noexcept;
  inline index_t ncolImpl() const noexcept;

  // Gets base class
  inline       BaseType& base() noexcept;
  inline const BaseType& base() const noexcept;

};

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_GPU_MATRIX_DENSE_DENSE_DIAGONAL_GPU_MATRIX_HH_
