////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/sketcher/column_sampling_sketcher.hpp
/// @brief   The column sampling sketcher.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_SKETCHER_COLUMN_SAMPLING_SKETCHER_HPP_
#define MCNLA_ISVD_SKETCHER_COLUMN_SAMPLING_SKETCHER_HPP_

#include <mcnla/def.hpp>
#include <mcnla/isvd/def.hpp>
#include <random>
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
template <class _Matrix> class ColumnSamplingSketcher;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace isvd

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The traits namespace.
//
namespace traits {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The column sampling sketcher traits.
///
/// @tparam  _Matrix  The matrix type.
///
template <class _Matrix>
struct Traits<isvd::ColumnSamplingSketcher<_Matrix>> {
  using MatrixType = _Matrix;
};

}  // namespace traits

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  isvd_sketcher_module
///
/// The column sampling sketcher.
///
/// @tparam  _Matrix  The matrix type.
///
template <class _Matrix>
class ColumnSamplingSketcher : public SketcherBase<ColumnSamplingSketcher<_Matrix>> {

  static_assert(std::is_base_of<MatrixBase<_Matrix>, _Matrix>::value, "'_Matrix' is not a matrix!");

  friend SketcherBase<ColumnSamplingSketcher<_Matrix>>;

 private:

  using BaseType = SketcherBase<ColumnSamplingSketcher<_Matrix>>;

 public:

  using ScalarType     = typename _Matrix::ScalarType;
  using RealScalarType = typename _Matrix::RealScalarType;
  using MatrixType     = _Matrix;

 protected:

  /// The name.
  static constexpr const char* name_= "Column Sampling Sketcher";

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

  using BaseType::parameters_;
  using BaseType::mpi_comm_;
  using BaseType::mpi_root_;

 public:

  // Constructor
  inline ColumnSamplingSketcher( const Parameters<ScalarType> &parameters,
                                 const MPI_Comm mpi_comm, const mpi_int_t mpi_root, index_t *seed ) noexcept;

 protected:

  // Initializes
  void initializeImpl() noexcept;

  // Random sketches
  void sketchImpl( const _Matrix &matrix_a, DenseMatrixSet120<ScalarType> &set_q ) noexcept;

  // Gets name
  inline constexpr const char* getNameImpl() const noexcept;

};

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_SKETCHER_COLUMN_SAMPLING_SKETCHER_HPP_
