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
#include <cstdlib>
#include <mcnla/core/blas.hpp>
#include <mcnla/isvd/sketcher/sketcher.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The Gaussian projection sketcher tag.
///
struct GaussianProjectionSketcherTag {};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  isvd_sketcher_module
///
/// The Gaussian projection sketcher.
///
/// @tparam  _Matrix  The matrix type.
///
template <class _Matrix>
class Sketcher<_Matrix, DenseMatrixSet120<ScalarT<_Matrix>>, GaussianProjectionSketcherTag>
  : public SketcherWrapper<Sketcher<_Matrix, DenseMatrixSet120<ScalarT<_Matrix>>, GaussianProjectionSketcherTag>> {

  friend SketcherWrapper<Sketcher<_Matrix, DenseMatrixSet120<ScalarT<_Matrix>>, GaussianProjectionSketcherTag>>;

 private:

  using BaseType =
    SketcherWrapper<Sketcher<_Matrix, DenseMatrixSet120<ScalarT<_Matrix>>, GaussianProjectionSketcherTag>>;

 public:

  using ScalarType = ScalarT<_Matrix>;
  using MatrixAType = _Matrix;
  using SetYType    = DenseMatrixSet120<ScalarType>;

 protected:

  /// The name.
  static constexpr const char* name_= "Gaussian Projection Sketcher";

  /// The starting time
  double time0_;

  /// The ending time of random generating
  double time1_;

  /// The ending time of random sketching
  double time2_;

  /// The matrix Omega.
  DenseMatrixColMajor<ScalarType> matrix_omegas_;

  /// The random seed
  index_t seed_[4];

  using BaseType::parameters_;

 public:

  // Constructor
  inline Sketcher( const Parameters<ScalarType> &parameters, const MPI_Comm mpi_comm, const mpi_int_t mpi_root ) noexcept;

 protected:

  // Initializes
  void initializeImpl() noexcept;

  // Random sketches
  void sketchImpl( const MatrixAType &matrix_a, SetYType &set_y ) noexcept;

  // Gets name
  inline constexpr const char* nameImpl() const noexcept;

  // Gets time
  inline double timeImpl() const noexcept;
  inline double time1() const noexcept;
  inline double time2() const noexcept;

  Sketcher& setSeed( const index_t seed[4] ) noexcept;

};

/// @ingroup  isvd_sketcher_module
template <class _Matrix>
using GaussianProjectionSketcher =
    Sketcher<_Matrix, DenseMatrixSet120<ScalarT<_Matrix>>, GaussianProjectionSketcherTag>;

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_SKETCHER_GAUSSIAN_PROJECTION_SKETCHER_HPP_
