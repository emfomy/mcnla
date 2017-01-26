////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/former/former_wrapper.hpp
/// @brief   The iSVD former wrapper.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_FORMER_FORMER_WRAPPER_HPP_
#define MCNLA_ISVD_FORMER_FORMER_WRAPPER_HPP_

#include <mcnla/isvd/former/former_wrapper.hh>

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
FormerWrapper<_Derived>::FormerWrapper(
    const ParametersType &parameters,
    const MPI_Comm mpi_comm,
    const mpi_int_t mpi_root
) noexcept
  : parameters_(parameters),
    mpi_comm_(mpi_comm),
    mpi_root_(mpi_root) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Initializes.
///
template <class _Derived>
void FormerWrapper<_Derived>::initialize() noexcept {
  this->derived().initializeImpl();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Forms SVD.
///
template <class _Derived> template <class _Matrix>
void FormerWrapper<_Derived>::form(
    const _Matrix &matrix_a,
    const DenseMatrixRowMajor<ScalarType> &matrix_q
) noexcept {
  this->derived().formImpl(matrix_a, matrix_q);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Output name to stream.
///
template <class __Derived>
std::ostream& operator<< (
    std::ostream &os,
    const FormerWrapper<__Derived> &wrapper
) {
  return wrapper.outputName(os);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  operator<<
///
template <class _Derived>
std::ostream& FormerWrapper<_Derived>::outputName(
    std::ostream &os
) const noexcept {
  return this->derived().outputNameImpl(os);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copydoc  mcnla::isvd::Driver::formerTime
///
template <class _Derived>
double FormerWrapper<_Derived>::time() const noexcept {
  return this->derived().timeImpl();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the vector S.
///
template <class _Derived>
const DenseVector<RealScalarT<ScalarT<_Derived>>>& FormerWrapper<_Derived>::vectorS() const noexcept {
  return this->derived().vectorSImpl();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the matrix U.
///
template <class _Derived>
const DenseMatrixColMajor<ScalarT<_Derived>>& FormerWrapper<_Derived>::matrixU() const noexcept {
  return this->derived().matrixUImpl();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the transpose of the matrix V.
///
template <class _Derived>
const DenseMatrixColMajor<ScalarT<_Derived>>& FormerWrapper<_Derived>::matrixVt() const noexcept {
  return this->derived().matrixVtImpl();
}

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_FORMER_FORMER_WRAPPER_HPP_
