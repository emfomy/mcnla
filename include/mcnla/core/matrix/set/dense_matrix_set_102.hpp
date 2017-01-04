////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/set/dense_matrix_set_102.hpp
/// @brief   The dense matrix set with dimension order [1 0 2].
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_SET_DENSE_MATRIX_SET_102_HPP_
#define MCNLA_CORE_MATRIX_SET_DENSE_MATRIX_SET_102_HPP_

#include <mcnla/def.hpp>
#include <mcnla/core/def.hpp>
#include <tuple>
#include <mcnla/core/matrix/set/matrix_set_wrapper.hpp>
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
template <typename _Scalar> class DenseMatrixSet102;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace matrix

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The traits namespace.
//
namespace traits {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The traits of dense matrix set with dimension order [1 0 2].
///
template <typename _Scalar>
struct Traits<matrix::DenseMatrixSet102<_Scalar>> {
  using MatrixType = matrix::DenseMatrixRowMajor<_Scalar>;
};

}  // namespace traits

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  matrix_set_module
/// The dense matrix set with dimension order [1 0 2].
///
/// @tparam  _Scalar  The scalar type.
///
template <typename _Scalar>
class DenseMatrixSet102
  : public MatrixSetWrapper<DenseMatrixSet102<_Scalar>> {

  friend MatrixSetWrapper<DenseMatrixSet102<_Scalar>>;

 public:

  using SetType    = DenseMatrixSet102<_Scalar>;
  using MatrixType = DenseMatrixRowMajor<_Scalar>;

 private:

  using BaseType = MatrixSetWrapper<DenseMatrixSet102<_Scalar>>;

 protected:

  /// The base data.
  MatrixType data_;

  /// The number of columns in each matrix.
  index_t nrow_;

 public:

  // Constructors
  inline DenseMatrixSet102() noexcept;
  inline DenseMatrixSet102( const index_t nrow, const index_t ncol, const index_t nmat ) noexcept;
  inline DenseMatrixSet102( const std::tuple<index_t, index_t, index_t> sizes ) noexcept;
  inline DenseMatrixSet102( const index_t ncol, const MatrixType &data ) noexcept;
  inline DenseMatrixSet102( const DenseMatrixSet102 &other ) noexcept;
  inline DenseMatrixSet102( DenseMatrixSet102 &&other ) noexcept;

  // Operators
  inline DenseMatrixSet102& operator=( const DenseMatrixSet102 &other ) noexcept;
  inline DenseMatrixSet102& operator=( DenseMatrixSet102 &&other ) noexcept;

  // Gets information
  inline bool isShrunk() const noexcept;

  // Gets data
  inline       MatrixType& data() noexcept;
  inline const MatrixType& data() const noexcept;

  // Resizes
  template <typename... Args>
  inline void reconstruct( Args... args ) noexcept;

  // Gets set
  using BaseType::operator();
  inline       SetType operator()( const IdxRange &idxrange ) noexcept;
  inline const SetType operator()( const IdxRange &idxrange ) const noexcept;
  inline       SetType operator()( const char*, const char*, const IdxRange &idxrange ) noexcept;
  inline const SetType operator()( const char*, const char*, const IdxRange &idxrange ) const noexcept;
  inline       SetType operator()( const char*, const IdxRange &colrange, const char* ) noexcept;
  inline const SetType operator()( const char*, const IdxRange &colrange, const char* ) const noexcept;

  // Gets matrix
  inline       MatrixType unfold() noexcept;
  inline const MatrixType unfold() const noexcept;

 protected:

  // Gets information
  inline index_t nrowImpl() const noexcept;
  inline index_t ncolImpl() const noexcept;
  inline index_t nmatImpl() const noexcept;

  // Gets matrix
  inline       MatrixType getMatrixImpl( const index_t idx ) noexcept;
  inline const MatrixType getMatrixImpl( const index_t idx ) const noexcept;

};

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_SET_DENSE_MATRIX_SET_102_HPP_
