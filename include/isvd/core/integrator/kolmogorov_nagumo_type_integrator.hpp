////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/core/integrator/kolmogorov_nagumo_type_integrator.hpp
/// @brief   The Kolmogorov-Nagumo-type integrator.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_CORE_INTEGRATOR_KOLMOGOROV_NAGUMO_TYPE_INTEGRATOR_HPP_
#define ISVD_CORE_INTEGRATOR_KOLMOGOROV_NAGUMO_TYPE_INTEGRATOR_HPP_

#include <isvd/isvd.hpp>
#include <isvd/blas.hpp>
#include <isvd/lapack.hpp>
#include <isvd/core/integrator/integrator_base.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <class _Matrix> class KolmogorovNagumoTypeIntegrator;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The detail namespace.
//
namespace detail {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The Kolmogorov-Nagumo-type integrator traits.
///
/// @tparam  _Matrix  The matrix type.
///
template <class _Matrix>
struct Traits<KolmogorovNagumoTypeIntegrator<_Matrix>> {
  using MatrixType = _Matrix;
};

}  // namespace detail

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The Kolmogorov-Nagumo-type integrator.
///
/// @tparam  _Matrix  The matrix type.
///
template <class _Matrix>
class KolmogorovNagumoTypeIntegrator : public IntegratorBase<KolmogorovNagumoTypeIntegrator<_Matrix>> {

  friend IntegratorBase<KolmogorovNagumoTypeIntegrator<_Matrix>>;

 private:

  using BaseType = IntegratorBase<KolmogorovNagumoTypeIntegrator<_Matrix>>;

 public:

  using ScalarType     = typename _Matrix::ScalarType;
  using RealScalarType = typename _Matrix::RealScalarType;
  using MatrixType     = _Matrix;

  static_assert(std::is_base_of<MatrixBase<_Matrix>, _Matrix>::value, "'_Matrix' is not a matrix!");

 protected:

  /// The parameters.
  const Parameters<ScalarType> &parameters_ = BaseType::parameters_;

  /// The name.
  const char *name_ = "Kolmogorov-Nagumo-Type Integrator";

  /// The number of rows of the matrix per MPI node.
  index_t nrow_each_;

  /// The number of rows of the matrix of all MPI nodes.
  index_t nrow_all_;

  /// The cube Q.
  DenseCube<ScalarType, Layout::ROWMAJOR> cube_q_;

  /// The cut cube Q.
  DenseCube<ScalarType, Layout::ROWMAJOR> cube_q_cut_;

  /// The cube Qj.
  DenseCube<ScalarType, Layout::ROWMAJOR> cube_qj_;

  /// The matrix Qc.
  DenseMatrix<ScalarType, Layout::ROWMAJOR> matrix_qc_;

  /// The cut matrix Qc.
  DenseMatrix<ScalarType, Layout::ROWMAJOR> matrix_qc_cut_;

  /// The matrix Qcj.
  DenseMatrix<ScalarType, Layout::ROWMAJOR> matrix_qcj_;

  /// The cube B.
  DenseCube<ScalarType, Layout::ROWMAJOR> cube_b_;

  /// The matrix B.
  DenseMatrix<ScalarType, Layout::ROWMAJOR> matrix_b_;

  /// The matrix D.
  DenseMatrix<ScalarType, Layout::ROWMAJOR> matrix_d_;

  /// The matrix C.
  DenseMatrix<ScalarType, Layout::ROWMAJOR> matrix_c_;

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
  inline KolmogorovNagumoTypeIntegrator( const Parameters<ScalarType> &parameters ) noexcept;

 protected:

  // Initializes
  void initializeImpl() noexcept;

  // Integrates
  void integrateImpl() noexcept;

  // Gets name
  inline const char* getNameImpl() const noexcept;

  // Gets matrices
  inline DenseCube<ScalarType, Layout::ROWMAJOR>& getCubeQImpl() noexcept;
  inline DenseMatrix<ScalarType, Layout::ROWMAJOR>& getMatrixQcImpl() noexcept;

};

}  // namespace isvd

#endif  // ISVD_CORE_INTEGRATOR_KOLMOGOROV_NAGUMO_TYPE_INTEGRATOR_HPP_
