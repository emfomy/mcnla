////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/former/former_wrapper.hh
/// @brief   The definition of iSVD former wrapper.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_FORMER_FORMER_WRAPPER_HH_
#define MCNLA_ISVD_FORMER_FORMER_WRAPPER_HH_

#include <mcnla/isvd/def.hpp>
#include <iostream>
#include <mcnla/isvd/driver/parameters.hpp>
#include <mcnla/core/matrix.hpp>
#include <mcnla/core/utility/crtp.hpp>
#include <mcnla/core/utility/traits.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  isvd_former_module_detail
/// The iSVD former wrapper.
///
/// @tparam  _Derived  The derived type.
///
template <class _Derived>
class FormerWrapper : public utility::CrtpBase<_Derived, FormerWrapper<_Derived>> {

 public:

  using ValType = ValT<_Derived>;
  using RealValType = RealValT<ValType>;

  using ParametersType = Parameters<ValType>;

 protected:

  /// @copydoc  mcnla::isvd::Driver::parameters_
  const ParametersType &parameters_;

  /// @copydoc  mcnla::isvd::Driver::mpi_comm_
  const MPI_Comm mpi_comm_;

  /// @copydoc  mcnla::isvd::Driver::mpi_root_
  const mpi_int_t mpi_root_;

 protected:

  // Constructor
  inline FormerWrapper( const ParametersType &parameters,
                        const MPI_Comm mpi_comm, const mpi_int_t mpi_root ) noexcept;

  // Outputs name
  inline std::ostream& outputName( std::ostream &os ) const noexcept;

 public:

  // Initializes
  inline void initialize() noexcept;

  // Forms SVD
  template <class _Matrix>
  inline void form( const _Matrix &matrix_a, const DenseMatrixRowMajor<ValType> &matrix_q ) noexcept;

  // Operators
  template <class __Derived>
  friend inline std::ostream& operator<<( std::ostream &os, const FormerWrapper<__Derived> &wrapper );

  // Gets compute time
  inline double time() const noexcept;

  // Gets matrices
  inline const DenseVector<RealValType>& vectorS() const noexcept;
  inline const DenseMatrixColMajor<ValType>& matrixU() const noexcept;
  inline const DenseMatrixColMajor<ValType>& matrixVt() const noexcept;

};

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_FORMER_FORMER_WRAPPER_HH_
