////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/orthogonalizer/qr_orthogonalizer.hh
/// @brief   The definition of QR orthogonalizer.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_ORTHOGONALIZER_QR_ORTHOGONALIZER_HH_
#define MCNLA_ISVD_ORTHOGONALIZER_QR_ORTHOGONALIZER_HH_

#include <mcnla/isvd/def.hpp>
#include <mcnla/isvd/orthogonalizer/orthogonalizer.hpp>
#include <mcnla/core/la.hpp>

#ifndef DOXYGEN_SHOULD_SKIP_THIS
  #define MCNLA_ALIAS0 Orthogonalizer
  #define MCNLA_ALIAS1 Orthogonalizer<QrOrthogonalizerTag, _Val>
#else  // DOXYGEN_SHOULD_SKIP_THIS
  #define MCNLA_ALIAS0 QrOrthogonalizer
  #define MCNLA_ALIAS1 QrOrthogonalizer
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The iSVD namespace.
//
namespace isvd {

#ifndef DOXYGEN_SHOULD_SKIP_THIS
struct QrOrthogonalizerTag {};
template <typename _Val> using QrOrthogonalizer = Orthogonalizer<QrOrthogonalizerTag, _Val>;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  isvd_orthogonalizer_module
/// The QR orthogonalizer.
///
/// @tparam  _Val  The value type.
///
template <typename _Val>
class MCNLA_ALIAS1
  : public StageWrapper<QrOrthogonalizer<_Val>> {

  friend StageWrapper<QrOrthogonalizer<_Val>>;

 private:

  using BaseType = StageWrapper<QrOrthogonalizer<_Val>>;

 protected:

  /// The name.
  static constexpr const char* name_ = "QR Orthogonalizer";

  /// The name of each part of the stage.
  static constexpr const char* names_ = "orthogonalization";

  /// The vector Tau.
  DenseVector<_Val> vector_tau_;

  /// The empty matrix.
  DenseMatrixRowMajor<_Val> matrix_empty_;

  /// The GEQRFG driver.
  la::DenseGeqrfgDriverRowMajor<'O', 'N', _Val> geqrfg_driver_;

  using BaseType::parameters_;
  using BaseType::initialized_;
  using BaseType::computed_;
  using BaseType::moments_;
  using BaseType::comm_times_;

 public:

  // Constructor
  inline MCNLA_ALIAS0( const Parameters<_Val> &parameters ) noexcept;

 protected:

  // Initializes
  void initializeImpl() noexcept;

  // Orthogonalizes
  void runImpl( DenseMatrixCollectionColBlockRowMajor<_Val> &collection_q ) noexcept;

};

}  // namespace isvd

}  // namespace mcnla

#undef MCNLA_ALIAS0
#undef MCNLA_ALIAS1

#endif  // MCNLA_ISVD_ORTHOGONALIZER_QR_ORTHOGONALIZER_HH_
