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
#include <isvd/core/reconstructor_base.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

template <class _Matrix> class StandardReconstructor;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The internal namespace.
//
namespace internal {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The Gaussian projection reconstructor traits.
///
/// @tparam  _Matrix  The matrix type.
///
template <class _Matrix>
struct Traits<StandardReconstructor<_Matrix>> {
  using ScalarType     = typename _Matrix::ScalarType;
  using RealScalarType = typename _Matrix::RealScalarType;
  using MatrixType     = _Matrix;
};

}  // namespace internal

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The interface of iSVD reconstructor.
///
/// @tparam  _Matrix  The matrix type.
///
template <class _Matrix>
class StandardReconstructor : public internal::ReconstructorBase<StandardReconstructor<_Matrix>> {

  friend internal::ReconstructorBase<StandardReconstructor<_Matrix>>;

 private:

  using BaseType = internal::ReconstructorBase<StandardReconstructor<_Matrix>>;

 public:

  static const Layout layout = _Matrix::layout;
  using ScalarType     = typename _Matrix::ScalarType;
  using RealScalarType = typename _Matrix::RealScalarType;

  static_assert(std::is_same<DenseMatrix<ScalarType, layout>, _Matrix>::value, "'_Matrix' is not a dense matrix!");

 protected:

  /// The parameters.
  const internal::Parameters<ScalarType> &parameters_ = BaseType::parameters_;

  /// The matrix W.
  DenseMatrix<ScalarType, Layout::COLMAJOR> matrix_w_;

  /// The GESVD driver.
  lapack::GesvdDriver<DenseMatrix<ScalarType, Layout::COLMAJOR>, 'S', 'O'> gesvd_driver_;

  /// The empty matrix.
  DenseMatrix<ScalarType, Layout::COLMAJOR> matrix_empty_;

 public:

  // Constructor
  StandardReconstructor( const internal::Parameters<ScalarType> &parameters ) noexcept;

 protected:

  // Initializes
  void initializeImpl() noexcept;

  // Reconstructs
  void reconstructImpl( const _Matrix &matrix_a,
                        const DenseMatrix<ScalarType, Layout::ROWMAJOR> &matrix_q,
                              DenseVector<RealScalarType> &vector_s,
                              DenseMatrix<ScalarType, Layout::COLMAJOR> &matrix_u,
                              DenseMatrix<ScalarType, Layout::COLMAJOR> &matrix_vt ) noexcept;

};

}  // namespace isvd

#endif  // ISVD_CORE_RECONSTRUCTOR_STANDARD_RECONSTRUCTOR_HPP_
