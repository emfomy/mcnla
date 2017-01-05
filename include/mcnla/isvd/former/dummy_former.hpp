////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/former/dummy_former.hpp
/// @brief   The dummy former.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_FORMER_DUMMY_FORMER_HPP_
#define MCNLA_ISVD_FORMER_DUMMY_FORMER_HPP_

#include <mcnla/def.hpp>
#include <mcnla/isvd/def.hpp>
#include <mcnla/isvd/former/former_base.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <class _Matrix> class DummyFormer;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

}  // namespace isvd

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The traits namespace.
//
namespace traits {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// The dummy former traits.
///
/// @tparam  _Matrix  The matrix type.
///
template <class _Matrix>
struct Traits<isvd::DummyFormer<_Matrix>> {
  using MatrixType = _Matrix;
};

}  // namespace traits

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  isvd_former_module
///
/// The dummy former.
///
/// @tparam  _Matrix  The matrix type.
///
template <class _Matrix>
class DummyFormer : public FormerBase<DummyFormer<_Matrix>> {

  static_assert(std::is_base_of<MatrixBase<_Matrix>, _Matrix>::value, "'_Matrix' is not a matrix!");

  friend FormerBase<DummyFormer<_Matrix>>;

 private:

  using BaseType = FormerBase<DummyFormer<_Matrix>>;

 public:

  using ScalarType     = ScalarT<_Matrix>;
  using RealScalarType = typename _Matrix::RealScalarType;
  using MatrixType     = _Matrix;

 protected:

  /// The name.
  static constexpr const char* name_= "Dummy Former";

  /// The parameters.
  const Parameters<ScalarType> &parameters_ = BaseType::parameters_;

 public:

  // Constructor
  inline DummyFormer( const Parameters<ScalarType> &parameters ) noexcept;

 protected:

  // Initializes
  void initializeImpl() noexcept;

  // Reconstructs
  void formImpl( const _Matrix &matrix_a, const DenseMatrix<ScalarType, Layout::ROWMAJOR> &matrix_qc ) noexcept;

  // Gets name
  inline constexpr const char* nameImpl() const noexcept;

  // Gets compute time
  inline double getTimeImpl() const noexcept;
  inline const std::vector<double> getTimesImpl() const noexcept;

  // Gets matrices
  inline const DenseVector<RealScalarType>& getVectorSImpl() const noexcept = delete;
  inline const DenseMatrix<ScalarType, Layout::COLMAJOR>& getMatrixUImpl() const noexcept = delete;
  inline const DenseMatrix<ScalarType, Layout::COLMAJOR>& getMatrixVtImpl() const noexcept = delete;

};

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_FORMER_DUMMY_FORMER_HPP_
