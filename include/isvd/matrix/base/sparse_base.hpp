////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/matrix/base/sparse_base.hpp
/// @brief   The sparse container interface.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef ISVD_MATRIX_BASE_SPARSE_BASE_HPP_
#define ISVD_MATRIX_BASE_SPARSE_BASE_HPP_

#include <isvd/isvd.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The interface of sparse container.
///
/// @tparam  _Derived  The derived type.
///
template <typename _Derived>
class SparseBase {

 protected:

  /// The number of nonzero elements.
  index_t nnz_;

 protected:

  // Constructors
  inline SparseBase() noexcept;
  inline SparseBase( const index_t nnz ) noexcept;
  inline SparseBase( const SparseBase &other ) noexcept;
  inline SparseBase( SparseBase &&other ) noexcept;

  // Operators
  inline SparseBase& operator=( const SparseBase &other ) noexcept;
  inline SparseBase& operator=( SparseBase &&other ) noexcept;

 public:

  // Gets information
  inline index_t getNnz() const noexcept;

};

}  // namespace isvd

#endif  // ISVD_MATRIX_BASE_SPARSE_BASE_HPP_
