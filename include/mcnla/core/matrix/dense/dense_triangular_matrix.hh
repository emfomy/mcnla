////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/dense/dense_triangular_matrix.hh
/// @brief   The definition of dense triangular matrix class.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_DENSE_DENSE_TRIANGULAR_MATRIX_HH_
#define MCNLA_CORE_MATRIX_DENSE_DENSE_TRIANGULAR_MATRIX_HH_

#include <mcnla/core/matrix/def.hpp>
#include <mcnla/core/matrix/base/dense_matrix_wrapper.hpp>
#include <mcnla/core/matrix/base/iterable_wrapper.hpp>
#include <mcnla/core/matrix/base/invertible_wrapper.hpp>
#include <mcnla/core/matrix/dense/dense_matrix_storage.hpp>
#include <mcnla/core/matrix/dense/dense_vector.hpp>
#include <mcnla/core/matrix/dense/dense_matrix.hpp>
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
template <typename _Val> class DenseVector;
template <typename _Val, Trans _trans> class DenseMatrix;
template <typename _Val, Trans _trans, Uplo _uplo> class DenseTriangularMatrix;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace matrix

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The traits namespace.
//
namespace traits {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense triangular matrix traits.
///
template <typename _Val, Trans _trans, Uplo _uplo>
struct Traits<matrix::DenseTriangularMatrix<_Val, _trans, _uplo>> {

  static constexpr index_t ndim = 2;
  static constexpr Trans trans = _trans;
  static constexpr Uplo uplo = _uplo;

  using ValType     = _Val;

  using RealType    = matrix::DenseTriangularMatrix<RealValT<_Val>, _trans, _uplo>;
  using ComplexType = matrix::DenseTriangularMatrix<ComplexValT<_Val>, _trans, _uplo>;

  using VectorType  = matrix::DenseVector<_Val>;
  using MatrixType  = matrix::DenseTriangularMatrix<_Val, _trans, _uplo>;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense triangular matrix instantiation type traits.
///
template <typename _Type>
struct IsDenseTriangularMatrix : std::false_type {};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc IsDenseTriangularMatrix
///
template <typename _Val, Trans _trans, Uplo _uplo>
struct IsDenseTriangularMatrix<matrix::DenseTriangularMatrix<_Val, _trans, _uplo>> : std::true_type {};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense triangular matrix assert.
///
#define assertDenseTriangularMatrix( Type ) \
    static_assert(traits::IsDenseTriangularMatrix<Type>::value, "'"#Type"' is not a dense triangular matrix!")

}  // namespace traits

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  matrix_dense_module
/// The dense triangular matrix class.
///
/// @tparam  _Val  The value type.
/// @tparam  _trans   The transpose storage layout.
/// @tparam  _uplo    The triangular storage layout.
///
template <typename _Val, Trans _trans = Trans::NORMAL, Uplo _uplo = Uplo::UPPER ^ _trans>
class DenseTriangularMatrix
  : public DenseMatrixStorage<_Val>,
    public DenseMatrixWrapper<DenseTriangularMatrix<_Val, _trans, _uplo>>,
    public InvertibleWrapper<DenseTriangularMatrix<_Val, _trans, _uplo>> {

  static_assert(!isConj(_trans), "Conjugate matrix is not supported!");

  friend MatrixWrapper<DenseTriangularMatrix<_Val, _trans, _uplo>>;
  friend DenseMatrixWrapper<DenseTriangularMatrix<_Val, _trans, _uplo>>;
  friend InvertibleWrapper<DenseTriangularMatrix<_Val, _trans, _uplo>>;

 public:

  static constexpr index_t ndim = 2;
  static constexpr Trans trans = _trans;
  static constexpr Uplo uplo = _uplo;

  using ValType       = _Val;
  using ValArrayType  = Array<_Val>;

  using RealType      = DenseTriangularMatrix<RealValT<_Val>, _trans, _uplo>;
  using ComplexType   = DenseTriangularMatrix<ComplexValT<_Val>, _trans, _uplo>;

  using VectorType    = DenseVector<_Val>;
  using MatrixType    = DenseTriangularMatrix<_Val, _trans, _uplo>;

  using TransposeType = DenseTriangularMatrix<_Val, changeTrans(_trans), changeUplo(_uplo)>;

  using GeneralType   = DenseMatrix<_Val, _trans>;

 private:

  using BaseType      = DenseMatrixStorage<_Val>;

 public:

  // Constructors
  inline DenseTriangularMatrix() noexcept;
  inline DenseTriangularMatrix( const index_t size ) noexcept;
  inline DenseTriangularMatrix( const index_t size, const index_t pitch ) noexcept;
  inline DenseTriangularMatrix( const index_t size, const index_t pitch, const index_t capacity ) noexcept;
  inline DenseTriangularMatrix( const index_t size, const index_t pitch,
                                const ValArrayType &val, const index_t offset = 0 ) noexcept;
  inline DenseTriangularMatrix( const DenseTriangularMatrix &other ) noexcept;

  // Operators
  inline DenseTriangularMatrix& operator=( const DenseTriangularMatrix &other ) noexcept;

  // Copy
  inline DenseTriangularMatrix copy() const noexcept;

  // Gets information
  inline index_t size() const noexcept;
  inline index_t nnz() const noexcept;

  // Gets element
  inline ValType operator()( const index_t rowidx, const index_t colidx ) const noexcept;

  // Resizes
  template <typename... Args>
  inline void reconstruct( Args... args ) noexcept;
  inline void resize( const index_t size ) noexcept;

  // Transpose/Conjugate
  inline       TransposeType& t() noexcept;
  inline const TransposeType& t() const noexcept;

  // Change view
  inline       GeneralType& viewGeneral() noexcept;
  inline const GeneralType& viewGeneral() const noexcept;

 protected:

  // Gets information
  inline index_t nrowImpl() const noexcept;
  inline index_t ncolImpl() const noexcept;

  // Gets base class
  inline       BaseType& base() noexcept;
  inline const BaseType& base() const noexcept;

};

/// @ingroup  matrix_dense_module
template <typename _Val, Uplo _uplo = Uplo::UPPER>
using DenseTriangularMatrixColMajor = DenseTriangularMatrix<_Val, Trans::NORMAL, _uplo>;

/// @ingroup  matrix_dense_module
template <typename _Val, Uplo _uplo = Uplo::LOWER>
using DenseTriangularMatrixRowMajor = DenseTriangularMatrix<_Val, Trans::TRANS, _uplo>;

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_DENSE_DENSE_TRIANGULAR_MATRIX_HH_
