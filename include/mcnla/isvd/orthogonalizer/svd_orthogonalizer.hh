////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/orthogonalizer/svd_orthogonalizer.hh
/// @brief   The definition of SVD orthogonalizer.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_ORTHOGONALIZER_SVD_ORTHOGONALIZER_HH_
#define MCNLA_ISVD_ORTHOGONALIZER_SVD_ORTHOGONALIZER_HH_

#include <mcnla/def.hpp>
#include <mcnla/isvd/def.hpp>
#include <mcnla/isvd/orthogonalizer/orthogonalizer.hpp>
#include <mcnla/core/lapack.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  isvd_orthogonalizer_module
/// The SVD orthogonalizer tag.
///
struct SvdOrthogonalizerTag {};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  isvd_orthogonalizer_module
/// The SVD orthogonalizer.
///
/// @tparam  _Scalar  The scalar type.
///
template <typename _Scalar>
class Orthogonalizer<_Scalar, SvdOrthogonalizerTag>
  : public OrthogonalizerWrapper<Orthogonalizer<_Scalar, SvdOrthogonalizerTag>> {

  friend OrthogonalizerWrapper<Orthogonalizer<_Scalar, SvdOrthogonalizerTag>>;

 private:

  using BaseType = OrthogonalizerWrapper<Orthogonalizer<_Scalar, SvdOrthogonalizerTag>>;

 public:

  using ScalarType     = _Scalar;
  using RealScalarType = RealScalarT<ScalarType>;
  using MatrixType     = MatrixT<DenseMatrixCollection120<ScalarType>>;

  using ParametersType = Parameters<ScalarType>;

 protected:

  /// The name.
  static constexpr const char* name_= "SVD Orthogonalizer";

  /// The starting time
  double time0_;

  /// The ending time of orthogonalization
  double time1_;

  /// The vector S.
  DenseVector<RealScalarType> vector_s_;

  /// The empty matrix.
  MatrixType matrix_empty_;

  /// The random engine.
  lapack::GesvdEngine<MatrixType, 'O', 'N'> gesvd_engine_;

  using BaseType::parameters_;
  using BaseType::mpi_comm_;
  using BaseType::mpi_root_;

 public:

  // Constructor
  inline Orthogonalizer( const ParametersType &parameters,
                         const MPI_Comm mpi_comm, const mpi_int_t mpi_root ) noexcept;

  // Gets time
  inline double time1() const noexcept;
  inline double time2() const noexcept;

 protected:

  // Initializes
  void initializeImpl() noexcept;

  // Orthogonalizes
  void orthogonalizeImpl( DenseMatrixCollection120<ScalarType> &collection_q ) noexcept;

  // Gets name
  inline constexpr const char* nameImpl() const noexcept;

  // Gets time
  inline double timeImpl() const noexcept;

};

/// @ingroup  isvd_orthogonalizer_module
template <typename _Scalar>
using SvdOrthogonalizer = Orthogonalizer<_Scalar, SvdOrthogonalizerTag>;

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_ORTHOGONALIZER_SVD_ORTHOGONALIZER_HH_
