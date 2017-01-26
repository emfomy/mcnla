////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/matrix/collection/dense_matrix_collection_wrapper.hh
/// @brief   The definition of dense matrix collection wrapper.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_MATRIX_COLLECTION_DENSE_MATRIX_COLLECTION_WRAPPER_HH_
#define MCNLA_CORE_MATRIX_COLLECTION_DENSE_MATRIX_COLLECTION_WRAPPER_HH_

#include <mcnla/core/matrix/def.hpp>
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
/// @ingroup  matrix_collection_module
/// The dense matrix collection wrapper.
///
/// @tparam  _Derived  The derived type.
///
template <class _Derived>
class DenseMatrixCollectionWrapper : public utility::CrtpBase<_Derived, DenseMatrixCollectionWrapper<_Derived>> {

  assertDenseMatrix(MatrixT<_Derived>);

 private:

  using MatrixType = MatrixT<_Derived>;

 protected:

  // Constructors
  inline DenseMatrixCollectionWrapper() noexcept;

 public:

  // Gets information
  inline index_t nrow() const noexcept;
  inline index_t ncol() const noexcept;
  inline index_t nmat() const noexcept;
  inline std::tuple<index_t, index_t, index_t> sizes() const noexcept;

  // Gets matrix
  inline       MatrixType operator()( const index_t idx ) noexcept;
  inline const MatrixType operator()( const index_t idx ) const noexcept;

};

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_MATRIX_COLLECTION_DENSE_MATRIX_COLLECTION_WRAPPER_HH_
