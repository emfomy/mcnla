////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/core/reconstructor/standard_reconstructor.hpp
/// @brief   The standard reconstructor.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_CORE_RECONSTRUCTOR_STANDARD_RECONSTRUCTOR_HPP_
#define ISVD_CORE_RECONSTRUCTOR_STANDARD_RECONSTRUCTOR_HPP_

#include <isvd/isvd.hpp>
#include <isvd/blas.hpp>
#include <isvd/lapack.hpp>
#include <isvd/core/reconstructor/reconstructor_base.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <class _Matrix> class StandardReconstructor;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The internal namespace.
//
namespace internal {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The standard reconstructor traits.
///
/// @tparam  _Matrix  The matrix type.
///
template <class _Matrix>
struct Traits<StandardReconstructor<_Matrix>> {
  using MatrixType = _Matrix;
};

}  // namespace internal

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The standard reconstructor.
///
/// @tparam  _Matrix  The matrix type.
///
template <class _Matrix>
class StandardReconstructor : public internal::ReconstructorBase<StandardReconstructor<_Matrix>> {

  friend internal::ReconstructorBase<StandardReconstructor<_Matrix>>;

 private:

  using BaseType = internal::ReconstructorBase<StandardReconstructor<_Matrix>>;

 public:

  using ScalarType     = typename _Matrix::ScalarType;
  using RealScalarType = typename _Matrix::RealScalarType;
  using MatrixType     = _Matrix;

  static_assert(std::is_base_of<internal::MatrixBase<_Matrix>, _Matrix>::value, "'_Matrix' is not a matrix!");

 protected:

  /// The parameters.
  const internal::Parameters<ScalarType> &parameters_ = BaseType::parameters_;

  /// The name.
  const char *name_ = "Standard Reconstructor";

  /// The matrix W.
  DenseMatrix<ScalarType, Layout::COLMAJOR> matrix_w_;

  /// The vector S.
  DenseVector<RealScalarType> vector_s_;

  /// The vector Sl.
  DenseVector<RealScalarType> vector_sl_;

  /// The matrix U.
  DenseMatrix<ScalarType, Layout::COLMAJOR> matrix_u_;

  /// The matrix Ul.
  DenseMatrix<ScalarType, Layout::COLMAJOR> matrix_ul_;

  /// The matrix Vt.
  DenseMatrix<ScalarType, Layout::COLMAJOR> matrix_vt_;

  /// The matrix Vlt.
  DenseMatrix<ScalarType, Layout::COLMAJOR> matrix_vlt_;

  /// The empty vector.
  DenseVector<RealScalarType> vector_real_empty_;

  /// The empty matrix.
  DenseMatrix<ScalarType, Layout::COLMAJOR> matrix_empty_;

  /// The GESVD driver.
  lapack::GesvdDriver<DenseMatrix<ScalarType, Layout::COLMAJOR>, 'S', 'O'> gesvd_driver_;

 public:

  // Constructor
  StandardReconstructor( const internal::Parameters<ScalarType> &parameters ) noexcept;

 protected:

  // Initializes
  void initializeImpl() noexcept;

  // Reconstructs
  void reconstructImpl( const _Matrix &matrix_a, const DenseMatrix<ScalarType, Layout::ROWMAJOR> &matrix_qc ) noexcept;

  // Gets name
  inline const char* getNameImpl() const noexcept;

  // Gets matrices
  inline const DenseVector<RealScalarType>& getSingularValuesImpl() const noexcept;
  inline const DenseMatrix<ScalarType, Layout::COLMAJOR>& getLeftSingularVectorsImpl() const noexcept;
  inline const DenseMatrix<ScalarType, Layout::COLMAJOR>& getRightSingularVectorsImpl() const noexcept;

};

}  // namespace isvd

#endif  // ISVD_CORE_RECONSTRUCTOR_STANDARD_RECONSTRUCTOR_HPP_
