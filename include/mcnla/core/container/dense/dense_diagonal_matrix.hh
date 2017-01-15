////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/container/dense/dense_diagonal_matrix.hh
/// @brief   The definition of definition of dense diagonal matrix class.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_CONTAINER_DENSE_DENSE_DIAGONAL_MATRIX_HH_
#define MCNLA_CORE_CONTAINER_DENSE_DENSE_DIAGONAL_MATRIX_HH_

#include <mcnla/def.hpp>
#include <mcnla/core/def.hpp>
#include <mcnla/core/container/base/matrix_wrapper.hpp>
#include <mcnla/core/container/base/container_wrapper.hpp>
#include <mcnla/core/container/dense/dense_vector_storage.hpp>
#include <mcnla/core/utility/traits.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The container namespace.
//
namespace container {

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Scalar> class DenseDiagonalMatrix;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace container

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The traits namespace.
//
namespace traits {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense diagonal matrix traits.
///
template <typename _Scalar>
struct Traits<container::DenseDiagonalMatrix<_Scalar>> {

  static constexpr index_t ndim = 2;

  using ScalarType  = _Scalar;
  using RealType    = container::DenseDiagonalMatrix<RealScalarT<_Scalar>>;
  using ComplexType = container::DenseDiagonalMatrix<ComplexScalarT<_Scalar>>;
  using VectorType  = container::DenseVector<_Scalar>;
  using MatrixType  = container::DenseDiagonalMatrix<_Scalar>;
};

}  // namespace traits

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The container namespace.
//
namespace container {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  container_dense_module
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
  using ValueArrayType = Array<_Scalar>;

  using RealType       = DenseDiagonalMatrix<RealScalarT<_Scalar>>;
  using ComplexType    = DenseDiagonalMatrix<ComplexScalarT<_Scalar>>;

  using VectorType     = DenseVector<_Scalar>;
  using MatrixType     = DenseDiagonalMatrix<_Scalar>;

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
  inline ScalarType operator()( const index_t rowidx, const index_t colidx ) const noexcept;

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

}  // namespace container

}  // namespace mcnla

#endif  // MCNLA_CORE_CONTAINER_DENSE_DENSE_DIAGONAL_MATRIX_HH_
