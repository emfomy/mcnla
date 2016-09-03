////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/lapack/driver/gesvd.hpp
/// @brief   The definition of LAPACK GESVD driver.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_LAPACK_DRIVER_GESVD_DRIVER_HPP_
#define ISVD_LAPACK_DRIVER_GESVD_DRIVER_HPP_

#include <isvd/isvd.hpp>
#include <isvd/utility/traits.hpp>
#include <isvd/matrix.hpp>
#include <isvd/lapack/lapack.hpp>
#include <isvd/lapack/lapack/gesvd.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The LAPACK namespace
//
namespace lapack {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  isvd::lapack::internal::gesvd
///
/// @tparam  _Matrix  The matrix type.
///
template <class _Matrix, JobOption _jobu, JobOption _jobvt>
class GesvdDriver {

  static_assert(_jobu  == 'A' || _jobu  == 'S' || _jobu  == 'O' || _jobu  == 'N', "Job undefined!");
  static_assert(_jobvt == 'A' || _jobvt == 'S' || _jobvt == 'O' || _jobvt == 'N', "Job undefined!");
  static_assert(_jobu  != 'O' || _jobvt != 'O', "Job conflict!");

 private:

  static const Layout layout = _Matrix::layout;
  using ScalarType     = typename _Matrix::ScalarType;
  using VectorType     = typename _Matrix::VectorType;
  using RealVectorType = typename _Matrix::RealVectorType;
  static const bool is_real = isvd::internal::ScalarTraits<ScalarType>::is_real;

  static_assert(std::is_same<DenseMatrix<ScalarType, layout>, _Matrix>::value, "'_Matrix' is not a dense matrix!");

 protected:

  /// The number of rows.
  const index_t nrow_;

  /// The number of columns.
  const index_t ncol_;

  /// The workspace.
  VectorType work_;

  /// The real workspace.
  RealVectorType rwork_;

 public:

  // Constructors
  GesvdDriver( const index_t nrow, const index_t ncol ) noexcept;
  GesvdDriver( const _Matrix &a ) noexcept;

  // Operators
  template <class _TypeA, class _TypeS, class _TypeU, class _TypeVt>
  inline void operator()( _TypeA &&a, _TypeS &&s, _TypeU &&u, _TypeVt &&vt ) noexcept;

  // Gets workspaces
  inline       VectorType& getWork() noexcept;
  inline const VectorType& getWork() const noexcept;
  inline       RealVectorType& getRwork() noexcept;
  inline const RealVectorType& getRwork() const noexcept;

 protected:

  // Computes
  inline void compute( _Matrix &a, RealVectorType &s, _Matrix &u, _Matrix &vt ) noexcept;

  // Queries
  inline index_t query( const index_t nrow, const index_t ncol ) const noexcept;

};

}  // namespace lapack

}  // namespace isvd

#endif  // ISVD_LAPACK_DRIVER_GESVD_DRIVER_HPP_
