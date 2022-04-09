template <_Lock_policy _Lp = __default_lock_policy>
class _Sp_counted_base : public _Mutex_base<_Lp> {
 public:
  _Sp_counted_base() noexcept : _M_use_count(1), _M_weak_count(1) {}

  virtual ~_Sp_counted_base() noexcept {}

  // Called when _M_use_count drops to zero, to release the resources
  // managed by *this.
  virtual void _M_dispose() noexcept = 0;

  // Called when _M_weak_count drops to zero.
  virtual void _M_destroy() noexcept { delete this; }

  virtual void* _M_get_deleter(const std::type_info&) noexcept = 0;

  void _M_add_ref_copy() { __gnu_cxx::__atomic_add_dispatch(&_M_use_count, 1); }

  void _M_add_ref_lock();

  bool _M_add_ref_lock_nothrow();

  inline void _M_release() noexcept {
    if (--_M_use_count == 0) {
      _M_dispose();
      if (--_M_weak_count == 0) _M_destroy();
    }
  }

  void _M_weak_add_ref() noexcept {
    __gnu_cxx::__atomic_add_dispatch(&_M_weak_count, 1);
  }

  void _M_weak_release() noexcept {
    // Be race-detector-friendly. For more info see bits/c++config.
    _GLIBCXX_SYNCHRONIZATION_HAPPENS_BEFORE(&_M_weak_count);
    if (__gnu_cxx::__exchange_and_add_dispatch(&_M_weak_count, -1) == 1) {
      _GLIBCXX_SYNCHRONIZATION_HAPPENS_AFTER(&_M_weak_count);
      if (_Mutex_base<_Lp>::_S_need_barriers) {
        // See _M_release(),
        // destroy() must observe results of dispose()
        __atomic_thread_fence(__ATOMIC_ACQ_REL);
      }
      _M_destroy();
    }
  }

  long _M_get_use_count() const noexcept {
    // No memory barrier is used here so there is no synchronization
    // with other threads.
    return __atomic_load_n(&_M_use_count, __ATOMIC_RELAXED);
  }

 private:
  _Sp_counted_base(_Sp_counted_base const&) = delete;
  _Sp_counted_base& operator=(_Sp_counted_base const&) = delete;

  _Atomic_word _M_use_count;   // #shared
  _Atomic_word _M_weak_count;  // #weak + (#shared != 0)
};
