////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/reconstructor/standard_reconstructor.hpp
/// @brief   The standard reconstructor.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_RECONSTRUCTOR_STANDARD_RECONSTRUCTOR_HPP_
#define MCNLA_ISVD_RECONSTRUCTOR_STANDARD_RECONSTRUCTOR_HPP_

#include <mcnla/def.hpp>
#include <mcnla/isvd/def.hpp>
#include <mcnla/core/blas.hpp>
#include <mcnla/core/lapack.hpp>
#include <mcnla/isvd/reconstructor/reconstructor_base.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <class _Matrix> class StandardReconstructor;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace isvd

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The traits namespace.
//
namespace traits {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The standard reconstructor traits.
///
/// @tparam  _Matrix  The matrix type.
///
template <class _Matrix>
struct Traits<isvd::StandardReconstructor<_Matrix>> {
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
/// The standard reconstructor.
///
/// @tparam  _Matrix  The matrix type.
///
template <class _Matrix>
class StandardReconstructor : public ReconstructorBase<StandardReconstructor<_Matrix>> {

  friend ReconstructorBase<StandardReconstructor<_Matrix>>;

 private:

  using BaseType = ReconstructorBase<StandardReconstructor<_Matrix>>;

 public:

  using ScalarType     = typename _Matrix::ScalarType;
  using RealScalarType = typename _Matrix::RealScalarType;
  using MatrixType     = _Matrix;

  static_assert(std::is_base_of<MatrixBase<_Matrix>, _Matrix>::value, "'_Matrix' is not a matrix!");

 protected:

  /// The name.
  static constexpr const char* name_= "Standard Reconstructor";

  /// The parameters.
  const Parameters<ScalarType> &parameters_ = BaseType::parameters_;

  /// The matrix W.
  DenseMatrix<ScalarType, Layout::COLMAJOR> matrix_w_;

  /// The vector S.
  DenseVector<RealScalarType> vector_s_;

  /// The cut vector S.
  DenseVector<RealScalarType> vector_s_cut_;

  /// The matrix U.
  DenseMatrix<ScalarType, Layout::COLMAJOR> matrix_u_;

  /// The cut matrix U.
  DenseMatrix<ScalarType, Layout::COLMAJOR> matrix_u_cut_;

  /// The matrix Vt.
  DenseMatrix<ScalarType, Layout::COLMAJOR> matrix_vt_;

  /// The cut matrix Vt.
  DenseMatrix<ScalarType, Layout::COLMAJOR> matrix_vt_cut_;

  /// The empty vector.
  DenseVector<RealScalarType> vector_real_empty_;

  /// The empty matrix.
  DenseMatrix<ScalarType, Layout::COLMAJOR> matrix_empty_;

  /// The GESVD driver.
  lapack::GesvdDriver<DenseMatrix<ScalarType, Layout::COLMAJOR>, 'S', 'O'> gesvd_driver_;

 public:

  // Constructor
  inline StandardReconstructor( const Parameters<ScalarType> &parameters ) noexcept;

 protected:

  // Initializes
  void initializeImpl() noexcept;

  // Reconstructs
  void reconstructImpl( const _Matrix &matrix_a, const DenseMatrix<ScalarType, Layout::ROWMAJOR> &matrix_qc ) noexcept;

  // Gets name
  inline constexpr const char* getNameImpl() const noexcept;

  // Gets matrices
  inline const DenseVector<RealScalarType>& getVectorSImpl() const noexcept;
  inline const DenseMatrix<ScalarType, Layout::COLMAJOR>& getMatrixUImpl() const noexcept;
  inline const DenseMatrix<ScalarType, Layout::COLMAJOR>& getMatrixVtImpl() const noexcept;

};

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_RECONSTRUCTOR_STANDARD_RECONSTRUCTOR_HPP_
