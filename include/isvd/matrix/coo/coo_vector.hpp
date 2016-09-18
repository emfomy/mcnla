////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/matrix/coo/coo_vector.hpp
/// @brief   The COO vector class.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_MATRIX_COO_COO_VECTOR_HPP_
#define ISVD_MATRIX_COO_COO_VECTOR_HPP_

#include <isvd/isvd.hpp>
#include <iostream>
#include <isvd/matrix/base/container_base.hpp>
#include <isvd/matrix/base/vector_base.hpp>
#include <isvd/matrix/coo/coo_base.hpp>
#include <isvd/matrix/coo/coo_vector_iterator.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <typename _Scalar> class CooVector;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The internal namespace.
//
namespace internal {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The coordinate list (COO) vector traits.
///
/// @tparam  _Scalar  The scalar type.
///
template <typename _Scalar>
struct Traits<CooVector<_Scalar>> {
  static constexpr index_t ndim = 1;
  using ScalarType     = _Scalar;
  using RealScalarType = typename internal::ScalarTraits<_Scalar>::RealType;

  using VectorType     = CooVector<ScalarType>;
  using RealVectorType = CooVector<RealScalarType>;

  using IteratorType         = CooVectorIterator<ScalarType>;
  using ConstIteratorType    = CooVectorConstIterator<ScalarType>;
  using IdxIteratorType      = CooVectorIdxIterator<ScalarType>;
  using ConstIdxIteratorType = CooVectorConstIdxIterator<ScalarType>;
};

}  // namespace internal

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The coordinate list (COO) vector class.
///
/// @tparam  _Scalar  The scalar type.
///
template <typename _Scalar>
class CooVector
  : public internal::ContainerBase<CooVector<_Scalar>>,
    public internal::VectorBase<CooVector<_Scalar>>,
    public internal::CooBase<CooVector<_Scalar>> {

 public:

  using ScalarType        = _Scalar;
  using RealScalarType    = typename internal::ScalarTraits<_Scalar>::RealType;
  using ValuePtrType      = std::shared_ptr<std::valarray<ScalarType>>;
  using IdxPtrType        = std::shared_ptr<std::valarray<index_t>>;

  using VectorType        = CooVector<ScalarType>;
  using RealVectorType    = CooVector<RealScalarType>;

  using DataType          = CooData<ScalarType, 1>;

  using IteratorType      = CooVectorIterator<ScalarType>;
  using ConstIteratorType = CooVectorConstIterator<ScalarType>;

 private:

  using VectorBaseType    = internal::VectorBase<CooVector<_Scalar>>;
  using CooBaseType       = internal::CooBase<CooVector<_Scalar>>;

 protected:

  using VectorBaseType::length_;
  using CooBaseType::nnz_;
  using CooBaseType::offset_;
  using CooBaseType::data_;

 public:

  // Constructors
  inline CooVector() noexcept;
  inline CooVector( const index_t length ) noexcept;
  inline CooVector( const index_t length, const index_t capability ) noexcept;
  inline CooVector( const index_t length, const index_t nnz, const index_t capability, const index_t offset ) noexcept;
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

  // Sorts
  inline void sort() noexcept;
  inline bool isSorted() const noexcept;

  // Resizes
  inline void resize( const index_t length ) noexcept;

  // Gets segment
  inline       VectorType getSegment( const IdxRange range ) noexcept;
  inline const VectorType getSegment( const IdxRange range ) const noexcept;

};

}  // namespace isvd

#endif  // ISVD_MATRIX_COO_COO_VECTOR_HPP_
