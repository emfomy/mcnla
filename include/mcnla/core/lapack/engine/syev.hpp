////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core/lapack/engine/syev.hpp
/// @brief   The LAPACK SYEV engine.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_LAPACK_ENGINE_SYEV_ENGINE_HPP_
#define MCNLA_CORE_LAPACK_ENGINE_SYEV_ENGINE_HPP_

#include <mcnla/def.hpp>
#include <mcnla/core/def.hpp>
#include <mcnla/core/lapack/def.hpp>
#include <tuple>
#include <mcnla/core/matrix.hpp>
#include <mcnla/core/utility/traits.hpp>
#include <mcnla/core/lapack/lapack/syev.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The LAPACK namespace
//
namespace lapack {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  lapack_driver_module
/// @brief  The eigenvalue solver of symmetric / Hermitian matrices.
///
/// @tparam  _Matrix  The matrix type.
///
/// @see mcnla::lapack::syev
///
template <class _Matrix, JobOption _jobz>
class SyevEngine {

  static_assert(_jobz == 'N' || _jobz == 'V', "Job undefined!");

 private:

  static constexpr Trans trans = _Matrix::trans;
  static constexpr Uplo  uplo  = _Matrix::uplo;

  using ScalarType     = ScalarT<_Matrix>;
  using VectorType     = typename _Matrix::VectorType;
  using RealVectorType = typename _Matrix::VectorType::RealType;
  using MatrixType     = _Matrix;

  static constexpr bool is_real = traits::ScalarTraits<ScalarType>::is_real;

  static_assert(std::is_same<DenseSymmetricMatrix<ScalarType, trans, uplo>, _Matrix>::value,
                "'_Matrix' is not a dense symmetric matrix!");

 protected:

  /// The dimension.
  index_t size_;

  /// The workspace.
  VectorType work_;

  /// The real workspace.
  RealVectorType rwork_;

 public:

  // Constructor
  inline SyevEngine() noexcept;
  inline SyevEngine( const index_t size ) noexcept;
  inline SyevEngine( const MatrixType &a ) noexcept;

  // Operators
  template <class _TypeA, class _TypeW>
  inline void operator()( _TypeA &&a, _TypeW &&w ) noexcept;

  // Computes eigenvalues
  template <class _TypeA, class _TypeW>
  inline void computeValues( _TypeA &&a, _TypeW &&w ) noexcept;

  // Resizes
  template <typename... Args>
  inline void reconstruct( Args... args ) noexcept;

  // Get sizes
  inline std::tuple<index_t> sizes() const noexcept;

  // Gets workspaces
  inline       VectorType& getWork() noexcept;
  inline const VectorType& getWork() const noexcept;
  inline       RealVectorType& getRwork() noexcept;
  inline const RealVectorType& getRwork() const noexcept;

 protected:

  // Computes
  template <JobOption __jobz = _jobz>
  inline void compute( MatrixType &a, RealVectorType &w ) noexcept;

  // Queries
  inline index_t query( const index_t size ) const noexcept;

};

}  // namespace lapack

}  // namespace mcnla

#endif  // MCNLA_CORE_LAPACK_ENGINE_SYEV_ENGINE_HPP_
