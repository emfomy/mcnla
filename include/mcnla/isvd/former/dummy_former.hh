////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/former/dummy_former.hh
/// @brief   The definition of dummy former.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_FORMER_DUMMY_FORMER_HH_
#define MCNLA_ISVD_FORMER_DUMMY_FORMER_HH_

#include <mcnla/def.hpp>
#include <mcnla/isvd/def.hpp>
#include <mcnla/isvd/former/former.hpp>
#include <mcnla/core/blas.hpp>
#include <mcnla/core/lapack.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  isvd_former_module
/// The dummy former tag.
///
struct DummyFormerTag {};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  isvd_former_module
///
/// The dummy former.
///
/// @tparam  _Scalar  The scalar type.
///
template <typename _Scalar>
class Former<_Scalar, DummyFormerTag>
  : public FormerWrapper<Former<_Scalar, DummyFormerTag>> {

  friend FormerWrapper<Former<_Scalar, DummyFormerTag>>;

 private:

  using BaseType = FormerWrapper<Former<_Scalar, DummyFormerTag>>;

 public:

  using ScalarType     = _Scalar;
  using RealScalarType = RealScalarT<ScalarType>;

  using ParametersType = Parameters<ScalarType>;

 protected:

  /// The name.
  static constexpr const char* name_= "Dummy Former";

 public:

  // Constructor
  inline Former( const ParametersType &parameters, const MPI_Comm mpi_comm, const mpi_int_t mpi_root ) noexcept;

 protected:

  // Initializes
  void initializeImpl() noexcept;

  // Forms SVD
  template <class _Matrix>
  void formImpl( const _Matrix &matrix_a, const DenseMatrixRowMajor<ScalarType> &matrix_qc ) noexcept;

  // Outputs name
  inline std::ostream& outputNameImpl( std::ostream& os ) const noexcept;

  // Gets time
  inline double timeImpl() const noexcept;

  // Gets matrices
  inline const DenseVector<RealScalarType>& vectorSImpl() const noexcept;
  inline const DenseMatrixColMajor<ScalarType>& matrixUImpl() const noexcept;
  inline const DenseMatrixColMajor<ScalarType>& matrixVtImpl() const noexcept;

};

/// @ingroup  isvd_former_module
template <typename _Scalar>
using DummyFormer = Former<_Scalar, DummyFormerTag>;

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_FORMER_DUMMY_FORMER_HH_
