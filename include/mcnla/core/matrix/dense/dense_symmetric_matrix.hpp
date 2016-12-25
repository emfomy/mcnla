////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/dense/dense_symmetric_matrix.hpp
/// @brief   The dense symmetric matrix class.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_DENSE_DENSE_SYMMETRIC_MATRIX_HPP_
#define MCNLA_CORE_MATRIX_DENSE_DENSE_SYMMETRIC_MATRIX_HPP_

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
template <typename _Scalar, Trans _trans, Uplo _uplo> class DenseSymmetricMatrix;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace matrix

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The traits namespace.
//
namespace traits {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dense symmetric matrix traits.
///
/// @tparam  _Scalar  The scalar type.
///
template <typename _Scalar, Trans _trans, Uplo _uplo>
struct Traits<matrix::DenseSymmetricMatrix<_Scalar, _trans, _uplo>> {
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
/// The dense symmetric matrix class.
///
/// @tparam  _Scalar  The scalar type.
///
template <typename _Scalar, Trans _trans = Trans::NORMAL, Uplo _uplo = Uplo::UPPER>
class DenseSymmetricMatrix
  : public DenseMatrixStorage<_Scalar>,
    public MatrixWrapper<DenseSymmetricMatrix<_Scalar, _trans, _uplo>> {

  static_assert(!isConj(_trans), "Conjugate matrix is not supported!");
  static_assert(!isUnitDiag(_uplo), "Unit-diagonal symmetric matrix is not supported!");

  friend MatrixWrapper<DenseSymmetricMatrix<_Scalar, _trans, _uplo>>;

 public:

  static constexpr index_t ndim = 2;

  using ScalarType     = _Scalar;
  using RealScalarType = RealType<_Scalar>;
  using ValueArrayType = Array<_Scalar>;

  using TransposeType  = DenseSymmetricMatrix<_Scalar, changeTrans(_trans), _uplo>;

 private:

  using BaseType       = DenseMatrixStorage<_Scalar>;

 public:

  // Constructors
  inline DenseSymmetricMatrix() noexcept;
  inline DenseSymmetricMatrix( const index_t size ) noexcept;
  inline DenseSymmetricMatrix( const index_t size, const index_t pitch ) noexcept;
  inline DenseSymmetricMatrix( const index_t size, const index_t pitch, const index_t capacity ) noexcept;
  inline DenseSymmetricMatrix( const index_t size, const index_t pitch,
                               const ValueArrayType &value, const index_t offset = 0 ) noexcept;
  inline DenseSymmetricMatrix( const DenseSymmetricMatrix &other ) noexcept;
  inline DenseSymmetricMatrix( DenseSymmetricMatrix &&other ) noexcept;

  // Operators
  inline DenseSymmetricMatrix& operator=( const DenseSymmetricMatrix &other ) noexcept;
  inline DenseSymmetricMatrix& operator=( DenseSymmetricMatrix &&other ) noexcept;

  // Gets information
  inline index_t getSize() const noexcept;

  // Gets element
  inline       ScalarType operator()( const index_t rowidx, const index_t colidx ) noexcept;
  inline const ScalarType operator()( const index_t rowidx, const index_t colidx ) const noexcept;

  // Resizes
  template <typename... Args>
  inline void reconstruct( Args... args ) noexcept;
  inline void resize( const index_t nrow, const index_t ncol ) noexcept;

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

#endif  // MCNLA_CORE_MATRIX_DENSE_DENSE_SYMMETRIC_MATRIX_HPP_
