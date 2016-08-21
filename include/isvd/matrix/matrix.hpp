////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/matrix/matrix.hpp
/// @brief   The matrix interface.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_MATRIX_MATRIX_HPP_
#define ISVD_MATRIX_MATRIX_HPP_

#include <memory>
#include <isvd/config.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The enumeration of matrix storage layout.
///
enum class Layout {
  COLMAJOR,  ///< Column-major order.
  ROWMAJOR,  ///< Row-major order.
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The implementation namespace.
//
namespace impl {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The interface of matrix data storage.
///
/// @tparam  _Scalar  The scalar type of matrix.
///
template <typename _Scalar>
class MatrixData {

 public:

  /// Type alias
  using ScalarType = _Scalar;

 public:

  // Constructors
  MatrixData() noexcept;

  // Destructor
  ~MatrixData() noexcept;

  // Gets data
  index_t getNrow() const noexcept;
  index_t getNcol() const noexcept;

};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The interface of matrix.
///
/// @tparam  _Data  The storage data type.
///
template <class _Data>
class Matrix {

 protected:

  /// The matrix storage
  std::shared_ptr<_Data> data_;

 public:

  // Constructors
  template <typename... Args>
  Matrix( Args... args ) noexcept;
  Matrix( const Matrix &other ) noexcept;
  Matrix( _Data *data ) noexcept;

  // Destructor
  ~Matrix() noexcept;

  // Operators
  Matrix& operator=( const Matrix &other ) noexcept;
  _Data* operator*() const noexcept;
  _Data* operator->() const noexcept;

#ifndef DOXYGEN_SHOULD_SKIP_THIS
 private:

  // Constructors
  Matrix( Matrix &&other ) noexcept;

  // Operators
  Matrix& operator=( Matrix &&other ) noexcept;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

};

}  // namespace impl

}  // namespace isvd

#endif  // ISVD_MATRIX_MATRIX_HPP_
