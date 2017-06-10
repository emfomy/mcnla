////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/isvd/integrator/row_block_reduce_sum_integrator.hh
/// @brief   The definition of reduce-sum integrator (row-block version).
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_ISVD_INTEGRATOR_ROW_BLOCK_REDUCE_SUM_INTEGRATOR_HH_
#define MCNLA_ISVD_INTEGRATOR_ROW_BLOCK_REDUCE_SUM_INTEGRATOR_HH_

#include <mcnla/isvd/def.hpp>
#include <mcnla/isvd/integrator/integrator.hpp>
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
struct RowBlockReduceSumIntegratorTag {};
template <typename _Val> using RowBlockReduceSumIntegrator = Integrator<RowBlockReduceSumIntegratorTag, _Val>;
#endif  // DOXYGEN_SHOULD_SKIP_THIS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  isvd_integrator_module
/// The reduce-sum integrator (row-block version).
///
/// @tparam  _Val  The value type.
///
template <typename _Val>
#ifndef DOXYGEN_SHOULD_SKIP_THIS
class Integrator<RowBlockReduceSumIntegratorTag, _Val>
#else  // DOXYGEN_SHOULD_SKIP_THIS
class RowBlockReduceSumIntegrator
#endif  // DOXYGEN_SHOULD_SKIP_THIS
  : public StageWrapper<RowBlockReduceSumIntegrator<_Val>> {

  friend StageWrapper<RowBlockReduceSumIntegrator<_Val>>;

 private:

  using BaseType = StageWrapper<RowBlockReduceSumIntegrator<_Val>>;

 protected:

  /// The name.
  static constexpr const char* name_ = "Reduce-Sum Integrator (Row-Block Version)";

  /// The name of each part of the stage.
  static constexpr const char* names_ = "loop";

  /// The collection B.
  DenseMatrixCollectionRowBlockRowMajor<_Val> collection_b_;

  /// The matrix W.
  DenseMatrixRowMajor<_Val> matrix_w_;

  /// The matrix Tt.
  DenseMatrixRowMajor<_Val> matrix_tt_;

  /// The vector S.
  DenseVector<_Val> vector_s_;

  /// The GESVD driver.
  la::GesvdDriver<DenseMatrixRowMajor<_Val>, 'V'> gesvd_driver_;

  using BaseType::parameters_;
  using BaseType::initialized_;
  using BaseType::computed_;
  using BaseType::moments_;
  using BaseType::comm_times_;

 public:

  // Constructor
  inline Integrator( const Parameters<_Val> &parameters ) noexcept;

 protected:

  // Initializes
  void initializeImpl() noexcept;

  // Initializes
  void runImpl( DenseMatrixCollectionColBlockRowMajor<_Val> &collection_qj, DenseMatrixRowMajor<_Val> &matrix_qbarj ) noexcept;

};

}  // namespace isvd

}  // namespace mcnla

#endif  // MCNLA_ISVD_INTEGRATOR_ROW_BLOCK_REDUCE_SUM_INTEGRATOR_HH_
