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
/// The column sampling sketcher tag.
///
struct ColumnSamplingSketcherTag {};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  isvd_sketcher_module
///
/// The column sampling sketcher.
///
/// @tparam  _Matrix  The matrix type.
///
template <class _Matrix>
class Sketcher<_Scalar, ColumnSamplingSketcherTag>
  : public SketcherWrapper<Sketcher<_Scalar, ColumnSamplingSketcherTag>> {

  friend SketcherWrapper<Sketcher<_Scalar, ColumnSamplingSketcherTag>>;

 private:

  using BaseType = SketcherWrapper<Sketcher<_Scalar, ColumnSamplingSketcherTag>>;

 public:

  using ScalarType  = _Scalar;

 protected:

  /// The name.
  static constexpr const char* name_= "Column Sampling Sketcher";

  /// The starting time
  double time0_;

  /// The ending time of random sketching
  double time1_;

  /// The random generator
  std::default_random_engine random_generator_;

  /// The uniform integer distribution
  std::uniform_int_distribution<index_t> random_distribution_;

  /// The random seed
  index_t seed_;

  using BaseType::parameters_;

 public:

  // Constructor
  inline Sketcher( const Parameters<ScalarType> &parameters,
                   const MPI_Comm mpi_comm, const mpi_int_t mpi_root, const index_t seed ) noexcept;

  // Gets time
  inline double time1() const noexcept;

 protected:

  // Initializes
  void initializeImpl() noexcept;

  // Random sketches
  template <class _Matrix>
  void sketchImpl( const _Matrix &matrix_a, DenseMatrixSet120<ScalarType> &set_y ) noexcept;

  // Gets name
  inline constexpr const char* nameImpl() const noexcept;

  // Gets time
  inline double timeImpl() const noexcept;

  // Sets seed
  void setSeedImpl( const index_t seed ) noexcept;

};

/// @ingroup  isvd_sketcher_module
template <class _Matrix>
using ColumnSamplingSketcher = Sketcher<_Scalar, ColumnSamplingSketcherTag>;

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_SKETCHER_COLUMN_SAMPLING_SKETCHER_HPP_
