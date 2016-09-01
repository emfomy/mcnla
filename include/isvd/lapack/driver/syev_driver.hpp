////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/lapack/driver/syev_driver.hpp
/// @brief   The definition of LAPACK SYEV driver.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_LAPACK_DRIVER_SYEV_DRIVER_HPP_
#define ISVD_LAPACK_DRIVER_SYEV_DRIVER_HPP_

#include <isvd/utility/traits.hpp>
#include <isvd/matrix.hpp>
#include <isvd/lapack/lapack.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The LAPACK namespace
//
namespace lapack {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Computes all eigenvalues and, optionally, eigenvectors of a symmetric or Hermitian matrix.
///
/// @tparam  _Matrix  The matrix type.
///
template <class _Matrix, JobOption _jobz, UploOption _uplo = UploOption::LOWER>
class SyevDriver {

  static_assert(_jobz == 'N' || _jobz == 'V', "Job undefined!");

 private:

  static const Layout layout = _Matrix::layout;
  using ScalarType     = typename _Matrix::ScalarType;
  using VectorType     = typename _Matrix::VectorType;
  using RealVectorType = typename _Matrix::RealVectorType;
  static const bool is_real  = isvd::internal::ScalarTraits<ScalarType>::is_real;

  static_assert(std::is_same<DenseMatrix<ScalarType, layout>, _Matrix>::value, "'_Matrix' is not a dense matrix!");

 protected:

  /// The dimension.
  const index_t dim_;

  /// The workspace.
  VectorType work_;

  /// The real workspace.
  RealVectorType rwork_;

 public:

  // Constructor
  SyevDriver( const _Matrix &a ) noexcept;

  // Computes
  inline void compute( _Matrix &a, RealVectorType &w ) noexcept;
  template <class _TypeA, class _TypeW>
  inline void compute( _TypeA &&a, _TypeW &&w ) noexcept;

  // Gets workspaces
  inline       VectorType& getWork() noexcept;
  inline const VectorType& getWork() const noexcept;
  inline       RealVectorType& getRwork() noexcept;
  inline const RealVectorType& getRwork() const noexcept;

 protected:

  inline index_t query( const _Matrix &a ) const noexcept;

};

}  // namespace lapack

}  // namespace isvd

#endif  // ISVD_LAPACK_DRIVER_SYEV_DRIVER_HPP_
