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
/// @tparam _Type  The type of numeric value in matrix.
///
template <typename _Type>
class MatrixData {

 public:

  /// Type alias
  using ValueType = _Type;

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
/// The interface of matrix base.
///
/// @tparam _Data  The storage data type.
///
template <class _Data>
class MatrixBase {

 protected:

  /// The matrix storage
  std::shared_ptr<_Data> data_;

 public:

  // Constructors
  MatrixBase() noexcept;
  MatrixBase( const MatrixBase &other ) noexcept;
  MatrixBase( _Data *data ) noexcept;

  // Destructor
  ~MatrixBase() noexcept;

  // Operators
  MatrixBase& operator=( const MatrixBase &other ) noexcept;

  // Gets data
  index_t getNrow() const noexcept;
  index_t getNcol() const noexcept;
  _Data*  getData() const noexcept;

};

}  // namespace impl

}  // namespace isvd

#endif  // ISVD_MATRIX_MATRIX_HPP_
