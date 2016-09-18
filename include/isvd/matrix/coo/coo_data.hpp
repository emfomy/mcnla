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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The coordinate list (COO) data storage.
///
/// @tparam  _Scalar  The scalar type.
/// @tparam  _ndim    The dimension.
///
template <typename _Scalar, index_t _ndim>
class CooData {

  static_assert(_ndim >= 0, "Invalid dimension!");

 private:

  using ValuePtrType = std::shared_ptr<std::valarray<_Scalar>>;
  using IdxPtrType   = std::shared_ptr<std::valarray<index_t>>;

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
  template <index_t dim> inline       index_t* getIdx() noexcept;
  template <index_t dim> inline const index_t* getIdx() const noexcept;

};

template <typename _Scalar, index_t _ndim>
const typename CooData<_Scalar, _ndim>::ValuePtrType
    CooData<_Scalar, _ndim>::kNullValue = std::make_shared<std::valarray<_Scalar>>();

template <typename _Scalar, index_t _ndim>
const typename CooData<_Scalar, _ndim>::IdxPtrType
    CooData<_Scalar, _ndim>::kNullIdx   = std::make_shared<std::valarray<index_t>>();

}  // namespace isvd

#endif  // ISVD_MATRIX_COO_COO_DATA_HPP_
