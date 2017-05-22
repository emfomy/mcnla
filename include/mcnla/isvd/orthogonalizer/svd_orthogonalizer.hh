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

#ifndef DOXYGEN_SHOULD_SKIP_THIS
struct SvdOrthogonalizerTag {};
template <typename _Val> using SvdOrthogonalizer = Orthogonalizer<SvdOrthogonalizerTag, _Val>;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  isvd_orthogonalizer_module
/// The SVD orthogonalizer.
///
/// @tparam  _Val  The value type.
///
template <typename _Val>
#ifndef DOXYGEN_SHOULD_SKIP_THIS
class Orthogonalizer<SvdOrthogonalizerTag, _Val>
#else  // DOXYGEN_SHOULD_SKIP_THIS
class SvdOrthogonalizer
#endif  // DOXYGEN_SHOULD_SKIP_THIS
  : public StageWrapper<SvdOrthogonalizer<_Val>> {

  friend StageWrapper<SvdOrthogonalizer<_Val>>;

 private:

  using BaseType = StageWrapper<SvdOrthogonalizer<_Val>>;

 public:

  using ValType     = _Val;
  using RealValType = RealValT<ValType>;
  using MatrixType  = MatrixT<DenseMatrixCollection201<ValType>>;

 protected:

  /// The name.
  static constexpr const char* name_ = "SVD Orthogonalizer";

  /// The name of each part of the stage.
  static constexpr const char* names_ = "orthogonalization";

  /// The vector S.
  DenseVector<RealValType> vector_s_;

  /// The empty matrix.
  MatrixType matrix_empty_;

  /// The GESVD driver.
  la::GesvdDriver<MatrixType, 'O', 'N'> gesvd_driver_;

  using BaseType::parameters_;
  using BaseType::initialized_;
  using BaseType::computed_;
  using BaseType::moments_;
  using BaseType::comm_times_;

 public:

  // Constructor
  inline Orthogonalizer( const Parameters<ValType> &parameters ) noexcept;

 protected:

  // Initializes
  void initializeImpl() noexcept;

  // Orthogonalizes
  void runImpl( DenseMatrixCollection201<ValType> &collection_q ) noexcept;

};

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_ORTHOGONALIZER_SVD_ORTHOGONALIZER_HH_
