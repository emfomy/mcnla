////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/isvd/core/reconstructor/dummy_reconstructor.hpp
/// @brief   The dummy reconstructor.
///
/// @author  Mu Yang <emfomy@gmail.com>
///

#ifndef ISVD_CORE_RECONSTRUCTOR_DUMMY_RECONSTRUCTOR_HPP_
#define ISVD_CORE_RECONSTRUCTOR_DUMMY_RECONSTRUCTOR_HPP_

#include <isvd/isvd.hpp>
#include <isvd/core/reconstructor/reconstructor_base.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <class _Matrix> class DummyReconstructor;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The detail namespace.
//
namespace detail {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dummy reconstructor traits.
///
/// @tparam  _Matrix  The matrix type.
///
template <class _Matrix>
struct Traits<DummyReconstructor<_Matrix>> {
  using MatrixType = _Matrix;
};

}  // namespace detail

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dummy reconstructor.
///
/// @tparam  _Matrix  The matrix type.
///
template <class _Matrix>
class DummyReconstructor : public ReconstructorBase<DummyReconstructor<_Matrix>> {

  friend ReconstructorBase<DummyReconstructor<_Matrix>>;

 private:

  using BaseType = ReconstructorBase<DummyReconstructor<_Matrix>>;

 public:

  using ScalarType     = typename _Matrix::ScalarType;
  using RealScalarType = typename _Matrix::RealScalarType;
  using MatrixType     = _Matrix;

  static_assert(std::is_base_of<MatrixBase<_Matrix>, _Matrix>::value, "'_Matrix' is not a matrix!");

 protected:

  /// The parameters.
  const Parameters<ScalarType> &parameters_ = BaseType::parameters_;

  /// The name.
  static constexpr const char* name_= "Dummy Reconstructor";

 public:

  // Constructor
  inline DummyReconstructor( const Parameters<ScalarType> &parameters ) noexcept;

 protected:

  // Initializes
  void initializeImpl() noexcept;

  // Reconstructs
  void reconstructImpl( const _Matrix &matrix_a, const DenseMatrix<ScalarType, Layout::ROWMAJOR> &matrix_qc ) noexcept;

  // Gets name
  inline constexpr const char* getNameImpl() const noexcept;

  // Gets matrices
  inline const DenseVector<RealScalarType>& getVectorSImpl() const noexcept = delete;
  inline const DenseMatrix<ScalarType, Layout::COLMAJOR>& getMatrixUImpl() const noexcept = delete;
  inline const DenseMatrix<ScalarType, Layout::COLMAJOR>& getMatrixVtImpl() const noexcept = delete;

};

}  // namespace isvd

#endif  // ISVD_CORE_RECONSTRUCTOR_DUMMY_RECONSTRUCTOR_HPP_
