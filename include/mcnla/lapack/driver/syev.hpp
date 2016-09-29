////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/lapack/driver/syev.hpp
/// @brief   The LAPACK SYEV driver.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_LAPACK_DRIVER_SYEV_DRIVER_HPP_
#define MCNLA_LAPACK_DRIVER_SYEV_DRIVER_HPP_

#include <mcnla/mcnla.hpp>
#include <mcnla/utility/traits.hpp>
#include <mcnla/matrix.hpp>
#include <mcnla/lapack/lapack.hpp>
#include <mcnla/lapack/lapack/syev.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The LAPACK namespace
//
namespace lapack {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::lapack::detail::syev
///
/// @tparam  _Matrix  The matrix type.
///
template <class _Matrix, JobOption _jobz, UploOption _uplo = UploOption::LOWER>
class SyevDriver {

  static_assert(_jobz == 'N' || _jobz == 'V', "Job undefined!");

 private:

  static constexpr Layout layout = _Matrix::layout;
  using ScalarType     = typename _Matrix::ScalarType;
  using VectorType     = typename _Matrix::VectorType;
  using RealVectorType = typename _Matrix::RealVectorType;
  static constexpr bool is_real = mcnla::detail::ScalarTraits<ScalarType>::is_real;

  static_assert(std::is_same<DenseMatrix<ScalarType, layout>, _Matrix>::value, "'_Matrix' is not a dense matrix!");

 protected:

  /// The dimension.
  index_t dim_;

  /// The workspace.
  VectorType work_;

  /// The real workspace.
  RealVectorType rwork_;

 public:

  // Constructor
  inline SyevDriver() noexcept;
  inline SyevDriver( const index_t dim ) noexcept;
  inline SyevDriver( const _Matrix &a ) noexcept;

  // Operators
  template <class _TypeA, class _TypeW>
  inline void operator()( _TypeA &&a, _TypeW &&w ) noexcept;

  // Computes eigenvalues
  template <class _TypeA, class _TypeW>
  inline void computeValues( _TypeA &&a, _TypeW &&w ) noexcept;

  // Resizes
  inline void resize( const index_t dim ) noexcept;
  inline void resize( const _Matrix &a ) noexcept;

  // Get sizes
  inline index_t getSizes() const noexcept;

  // Gets workspaces
  inline       VectorType& getWork() noexcept;
  inline const VectorType& getWork() const noexcept;
  inline       RealVectorType& getRwork() noexcept;
  inline const RealVectorType& getRwork() const noexcept;

 protected:

  // Computes
  template <JobOption __jobz = _jobz>
  inline void compute( _Matrix &a, RealVectorType &w ) noexcept;

  // Queries
  inline index_t query( const index_t dim ) const noexcept;

};

}  // namespace lapack

}  // namespace mcnla

#endif  // MCNLA_LAPACK_DRIVER_SYEV_DRIVER_HPP_
