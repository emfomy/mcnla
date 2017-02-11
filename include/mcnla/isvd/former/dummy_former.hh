////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/former/dummy_former.hh
/// @brief   The definition of dummy former.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_FORMER_DUMMY_FORMER_HH_
#define MCNLA_ISVD_FORMER_DUMMY_FORMER_HH_

#include <mcnla/isvd/def.hpp>
#include <mcnla/isvd/former/former.hpp>
#include <mcnla/core/la.hpp>

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
/// The dummy former tag.
///
struct DummyFormerTag {};

/// @ingroup  isvd_former_module
template <typename _Val>
using DummyFormer = Former<DummyFormerTag, _Val>;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  isvd_former_module
/// The dummy former.
///
/// @tparam  _Val  The value type.
///
template <typename _Val>
class Former<DummyFormerTag, _Val>
  : public FormerWrapper<DummyFormer<_Val>> {

  friend FormerWrapper<DummyFormer<_Val>>;

 private:

  using BaseType = FormerWrapper<DummyFormer<_Val>>;

 public:

  using ValType        = _Val;
  using RealValType = RealValT<ValType>;

  using ParametersType = Parameters<ValType>;

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
  void formImpl( const _Matrix &matrix_a, const DenseMatrixRowMajor<ValType> &matrix_qc ) noexcept;

  // Outputs name
  inline std::ostream& outputNameImpl( std::ostream& os ) const noexcept;

  // Gets time
  inline double timeImpl() const noexcept;

  // Gets matrices
  inline const DenseVector<RealValType>& vectorSImpl() const noexcept;
  inline const DenseMatrixColMajor<ValType>& matrixUImpl() const noexcept;
  inline const DenseMatrixColMajor<ValType>& matrixVtImpl() const noexcept;

};

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_FORMER_DUMMY_FORMER_HH_
