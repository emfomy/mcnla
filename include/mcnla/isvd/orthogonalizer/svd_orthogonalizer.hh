////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/orthogonalizer/svd_orthogonalizer.hh
/// @brief   The definition of SVD orthogonalizer.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_ORTHOGONALIZER_SVD_ORTHOGONALIZER_HH_
#define MCNLA_ISVD_ORTHOGONALIZER_SVD_ORTHOGONALIZER_HH_

#include <mcnla/isvd/def.hpp>
#include <mcnla/isvd/orthogonalizer/orthogonalizer.hpp>
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
/// @ingroup  isvd_orthogonalizer_module_detail
/// The SVD orthogonalizer tag.
///
struct SvdOrthogonalizerTag {};

/// @ingroup  isvd_orthogonalizer_module
template <typename _Val>
using SvdOrthogonalizer = Orthogonalizer<SvdOrthogonalizerTag, _Val>;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  isvd_orthogonalizer_module
/// The SVD orthogonalizer.
///
/// @tparam  _Val  The value type.
///
template <typename _Val>
class Orthogonalizer<SvdOrthogonalizerTag, _Val>
  : public OrthogonalizerWrapper<SvdOrthogonalizer<_Val>> {

  friend OrthogonalizerWrapper<SvdOrthogonalizer<_Val>>;

 private:

  using BaseType = OrthogonalizerWrapper<SvdOrthogonalizer<_Val>>;

 public:

  using ValType        = _Val;
  using RealValType = RealValT<ValType>;
  using MatrixType     = MatrixT<DenseMatrixCollection120<ValType>>;

  using ParametersType = Parameters<ValType>;

 protected:

  /// The name.
  static constexpr const char* name_= "SVD Orthogonalizer";

  /// The starting time
  double moment0_;

  /// The ending time of orthogonalization
  double moment1_;

  /// The vector S.
  DenseVector<RealValType> vector_s_;

  /// The empty matrix.
  MatrixType matrix_empty_;

  /// The random driver.
  la::GesvdDriver<MatrixType, 'O', 'N'> gesvd_driver_;

  using BaseType::parameters_;
  using BaseType::mpi_comm_;
  using BaseType::mpi_root_;

 public:

  // Constructor
  inline Orthogonalizer( const ParametersType &parameters,
                         const MPI_Comm mpi_comm, const mpi_int_t mpi_root ) noexcept;

  // Gets time
  inline double time1() const noexcept;
  inline double time2() const noexcept;

 protected:

  // Initializes
  void initializeImpl() noexcept;

  // Orthogonalizes
  void orthogonalizeImpl( DenseMatrixCollection120<ValType> &collection_q ) noexcept;

  // Outputs name
  inline std::ostream& outputNameImpl( std::ostream& os ) const noexcept;

  // Gets time
  inline double timeImpl() const noexcept;

};

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_ORTHOGONALIZER_SVD_ORTHOGONALIZER_HH_
