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
/// @tparam  _Val  The scalar type.
///
template <typename _Val>
class Integrator<NaiveKolmogorovNagumoIntegratorTag, _Val>
  : public IntegratorWrapper<Integrator<NaiveKolmogorovNagumoIntegratorTag, _Val>> {

  friend IntegratorWrapper<Integrator<NaiveKolmogorovNagumoIntegratorTag, _Val>>;

 private:

  using ThisType = Integrator<NaiveKolmogorovNagumoIntegratorTag, _Val>;
  using BaseType = IntegratorWrapper<Integrator<NaiveKolmogorovNagumoIntegratorTag, _Val>>;

 public:

  using ValType     = _Val;

  using ParametersType = Parameters<ValType>;

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
  DenseMatrixCollection120<ValType> collection_q_;

  /// The matrix Qs.
  DenseMatrixRowMajor<ValType> matrix_qs_;

  /// The matrix Qc.
  DenseMatrixRowMajor<ValType> matrix_qc_;

  /// The matrix Bs.
  DenseMatrixRowMajor<ValType> matrix_bs_;

  /// The matrix D.
  DenseMatrixRowMajor<ValType> matrix_d_;

  /// The matrix Z.
  DenseMatrixRowMajor<ValType> matrix_z_;

  /// The matrix C.
  DenseMatrixRowMajor<ValType> matrix_c_;

  /// The matrix X.
  DenseMatrixRowMajor<ValType> matrix_x_;

  /// The temporary matrix.
  DenseMatrixRowMajor<ValType> matrix_tmp_;

  /// The vector E.
  DenseVector<ValType> vector_e_;

  /// The vector F.
  DenseVector<ValType> vector_f_;

  /// The SYEV engine.
  la::SyevDriver<DenseSymmetricMatrixRowMajor<ValType>, 'V'> syev_driver_;

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
  inline       DenseMatrixCollection120<ValType>& collectionQImpl() noexcept;
  inline const DenseMatrixCollection120<ValType>& collectionQImpl() const noexcept;
  inline       DenseMatrixRowMajor<ValType>& matrixQImpl() noexcept;
  inline const DenseMatrixRowMajor<ValType>& matrixQImpl() const noexcept;

};

/// @ingroup  isvd_integrator_module
template <typename _Val>
using NaiveKolmogorovNagumoIntegrator = Integrator<NaiveKolmogorovNagumoIntegratorTag, _Val>;

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_INTEGRATOR_NAIVE_KOLMOGOROV_NAGUMO_INTEGRATOR_HH_
