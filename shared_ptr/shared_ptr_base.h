namespace ghan {

/**
 * @brief 接口，维护两个引用计数
 * @c _M_use_count = #shared
 * @c _M_weak_count = #weak + (#shared != 0)
 *
 */
class _Sp_counted_base {
 public:
  _Sp_counted_base() noexcept : _M_use_count(1), _M_weak_count(1) {}

  virtual ~_Sp_counted_base() noexcept {}

  // Called when _M_use_count drops to zero, to release the resources
  // managed by *this.
  virtual void _M_dispose() noexcept = 0;

  // Called when _M_weak_count drops to zero.
  virtual void _M_destroy() noexcept { delete this; }

  void _M_release() noexcept {
    // TODO 原子操作
    if (--_M_use_count == 0) _M_dispose();

    // TODO 原子操作
    if (--_M_weak_count == 0) _M_destroy();
  }

  void _M_add_ref_copy() {
    // TODO 原子操作
    ++_M_use_count;
  }

  void _M_weak_add_ref() noexcept {
    // TODO 原子操作
    ++_M_weak_count;
  }

 private:
  // TODO 原子类型
  int _M_use_count;   // #shared
  int _M_weak_count;  // #weak + (#shared != 0)
};

/**
 * @brief 实现 _Sp_counted_ptr 接口
 * 
 * @tparam _Ptr 
 */
template <typename _Ptr>
class _Sp_counted_ptr final : public _Sp_counted_base {
 public:
  explicit _Sp_counted_ptr(_Ptr __p) noexcept : _M_ptr(__p) {}

  virtual void _M_dispose() noexcept { delete _M_ptr; }

  virtual void _M_destroy() noexcept { delete this; }

 private:
  _Ptr _M_ptr;
};

/**
 * @brief 维护弱引用计数。复制构造时，++weak_refcount
 *
 */
class __weak_count {
 public:
  constexpr __weak_count() noexcept : _M_pi(nullptr) {}

  __weak_count(const __shared_count& __r) noexcept : _M_pi(__r._M_pi) {
    if (_M_pi != nullptr) _M_pi->_M_weak_add_ref();  // ++weak_refcount
  }

  __weak_count(const __weak_count& __r) noexcept : _M_pi(__r._M_pi) {
    if (_M_pi != nullptr) _M_pi->_M_weak_add_ref();  // ++weak_refcount
  }

 private:
  friend class __shared_count;  // 友元，使得 __shared_count 可以访问任何成员
  _Sp_counted_base* _M_pi;
};

/**
 * @brief 维护强引用计数。复制构造时，++use_refcount
 *
 */
class __shared_count {
 public:
  constexpr __shared_count() noexcept : _M_pi(0) {}

  template <typename _Ptr>
  explicit __shared_count(_Ptr __p) : _M_pi(0) {
    _M_pi = new _Sp_counted_ptr;
  }

  __shared_count(const __shared_count& __r) noexcept : _M_pi(__r._M_pi) {
    if (_M_pi != 0) _M_pi->_M_add_ref_copy();  // ++use_refcount
  }

  ~__shared_count() {
    if (_M_pi != 0) _M_pi->_M_release();
  }

  explicit __shared_count(const __weak_count& __r) {}

 private:
  friend class __weak_count; // 友元，使得 __weak_count 可以访问所有成员
  _Sp_counted_base* _M_pi;
};

template <typename _Tp>
class __weak_ptr {
 public:
  __weak_ptr() : _M_ptr(nullptr), _M_refcount() {}

 private:
  _Tp* _M_ptr;
  __weak_count _M_refcount;
};

template <typename _Tp>
class __shared_ptr {
 public:
  constexpr __shared_ptr() noexcept : _M_ptr(0), _M_refcount() {}

  __shared_ptr(const __shared_ptr&) noexcept = default;

  explicit __shared_ptr(const __weak_ptr<_Tp>& __r)
      : _M_refcount(__r._M_refcount) {
    _M_ptr = __._M_ptr;
  }

  explicit __shared_ptr(_Tp* __p) : _M_ptr(__p), _M_refcount(__p) {}

 private:
  _Tp* _M_ptr;
  __shared_count _M_refcount;  // 对象：复制构造时，会调用该对象的复制构造函数
};

}  // namespace ghan