////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    include/mcnla/core_gpu/matrix/kit/array_gpu.hh
/// @brief   The definition of GPU value array class.
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef MCNLA_CORE_GPU_MATRIX_KIT_ARRAY_GPU_HH_
#define MCNLA_CORE_GPU_MATRIX_KIT_ARRAY_GPU_HH_

#include <mcnla/core_gpu/matrix/kit/def.hpp>
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
/// @ingroup  matrix_kit_gpu_module
/// The GPU value array.
///
/// @tparam  _Val  The value type.
///
template <typename _Val>
#ifndef DOXYGEN_SHOULD_SKIP_THIS
class ArrS<GpuTag, _Val>
  : public ArrayBase<GpuTag, _Val> {
#else  // DOXYGEN_SHOULD_SKIP_THIS
class ArrayGpu
  : public ArrayBase_<GpuTag, _Val> {
#endif  // DOXYGEN_SHOULD_SKIP_THIS

 private:

  using BaseType = ArrayBase<GpuTag, _Val>;

 protected:

  using BaseType::size_;
  using BaseType::offset_;

 public:

  using BaseType::ArrayBase;

#ifdef DOXYGEN_SHOULD_SKIP_THIS
  /// @copydoc ArrayBase_::operator=
  ArrayGpu& operator=( const ArrayGpu &other );
#endif  // DOXYGEN_SHOULD_SKIP_THIS

  // Constructors
  inline ArrS() noexcept;
  inline ArrS( const index_t size, const index_t offset = 0 ) noexcept;

  // Gets data
  inline       _Val& operator[]( const index_t idx ) noexcept = delete;
  inline const _Val& operator[]( const index_t idx ) const noexcept = delete;

};

}  // namespace matrix

}  // namespace mcnla

#endif  // MCNLA_CORE_GPU_MATRIX_KIT_ARRAY_GPU_HH_
