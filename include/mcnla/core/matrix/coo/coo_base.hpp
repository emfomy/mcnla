////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/coo/coo_base.hpp
/// @brief   The COO container interface.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_COO_COO_BASE_HPP_
#define MCNLA_CORE_MATRIX_COO_COO_BASE_HPP_

#include <mcnla/def.hpp>
#include <mcnla/core/def.hpp>
#include <mcnla/core/utility/traits.hpp>
#include <mcnla/core/matrix/base/sparse_base.hpp>
#include <mcnla/core/matrix/coo/coo_data.hpp>
#include <mcnla/core/matrix/coo/coo_tuple.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  matrix_coo_module
/// The interface of coordinate list (COO) container.
///
/// @tparam  _Derived  The derived type.
///
template <class _Derived>
class CooBase : public SparseBase<_Derived> {

 private:

  static constexpr index_t ndim = traits::Traits<_Derived>::ndim;

  using ScalarType     = typename traits::Traits<_Derived>::ScalarType;
  using ValuePtrType   = std::shared_ptr<std::valarray<ScalarType>>;
  using IdxPtrType     = std::shared_ptr<std::valarray<index_t>>;
  using TupleType      = CooTuple<ndim, ScalarType, index_t>;
  using ConstTupleType = CooTuple<ndim, const ScalarType, const index_t>;

  using DataType       = CooData<ndim, ScalarType>;

  using SparseBaseType = SparseBase<_Derived>;

 protected:

  /// The offset of starting position.
  index_t offset_;

  /// The data storage
  DataType data_;

  using SparseBaseType::nnz_;

 protected:

  // Constructors
  inline CooBase() noexcept;
  inline CooBase( const index_t capacity ) noexcept;
  inline CooBase( const index_t nnz, const index_t capacity, const index_t offset = 0 ) noexcept;
  inline CooBase( const index_t nnz, const ValuePtrType &value,
                  const std::array<IdxPtrType, ndim> &idx, const index_t offset = 0 ) noexcept;
  inline CooBase( const index_t nnz, const DataType &data, const index_t offset = 0 ) noexcept;
  inline CooBase( const CooBase &other ) noexcept;
  inline CooBase( CooBase &&other ) noexcept;

  // Operators
  inline CooBase& operator=( const CooBase &other ) noexcept;
  inline CooBase& operator=( CooBase &&other ) noexcept;

 public:

  // Gets information
  inline index_t getCapacity() const noexcept;
  inline index_t getOffset() const noexcept;

  // Sets information
  inline void setNnz( const index_t nnz ) noexcept;

  // Gets data storage
  inline DataType& getData() noexcept;
  inline const DataType& getData() const noexcept;

  // Gets value array
  inline       ScalarType* getValue() noexcept;
  inline const ScalarType* getValue() const noexcept;

  // Gets index array
  inline       index_t* getIdx( const index_t dim ) noexcept;
  inline const index_t* getIdx( const index_t dim ) const noexcept;
  template <index_t _dim> inline       index_t* getIdx() noexcept;
  template <index_t _dim> inline const index_t* getIdx() const noexcept;

  // Gets tuple
  inline TupleType      getTuple( const index_t itidx ) noexcept;
  inline ConstTupleType getTuple( const index_t itidx ) const noexcept;

  // Gets derived class
  inline       _Derived& derived() noexcept;
  inline const _Derived& derived() const noexcept;

};

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_COO_COO_BASE_HPP_
