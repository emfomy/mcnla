////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/core/sketcher/gaussian_projection_sketcher.hpp
/// @brief   The Gaussian projection sketcher.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_CORE_SKETCHER_GAUSSIAN_PROJECTION_SKETCHER_HPP_
#define ISVD_CORE_SKETCHER_GAUSSIAN_PROJECTION_SKETCHER_HPP_

#include <isvd/isvd.hpp>
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
  using ScalarType = typename _Matrix::ScalarType;
  using MatrixType = _Matrix;
};

}  // namespace internal

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The interface of iSVD sketcher.
///
/// @tparam  _Matrix  The matrix type.
///
template <class _Matrix>
class GaussianProjectionSketcher : public internal::SketcherBase<GaussianProjectionSketcher<_Matrix>> {

  friend internal::SketcherBase<GaussianProjectionSketcher<_Matrix>>;

 public:

  static const Layout layout = _Matrix::layout;
  using ScalarType      = typename _Matrix::ScalarType;
  using RealScalarType  = typename _Matrix::RealScalarType;
  using DenseVectorType = isvd::DenseVector<ScalarType>;
  using DenseMatrixType = isvd::DenseMatrix<ScalarType, Layout::ROWMAJOR>;
  using DenseCubeType   = isvd::DenseCube<ScalarType, Layout::ROWMAJOR>;

  static_assert(std::is_same<DenseMatrix<ScalarType, layout>, _Matrix>::value, "'_Matrix' is not a dense matrix!");

 protected:

  /// The number of random sketches per MPI node.
  const internal::Parameters<RealScalarType> &parameters_;

  /// The matrix Omega.
  DenseMatrixType matrix_omega_;

  /// The vector Tau.
  DenseVectorType matrix_tau_;

 public:

  // Constructor
  GaussianProjectionSketcher( const internal::Parameters<RealScalarType> &parameters ) noexcept;

 protected:

  // Initializes
  void initializeImpl() noexcept;

  // Random sketches
  void sketchImpl( const _Matrix &matrix_a, DenseCubeType &cube_qj ) noexcept;

};

}  // namespace isvd

#endif  // ISVD_CORE_SKETCHER_GAUSSIAN_PROJECTION_SKETCHER_HPP_
