////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/coo/coo_data.hpp
/// @brief   The COO data storage.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_COO_COO_DATA_HPP_
#define MCNLA_CORE_MATRIX_COO_COO_DATA_HPP_

#include <mcnla/def.hpp>
#include <mcnla/core/def.hpp>
#include <array>
#include <mcnla/core/matrix/coo/coo_tuple.hpp>
#include <mcnla/core/matrix/kit/array.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

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
  using IdxsType    = std::array<Array<index_t>, __ndim>;

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
  using IdxsType    = std::array<Array<index_t>, __ndim>;

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
/// @ingroup  matrix_coo_module
/// The coordinate list (COO) data storage.
///
/// @tparam  _ndim    The dimension.
/// @tparam  _Scalar  The scalar type.
///
template <index_t _ndim, typename _Scalar>
class CooData {

  static_assert(_ndim >= 0, "Invalid dimension!");

 private:

  using ValueArrayType = Array<_Scalar>;
  using IdxArrayType   = Array<index_t>;
  using TupleType      = CooTuple<_ndim, _Scalar, index_t>;
  using ConstTupleType = CooTuple<_ndim, const _Scalar, const index_t>;

 protected:

  /// The value array.
  ValueArrayType value_;

  /// The index array.
  std::array<IdxArrayType, _ndim> idxs_;

 public:

  // Constructors
  inline CooData() noexcept;
  inline CooData( const index_t capacity ) noexcept;
  inline CooData( const ValueArrayType &value, const std::array<IdxArrayType, _ndim> &idxs ) noexcept;
  inline CooData( const CooData &other ) noexcept;
  inline CooData( CooData &&other ) noexcept;

  // Operators
  inline CooData& operator=( const CooData &other ) noexcept;
  inline CooData& operator=( CooData &&other ) noexcept;
  inline void operator>>=( const index_t offset ) noexcept;
  inline void operator<<=( const index_t offset ) noexcept;
  inline       CooData operator>>( const index_t offset ) noexcept;
  inline const CooData operator>>( const index_t offset ) const noexcept;
  inline       CooData operator<<( const index_t offset ) noexcept;
  inline const CooData operator<<( const index_t offset ) const noexcept;

  // Gets array
  inline       ValueArrayType& getValueArray() noexcept;
  inline const ValueArrayType& getValueArray() const noexcept;
  inline       IdxArrayType& getIdxArray( const index_t dim ) noexcept;
  inline const IdxArrayType& getIdxArray( const index_t dim ) const noexcept;
  template <index_t _dim> inline       IdxArrayType& getIdxArray() noexcept;
  template <index_t _dim> inline const IdxArrayType& getIdxArray() const noexcept;

  // Gets tuple
  inline TupleType      getTuple( const index_t itidx ) noexcept;
  inline ConstTupleType getTuple( const index_t itidx ) const noexcept;

  // Reduces dimension
  template <index_t... _dims> inline       CooData<sizeof...(_dims), _Scalar> getReduced() noexcept;
  template <index_t... _dims> inline const CooData<sizeof...(_dims), _Scalar> getReduced() const noexcept;

};

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_COO_COO_DATA_HPP_
