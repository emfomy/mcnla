////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/coo/coo_vector.hpp
/// @brief   The COO vector class.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_COO_COO_VECTOR_HPP_
#define MCNLA_CORE_MATRIX_COO_COO_VECTOR_HPP_

#include <mcnla/def.hpp>
#include <mcnla/core/def.hpp>
#include <iostream>
#include <mcnla/core/matrix/base/container_base.hpp>
#include <mcnla/core/matrix/base/vector_base.hpp>
#include <mcnla/core/matrix/coo/coo_base.hpp>
#include <mcnla/core/matrix/coo/coo_vector_iterator.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Scalar> class CooVector;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace matrix

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The traits namespace.
//
namespace traits {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The coordinate list (COO) vector traits.
///
/// @tparam  _Scalar  The scalar type.
///
template <typename _Scalar>
struct Traits<matrix::CooVector<_Scalar>> {
  static constexpr index_t ndim = 1;
  using ScalarType        = _Scalar;
  using RealScalarType    = RealType<_Scalar>;

  using VectorType        = matrix::CooVector<ScalarType>;
  using RealVectorType    = matrix::CooVector<RealScalarType>;

  using IteratorType      = matrix::CooVectorIterator<ScalarType>;
  using ConstIteratorType = matrix::CooVectorConstIterator<ScalarType>;
};

}  // namespace traits

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  matrix_coo_module
/// The coordinate list (COO) vector class.
///
/// @tparam  _Scalar  The scalar type.
///
/// @todo  Add sorting attention to routines.
///
template <typename _Scalar>
class CooVector
  : public ContainerBase<CooVector<_Scalar>>,
    public VectorBase<CooVector<_Scalar>>,
    public CooBase<CooVector<_Scalar>> {

 public:

  static constexpr index_t ndim = 1;

  using ScalarType        = _Scalar;
  using RealScalarType    = RealType<_Scalar>;
  using ValuePtrType      = std::shared_ptr<std::valarray<ScalarType>>;
  using IdxPtrType        = std::shared_ptr<std::valarray<index_t>>;

  using VectorType        = CooVector<ScalarType>;
  using RealVectorType    = CooVector<RealScalarType>;

  using DataType          = CooData<ndim, ScalarType>;

  using IteratorType      = CooVectorIterator<ScalarType>;
  using ConstIteratorType = CooVectorConstIterator<ScalarType>;

 private:

  using ContainerBaseType = ContainerBase<CooVector<_Scalar>>;
  using VectorBaseType    = VectorBase<CooVector<_Scalar>>;
  using CooBaseType       = CooBase<CooVector<_Scalar>>;

 protected:

  using VectorBaseType::length_;
  using CooBaseType::nnz_;
  using CooBaseType::offset_;
  using CooBaseType::data_;

 public:

  // Constructors
  inline CooVector() noexcept;
  inline CooVector( const index_t length ) noexcept;
  inline CooVector( const index_t length, const index_t capacity ) noexcept;
  inline CooVector( const index_t length, const index_t nnz, const index_t capacity, const index_t offset = 0 ) noexcept;
  inline CooVector( const index_t length, const index_t nnz,
                    const ValuePtrType &value, const IdxPtrType &idx, const index_t offset = 0 ) noexcept;
  inline CooVector( const index_t length, const index_t nnz, const DataType &data, const index_t offset = 0 ) noexcept;
  inline CooVector( const CooVector &other ) noexcept;
  inline CooVector( CooVector &&other ) noexcept;

  // Operators
  inline CooVector& operator=( const CooVector &other ) noexcept;
  inline CooVector& operator=( CooVector &&other ) noexcept;
  template <typename __Scalar>
  friend inline std::ostream& operator<<( std::ostream &out, const CooVector<__Scalar> &vector );

  // Gets index array
  using CooBaseType::getIdx;
  inline       index_t* getIdx() noexcept;
  inline const index_t* getIdx() const noexcept;

  // Gets element
  inline ScalarType getElem( const index_t idx ) const noexcept;
  inline ScalarType operator()( const index_t idx ) const noexcept;

  // Gets the internal position
  inline index_t getPos( const index_t idx ) const noexcept;
  inline void getPosNnz( const IdxRange range, index_t &pos, index_t &nnz ) const noexcept;

  // Finds the iterator
  inline IteratorType      find( const index_t idx ) noexcept;
  inline ConstIteratorType find( const index_t idx ) const noexcept;
  inline ConstIteratorType cfind( const index_t idx ) const noexcept;

  // Sorts
  inline void sort() noexcept;
  inline bool isSorted() const noexcept;

  // Resizes
  inline void resize( const index_t length ) noexcept;

};

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_COO_COO_VECTOR_HPP_
