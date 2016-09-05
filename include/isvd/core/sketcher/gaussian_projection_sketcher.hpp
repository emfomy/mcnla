////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/core/sketcher/gaussian_projection_sketcher.hpp
/// @brief   The Gaussian projection sketcher.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_CORE_SKETCHER_GAUSSIAN_PROJECTION_SKETCHER_HPP_
#define ISVD_CORE_SKETCHER_GAUSSIAN_PROJECTION_SKETCHER_HPP_

#include <isvd/isvd.hpp>
#include <isvd/blas.hpp>
#include <isvd/lapack.hpp>
#include <isvd/core/sketcher_base.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

template <class _Matrix> class GaussianProjectionSketcher;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The internal namespace.
//
namespace internal {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The Gaussian projection sketcher traits.
///
/// @tparam  _Matrix  The matrix type.
///
template <class _Matrix>
struct Traits<GaussianProjectionSketcher<_Matrix>> {
  using MatrixType = _Matrix;
};

}  // namespace internal

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The Gaussian projection sketcher.
///
/// @tparam  _Matrix  The matrix type.
///
template <class _Matrix>
class GaussianProjectionSketcher : public internal::SketcherBase<GaussianProjectionSketcher<_Matrix>> {

  friend internal::SketcherBase<GaussianProjectionSketcher<_Matrix>>;

 private:

  using BaseType = internal::SketcherBase<GaussianProjectionSketcher<_Matrix>>;

 public:

  static const Layout layout = _Matrix::layout;
  using ScalarType     = typename _Matrix::ScalarType;
  using RealScalarType = typename _Matrix::RealScalarType;
  using MatrixType     = _Matrix;

  static_assert(std::is_same<DenseMatrix<ScalarType, layout>, _Matrix>::value, "'_Matrix' is not a dense matrix!");

 protected:

  /// The parameters.
  const internal::Parameters<ScalarType> &parameters_ = BaseType::parameters_;

  /// The matrix Omega.
  DenseMatrix<ScalarType, Layout::ROWMAJOR> matrix_omega_;

  /// The vector S.
  DenseVector<RealScalarType> vector_s_;

  /// The empty matrix.
  DenseMatrix<ScalarType, Layout::ROWMAJOR> matrix_empty_;

  /// The GESVD driver
  lapack::GesvdDriver<DenseMatrix<ScalarType, Layout::ROWMAJOR>, 'O', 'N'> gesvd_driver_;

 public:

  // Constructor
  GaussianProjectionSketcher( const internal::Parameters<ScalarType> &parameters, index_t *seed ) noexcept;

 protected:

  // Initializes
  void initializeImpl() noexcept;

  // Random sketches
  void sketchImpl( const _Matrix &matrix_a, DenseCube<ScalarType, Layout::ROWMAJOR> &cube_q ) noexcept;

};

}  // namespace isvd

#endif  // ISVD_CORE_SKETCHER_GAUSSIAN_PROJECTION_SKETCHER_HPP_
