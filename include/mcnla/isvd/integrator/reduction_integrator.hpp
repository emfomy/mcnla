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
/// @ingroup  isvd_integrator_module
///
/// The reduction integrator.
///
/// @tparam  _Matrix  The matrix type.
///
template <class _Matrix>
class ReductionIntegrator : public IntegratorBase<ReductionIntegrator<_Matrix>> {

  static_assert(std::is_base_of<MatrixBase<_Matrix>, _Matrix>::value, "'_Matrix' is not a matrix!");

  friend IntegratorBase<ReductionIntegrator<_Matrix>>;

 private:

  using BaseType = IntegratorBase<ReductionIntegrator<_Matrix>>;

 public:

  using ScalarType     = ScalarT<_Matrix>;
  using RealScalarType = typename _Matrix::RealScalarType;
  using MatrixType     = _Matrix;
  using SetType        = DenseMatrixSet120<ScalarType>;

 protected:

  /// The name.
  static constexpr const char* name_= "Reduction Integrator";

  /// The parameters.
  const Parameters<ScalarType> &parameters_ = BaseType::parameters_;

  /// The set Q.
  DenseMatrixSet120<ScalarType> set_q_;

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
  lapack::GesvdEngine<DenseMatrix<ScalarType, Layout::ROWMAJOR>, 'O', 'S'> gesvd_driver_;

 public:

  // Constructor
  inline ReductionIntegrator( const Parameters<ScalarType> &parameters ) noexcept;

 protected:

  // Initializes
  void initializeImpl() noexcept;

  // Integrates
  void integrateImpl() noexcept;

  // Gets name
  inline constexpr const char* nameImpl() const noexcept;

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

#endif  // MCNLA_ISVD_INTEGRATOR_REDUCTION_INTEGRATOR_HPP_
