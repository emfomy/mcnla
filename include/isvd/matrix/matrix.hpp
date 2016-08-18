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
/// The interface of matrix data storage.
///
/// @tparam _Type  The type of numeric value in matrix.
///
template <typename _Type>
class MatrixData {

 public:

  /// Type alias
  typedef _Type ValueType;

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
/// @tparam _Data  The storage data type.
///
template <class _Data>
class Matrix {

 public:

  /// Type alias
  typedef _Data DataType;

 private:

  /// The matrix storage
  std::shared_ptr<DataType> data_;

 public:

  // Constructors
  Matrix() noexcept;
  Matrix( const Matrix &other ) noexcept;
  Matrix( _Data *data ) noexcept;

  // Destructor
  ~Matrix() noexcept;

  // Operators
  Matrix& operator=( const Matrix &other ) noexcept;

  // Gets data
  index_t getNrow() const noexcept;
  index_t getNcol() const noexcept;
  _Data*  getData() const noexcept;

};

}  // namespace isvd

#endif  // ISVD_MATRIX_MATRIX_HPP_
