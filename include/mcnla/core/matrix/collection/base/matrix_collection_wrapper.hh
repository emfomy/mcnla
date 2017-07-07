////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/collection/base/matrix_collection_wrapper.hh
/// @brief   The definition of matrix collection wrapper.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_COLLECTION_BASE_MATRIX_COLLECTION_WRAPPER_HH_
#define MCNLA_CORE_MATRIX_COLLECTION_BASE_MATRIX_COLLECTION_WRAPPER_HH_

#include <mcnla/core/matrix/collection/def.hpp>
#include <tuple>
#include <mcnla/core/matrix/dense.hpp>
#include <mcnla/core/utility/crtp.hpp>
#include <mcnla/core/utility/traits.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The matrix collection wrapper.
///
/// @tparam  _Derived  The derived type.
///
template <class _Derived>
class MatrixCollectionWrapper {

 private:

  using MatrixType = MatrixT<_Derived>;

 protected:

  // Constructors
  inline MatrixCollectionWrapper() noexcept = default;

 public:

  // Gets information
  inline bool    isEmpty() const noexcept;
  inline index_t nrow() const noexcept;
  inline index_t ncol() const noexcept;
  inline index_t nmat() const noexcept;
  inline std::tuple<index_t, index_t, index_t> sizes() const noexcept;

  // Gets matrix
  inline       MatrixType operator()( const index_t idx ) noexcept;
  inline const MatrixType operator()( const index_t idx ) const noexcept;

 protected:

  MCNLA_CRTP_DERIVED(_Derived)

};

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_COLLECTION_BASE_MATRIX_COLLECTION_WRAPPER_HH_
