////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/integrator/kolmogorov_nagumo_integrator.hh
/// @brief   The definition of Kolmogorov-Nagumo-type integrator.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_INTEGRATOR_KOLMOGOROV_NAGUMO_INTEGRATOR_HH_
#define MCNLA_ISVD_INTEGRATOR_KOLMOGOROV_NAGUMO_INTEGRATOR_HH_

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
/// @ingroup  isvd_integrator_module_detail
/// The Kolmogorov-Nagumo-type integrator tag.
///
struct KolmogorovNagumoIntegratorTag {};

/// @ingroup  isvd_integrator_module
template <typename _Val>
using KolmogorovNagumoIntegrator = Integrator<KolmogorovNagumoIntegratorTag, _Val>;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  isvd_integrator_module
/// The Kolmogorov-Nagumo-type integrator.
///
/// @tparam  _Val  The value type.
///
template <typename _Val>
class Integrator<KolmogorovNagumoIntegratorTag, _Val>
  : public IntegratorWrapper<KolmogorovNagumoIntegrator<_Val>> {

  friend IntegratorWrapper<KolmogorovNagumoIntegrator<_Val>>;

 private:

  using BaseType = IntegratorWrapper<KolmogorovNagumoIntegrator<_Val>>;

 public:

  using ValType        = _Val;

  using ParametersType = Parameters<ValType>;

 protected:

  /// The name.
  static constexpr const char* name_= "Kolmogorov-Nagumo-Type Integrator";

  /// The starting time
  double time0_;

  /// The ending time of rearrangeing Q
  double time1_;

  /// The ending time of integrating
  double time2_;

  /// The ending time of gathering Qc
  double time3_;

  /// The number of rows of the matrix per MPI node.
  index_t nrow_each_;

  /// The number of rows of the matrix of all MPI nodes.
  index_t nrow_all_;

  /// The collection Q.
  DenseMatrixCollection120<ValType> collection_q_;

  /// The cut collection Q.
  DenseMatrixCollection120<ValType> collection_q_cut_;

  /// The matrix Qs.
  DenseMatrixRowMajor<ValType> matrix_qs_;

  /// The matrix Qjs.
  DenseMatrixRowMajor<ValType> matrix_qjs_;

  /// The matrix Qc.
  DenseMatrixRowMajor<ValType> matrix_qc_;

  /// The cut matrix Qc.
  DenseMatrixRowMajor<ValType> matrix_qc_cut_;

  /// The matrix Qcj.
  DenseMatrixRowMajor<ValType> matrix_qcj_;

  /// The matrix Bs.
  DenseMatrixRowMajor<ValType> matrix_bs_;

  /// The matrix D.
  DenseMatrixRowMajor<ValType> matrix_d_;

  /// The matrix Z.
  DenseMatrixRowMajor<ValType> matrix_z_;

  /// The matrix C.
  DenseMatrixRowMajor<ValType> matrix_c_;

  /// The matrix Xj.
  DenseMatrixRowMajor<ValType> matrix_xj_;

  /// The temporary matrix.
  DenseMatrixRowMajor<ValType> matrix_tmp_;

  /// The vector E.
  DenseVector<ValType> vector_e_;

  /// The vector F.
  DenseVector<ValType> vector_f_;

  /// The SYEV driver.
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

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_INTEGRATOR_KOLMOGOROV_NAGUMO_INTEGRATOR_HH_
