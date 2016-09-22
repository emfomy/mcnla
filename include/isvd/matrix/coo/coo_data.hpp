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
template <index_t _ndim, typename _Scalar, index_t __ndim, index_t __dim, index_t... __dims>
struct CooDataHelper {
  static_assert(sizeof...(__dims) < __ndim && __ndim <= _ndim, "Invalid dimension!");

  using DataType    = CooData<_ndim, _Scalar>;
  using ReducedType = CooData<__ndim, _Scalar>;
  using IdxsType    = std::array<std::shared_ptr<std::valarray<index_t>>, __ndim>;

  template <typename... _Args>
  static inline       ReducedType getData( DataType &data, _Args&... args ) noexcept;

  template <typename... _Args>
  static inline const ReducedType getConstData( const DataType &data, _Args&... args ) noexcept;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The COO data helper.
///
template <index_t _ndim, typename _Scalar, index_t __ndim, index_t __dim>
struct CooDataHelper<_ndim, _Scalar, __ndim, __dim> {
  static_assert(__ndim <= _ndim, "Invalid dimension!");

  using DataType    = CooData<_ndim, _Scalar>;
  using ReducedType = CooData<__ndim, _Scalar>;
  using IdxsType    = std::array<std::shared_ptr<std::valarray<index_t>>, __ndim>;

  template <typename... _Args>
  static inline       ReducedType getData( DataType &data, _Args&... args ) noexcept;

  template <typename... _Args>
  static inline const ReducedType getConstData( const DataType &data, _Args&... args ) noexcept;

};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The COO data tuple helper.
///
template <index_t _ndim, typename _Scalar, index_t _dim = _ndim-1>
struct CooDataTupleHelper {
  static_assert(_dim > 0 && _dim < _ndim, "Invalid dimension!");

  using DataType       = CooData<_ndim, _Scalar>;
  using TupleType      = CooTuple<_ndim, _Scalar, index_t>;
  using ConstTupleType = CooTuple<_ndim, const _Scalar, const index_t>;

  template <typename... _Args>
  static inline TupleType getTuple( DataType &data, const index_t itidx, _Args&... args ) noexcept;

  template <typename... _Args>
  static inline ConstTupleType getConstTuple( const DataType &data, const index_t itidx, _Args&... args ) noexcept;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The COO data tuple helper.
///
template <index_t _ndim, typename _Scalar>
struct CooDataTupleHelper<_ndim, _Scalar, 0> {

  using DataType       = CooData<_ndim, _Scalar>;
  using TupleType      = CooTuple<_ndim, _Scalar, index_t>;
  using ConstTupleType = CooTuple<_ndim, const _Scalar, const index_t>;

  template <typename... _Args>
  static inline TupleType getTuple( DataType &data, const index_t itidx, _Args&... args ) noexcept;

  template <typename... _Args>
  static inline ConstTupleType getConstTuple( const DataType &data, const index_t itidx, _Args&... args ) noexcept;

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
  std::array<IdxPtrType, _ndim> idxs_;

  /// The empty value array
  static const ValuePtrType kNullValue;

  /// The empty value array
  static const IdxPtrType kNullIdx;

 public:

  // Constructors
  inline CooData() noexcept;
  inline CooData( const index_t capability ) noexcept;
  inline CooData( ValuePtrType value, std::array<IdxPtrType, _ndim> idxs ) noexcept;
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
  inline TupleType      getTuple( const index_t itidx ) noexcept;
  inline ConstTupleType getTuple( const index_t itidx ) const noexcept;

  // Gets data pointer
  inline       ValuePtrType& getValuePtr() noexcept;
  inline const ValuePtrType& getValuePtr() const noexcept;
  inline       IdxPtrType&   getIdxPtr( const index_t dim ) noexcept;
  inline const IdxPtrType&   getIdxPtr( const index_t dim ) const noexcept;
  template <index_t _dim> inline       IdxPtrType& getIdxPtr() noexcept;
  template <index_t _dim> inline const IdxPtrType& getIdxPtr() const noexcept;

  // Reduces dimension
  template <index_t... _dims> inline       CooData<sizeof...(_dims), _Scalar> getReduced() noexcept;
  template <index_t... _dims> inline const CooData<sizeof...(_dims), _Scalar> getReduced() const noexcept;

};

template <index_t _ndim, typename _Scalar>
const typename CooData<_ndim, _Scalar>::ValuePtrType
    CooData<_ndim, _Scalar>::kNullValue = std::make_shared<std::valarray<_Scalar>>();

template <index_t _ndim, typename _Scalar>
const typename CooData<_ndim, _Scalar>::IdxPtrType
    CooData<_ndim, _Scalar>::kNullIdx   = std::make_shared<std::valarray<index_t>>();

}  // namespace isvd

#endif  // ISVD_MATRIX_COO_COO_DATA_HPP_
