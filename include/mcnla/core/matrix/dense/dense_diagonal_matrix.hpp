////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/dense/dense_diagonal_matrix.hpp
/// @brief   The dense diagonal matrix class.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_DENSE_DENSE_DIAGONAL_MATRIX_HPP_
#define MCNLA_CORE_MATRIX_DENSE_DENSE_DIAGONAL_MATRIX_HPP_

#include <mcnla/def.hpp>
#include <mcnla/core/def.hpp>
#include <mcnla/core/matrix/base/matrix_wrapper.hpp>
#include <mcnla/core/matrix/base/container_wrapper.hpp>
#include <mcnla/core/matrix/dense/dense_vector_storage.hpp>
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
template <typename _Scalar> class DenseDiagonalMatrix;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace matrix

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The traits namespace.
//
namespace traits {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense diagonal matrix traits.
///
/// @tparam  _Scalar  The scalar type.
///
template <typename _Scalar>
struct Traits<matrix::DenseDiagonalMatrix<_Scalar>> {
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
/// The dense diagonal matrix class.
///
/// @tparam  _Scalar  The scalar type.
///
template <typename _Scalar>
class DenseDiagonalMatrix
  : public DenseVectorStorage<_Scalar>,
    public MatrixWrapper<DenseDiagonalMatrix<_Scalar>> {

  friend MatrixWrapper<DenseDiagonalMatrix<_Scalar>>;

 public:

  static constexpr index_t ndim = 2;

  using ScalarType     = _Scalar;
  using RealScalarType = RealType<_Scalar>;
  using ValueArrayType = Array<_Scalar>;

  using TransposeType  = DenseDiagonalMatrix<_Scalar>;

 private:

  using BaseType       = DenseVectorStorage<_Scalar>;

 public:

  // Constructors
  inline DenseDiagonalMatrix() noexcept;
  inline DenseDiagonalMatrix( const index_t size ) noexcept;
  inline DenseDiagonalMatrix( const index_t size, const index_t pitch ) noexcept;
  inline DenseDiagonalMatrix( const index_t size, const index_t pitch, const index_t capacity ) noexcept;
  inline DenseDiagonalMatrix( const index_t size, const index_t pitch,
                              const ValueArrayType &value, const index_t offset = 0 ) noexcept;
  inline DenseDiagonalMatrix( const DenseDiagonalMatrix &other ) noexcept;
  inline DenseDiagonalMatrix( DenseDiagonalMatrix &&other ) noexcept;

  // Operators
  inline DenseDiagonalMatrix& operator=( const DenseDiagonalMatrix &other ) noexcept;
  inline DenseDiagonalMatrix& operator=( DenseDiagonalMatrix &&other ) noexcept;

  // Gets information
  inline index_t size() const noexcept;

  // Gets element
  inline       ScalarType operator()( const index_t rowidx, const index_t colidx ) noexcept;
  inline const ScalarType operator()( const index_t rowidx, const index_t colidx ) const noexcept;

  // Resizes
  template <typename... Args>
  inline void reconstruct( Args... args ) noexcept;

  // Transpose
  inline       TransposeType& t() noexcept;
  inline const TransposeType& t() const noexcept;

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

#endif  // MCNLA_CORE_MATRIX_DENSE_DENSE_DIAGONAL_MATRIX_HPP_
