////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/matrix/sparse_base.hpp
/// @brief   The sparse interface.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_MATRIX_SPARSE_BASE_HPP_
#define ISVD_MATRIX_SPARSE_BASE_HPP_

#include <isvd/isvd.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The internal namespace.
//
namespace internal {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The interface of sparse type.
///
/// @tparam  _Derived  The derived type.
///
template <class _Derived>
class SparseBase {

 protected:

  /// The number of nonzero elements.
  index_t nnz_;

 public:

  // Constructors
  SparseBase() noexcept;
  SparseBase( const index_t nnz ) noexcept;
  SparseBase( const SparseBase &other ) noexcept;
  SparseBase( SparseBase &&other ) noexcept;

  // Operators
  inline SparseBase& operator=( const SparseBase &other ) noexcept;
  inline SparseBase& operator=( SparseBase &&other ) noexcept;

  // Gets information
  inline index_t getNnz() const noexcept;

};

}  // namespace internal

}  // namespace isvd

#endif  // ISVD_MATRIX_SPARSE_BASE_HPP_
