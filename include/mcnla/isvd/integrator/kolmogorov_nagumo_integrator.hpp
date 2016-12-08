////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/integrator/kolmogorov_nagumo_integrator.hpp
/// @brief   The Kolmogorov-Nagumo-type integrator.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_INTEGRATOR_KOLMOGOROV_NAGUMO_INTEGRATOR_HPP_
#define MCNLA_ISVD_INTEGRATOR_KOLMOGOROV_NAGUMO_INTEGRATOR_HPP_

#include <mcnla/def.hpp>
#include <mcnla/isvd/def.hpp>
#include <mcnla/core/blas.hpp>
#include <mcnla/core/lapack.hpp>
#include <mcnla/isvd/integrator/integrator_base.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <class _Matrix> class KolmogorovNagumoIntegrator;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace isvd

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The traits namespace.
//
namespace traits {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The Kolmogorov-Nagumo-type integrator traits.
///
/// @tparam  _Matrix  The matrix type.
///
template <class _Matrix>
struct Traits<isvd::KolmogorovNagumoIntegrator<_Matrix>> {
  using MatrixType = _Matrix;
};

}  // namespace traits

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  isvd_module
///
/// The Kolmogorov-Nagumo-type integrator.
///
/// @tparam  _Matrix  The matrix type.
///
template <class _Matrix>
class KolmogorovNagumoIntegrator : public IntegratorBase<KolmogorovNagumoIntegrator<_Matrix>> {

  static_assert(std::is_base_of<MatrixBase<_Matrix>, _Matrix>::value, "'_Matrix' is not a matrix!");

  friend IntegratorBase<KolmogorovNagumoIntegrator<_Matrix>>;

 private:

  using BaseType = IntegratorBase<KolmogorovNagumoIntegrator<_Matrix>>;

 public:

  using ScalarType     = typename _Matrix::ScalarType;
  using RealScalarType = typename _Matrix::RealScalarType;
  using MatrixType     = _Matrix;

 protected:

  /// The name.
  static constexpr const char* name_= "Kolmogorov-Nagumo-Type Integrator";

  /// The parameters.
  const Parameters<ScalarType> &parameters_ = BaseType::parameters_;

  /// The starting time
  double time0_;

  /// The ending time of reforming Q
  double time1_;

  /// The ending time of integrating
  double time2_;

  /// The ending time of gathering Qc
  double time3_;

  /// The number of rows of the matrix per MPI node.
  index_t nrow_each_;

  /// The number of rows of the matrix of all MPI nodes.
  index_t nrow_all_;

  /// The number of iteration.
  index_t iter_;

  /// The set Q.
  DenseMatrixSet120<ScalarType> set_q_;

  /// The cut set Q.
  DenseMatrixSet120<ScalarType> set_q_cut_;

  /// The matrix Qs.
  DenseMatrix<ScalarType, Layout::ROWMAJOR> matrix_qs_;

  /// The matrix Qjs.
  DenseMatrix<ScalarType, Layout::ROWMAJOR> matrix_qjs_;

  /// The matrix Qc.
  DenseMatrix<ScalarType, Layout::ROWMAJOR> matrix_qc_;

  /// The cut matrix Qc.
  DenseMatrix<ScalarType, Layout::ROWMAJOR> matrix_qc_cut_;

  /// The matrix Qcj.
  DenseMatrix<ScalarType, Layout::ROWMAJOR> matrix_qcj_;

  /// The matrix Bs.
  DenseMatrix<ScalarType, Layout::ROWMAJOR> matrix_bs_;

  /// The matrix C.
  DenseMatrix<ScalarType, Layout::ROWMAJOR> matrix_c_;

  /// The matrix D.
  DenseMatrix<ScalarType, Layout::ROWMAJOR> matrix_d_;

  /// The matrix F.
  DenseMatrix<ScalarType, Layout::ROWMAJOR> matrix_f_;

  /// The matrix Xj.
  DenseMatrix<ScalarType, Layout::ROWMAJOR> matrix_xj_;

  /// The temporary matrix.
  DenseMatrix<ScalarType, Layout::ROWMAJOR> matrix_tmp_;

  /// The vector E.
  DenseVector<ScalarType> vector_e_;

  /// The SYEV driver.
  lapack::SyevDriver<DenseMatrix<ScalarType, Layout::ROWMAJOR>, 'V'> syev_driver_;

 public:

  // Constructor
  inline KolmogorovNagumoIntegrator( const Parameters<ScalarType> &parameters ) noexcept;

 protected:

  // Initializes
  void initializeImpl() noexcept;

  // Integrates
  void integrateImpl() noexcept;

  // Gets name
  inline constexpr const char* getNameImpl() const noexcept;

  // Gets time
  inline double getTimeImpl() const noexcept;
  inline const std::vector<double> getTimesImpl() const noexcept;

  // Gets name
  inline index_t getIterImpl() const noexcept;

  // Gets matrices
  inline       DenseMatrixSet120<ScalarType>& getSetQImpl() noexcept;
  inline const DenseMatrixSet120<ScalarType>& getSetQImpl() const noexcept;
  inline       DenseMatrix<ScalarType, Layout::ROWMAJOR>& getMatrixQbarImpl() noexcept;
  inline const DenseMatrix<ScalarType, Layout::ROWMAJOR>& getMatrixQbarImpl() const noexcept;

};

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_INTEGRATOR_KOLMOGOROV_NAGUMO_INTEGRATOR_HPP_
