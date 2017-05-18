////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core_gpu/matrix/kit/array_gpu.hh
/// @brief   The definition of GPU value array class.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_GPU_MATRIX_KIT_ARRAY_GPU_HH_
#define MCNLA_CORE_GPU_MATRIX_KIT_ARRAY_GPU_HH_

#include <mcnla/core_gpu/matrix/def.hpp>
#include <mcnla/core/matrix/kit/array_base.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The MCNLA namespace.
//
namespace mcnla {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  The matrix namespace.
//
namespace matrix {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @ingroup  matrix_gpu_module
/// The GPU value array.
///
/// @tparam  _Val  The value type.
///
template <typename _Val>
class ArrI<CoreGpuTag, _Val> : public ArrayBase<CoreGpuTag, _Val> {

 private:

  using BaseType = ArrayBase<CoreGpuTag, _Val>;

 protected:

  using BaseType::size_;
  using BaseType::offset_;

 public:

  using BaseType::ArrayBase;

  // Constructors
  inline ArrI() noexcept;
  inline ArrI( const index_t size, const index_t offset = 0 ) noexcept;

  // Gets data
  inline       _Val& operator[]( const index_t idx ) noexcept = delete;
  inline const _Val& operator[]( const index_t idx ) const noexcept = delete;

};

/// @ingroup  matrix_gpu_module
template <typename _Val> using ArrayGpu = ArrI<CoreGpuTag, _Val>;

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_GPU_MATRIX_KIT_ARRAY_GPU_HH_
