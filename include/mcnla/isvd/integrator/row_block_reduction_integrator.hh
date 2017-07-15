////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/integrator/row_block_reduction_integrator.hh
/// @brief   The definition of reduction integrator (row-block version).
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_INTEGRATOR_ROW_BLOCK_REDUCTION_INTEGRATOR_HH_
#define MCNLA_ISVD_INTEGRATOR_ROW_BLOCK_REDUCTION_INTEGRATOR_HH_

#include <mcnla/isvd/def.hpp>
#include <mcnla/isvd/integrator/integrator.hpp>
#include <mcnla/core/la.hpp>

#ifndef DOXYGEN_SHOULD_SKIP_THIS
  #define MCNLA_ALIAS0 Integrator
  #define MCNLA_ALIAS1 Integrator<RowBlockReductionIntegratorTag, _Val>
#else  // DOXYGEN_SHOULD_SKIP_THIS
  #define MCNLA_ALIAS0 RowBlockReductionIntegrator
  #define MCNLA_ALIAS1 RowBlockReductionIntegrator
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
struct RowBlockReductionIntegratorTag {};
template <typename _Val> using RowBlockReductionIntegrator = Integrator<RowBlockReductionIntegratorTag, _Val>;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  isvd_integrator_module
/// The reduction integrator (row-block version).
///
/// @tparam  _Val  The value type.
///
template <typename _Val>
class MCNLA_ALIAS1
  : public StageWrapper<RowBlockReductionIntegrator<_Val>> {

  friend StageWrapper<RowBlockReductionIntegrator<_Val>>;

 private:

  using BaseType = StageWrapper<RowBlockReductionIntegrator<_Val>>;

 protected:

  /// The name.
  static constexpr const char* name_ = "Reduce-Sum Integrator (Row-Block Version)";

  /// The name of each part of the stage.
  static constexpr const char* names_ = "loop";

  /// The collection B.
  DenseMatrixCollectionRowBlockRowMajor<_Val> collection_b_;

  /// The matrix T.
  DenseMatrixColMajor<_Val> matrix_t_;

  /// The vector S.
  DenseVector<RealValT<_Val>> vector_s_;

  /// The temporary matrix.
  DenseMatrixRowMajor<_Val> matrix_tmp_;

  /// The empty matrix.
  DenseMatrixRowMajor<_Val> matrix_empty_;

  /// The GESVD driver.
  la::DenseGesvdDriverRowMajor<'O', 'S', _Val> gesvd_driver_;

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

  // Initializes
  void runImpl( DenseMatrixCollectionColBlockRowMajor<_Val> &collection_qj, DenseMatrixRowMajor<_Val> &matrix_qbarj ) noexcept;

};

}  // namespace isvd

}  // namespace mcnla

#undef MCNLA_ALIAS0
#undef MCNLA_ALIAS1

#endif  // MCNLA_ISVD_INTEGRATOR_ROW_BLOCK_REDUCTION_INTEGRATOR_HH_
