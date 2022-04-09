#include <functional>  // std::less
#include <typeinfo>    // std::typeinfo

namespace ghan {

// Forward declarations.
template <typename _Tp, typename _Del>
class unique_ptr;  // TODO

class __weak_count;

class __shared_count;

class _Sp_counted_base {
  using _Atomic_word = int;

 public:
  _Sp_counted_base() noexcept : _M_use_count(1), _M_weak_count(1) {}

  virtual ~_Sp_counted_base() noexcept {}

  // Called when _M_use_count drops to zero, to release the resources
  // managed by *this.
  virtual void _M_dispose() noexcept = 0;

  // Called when _M_weak_count drops to zero.
  virtual void _M_destroy() noexcept { delete this; }

  virtual void* _M_get_deleter(const std::type_info&) noexcept = 0;

  inline void _M_add_ref_copy() { ++_M_use_count; }

  void _M_add_ref_lock();

  bool _M_add_ref_lock_nothrow();

  inline void _M_release() noexcept {
    if (--_M_use_count == 0) {
      _M_dispose();
      if (--_M_weak_count == 0) _M_destroy();
    }
  }

  inline void _M_weak_add_ref() noexcept { ++_M_weak_count; }

  inline void _M_weak_release() noexcept {
    if (--_M_weak_count == 0) _M_destroy();
  }

  inline long _M_get_use_count() const noexcept { return _M_use_count; }

 private:
  _Sp_counted_base(_Sp_counted_base const&) = delete;
  _Sp_counted_base& operator=(_Sp_counted_base const&) = delete;

  _Atomic_word _M_use_count;   // #shared
  _Atomic_word _M_weak_count;  // #weak + (#shared != 0)
};

// Counted ptr with no deleter or allocator support
template <typename _Ptr>
class _Sp_counted_ptr final : public _Sp_counted_base {
 public:
  explicit _Sp_counted_ptr(_Ptr __p) noexcept : _M_ptr(__p) {}

  virtual void _M_dispose() noexcept { delete _M_ptr; }

  virtual void _M_destroy() noexcept { delete this; }

  virtual void* _M_get_deleter(const std::type_info&) noexcept {
    return nullptr;
  }

  _Sp_counted_ptr(const _Sp_counted_ptr&) = delete;
  _Sp_counted_ptr& operator=(const _Sp_counted_ptr&) = delete;

 private:
  _Ptr _M_ptr;
};

class __shared_count {
 public:
  constexpr __shared_count() noexcept : _M_pi(0) {}

  template <typename _Ptr>
  explicit __shared_count(_Ptr __p) : _M_pi(0) {
    __try {
      _M_pi = new _Sp_counted_ptr<_Ptr>(__p);
    }
    __catch(...) {
      delete __p;
      __throw_exception_again;
    }
  }

  // Special case for unique_ptr<_Tp,_Del> to provide the strong guarantee.
  template <typename _Tp, typename _Del>
  explicit __shared_count(ghan::unique_ptr<_Tp, _Del>&& __r) : _M_pi(0) {
    // _GLIBCXX_RESOLVE_LIB_DEFECTS
    // 2415. Inconsistency between unique_ptr and shared_ptr
    if (__r.get() == nullptr) return;

    using _Ptr = typename unique_ptr<_Tp, _Del>::pointer;
    using _Del2 = typename conditional<
        is_reference<_Del>::value,
        reference_wrapper<typename remove_reference<_Del>::type>, _Del>::type;
    using _Sp_cd_type = _Sp_counted_deleter<_Ptr, _Del2, allocator<void>, _Lp>;
    using _Alloc = allocator<_Sp_cd_type>;
    using _Alloc_traits = allocator_traits<_Alloc>;
    _Alloc __a;
    _Sp_cd_type* __mem = _Alloc_traits::allocate(__a, 1);
    _Alloc_traits::construct(__a, __mem, __r.release(),
                             __r.get_deleter());  // non-throwing
    _M_pi = __mem;
  }

  // Throw bad_weak_ptr when __r._M_get_use_count() == 0.
  explicit __shared_count(const __weak_count& __r);

  ~__shared_count() noexcept {
    if (_M_pi != nullptr) _M_pi->_M_release();
  }

  __shared_count(const __shared_count& __r) noexcept : _M_pi(__r._M_pi) {
    if (_M_pi != 0) _M_pi->_M_add_ref_copy();
  }

  __shared_count& operator=(const __shared_count& __r) noexcept {
    _Sp_counted_base* __tmp = __r._M_pi;
    if (__tmp != _M_pi) {
      if (__tmp != 0) __tmp->_M_add_ref_copy();
      if (_M_pi != 0) _M_pi->_M_release();
      _M_pi = __tmp;
    }
    return *this;
  }

  void _M_swap(__shared_count& __r) noexcept {
    _Sp_counted_base* __tmp = __r._M_pi;
    __r._M_pi = _M_pi;
    _M_pi = __tmp;
  }

  long _M_get_use_count() const noexcept {
    return _M_pi != 0 ? _M_pi->_M_get_use_count() : 0;
  }

  bool _M_unique() const noexcept { return this->_M_get_use_count() == 1; }

  void* _M_get_deleter(const std::type_info& __ti) const noexcept {
    return _M_pi ? _M_pi->_M_get_deleter(__ti) : nullptr;
  }

  bool _M_less(const __shared_count& __rhs) const noexcept {
    return std::less<_Sp_counted_base*>()(this->_M_pi, __rhs._M_pi);
  }

  bool _M_less(const __weak_count& __rhs) const noexcept {
    return std::less<_Sp_counted_base*>()(this->_M_pi, __rhs._M_pi);
  }

  // Friend function injected into enclosing namespace and found by ADL
  friend inline bool operator==(const __shared_count& __a,
                                const __shared_count& __b) noexcept {
    return __a._M_pi == __b._M_pi;
  }

 private:
  friend class __weak_count;

  _Sp_counted_base* _M_pi;
};

class __weak_count {
 public:
  constexpr __weak_count() noexcept : _M_pi(nullptr) {}

  __weak_count(const __shared_count& __r) noexcept : _M_pi(__r._M_pi) {
    if (_M_pi != nullptr) _M_pi->_M_weak_add_ref();
  }

  __weak_count(const __weak_count& __r) noexcept : _M_pi(__r._M_pi) {
    if (_M_pi != nullptr) _M_pi->_M_weak_add_ref();
  }

  __weak_count(__weak_count&& __r) noexcept : _M_pi(__r._M_pi) {
    __r._M_pi = nullptr;
  }

  ~__weak_count() noexcept {
    if (_M_pi != nullptr) _M_pi->_M_weak_release();
  }

  __weak_count& operator=(const __shared_count& __r) noexcept {
    _Sp_counted_base* __tmp = __r._M_pi;
    if (__tmp != nullptr) __tmp->_M_weak_add_ref();
    if (_M_pi != nullptr) _M_pi->_M_weak_release();
    _M_pi = __tmp;
    return *this;
  }

  __weak_count& operator=(const __weak_count& __r) noexcept {
    _Sp_counted_base* __tmp = __r._M_pi;
    if (__tmp != nullptr) __tmp->_M_weak_add_ref();
    if (_M_pi != nullptr) _M_pi->_M_weak_release();
    _M_pi = __tmp;
    return *this;
  }

  __weak_count& operator=(__weak_count&& __r) noexcept {
    if (_M_pi != nullptr) _M_pi->_M_weak_release();
    _M_pi = __r._M_pi;
    __r._M_pi = nullptr;
    return *this;
  }

  void _M_swap(__weak_count& __r) noexcept {
    _Sp_counted_base* __tmp = __r._M_pi;
    __r._M_pi = _M_pi;
    _M_pi = __tmp;
  }

  long _M_get_use_count() const noexcept {
    return _M_pi != nullptr ? _M_pi->_M_get_use_count() : 0;
  }

  bool _M_less(const __weak_count& __rhs) const noexcept {
    return std::less<_Sp_counted_base*>()(this->_M_pi, __rhs._M_pi);
  }

  bool _M_less(const __shared_count& __rhs) const noexcept {
    return std::less<_Sp_counted_base*>()(this->_M_pi, __rhs._M_pi);
  }

  // Friend function injected into enclosing namespace and found by ADL
  friend inline bool operator==(const __weak_count& __a,
                                const __weak_count& __b) noexcept {
    return __a._M_pi == __b._M_pi;
  }

 private:
  friend class __shared_count;

  _Sp_counted_base* _M_pi;
};

// Now that __weak_count is defined we can define this constructor:
inline __shared_count::__shared_count(const __weak_count& __r)
    : _M_pi(__r._M_pi) {
  if (_M_pi != nullptr) _M_pi->_M_add_ref_lock();
  // else
  //   __throw_bad_weak_ptr();
}

template <typename _Tp>
class __shared_ptr /* : public __shared_ptr_access<_Tp> */ {
 public:
  using element_type = typename remove_extent<_Tp>::type;

 public:
  constexpr __shared_ptr() noexcept : _M_ptr(0), _M_refcount() {}

  explicit __shared_ptr(_Tp* __p) : _M_ptr(__p), _M_refcount(__p) {}

  template <ttypename _Deleter>
  __shared_ptr(_Tp* __p, _Deleter __d) : _M_ptr(__p), _M_refcount(__p) {}

  __shared_ptr(const __shared_ptr& __r, element_type* __p) noexcept
      : _M_ptr(__p),
        _M_refcount(__r._M_refcount)  // never throws
  {}

  __shared_ptr(const __shared_ptr&) noexcept = default;
  __shared_ptr& operator=(const __shared_ptr&) noexcept = default;
  ~__shared_ptr() = default;

  __shared_ptr(__shared_ptr&& __r) noexcept
      : _M_ptr(__r._M_ptr), _M_refcount() {
    _M_refcount._M_swap(__r._M_refcount);
    __r._M_ptr = 0;
  }

  explicit __shared_ptr(const __weak_ptr& __r)
      : _M_refcount(__r._M_refcount)  // may throw
  {
    // It is now safe to copy __r._M_ptr, as
    // _M_refcount(__r._M_refcount) did not throw.
    _M_ptr = __r._M_ptr;
  }

  // If an exception is thrown this constructor has no effect.
  template <typename _Del>
  __shared_ptr(unique_ptr<_Tp, _Del>&& __r) : _M_ptr(__r.get()), _M_refcount() {
    auto __raw = __to_address(__r.get());
    _M_refcount = __shared_count<_Lp>(std::move(__r));
    _M_enable_shared_from_this_with(__raw);
  }

  template <typename _Yp>
  _Assignable<_Yp> operator=(const __shared_ptr& __r) noexcept {
    _M_ptr = __r._M_ptr;
    _M_refcount = __r._M_refcount;  // __shared_count::op= doesn't throw
    return *this;
  }

  __shared_ptr& operator=(__shared_ptr&& __r) noexcept {
    __shared_ptr(std::move(__r)).swap(*this);
    return *this;
  }

  void reset() noexcept { __shared_ptr().swap(*this); }

  template <typename _Yp>
  _SafeConv<_Yp> reset(_Yp* __p)  // _Yp must be complete.
  {
    // Catch self-reset errors.
    __glibcxx_assert(__p == 0 || __p != _M_ptr);
    __shared_ptr(__p).swap(*this);
  }

  template <typename _Yp, typename _Deleter>
  _SafeConv<_Yp> reset(_Yp* __p, _Deleter __d) {
    __shared_ptr(__p, std::move(__d)).swap(*this);
  }

  template <typename _Yp, typename _Deleter, typename _Alloc>
  _SafeConv<_Yp> reset(_Yp* __p, _Deleter __d, _Alloc __a) {
    __shared_ptr(__p, std::move(__d), std::move(__a)).swap(*this);
  }

  element_type* get() const noexcept { return _M_ptr; }

  explicit operator bool() const  // never throws
  {
    return _M_ptr == 0 ? false : true;
  }

  bool unique() const noexcept { return _M_refcount._M_unique(); }

  long use_count() const noexcept { return _M_refcount._M_get_use_count(); }

  void swap(__shared_ptr<_Tp>& __other) noexcept {
    std::swap(_M_ptr, __other._M_ptr);
    _M_refcount._M_swap(__other._M_refcount);
  }

 protected:
  // This constructor is used by __weak_ptr::lock() and
  // shared_ptr::shared_ptr(const weak_ptr&, std::nothrow_t).
  __shared_ptr(const __weak_ptr<_Tp>& __r) : _M_refcount(__r._M_refcount) {
    _M_ptr = _M_refcount._M_get_use_count() ? __r._M_ptr : nullptr;
  }

 private:
  void* _M_get_deleter(const std::type_info& __ti) const noexcept {
    return _M_refcount._M_get_deleter(__ti);
  }

  friend class __weak_ptr;

  template <typename _Del, typename _Tp1, _Lock_policy _Lp1>
  friend _Del* get_deleter(const __shared_ptr<_Tp1, _Lp1>&) noexcept;

  template <typename _Del, typename _Tp1>
  friend _Del* get_deleter(const shared_ptr<_Tp1>&) noexcept;

  element_type* _M_ptr;        // Contained pointer.
  __shared_count _M_refcount;  // Reference counter.
};

template <typename _Tp, _Lock_policy _Lp>
class __weak_ptr {
  template <typename _Yp, typename _Res = void>
  using _Compatible =
      typename enable_if<__sp_compatible_with<_Yp*, _Tp*>::value, _Res>::type;

  // Constraint for assignment from shared_ptr and weak_ptr:
  template <typename _Yp>
  using _Assignable = _Compatible<_Yp, __weak_ptr&>;

 public:
  using element_type = typename remove_extent<_Tp>::type;

  constexpr __weak_ptr() noexcept : _M_ptr(nullptr), _M_refcount() {}

  __weak_ptr(const __weak_ptr&) noexcept = default;

  ~__weak_ptr() = default;

  // The "obvious" converting constructor implementation:
  //
  //  template<typename _Tp1>
  //    __weak_ptr(const __weak_ptr<_Tp1, _Lp>& __r)
  //    : _M_ptr(__r._M_ptr), _M_refcount(__r._M_refcount) // never throws
  //    { }
  //
  // has a serious problem.
  //
  //  __r._M_ptr may already have been invalidated. The _M_ptr(__r._M_ptr)
  //  conversion may require access to *__r._M_ptr (virtual inheritance).
  //
  // It is not possible to avoid spurious access violations since
  // in multithreaded programs __r._M_ptr may be invalidated at any point.
  template <typename _Yp, typename = _Compatible<_Yp>>
  __weak_ptr(const __weak_ptr<_Yp, _Lp>& __r) noexcept
      : _M_refcount(__r._M_refcount) {
    _M_ptr = __r.lock().get();
  }

  template <typename _Yp, typename = _Compatible<_Yp>>
  __weak_ptr(const __shared_ptr<_Yp, _Lp>& __r) noexcept
      : _M_ptr(__r._M_ptr), _M_refcount(__r._M_refcount) {}

  __weak_ptr(__weak_ptr&& __r) noexcept
      : _M_ptr(__r._M_ptr), _M_refcount(std::move(__r._M_refcount)) {
    __r._M_ptr = nullptr;
  }

  template <typename _Yp, typename = _Compatible<_Yp>>
  __weak_ptr(__weak_ptr<_Yp, _Lp>&& __r) noexcept
      : _M_ptr(__r.lock().get()), _M_refcount(std::move(__r._M_refcount)) {
    __r._M_ptr = nullptr;
  }

  __weak_ptr& operator=(const __weak_ptr& __r) noexcept = default;

  template <typename _Yp>
  _Assignable<_Yp> operator=(const __weak_ptr<_Yp, _Lp>& __r) noexcept {
    _M_ptr = __r.lock().get();
    _M_refcount = __r._M_refcount;
    return *this;
  }

  template <typename _Yp>
  _Assignable<_Yp> operator=(const __shared_ptr<_Yp, _Lp>& __r) noexcept {
    _M_ptr = __r._M_ptr;
    _M_refcount = __r._M_refcount;
    return *this;
  }

  __weak_ptr& operator=(__weak_ptr&& __r) noexcept {
    _M_ptr = __r._M_ptr;
    _M_refcount = std::move(__r._M_refcount);
    __r._M_ptr = nullptr;
    return *this;
  }

  template <typename _Yp>
  _Assignable<_Yp> operator=(__weak_ptr<_Yp, _Lp>&& __r) noexcept {
    _M_ptr = __r.lock().get();
    _M_refcount = std::move(__r._M_refcount);
    __r._M_ptr = nullptr;
    return *this;
  }

  __shared_ptr<_Tp, _Lp> lock() const noexcept {
    return __shared_ptr<element_type, _Lp>(*this, std::nothrow);
  }

  long use_count() const noexcept { return _M_refcount._M_get_use_count(); }

  bool expired() const noexcept { return _M_refcount._M_get_use_count() == 0; }

  template <typename _Tp1>
  bool owner_before(const __shared_ptr<_Tp1, _Lp>& __rhs) const noexcept {
    return _M_refcount._M_less(__rhs._M_refcount);
  }

  template <typename _Tp1>
  bool owner_before(const __weak_ptr<_Tp1, _Lp>& __rhs) const noexcept {
    return _M_refcount._M_less(__rhs._M_refcount);
  }

  void reset() noexcept { __weak_ptr().swap(*this); }

  void swap(__weak_ptr& __s) noexcept {
    std::swap(_M_ptr, __s._M_ptr);
    _M_refcount._M_swap(__s._M_refcount);
  }

 private:
  // Used by __enable_shared_from_this.
  void _M_assign(_Tp* __ptr, const __shared_count<_Lp>& __refcount) noexcept {
    if (use_count() == 0) {
      _M_ptr = __ptr;
      _M_refcount = __refcount;
    }
  }

  template <typename _Tp1, _Lock_policy _Lp1>
  friend class __shared_ptr;
  template <typename _Tp1, _Lock_policy _Lp1>
  friend class __weak_ptr;
  friend class __enable_shared_from_this<_Tp, _Lp>;
  friend class enable_shared_from_this<_Tp>;

  element_type* _M_ptr;           // Contained pointer.
  __weak_count<_Lp> _M_refcount;  // Reference counter.
};

}  // namespace ghan