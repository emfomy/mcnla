////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/core/sketcher/gaussian_projection_sketcher.hpp
/// @brief   The Gaussian projection sketcher.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef ISVD_CORE_SKETCHER_GAUSSIAN_PROJECTION_SKETCHER_HPP_
#define ISVD_CORE_SKETCHER_GAUSSIAN_PROJECTION_SKETCHER_HPP_

#include <isvd/isvd.hpp>
#include <isvd/blas.hpp>
#include <isvd/lapack.hpp>
#include <isvd/core/sketcher/sketcher_base.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <class _Matrix> class GaussianProjectionSketcher;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The detail namespace.
//
namespace detail {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The Gaussian projection sketcher traits.
///
/// @tparam  _Matrix  The matrix type.
///
template <class _Matrix>
struct Traits<GaussianProjectionSketcher<_Matrix>> {
  using MatrixType = _Matrix;
};

}  // namespace detail

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The Gaussian projection sketcher.
///
/// @tparam  _Matrix  The matrix type.
///
template <class _Matrix>
class GaussianProjectionSketcher : public SketcherBase<GaussianProjectionSketcher<_Matrix>> {

  friend SketcherBase<GaussianProjectionSketcher<_Matrix>>;

 private:

  using BaseType = SketcherBase<GaussianProjectionSketcher<_Matrix>>;

 public:

  using ScalarType     = typename _Matrix::ScalarType;
  using RealScalarType = typename _Matrix::RealScalarType;
  using MatrixType     = _Matrix;

  static_assert(std::is_base_of<MatrixBase<_Matrix>, _Matrix>::value, "'_Matrix' is not a matrix!");

 protected:

  /// The parameters.
  const Parameters<ScalarType> &parameters_ = BaseType::parameters_;

  /// The name.
  static constexpr const char* name_= "Gaussian Projection Sketcher";

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
  inline GaussianProjectionSketcher( const Parameters<ScalarType> &parameters, index_t *seed ) noexcept;

 protected:

  // Initializes
  void initializeImpl() noexcept;

  // Random sketches
  void sketchImpl( const _Matrix &matrix_a, DenseCube<ScalarType, Layout::ROWMAJOR> &cube_q ) noexcept;

  // Gets name
  inline constexpr const char* getNameImpl() const noexcept;

};

}  // namespace isvd

#endif  // ISVD_CORE_SKETCHER_GAUSSIAN_PROJECTION_SKETCHER_HPP_
