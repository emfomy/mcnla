////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/set/dense_matrix_set_120.hpp
/// @brief   The dense matrix set with dimension order [1 2 0].
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_SET_DENSE_MATRIX_SET_120_HPP_
#define MCNLA_CORE_MATRIX_SET_DENSE_MATRIX_SET_120_HPP_

#include <mcnla/def.hpp>
#include <mcnla/core/def.hpp>
#include <mcnla/core/matrix/set/matrix_set_base.hpp>
#include <mcnla/core/matrix/dense/dense_matrix.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Scalar> class DenseMatrixSet120;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace matrix

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The traits namespace.
//
namespace traits {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The traits of dense matrix set with dimension order [1 2 0].
///
/// @tparam  _Scalar  The scalar type.
///
template <typename _Scalar>
struct Traits<matrix::DenseMatrixSet120<_Scalar>> {
  using MatrixType = matrix::DenseMatrix<_Scalar, Layout::ROWMAJOR>;
};

}  // namespace traits

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  matrix_set_module
/// The dense matrix set with dimension order [1 2 0].
///
/// @tparam  _Scalar  The scalar type.
///
template <typename _Scalar>
class DenseMatrixSet120
  : public MatrixSetBase<DenseMatrixSet120<_Scalar>> {

  friend MatrixSetBase<DenseMatrixSet120<_Scalar>>;

 public:

  using SetType    = DenseMatrixSet120<_Scalar>;
  using MatrixType = DenseMatrix<_Scalar, Layout::ROWMAJOR>;

 private:

  using BaseType = MatrixSetBase<DenseMatrixSet120<_Scalar>>;

 protected:

  MatrixType data_;

  /// The number of columns in each matrix.
  index_t ncol_;

 public:

  // Constructors
  inline DenseMatrixSet120() noexcept;
  inline DenseMatrixSet120( const index_t nrow, const index_t ncol, const index_t nmat ) noexcept;
  inline DenseMatrixSet120( const index_t ncol, const MatrixType &data ) noexcept;
  inline DenseMatrixSet120( const DenseMatrixSet120 &other ) noexcept;
  inline DenseMatrixSet120( DenseMatrixSet120 &&other ) noexcept;

  // Operators
  inline DenseMatrixSet120& operator=( const DenseMatrixSet120 &other ) noexcept;
  inline DenseMatrixSet120& operator=( DenseMatrixSet120 &&other ) noexcept;

  // Gets information
  inline bool isShrunk() const noexcept;

  // Gets data
  inline       MatrixType& getData() noexcept;
  inline const MatrixType& getData() const noexcept;

  // Gets set
  inline       SetType getRows( const IdxRange rowrange ) noexcept;
  inline const SetType getRows( const IdxRange rowrange ) const noexcept;

  // Gets matrix
  inline       MatrixType unfold() noexcept;
  inline const MatrixType unfold() const noexcept;

 protected:

  // Gets information
  inline index_t getNrowImpl() const noexcept;
  inline index_t getNcolImpl() const noexcept;
  inline index_t getNmatImpl() const noexcept;

  // Gets matrix
  inline       MatrixType getMatrixImpl( const index_t idx ) noexcept;
  inline const MatrixType getMatrixImpl( const index_t idx ) const noexcept;

};

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_SET_DENSE_MATRIX_SET_120_HPP_
