////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/lapack/driver/gesvd.hpp
/// @brief   The LAPACK GESVD driver.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_LAPACK_DRIVER_GESVD_DRIVER_HPP_
#define MCNLA_LAPACK_DRIVER_GESVD_DRIVER_HPP_

#include <mcnla/mcnla.hpp>
#include <mcnla/utility/traits.hpp>
#include <mcnla/matrix.hpp>
#include <mcnla/lapack/lapack.hpp>
#include <mcnla/lapack/lapack/gesvd.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The LAPACK namespace
//
namespace lapack {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::lapack::detail::gesvd
///
/// @tparam  _Matrix  The matrix type.
///
template <class _Matrix, JobOption _jobu, JobOption _jobvt>
class GesvdDriver {

  static_assert(_jobu  == 'A' || _jobu  == 'S' || _jobu  == 'O' || _jobu  == 'N', "Job undefined!");
  static_assert(_jobvt == 'A' || _jobvt == 'S' || _jobvt == 'O' || _jobvt == 'N', "Job undefined!");
  static_assert(_jobu  != 'O' || _jobvt != 'O', "Job conflict!");

 private:

  static constexpr Layout layout = _Matrix::layout;
  using ScalarType     = typename _Matrix::ScalarType;
  using VectorType     = typename _Matrix::VectorType;
  using RealVectorType = typename _Matrix::RealVectorType;
  static constexpr bool is_real = mcnla::detail::ScalarTraits<ScalarType>::is_real;

  static_assert(std::is_same<DenseMatrix<ScalarType, layout>, _Matrix>::value, "'_Matrix' is not a dense matrix!");

 protected:

  /// The number of rows.
  index_t nrow_;

  /// The number of columns.
  index_t ncol_;

  /// The workspace.
  VectorType work_;

  /// The real workspace.
  RealVectorType rwork_;

  /// Empty matrix.
  _Matrix matrix_empty_;

 public:

  // Constructors
  inline GesvdDriver() noexcept;
  inline GesvdDriver( const index_t nrow, const index_t ncol ) noexcept;
  inline GesvdDriver( const _Matrix &a ) noexcept;

  // Operators
  template <class _TypeA, class _TypeS, class _TypeU, class _TypeVt>
  inline void operator()( _TypeA &&a, _TypeS &&s, _TypeU &&u, _TypeVt &&vt ) noexcept;

  // Computes eigenvalues
  template <class _TypeA, class _TypeS>
  inline void computeValues( _TypeA &&a, _TypeS &&s ) noexcept;

  // Resizes
  inline void resize( const index_t nrow, const index_t ncol ) noexcept;
  inline void resize( const _Matrix &a ) noexcept;

  // Get sizes
  inline std::pair<index_t, index_t> getSizes() const noexcept;

  // Gets workspaces
  inline       VectorType& getWork() noexcept;
  inline const VectorType& getWork() const noexcept;
  inline       RealVectorType& getRwork() noexcept;
  inline const RealVectorType& getRwork() const noexcept;

 protected:

  // Computes
  template <JobOption __jobu = _jobu, JobOption __jobvt = _jobvt>
  inline void compute( _Matrix &a, RealVectorType &s, _Matrix &u, _Matrix &vt ) noexcept;

  // Queries
  inline index_t query( const index_t nrow, const index_t ncol ) const noexcept;

};

}  // namespace lapack

}  // namespace mcnla

#endif  // MCNLA_LAPACK_DRIVER_GESVD_DRIVER_HPP_
