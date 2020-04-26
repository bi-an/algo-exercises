class some_data
{
  int a;
  std::string b;

 public:
  void do_some_thing();
};

class data_wrapper
{
  some_data data;
  std::mutex m;

 public:
  template <typename Function>
  void process_data(Function func)
  {
    std::lock_guard<std::mutex> lock(m);
    func(data); // 危险！！！用func操作数据！你不知道func会对数据做什么！
  }
};

some_data *unprotected;
void malicious_function(some_data &protected_data)
{
  unprotected = &protected_data; // 恶意函数！！！
}

data_wrapper x;
void foo()
{
  x.process_data(malicious_function); // 传入了一个恶意函数
  unprotected->do_some_thing();       // 现在可以跳过锁定，而直接操作data_wrapper中受保护的数据成员data了。
}