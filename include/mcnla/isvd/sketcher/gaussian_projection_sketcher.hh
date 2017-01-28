////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/sketcher/gaussian_projection_sketcher.hh
/// @brief   The definition of Gaussian projection sketcher.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_SKETCHER_GAUSSIAN_PROJECTION_SKETCHER_HH_
#define MCNLA_ISVD_SKETCHER_GAUSSIAN_PROJECTION_SKETCHER_HH_

#include <mcnla/isvd/def.hpp>
#include <mcnla/isvd/sketcher/sketcher.hpp>
#include <mcnla/core/random.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  isvd_sketcher_module
/// The Gaussian projection sketcher tag.
///
/// @tparam  _exponent  exponent of the power method.
///
template <index_t _exponent = 0>
struct GaussianProjectionSketcherTag {};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  isvd_sketcher_module
/// The Gaussian projection sketcher.
///
/// @tparam  _Scalar    The scalar type.
/// @tparam  _exponent  exponent of the power method.
///
template <typename _Scalar, index_t _exponent>
class Sketcher<GaussianProjectionSketcherTag<_exponent>, _Scalar>
  : public SketcherWrapper<Sketcher<GaussianProjectionSketcherTag<_exponent>, _Scalar>> {

  friend SketcherWrapper<Sketcher<GaussianProjectionSketcherTag<_exponent>, _Scalar>>;

 private:

  using BaseType = SketcherWrapper<Sketcher<GaussianProjectionSketcherTag<_exponent>, _Scalar>>;

 public:

  using ScalarType = _Scalar;

  using ParametersType = Parameters<ScalarType>;

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
  DenseMatrixRowMajor<ScalarType> matrix_omegas_;

  /// The random driver
  random::Driver<ScalarType> random_driver_;

  using BaseType::parameters_;
  using BaseType::mpi_comm_;
  using BaseType::mpi_root_;

 public:

  // Constructor
  inline Sketcher( const ParametersType &parameters,
                   const MPI_Comm mpi_comm, const mpi_int_t mpi_root, const index_t seed ) noexcept;

  // Gets time
  inline double time1() const noexcept;
  inline double time2() const noexcept;

 protected:

  // Initializes
  void initializeImpl() noexcept;

  // Random sketches
  template <class _Matrix>
  void sketchImpl( const _Matrix &matrix_a, DenseMatrixCollection120<ScalarType> &collection_q ) noexcept;

  // Outputs name
  inline std::ostream& outputNameImpl( std::ostream& os ) const noexcept;

  // Gets time
  inline double timeImpl() const noexcept;

  // Sets seed
  inline void setSeedImpl( const index_t seed ) noexcept;

};

/// @ingroup  isvd_sketcher_module
template <typename _Scalar, index_t _exponent = 0>
using GaussianProjectionSketcher = Sketcher<GaussianProjectionSketcherTag<_exponent>, _Scalar>;

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_SKETCHER_GAUSSIAN_PROJECTION_SKETCHER_HH_
