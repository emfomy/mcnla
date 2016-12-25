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
template <typename _Scalar, Layout _layout, Uplo _uplo> class DenseTriangularMatrix;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace matrix

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The traits namespace.
//
namespace traits {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense triangular matrix traits.
///
/// @tparam  _Scalar  The scalar type.
///
template <typename _Scalar, Layout _layout, Uplo _uplo>
struct Traits<matrix::DenseTriangularMatrix<_Scalar, _layout, _uplo>> {
  static constexpr index_t ndim = 2;

  using ScalarType = _Scalar;
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
///
template <typename _Scalar, Layout _layout = Layout::COLMAJOR, Uplo _uplo = Uplo::UPPER>
class DenseTriangularMatrix
  : public DenseMatrixStorage<_Scalar>,
    public MatrixWrapper<DenseTriangularMatrix<_Scalar, _layout, _uplo>> {

  friend MatrixWrapper<DenseTriangularMatrix<_Scalar, _layout, _uplo>>;

 public:

  static constexpr index_t ndim = 2;

  using ScalarType     = _Scalar;
  using RealScalarType = RealType<_Scalar>;
  using ValueArrayType = Array<_Scalar>;

  using TransposeType  = DenseTriangularMatrix<_Scalar, changeLayout(_layout), _uplo>;

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

  // Gets element
  inline       ScalarType operator()( const index_t rowidx, const index_t colidx ) noexcept;
  inline const ScalarType operator()( const index_t rowidx, const index_t colidx ) const noexcept;

  // Transpose
  inline       TransposeType& transpose() noexcept;
  inline const TransposeType& transpose() const noexcept;

 protected:

  // Gets information
  inline index_t getNrowImpl() const noexcept;
  inline index_t getNcolImpl() const noexcept;

  // Gets base class
  inline       BaseType& base() noexcept;
  inline const BaseType& base() const noexcept;

};

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_DENSE_DENSE_TRIANGULAR_MATRIX_HPP_
