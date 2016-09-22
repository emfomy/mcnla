////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/matrix/csc/csc_matrix_data.hpp
/// @brief   The CSC matrix data storage.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_MATRIX_CSC_CSC_MATRIX_DATA_HPP_
#define ISVD_MATRIX_CSC_CSC_MATRIX_DATA_HPP_

#include <isvd/isvd.hpp>
#include <valarray>
#include <memory>
#include <isvd/matrix/coo/coo_data.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The compressed sparse column (CSC) matrix data storage.
///
/// @tparam  _Scalar  The scalar type.
///
template <typename _Scalar>
class CscMatrixData {

 private:

  using ValuePtrType   = std::shared_ptr<std::valarray<_Scalar>>;
  using IdxPtrType     = std::shared_ptr<std::valarray<index_t>>;
  using TupleType      = CooTuple<2, _Scalar, index_t>;
  using ConstTupleType = CooTuple<2, const _Scalar, const index_t>;

 protected:

  /// The value array.
  ValuePtrType value_;

  /// The leading index array.
  IdxPtrType idx0_;

  /// The second pointer array.
  IdxPtrType ptr1_;

  /// The empty value array
  static const ValuePtrType kNullValue;

  /// The empty value array
  static const IdxPtrType kNullIdx;

 public:

  // Constructors
  inline CscMatrixData() noexcept;
  inline CscMatrixData( const index_t size1, const index_t capability ) noexcept;
  inline CscMatrixData( ValuePtrType value, IdxPtrType idx0, IdxPtrType ptr1 ) noexcept;
  inline CscMatrixData( const CscMatrixData &other ) noexcept;
  inline CscMatrixData( CscMatrixData &&other ) noexcept;

  // Operators
  inline CscMatrixData& operator=( const CscMatrixData &other ) noexcept;
  inline CscMatrixData& operator=( CscMatrixData &&other ) noexcept;
  inline bool operator==( const CscMatrixData& other ) const noexcept;
  inline bool operator!=( const CscMatrixData& other ) const noexcept;
  inline       _Scalar* operator*() noexcept;
  inline const _Scalar* operator*() const noexcept;

  // Gets data
  inline        index_t getSize1() const noexcept;
  inline        index_t getCapability() const noexcept;
  inline       _Scalar* getValue() noexcept;
  inline const _Scalar* getValue() const noexcept;
  inline       index_t* getIdx0() noexcept;
  inline const index_t* getIdx0() const noexcept;
  inline       index_t* getPtr1() noexcept;
  inline const index_t* getPtr1() const noexcept;

  // Gets data pointer
  inline       ValuePtrType& getValuePtr() noexcept;
  inline const ValuePtrType& getValuePtr() const noexcept;
  inline       IdxPtrType&   getIdx0Ptr() noexcept;
  inline const IdxPtrType&   getIdx0Ptr() const noexcept;
  inline       IdxPtrType&   getPtr1Ptr() noexcept;
  inline const IdxPtrType&   getPtr1Ptr() const noexcept;

  // Reduces dimension
  inline       CooData<1, _Scalar> getReduced() noexcept;
  inline const CooData<1, _Scalar> getReduced() const noexcept;

};

template <typename _Scalar>
const typename CscMatrixData<_Scalar>::ValuePtrType
    CscMatrixData<_Scalar>::kNullValue = std::make_shared<std::valarray<_Scalar>>();

template <typename _Scalar>
const typename CscMatrixData<_Scalar>::IdxPtrType
    CscMatrixData<_Scalar>::kNullIdx   = std::make_shared<std::valarray<index_t>>();

}  // namespace isvd

#endif  // ISVD_MATRIX_CSC_CSC_MATRIX_DATA_HPP_
