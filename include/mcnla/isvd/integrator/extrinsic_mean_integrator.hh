////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/integrator/extrinsic_mean_integrator.hh
/// @brief   The definition of extrinsic mean integrator.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_INTEGRATOR_EXTRINSIC_MEAN_INTEGRATOR_HH_
#define MCNLA_ISVD_INTEGRATOR_EXTRINSIC_MEAN_INTEGRATOR_HH_

#include <mcnla/def.hpp>
#include <mcnla/isvd/def.hpp>
#include <mcnla/isvd/integrator/integrator.hpp>
#include <mcnla/core/lapack.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <class _Matrix> class ExtrinsicMeanIntegrator;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace isvd

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The traits namespace.
//
namespace traits {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The extrinsic mean integrator traits.
///
/// @tparam  _Matrix  The matrix type.
///
template <class _Matrix>
struct Traits<isvd::ExtrinsicMeanIntegrator<_Matrix>> {
  using MatrixType = _Matrix;
};

}  // namespace traits

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  isvd_integrator_module
///
/// The extrinsic mean integrator.
///
/// @tparam  _Matrix  The matrix type.
///
template <class _Matrix>
class ExtrinsicMeanIntegrator : public IntegratorBase<ExtrinsicMeanIntegrator<_Matrix>> {

  static_assert(std::is_base_of<MatrixBase<_Matrix>, _Matrix>::value, "'_Matrix' is not a matrix!");

  friend IntegratorBase<ExtrinsicMeanIntegrator<_Matrix>>;

 private:

  using BaseType = IntegratorBase<ExtrinsicMeanIntegrator<_Matrix>>;

 public:

  using ScalarType     = ScalarT<_Matrix>;
  using RealScalarType = RealScalarT<ScalarT<_Matrix>>;
  using MatrixType     = _Matrix;

 protected:

  /// The name.
  static constexpr const char* name_= "Extrinsic Mean Integrator";

  /// The parameters.
  const Parameters &parameters_ = BaseType::parameters_;

  /// The starting time
  double time0_;

  /// The ending time of rearrangeing Q
  double time1_;

  /// The ending time of computing B
  double time2_;

  /// The ending time of computing G
  double time3_;

  /// The ending time of rotating Qi
  double time4_;

  /// The ending time of average Qbar
  double time5_;

  /// The number of rows of the matrix per MPI node.
  index_t nrow_each_;

  /// The number of rows of the matrix of all MPI nodes.
  index_t nrow_all_;

  /// The collection Q.
  DenseMatrixCollection120<ScalarType> collection_q_;

  /// The cut collection Q.
  DenseMatrixCollection120<ScalarType> collection_q_cut_;

  /// The matrix Qjs.
  DenseMatrix<ScalarType, Layout::ROWMAJOR> matrix_qjs_;

  /// The matrix Qbar.
  DenseMatrix<ScalarType, Layout::ROWMAJOR> matrix_qbar_;

  /// The matrix Bjs.
  DenseMatrix<ScalarType, Layout::ROWMAJOR> matrix_bjs_;

  /// The matrix Bis.
  DenseMatrix<ScalarType, Layout::ROWMAJOR> matrix_bis_;

  /// The collection G.
  DenseMatrixCollection120<ScalarType> set_g_;

  /// The matrix G0.
  DenseMatrix<ScalarType, Layout::ROWMAJOR> matrix_g0_;

  /// The matrix GB (= G0 * B0i).
  DenseMatrix<ScalarType, Layout::ROWMAJOR> matrix_gb_;

  /// The vector S.
  DenseVector<ScalarType> vector_s_;

  /// The temporary matrix.
  DenseMatrix<ScalarType, Layout::ROWMAJOR> matrix_tmp_;

  /// The empty matrix.
  DenseMatrix<ScalarType, Layout::ROWMAJOR> matrix_empty_;

  /// The SYEV engine.
  lapack::SyevEngine<DenseMatrix<ScalarType, Layout::ROWMAJOR>, 'V'> syev_engine_;

  /// The GESVD engine.
  lapack::GesvdEngine<DenseMatrix<ScalarType, Layout::ROWMAJOR>, 'O', 'N'> gesvd_engine_;

 public:

  // Constructor
  inline ExtrinsicMeanIntegrator( const Parameters &parameters ) noexcept;

 protected:

  // Initializes
  void initializeImpl() noexcept;

  // Integrates
  void integrateImpl() noexcept;

  // Gets name
  inline constexpr const char* nameImpl() const noexcept;

  // Gets time
  inline double getTimeImpl() const noexcept;
  inline const std::vector<double> getTimesImpl() const noexcept;

  // Gets name
  inline index_t getIterImpl() const noexcept;

  // Gets matrices
  inline       DenseMatrixCollection120<ScalarType>& getCollectionQImpl() noexcept;
  inline const DenseMatrixCollection120<ScalarType>& getCollectionQImpl() const noexcept;
  inline       DenseMatrix<ScalarType, Layout::ROWMAJOR>& getMatrixQbarImpl() noexcept;
  inline const DenseMatrix<ScalarType, Layout::ROWMAJOR>& getMatrixQbarImpl() const noexcept;

};

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_INTEGRATOR_EXTRINSIC_MEAN_INTEGRATOR_HH_
