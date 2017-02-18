////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/integrator/naive_kolmogorov_nagumo_integrator.hh
/// @brief   The definition of naive Kolmogorov-Nagumo-type integrator.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_INTEGRATOR_NAIVE_KOLMOGOROV_NAGUMO_INTEGRATOR_HH_
#define MCNLA_ISVD_INTEGRATOR_NAIVE_KOLMOGOROV_NAGUMO_INTEGRATOR_HH_

#include <mcnla/isvd/def.hpp>
#include <mcnla/isvd/integrator/integrator.hpp>
#include <mcnla/core/la.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  isvd_integrator_module
/// The naive Kolmogorov-Nagumo-type integrator tag.
///
struct NaiveKolmogorovNagumoIntegratorTag {};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  isvd_integrator_module
/// The naive Kolmogorov-Nagumo-type integrator.
///
/// @tparam  _Scalar  The scalar type.
///
template <typename _Scalar>
class Integrator<_Scalar, NaiveKolmogorovNagumoIntegratorTag>
  : public IntegratorWrapper<Integrator<_Scalar, NaiveKolmogorovNagumoIntegratorTag>> {

  friend IntegratorWrapper<Integrator<_Scalar, NaiveKolmogorovNagumoIntegratorTag>>;

 private:

  using ThisType = Integrator<_Scalar, NaiveKolmogorovNagumoIntegratorTag>;
  using BaseType = IntegratorWrapper<Integrator<_Scalar, NaiveKolmogorovNagumoIntegratorTag>>;

 public:

  using ScalarType     = _Scalar;

  using ParametersType = Parameters<ScalarType>;

 protected:

  /// The name.
  static constexpr const char* name_= "Naive Kolmogorov-Nagumo-Type Integrator";

  /// The starting time
  double moment0_;

  /// The ending time of rearrangeing Q
  double moment1_;

  /// The ending time of integrating
  double moment2_;

  /// The ending time of gathering Qc
  double moment3_;

  /// The communication time of integrating
  double time2c_;

  /// The collection Q.
  DenseMatrixCollection120<ScalarType> collection_q_;

  /// The matrix Qs.
  DenseMatrixRowMajor<ScalarType> matrix_qs_;

  /// The matrix Qc.
  DenseMatrixRowMajor<ScalarType> matrix_qc_;

  /// The matrix Bs.
  DenseMatrixRowMajor<ScalarType> matrix_bs_;

  /// The matrix D.
  DenseMatrixRowMajor<ScalarType> matrix_d_;

  /// The matrix Z.
  DenseMatrixRowMajor<ScalarType> matrix_z_;

  /// The matrix C.
  DenseMatrixRowMajor<ScalarType> matrix_c_;

  /// The matrix X.
  DenseMatrixRowMajor<ScalarType> matrix_x_;

  /// The temporary matrix.
  DenseMatrixRowMajor<ScalarType> matrix_tmp_;

  /// The vector E.
  DenseVector<ScalarType> vector_e_;

  /// The vector F.
  DenseVector<ScalarType> vector_f_;

  /// The SYEV engine.
  la::SyevEngine<DenseSymmetricMatrixRowMajor<ScalarType>, 'V'> syev_engine_;

  using BaseType::parameters_;
  using BaseType::mpi_comm_;
  using BaseType::mpi_root_;
  using BaseType::iteration_;

 public:

  // Constructor
  inline Integrator( const ParametersType &parameters, const MPI_Comm mpi_comm, const mpi_int_t mpi_root ) noexcept;

  // Gets time
  inline double time1() const noexcept;
  inline double time2() const noexcept;
  inline double time2c() const noexcept;
  inline double time3() const noexcept;

 protected:

  // Initializes
  void initializeImpl() noexcept;

  // Integrates
  void integrateImpl() noexcept;

  // Outputs name
  inline std::ostream& outputNameImpl( std::ostream& os ) const noexcept;

  // Gets time
  inline double timeImpl() const noexcept;

  // Gets matrices
  inline       DenseMatrixCollection120<ScalarType>& collectionQImpl() noexcept;
  inline const DenseMatrixCollection120<ScalarType>& collectionQImpl() const noexcept;
  inline       DenseMatrixRowMajor<ScalarType>& matrixQImpl() noexcept;
  inline const DenseMatrixRowMajor<ScalarType>& matrixQImpl() const noexcept;

};

/// @ingroup  isvd_integrator_module
template <typename _Scalar>
using NaiveKolmogorovNagumoIntegrator = Integrator<_Scalar, NaiveKolmogorovNagumoIntegratorTag>;

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_INTEGRATOR_NAIVE_KOLMOGOROV_NAGUMO_INTEGRATOR_HH_
