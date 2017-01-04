////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/dense/dense_triangular_matrix.hpp
/// @brief   The dense triangular matrix class.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_DENSE_DENSE_TRIANGULAR_MATRIX_HPP_
#define MCNLA_CORE_MATRIX_DENSE_DENSE_TRIANGULAR_MATRIX_HPP_

#include <mcnla/def.hpp>
#include <mcnla/core/def.hpp>
#include <mcnla/core/matrix/base/matrix_wrapper.hpp>
#include <mcnla/core/matrix/base/container_wrapper.hpp>
#include <mcnla/core/matrix/dense/dense_matrix_storage.hpp>
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
template <typename _Scalar, Trans _trans, Uplo _uplo> class DenseTriangularMatrix;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace matrix

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The traits namespace.
//
namespace traits {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense triangular matrix traits.
///
template <typename _Scalar, Trans _trans, Uplo _uplo>
struct Traits<matrix::DenseTriangularMatrix<_Scalar, _trans, _uplo>> {

  static constexpr index_t ndim = 2;
  static constexpr Trans trans = _trans;
  static constexpr Uplo uplo = _uplo;

  using ScalarType = _Scalar;
  using RealType    = matrix::DenseTriangularMatrix<RealScalar<_Scalar>, _trans, _uplo>;
  using ComplexType = matrix::DenseTriangularMatrix<ComplexScalar<_Scalar>, _trans, _uplo>;
};

}  // namespace traits

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  matrix_dense_module
/// The dense triangular matrix class.
///
/// @tparam  _Scalar  The scalar type.
/// @tparam  _trans   The transpose storage layout.
/// @tparam  _uplo    The triangular storage layout.
///
template <typename _Scalar, Trans _trans = Trans::NORMAL, Uplo _uplo = Uplo::UPPER>
class DenseTriangularMatrix
  : public DenseMatrixStorage<_Scalar>,
    public MatrixWrapper<DenseTriangularMatrix<_Scalar, _trans, _uplo>> {

  static_assert(!isConj(_trans), "Conjugate matrix is not supported!");
  friend MatrixWrapper<DenseTriangularMatrix<_Scalar, _trans, _uplo>>;

 public:

  static constexpr index_t ndim = 2;
  static constexpr Trans trans = _trans;
  static constexpr Uplo uplo = _uplo;

  using ScalarType     = _Scalar;
  using ValueArrayType = Array<_Scalar>;

  using RealType       = DenseTriangularMatrix<RealScalar<_Scalar>, _trans, _uplo>;
  using ComplexType    = DenseTriangularMatrix<ComplexScalar<_Scalar>, _trans, _uplo>;

  using TransposeType  = DenseTriangularMatrix<_Scalar, changeTrans(_trans), _uplo>;

  using GeneralType    = DenseMatrix<_Scalar, _trans>;

 private:

  using BaseType       = DenseMatrixStorage<_Scalar>;

 public:

  // Constructors
  inline DenseTriangularMatrix() noexcept;
  inline DenseTriangularMatrix( const index_t size ) noexcept;
  inline DenseTriangularMatrix( const index_t size, const index_t pitch ) noexcept;
  inline DenseTriangularMatrix( const index_t size, const index_t pitch, const index_t capacity ) noexcept;
  inline DenseTriangularMatrix( const index_t size, const index_t pitch,
                                const ValueArrayType &value, const index_t offset = 0 ) noexcept;
  inline DenseTriangularMatrix( const DenseTriangularMatrix &other ) noexcept;
  inline DenseTriangularMatrix( DenseTriangularMatrix &&other ) noexcept;

  // Operators
  inline DenseTriangularMatrix& operator=( const DenseTriangularMatrix &other ) noexcept;
  inline DenseTriangularMatrix& operator=( DenseTriangularMatrix &&other ) noexcept;

  // Gets information
  inline index_t size() const noexcept;

  // Gets element
  inline       ScalarType operator()( const index_t rowidx, const index_t colidx ) noexcept;
  inline const ScalarType operator()( const index_t rowidx, const index_t colidx ) const noexcept;

  // Resizes
  template <typename... Args>
  inline void reconstruct( Args... args ) noexcept;
  inline void resize( const index_t nrow, const index_t ncol ) noexcept;

  // Transpose
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
template <typename _Scalar, Uplo _uplo = Uplo::UPPER>
using DenseTriangularMatrixColMajor = DenseTriangularMatrix<_Scalar, Trans::NORMAL, _uplo>;

/// @ingroup  matrix_dense_module
template <typename _Scalar, Uplo _uplo = Uplo::UPPER>
using DenseTriangularMatrixRowMajor = DenseTriangularMatrix<_Scalar, Trans::TRANS, _uplo>;

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_DENSE_DENSE_TRIANGULAR_MATRIX_HPP_
