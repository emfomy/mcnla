////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/matrix/coo/coo_base.hpp
/// @brief   The COO interface.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_MATRIX_COO_COO_BASE_HPP_
#define ISVD_MATRIX_COO_COO_BASE_HPP_

#include <isvd/isvd.hpp>
#include <isvd/utility/traits.hpp>
#include <isvd/matrix/base/sparse_base.hpp>
#include <isvd/matrix/coo/coo_data.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The internal namespace.
//
namespace internal {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The interface of coordinate list (COO) type.
///
/// @tparam  _Derived  The derived type.
///
template <class _Derived>
class CooBase : public SparseBase<_Derived> {

 private:

  static constexpr index_t ndim = Traits<_Derived>::ndim;
  using ScalarType   = typename Traits<_Derived>::ScalarType;
  using ValuePtrType = std::shared_ptr<std::valarray<ScalarType>>;
  using IdxPtrType   = std::shared_ptr<std::valarray<index_t>>;
  using DataType     = CooData<ScalarType, ndim>;

  using SparseBaseType = SparseBase<_Derived>;

 protected:

  /// The offset of starting position.
  index_t offset_;

  /// The data storage
  DataType data_;

  using SparseBaseType::nnz_;

 public:

  // Constructors
  CooBase() noexcept;
  CooBase( const index_t capability, const index_t offset = 0 ) noexcept;
  CooBase( const index_t nnz, const index_t capability, const index_t offset = 0 ) noexcept;
  CooBase( const index_t nnz, const ValuePtrType &value, std::array<IdxPtrType, ndim> idx, const index_t offset = 0 ) noexcept;
  CooBase( const index_t nnz, const DataType &data, const index_t offset = 0 ) noexcept;
  CooBase( const CooBase &other ) noexcept;
  CooBase( CooBase &&other ) noexcept;

  // Operators
  inline CooBase& operator=( const CooBase &other ) noexcept;
  inline CooBase& operator=( CooBase &&other ) noexcept;

  // Gets information
  inline index_t getCapability() const noexcept;
  inline index_t getOffset() const noexcept;

  // Sets information
  inline void setNnz( const index_t nnz ) noexcept;

  // Gets data storage
  inline DataType& getData() noexcept;
  inline const DataType& getData() const noexcept;

  // Gets data array
  inline       ScalarType* getValue() noexcept;
  inline const ScalarType* getValue() const noexcept;

 protected:

  // Gets index array
  template <index_t dim> inline       index_t* getIdx() noexcept;
  template <index_t dim> inline const index_t* getIdx() const noexcept;

};

}  // namespace internal

}  // namespace isvd

#endif  // ISVD_MATRIX_COO_COO_BASE_HPP_
