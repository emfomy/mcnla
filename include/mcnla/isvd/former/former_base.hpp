////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/former/former_base.hpp
/// @brief   The iSVD former interface.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_FORMER_BASE_HPP_
#define MCNLA_ISVD_FORMER_BASE_HPP_

#include <mcnla/isvd/former/former_base.hh>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Construct with given parameters.
///
template <class _Derived>
FormerBase<_Derived>::FormerBase(
    const Parameters<ScalarType> &parameters
) noexcept : parameters_(parameters) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Initializes.
///
template <class _Derived>
void FormerBase<_Derived>::initialize() noexcept { this->derived().initializeImpl(); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Reconstructs SVD.
///
template <class _Derived>
void FormerBase<_Derived>::form(
    const MatrixType &matrix_a,
    const DenseMatrix<ScalarType, Layout::ROWMAJOR> &matrix_qc
) noexcept { this->derived().formImpl(matrix_a, matrix_qc); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::Solver::getFormerName
///
template <class _Derived>
constexpr const char* FormerBase<_Derived>::name() const noexcept {
  return this->derived().nameImpl();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::Solver::getFormerTime
///
template <class _Derived>
double FormerBase<_Derived>::getTime() const noexcept {
  return this->derived().getTimeImpl();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::Solver::getFormerTimes
///
template <class _Derived>
const std::vector<double> FormerBase<_Derived>::getTimes() const noexcept {
  return this->derived().getTimesImpl();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the vector S.
///
template <class _Derived>
const DenseVector<typename FormerBase<_Derived>::RealScalarType>&
    FormerBase<_Derived>::getVectorS() const noexcept {
  return this->derived().getVectorSImpl();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the matrix U.
///
template <class _Derived>
const DenseMatrix<ScalarT<FormerBase<_Derived>>, Layout::COLMAJOR>&
    FormerBase<_Derived>::getMatrixU() const noexcept {
  return this->derived().getMatrixUImpl();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the transpose of the matrix V.
///
template <class _Derived>
const DenseMatrix<ScalarT<FormerBase<_Derived>>, Layout::COLMAJOR>&
    FormerBase<_Derived>::getMatrixVt() const noexcept {
  return this->derived().getMatrixVtImpl();
}

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_FORMER_BASE_HPP_
