////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/matrix/coo/coo_data.hpp
/// @brief   The COO data storage.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_MATRIX_COO_COO_DATA_HPP_
#define ISVD_MATRIX_COO_COO_DATA_HPP_

#include <isvd/isvd.hpp>
#include <array>
#include <valarray>
#include <memory>
#include <isvd/matrix/coo/coo_tuple.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <index_t _ndim, typename _Scalar> class CooData;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The detail namespace.
//
namespace detail {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The COO data helper.
///
template <index_t _ndim, typename _Scalar, index_t _dim = _ndim-1>
struct CooDataHelper {
  static_assert(_dim > 0 && _dim < _ndim, "Invalid dimension!");

  using DataType       = CooData<_ndim, _Scalar>;
  using TupleType      = CooTuple<_ndim, _Scalar, index_t>;
  using ConstTupleType = CooTuple<_ndim, const _Scalar, const index_t>;

  template <typename... _Args>
  static inline TupleType getTuple( DataType &data, const index_t pos, _Args&... args ) noexcept;

  template <typename... _Args>
  static inline ConstTupleType getConstTuple( const DataType &data, const index_t pos, _Args&... args ) noexcept;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The COO data helper.
///
template <index_t _ndim, typename _Scalar>
struct CooDataHelper<_ndim, _Scalar, 0> {

  using DataType       = CooData<_ndim, _Scalar>;
  using TupleType      = CooTuple<_ndim, _Scalar, index_t>;
  using ConstTupleType = CooTuple<_ndim, const _Scalar, const index_t>;

  template <typename... _Args>
  static inline TupleType getTuple( DataType &data, const index_t pos, _Args&... args ) noexcept;

  template <typename... _Args>
  static inline ConstTupleType getConstTuple( const DataType &data, const index_t pos, _Args&... args ) noexcept;

};

}  // namespace detail

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The coordinate list (COO) data storage.
///
/// @tparam  _ndim    The dimension.
/// @tparam  _Scalar  The scalar type.
///
template <index_t _ndim, typename _Scalar>
class CooData {

  static_assert(_ndim >= 0, "Invalid dimension!");

 private:

  using ValuePtrType   = std::shared_ptr<std::valarray<_Scalar>>;
  using IdxPtrType     = std::shared_ptr<std::valarray<index_t>>;
  using TupleType      = CooTuple<_ndim, _Scalar, index_t>;
  using ConstTupleType = CooTuple<_ndim, const _Scalar, const index_t>;

 protected:

  /// The value array.
  ValuePtrType value_;

  /// The index array.
  std::array<IdxPtrType, _ndim> idx_;

  /// The empty value array
  static const ValuePtrType kNullValue;

  /// The empty value array
  static const IdxPtrType kNullIdx;

 public:

  // Constructors
  inline CooData() noexcept;
  inline CooData( const index_t capability ) noexcept;
  inline CooData( ValuePtrType value, std::array<IdxPtrType, _ndim> idx ) noexcept;
  inline CooData( const CooData &other ) noexcept;
  inline CooData( CooData &&other ) noexcept;

  // Operators
  inline CooData& operator=( const CooData &other ) noexcept;
  inline CooData& operator=( CooData &&other ) noexcept;
  inline bool operator==( const CooData& other ) const noexcept;
  inline bool operator!=( const CooData& other ) const noexcept;
  inline       _Scalar* operator*() noexcept;
  inline const _Scalar* operator*() const noexcept;

  // Gets data
  inline        index_t getCapability() const noexcept;
  inline       _Scalar* getValue() noexcept;
  inline const _Scalar* getValue() const noexcept;
  inline       index_t* getIdx( const index_t dim ) noexcept;
  inline const index_t* getIdx( const index_t dim ) const noexcept;
  template <index_t _dim> inline       index_t* getIdx() noexcept;
  template <index_t _dim> inline const index_t* getIdx() const noexcept;
  inline TupleType      getTuple( const index_t pos ) noexcept;
  inline ConstTupleType getTuple( const index_t pos ) const noexcept;

};

template <index_t _ndim, typename _Scalar>
const typename CooData<_ndim, _Scalar>::ValuePtrType
    CooData<_ndim, _Scalar>::kNullValue = std::make_shared<std::valarray<_Scalar>>();

template <index_t _ndim, typename _Scalar>
const typename CooData<_ndim, _Scalar>::IdxPtrType
    CooData<_ndim, _Scalar>::kNullIdx   = std::make_shared<std::valarray<index_t>>();

}  // namespace isvd

#endif  // ISVD_MATRIX_COO_COO_DATA_HPP_
