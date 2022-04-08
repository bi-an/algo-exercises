/**
 * @file shared_ptr.h
 * @author zzg (2608120872@qq.com)
 * @brief minimum realization from gcc %shared_ptr
 * @version 0.1
 * @date 2022-04-08
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "shared_ptr_base.h"

namespace ghan {

template <typename _Tp>
class shared_ptr : public __shared_ptr<_Tp> {
 public:
  /**
   * @brief Construct an empty %shared_ptr.
   * @post use_count==0 && get()==0
   */
  constexpr shared_ptr() noexcept : __shared_ptr<_Tp>() {}

  shared_ptr(const shared_ptr&) noexcept = default;

  explicit shared_ptr(const weak_ptr<_Tp>& __r) : __shared_ptr<_Tp>(__r) {}

  friend class weak_ptr<_Tp>;
};

template <typename _Tp>
class weak_ptr : public __weak_ptr<_Tp> {
 public:
  constexpr weak_ptr() noexcept = default;

  weak_ptr(const shared_ptr<_Tp>& __r) noexcept : __weak_ptr<_Tp>(__r) {}

  shared_ptr<_Tp> lock() const noexcept { return shared_ptr<_Tp>(*this); }
};

}  // namespace ghan