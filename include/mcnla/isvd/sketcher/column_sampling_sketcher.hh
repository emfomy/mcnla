////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/sketcher/column_sampling_sketcher.hh
/// @brief   The definition of column sampling sketcher.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_SKETCHER_COLUMN_SAMPLING_SKETCHER_HH_
#define MCNLA_ISVD_SKETCHER_COLUMN_SAMPLING_SKETCHER_HH_

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
/// The column sampling sketcher tag.
///
struct ColumnSamplingSketcherTag {};

/// @ingroup  isvd_sketcher_module
template <typename _Scalar>
using ColumnSamplingSketcher = Sketcher<ColumnSamplingSketcherTag, _Scalar>;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  isvd_sketcher_module
/// The column sampling sketcher.
///
/// @tparam  _Scalar  The scalar type.
///
template <typename _Scalar>
class Sketcher<ColumnSamplingSketcherTag, _Scalar>
  : public SketcherWrapper<ColumnSamplingSketcher<_Scalar>> {

  friend SketcherWrapper<ColumnSamplingSketcher<_Scalar>>;

 private:

  using BaseType = SketcherWrapper<ColumnSamplingSketcher<_Scalar>>;

 public:

  using ScalarType = _Scalar;

  using ParametersType = Parameters<ScalarType>;

 protected:

  /// The name.
  static constexpr const char* name_= "Column Sampling Sketcher";

  /// The starting time
  double time0_;

  /// The ending time of random generating
  double time1_;

  /// The ending time of random sketching
  double time2_;

  /// The matrix Omega.
  DenseVector<index_t> vector_idxs_;

  /// The random driver
  random::Driver<index_t> random_driver_;

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

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_SKETCHER_COLUMN_SAMPLING_SKETCHER_HH_
