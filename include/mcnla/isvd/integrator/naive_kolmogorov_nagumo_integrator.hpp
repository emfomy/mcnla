////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/integrator/naive_kolmogorov_nagumo_integrator.hpp
/// @brief   The naive Kolmogorov-Nagumo-type integrator.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_INTEGRATOR_NAIVE_KOLMOGOROV_NAGUMO_INTEGRATOR_HPP_
#define MCNLA_ISVD_INTEGRATOR_NAIVE_KOLMOGOROV_NAGUMO_INTEGRATOR_HPP_

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
template <class _Matrix> class NaiveKolmogorovNagumoIntegrator;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace isvd

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The traits namespace.
//
namespace traits {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The naive Kolmogorov-Nagumo-type integrator traits.
///
/// @tparam  _Matrix  The matrix type.
///
template <class _Matrix>
struct Traits<isvd::NaiveKolmogorovNagumoIntegrator<_Matrix>> {
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
/// The naive Kolmogorov-Nagumo-type integrator.
///
/// @tparam  _Matrix  The matrix type.
///
template <class _Matrix>
class NaiveKolmogorovNagumoIntegrator : public IntegratorBase<NaiveKolmogorovNagumoIntegrator<_Matrix>> {

  friend IntegratorBase<NaiveKolmogorovNagumoIntegrator<_Matrix>>;

 private:

  using BaseType = IntegratorBase<NaiveKolmogorovNagumoIntegrator<_Matrix>>;

 public:

  using ScalarType     = typename _Matrix::ScalarType;
  using RealScalarType = typename _Matrix::RealScalarType;
  using MatrixType     = _Matrix;

  static_assert(std::is_base_of<MatrixBase<_Matrix>, _Matrix>::value, "'_Matrix' is not a matrix!");

 protected:

  /// The name.
  static constexpr const char* name_= "Naive Kolmogorov-Nagumo-Type Integrator";

  /// The parameters.
  const Parameters<ScalarType> &parameters_ = BaseType::parameters_;

  /// The vector E.
  index_t iter_;

  /// The cube Q.
  DenseCube<ScalarType, Layout::ROWMAJOR> cube_q_;

  /// The matrix Qc.
  DenseMatrix<ScalarType, Layout::ROWMAJOR> matrix_qc_;

  /// The matrix B.
  DenseMatrix<ScalarType, Layout::ROWMAJOR> matrix_b_;

  /// The matrix D.
  DenseMatrix<ScalarType, Layout::ROWMAJOR> matrix_d_;

  /// The matrix C.
  DenseMatrix<ScalarType, Layout::ROWMAJOR> matrix_c_;

  /// The matrix X.
  DenseMatrix<ScalarType, Layout::ROWMAJOR> matrix_x_;

  /// The temporary matrix.
  DenseMatrix<ScalarType, Layout::ROWMAJOR> matrix_tmp_;

  /// The vector E.
  DenseVector<ScalarType> vector_e_;

  /// The SYEV driver.
  lapack::SyevDriver<DenseMatrix<ScalarType, Layout::ROWMAJOR>, 'V'> syev_driver_;

 public:

  // Constructor
  inline NaiveKolmogorovNagumoIntegrator( const Parameters<ScalarType> &parameters ) noexcept;

 protected:

  // Initializes
  void initializeImpl() noexcept;

  // Integrates
  void integrateImpl() noexcept;

  // Gets name
  inline constexpr const char* getNameImpl() const noexcept;

  // Gets name
  inline index_t getIterImpl() const noexcept;

  // Gets matrices
  inline       DenseCube<ScalarType, Layout::ROWMAJOR>& getCubeQImpl() noexcept;
  inline const DenseCube<ScalarType, Layout::ROWMAJOR>& getCubeQImpl() const noexcept;
  inline       DenseMatrix<ScalarType, Layout::ROWMAJOR>& getMatrixQbarImpl() noexcept;
  inline const DenseMatrix<ScalarType, Layout::ROWMAJOR>& getMatrixQbarImpl() const noexcept;

};

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_INTEGRATOR_NAIVE_KOLMOGOROV_NAGUMO_INTEGRATOR_HPP_
