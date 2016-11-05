////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/integrator/reduction_integrator.hpp
/// @brief   The reduction integrator.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_INTEGRATOR_REDUCTION_INTEGRATOR_HPP_
#define MCNLA_ISVD_INTEGRATOR_REDUCTION_INTEGRATOR_HPP_

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
template <class _Matrix> class ReductionIntegrator;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace isvd

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The traits namespace.
//
namespace traits {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The reduction integrator traits.
///
/// @tparam  _Matrix  The matrix type.
///
template <class _Matrix>
struct Traits<isvd::ReductionIntegrator<_Matrix>> {
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
/// The reduction integrator.
///
/// @tparam  _Matrix  The matrix type.
///
template <class _Matrix>
class ReductionIntegrator : public IntegratorBase<ReductionIntegrator<_Matrix>> {

  friend IntegratorBase<ReductionIntegrator<_Matrix>>;

 private:

  using BaseType = IntegratorBase<ReductionIntegrator<_Matrix>>;

 public:

  using ScalarType     = typename _Matrix::ScalarType;
  using RealScalarType = typename _Matrix::RealScalarType;
  using MatrixType     = _Matrix;

  static_assert(std::is_base_of<MatrixBase<_Matrix>, _Matrix>::value, "'_Matrix' is not a matrix!");

 protected:

  /// The name.
  static constexpr const char* name_= "Reduction Integrator";

  /// The parameters.
  const Parameters<ScalarType> &parameters_ = BaseType::parameters_;

  /// The cube Q.
  DenseCube<ScalarType, Layout::ROWMAJOR> cube_q_;

  /// The matrix Qbar.
  DenseMatrix<ScalarType, Layout::ROWMAJOR> matrix_q_bar_;

  /// The temporary matrix Q.
  DenseMatrix<ScalarType, Layout::ROWMAJOR> matrix_q_tmp_;

  /// The buffer matrix.
  DenseMatrix<ScalarType, Layout::ROWMAJOR> matrix_buffer_;

  /// The matrix U.
  DenseMatrix<ScalarType, Layout::ROWMAJOR> matrix_u_;

  /// The matrix Vt.
  DenseMatrix<ScalarType, Layout::ROWMAJOR> matrix_vt_;

  /// The vector S.
  DenseVector<ScalarType> vector_s_;

  /// The empty matrix.
  DenseMatrix<ScalarType, Layout::ROWMAJOR> matrix_empty_;

  /// The GESVD driver.
  lapack::GesvdDriver<DenseMatrix<ScalarType, Layout::ROWMAJOR>, 'O', 'S'> gesvd_driver_;

 public:

  // Constructor
  inline ReductionIntegrator( const Parameters<ScalarType> &parameters ) noexcept;

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

#endif  // MCNLA_ISVD_INTEGRATOR_REDUCTION_INTEGRATOR_HPP_
