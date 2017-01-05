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
class Sketcher<_Matrix, DenseMatrixSet120<ScalarT<_Matrix>>, ColumnSamplingSketcherTag>
  : public SketcherWrapper<Sketcher<_Matrix, DenseMatrixSet120<ScalarT<_Matrix>>, ColumnSamplingSketcherTag>> {

  friend SketcherWrapper<Sketcher<_Matrix, DenseMatrixSet120<ScalarT<_Matrix>>, ColumnSamplingSketcherTag>>;

 private:

  using BaseType = SketcherWrapper<Sketcher<_Matrix, DenseMatrixSet120<ScalarT<_Matrix>>, ColumnSamplingSketcherTag>>;

 public:

  using ScalarType  = ScalarT<_Matrix>;
  using MatrixAType = _Matrix;
  using SetYType    = DenseMatrixSet120<ScalarType>;

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
  inline Sketcher( const Parameters<ScalarType> &parameters, const MPI_Comm mpi_comm, const mpi_int_t mpi_root ) noexcept;

  // Gets time
  inline double time1() const noexcept;

  // Sets seed
  Sketcher& setSeed( const index_t seed[4] ) noexcept;

 protected:

  // Initializes
  void initializeImpl() noexcept;

  // Random sketches
  void sketchImpl( const MatrixAType &matrix_a, SetYType &set_y ) noexcept;

  // Gets name
  inline constexpr const char* nameImpl() const noexcept;

  // Gets time
  inline double timeImpl() const noexcept;

};

/// @ingroup  isvd_sketcher_module
template <class _Matrix>
using ColumnSamplingSketcher =
    Sketcher<_Matrix, DenseMatrixSet120<ScalarT<_Matrix>>, ColumnSamplingSketcherTag>;

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_SKETCHER_COLUMN_SAMPLING_SKETCHER_HPP_
