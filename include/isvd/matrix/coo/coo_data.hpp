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

 protected:

  /// The length of data array.
  index_t capability_;

  /// The data array.
  std::shared_ptr<_Scalar> value_;

  /// The index array.
  std::array<std::shared_ptr<index_t>, _ndim> idx_;

 public:

  // Constructors
  CooData() noexcept;
  CooData( const index_t capability ) noexcept;
  CooData( const index_t capability, std::shared_ptr<_Scalar> value, std::array<std::shared_ptr<index_t>, _ndim> idx ) noexcept;
  CooData( const CooData &other ) noexcept;
  CooData( CooData &&other ) noexcept;

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
  template <index_t dim> inline index_t* getIdx() const noexcept;

};

}  // namespace isvd

#endif  // ISVD_MATRIX_COO_COO_DATA_HPP_
