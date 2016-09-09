////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/core/sketcher/column_sampling_sketcher.hpp
/// @brief   The column sampling sketcher.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_CORE_SKETCHER_COLUMN_SAMPLING_SKETCHER_HPP_
#define ISVD_CORE_SKETCHER_COLUMN_SAMPLING_SKETCHER_HPP_

#include <isvd/isvd.hpp>
#include <random>
#include <isvd/blas.hpp>
#include <isvd/lapack.hpp>
#include <isvd/core/sketcher_base.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

template <class _Matrix> class ColumnSamplingSketcher;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The internal namespace.
//
namespace internal {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The column sampling sketcher traits.
///
/// @tparam  _Matrix  The matrix type.
///
template <class _Matrix>
struct Traits<ColumnSamplingSketcher<_Matrix>> {
  using MatrixType = _Matrix;
};

}  // namespace internal

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The column sampling sketcher.
///
/// @tparam  _Matrix  The matrix type.
///
template <class _Matrix>
class ColumnSamplingSketcher : public internal::SketcherBase<ColumnSamplingSketcher<_Matrix>> {

  friend internal::SketcherBase<ColumnSamplingSketcher<_Matrix>>;

 private:

  using BaseType = internal::SketcherBase<ColumnSamplingSketcher<_Matrix>>;

 public:

  using ScalarType     = typename _Matrix::ScalarType;
  using RealScalarType = typename _Matrix::RealScalarType;
  using MatrixType     = _Matrix;

  static_assert(std::is_base_of<internal::MatrixBase<_Matrix>, _Matrix>::value, "'_Matrix' is not a matrix!");

 protected:

  /// The parameters.
  const internal::Parameters<ScalarType> &parameters_ = BaseType::parameters_;

  /// The name.
  const char *name_ = "Column Sampling Sketcher";

  /// The vector S.
  DenseVector<RealScalarType> vector_s_;

  /// The empty matrix.
  DenseMatrix<ScalarType, Layout::ROWMAJOR> matrix_empty_;

  /// The GESVD driver
  lapack::GesvdDriver<DenseMatrix<ScalarType, Layout::ROWMAJOR>, 'O', 'N'> gesvd_driver_;

  /// The random generator
  std::default_random_engine random_generator_;

  /// The uniform integer distribution
  std::uniform_int_distribution<index_t> random_distribution_;

 public:

  // Constructor
  ColumnSamplingSketcher( const internal::Parameters<ScalarType> &parameters, index_t *seed ) noexcept;

 protected:

  // Initializes
  void initializeImpl() noexcept;

  // Random sketches
  void sketchImpl( const _Matrix &matrix_a, DenseCube<ScalarType, Layout::ROWMAJOR> &cube_q ) noexcept;

  // Gets name
  inline const char* getNameImpl() const noexcept;

};

}  // namespace isvd

#endif  // ISVD_CORE_SKETCHER_COLUMN_SAMPLING_SKETCHER_HPP_
