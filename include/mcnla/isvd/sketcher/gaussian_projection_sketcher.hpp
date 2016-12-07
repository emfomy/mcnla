////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/sketcher/gaussian_projection_sketcher.hpp
/// @brief   The Gaussian projection sketcher.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_SKETCHER_GAUSSIAN_PROJECTION_SKETCHER_HPP_
#define MCNLA_ISVD_SKETCHER_GAUSSIAN_PROJECTION_SKETCHER_HPP_

#include <mcnla/def.hpp>
#include <mcnla/isvd/def.hpp>
#include <mcnla/core/blas.hpp>
#include <mcnla/core/lapack.hpp>
#include <mcnla/isvd/sketcher/sketcher_base.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <class _Matrix> class GaussianProjectionSketcher;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace isvd

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The traits namespace.
//
namespace traits {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The Gaussian projection sketcher traits.
///
/// @tparam  _Matrix  The matrix type.
///
template <class _Matrix>
struct Traits<isvd::GaussianProjectionSketcher<_Matrix>> {
  using MatrixType = _Matrix;
};

}  // namespace traits

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  isvd_module
///
/// The Gaussian projection sketcher.
///
/// @tparam  _Matrix  The matrix type.
///
template <class _Matrix>
class GaussianProjectionSketcher : public SketcherBase<GaussianProjectionSketcher<_Matrix>> {

  static_assert(std::is_base_of<MatrixBase<_Matrix>, _Matrix>::value, "'_Matrix' is not a matrix!");

  friend SketcherBase<GaussianProjectionSketcher<_Matrix>>;

 private:

  using BaseType = SketcherBase<GaussianProjectionSketcher<_Matrix>>;

 public:

  using ScalarType     = typename _Matrix::ScalarType;
  using RealScalarType = typename _Matrix::RealScalarType;
  using MatrixType     = _Matrix;

 protected:

  /// The name.
  static constexpr const char* name_= "Gaussian Projection Sketcher";

  /// The parameters.
  const Parameters<ScalarType> &parameters_ = BaseType::parameters_;

  /// The starting time
  double time0_;

  /// The ending time of random generating
  double time1_;

  /// The ending time of random sketching
  double time2_;

  /// The ending time of orthonormalizing
  double time3_;

  /// The matrix Omega.
  DenseMatrixSet120<ScalarType> set_omega_;

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
  void sketchImpl( const _Matrix &matrix_a, DenseMatrixSet120<ScalarType> &set_q ) noexcept;

  // Gets name
  inline constexpr const char* getNameImpl() const noexcept;

  // Gets time
  inline double getTimeImpl() const noexcept;
  inline const std::vector<double> getTimesImpl() const noexcept;

};

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_SKETCHER_GAUSSIAN_PROJECTION_SKETCHER_HPP_
