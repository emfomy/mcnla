////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/integrator/extrinsic_mean_integrator.hh
/// @brief   The definition of extrinsic mean integrator.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_INTEGRATOR_EXTRINSIC_MEAN_INTEGRATOR_HH_
#define MCNLA_ISVD_INTEGRATOR_EXTRINSIC_MEAN_INTEGRATOR_HH_

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
/// The extrinsic mean integrator tag.
///
struct ExtrinsicMeanIntegratorTag {};

/// @ingroup  isvd_integrator_module
template <typename _Val>
using ExtrinsicMeanIntegrator = Integrator<ExtrinsicMeanIntegratorTag, _Val>;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  isvd_integrator_module
/// The extrinsic mean integrator.
///
/// @tparam  _Val  The value type.
///
template <typename _Val>
class Integrator<ExtrinsicMeanIntegratorTag, _Val>
  : public IntegratorWrapper<ExtrinsicMeanIntegrator<_Val>> {

  friend IntegratorWrapper<ExtrinsicMeanIntegrator<_Val>>;

 private:

  using BaseType = IntegratorWrapper<ExtrinsicMeanIntegrator<_Val>>;

 public:

  using ValType        = _Val;
  using RealValType = RealValT<_Val>;

  using ParametersType = Parameters<ValType>;

 protected:

  /// The name.
  static constexpr const char* name_= "Extrinsic Mean Integrator";

  /// The starting time
  double time0_;

  /// The ending time of rearranging Q
  double time1_;

  /// The ending time of computing B
  double time2_;

  /// The ending time of computing G
  double time3_;

  /// The ending time of rotating Qi
  double time4_;

  /// The ending time of average Q
  double time5_;

  /// The number of rows of the matrix per MPI node.
  index_t nrow_each_;

  /// The number of rows of the matrix of all MPI nodes.
  index_t nrow_all_;

  /// The collection Q.
  DenseMatrixCollection120<ValType> collection_q_;

  /// The cut collection Q.
  DenseMatrixCollection120<ValType> collection_q_cut_;

  /// The matrix Qjs.
  DenseMatrixRowMajor<ValType> matrix_qjs_;

  /// The matrix Qbar.
  DenseMatrixRowMajor<ValType> matrix_qbar_;

  /// The matrix Bjs.
  DenseMatrixRowMajor<ValType> matrix_bjs_;

  /// The collection Bi.
  DenseMatrixCollection102<ValType> collection_bi_;

  /// The collection Bi0.
  DenseMatrixCollection102<ValType> collection_bi0_;

  /// The collection G.
  DenseMatrixCollection120<ValType> collection_g_;

  /// The matrix G0.
  DenseMatrixRowMajor<ValType> matrix_g0_;

  /// The matrix GB (= G0 * Bi0').
  DenseMatrixRowMajor<ValType> matrix_gb_;

  /// The vector S.
  DenseVector<ValType> vector_s_;

  /// The temporary matrix.
  DenseMatrixRowMajor<ValType> matrix_tmp_;

  /// The empty matrix.
  DenseMatrixRowMajor<ValType> matrix_empty_;

  /// The SYEV driver.
  la::SyevDriver<DenseSymmetricMatrixRowMajor<ValType>, 'V'> syev_driver_;

  /// The GESVD driver.
  la::GesvdDriver<DenseMatrixRowMajor<ValType>, 'O', 'N'> gesvd_driver_;

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
  inline double time4() const noexcept;
  inline double time5() const noexcept;

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

#endif  // MCNLA_ISVD_INTEGRATOR_EXTRINSIC_MEAN_INTEGRATOR_HH_
