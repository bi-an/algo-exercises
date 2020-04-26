#include <condition_variable>
#include <future>
#include <iostream>
#include <mutex>
#include <thread>
using namespace std;

// 测试
int g_order = 0; // 控制线程执行顺序

class rwlock
{
 private:
  condition_variable _rcon, _wcon; // 因为读队列可以同时唤醒（允许同时读），但是永远只能有一个写线程，故要读写队列分开（故用两个条件变量）
  mutex _lock;
  unsigned _reader, _writer; // 就绪/等待队列
  int _active; // 运行态，活动线程池，其绝对值表示活动线程数（大于0，当前线程都为读；小于0，当前线程为写（由于活动写线程只能有一个，所以小于0时只可能等于-1）；等于0，没有活动线程）
 public:
  void read_lock()
  {
    g_order = 2; // TODO: 测试完要删掉

    unique_lock<mutex> lk(_lock);      // 如果不能获得锁，则阻塞
    ++_reader;                         // 插入到读就绪队列中
    while (_active < 0 || _writer > 0) // 如果正在写或有写就绪线程，则进入就绪队列（FIFO，先就绪的先运行）
      _rcon.wait(lk); // 阻塞等待（依然在就绪队列中，或者说条件变量是就绪队列的维护者）并释放锁，要由其他线程通知才能结束等待并往下执行
    --_reader;        // 从读就绪队列中删除，
    ++_active;        // 并进入活动线程池中运行
  }
  void write_lock()
  {
    unique_lock<mutex> lk(_lock);
    ++_writer;           // 进入就绪队列
    while (_active != 0) // 如果正在读写，则等待
      _wcon.wait(lk);    // 就绪等待并释放锁
    --_writer;           // 从就绪队列中删除
    _active = -1;        // 进入运行态
  }
  void unlock()
  {
    unique_lock<mutex> lk(_lock);
    if (_active > 0)
    { // 释放读锁：当前的线程都为读，那么应该先全部读完再写
      --_active;
      if (_active == 0)
        _wcon.notify_one(); // 因为可以同时读，所以不需要通知读等待线程（此时如果存在读等待线程，它一定比写等待线程来得晚，应该写完再去唤醒）
    }
    else
    { // 释放写锁：活动线程为写或没有活动线程
      _active = 0;
      if (_writer > 0)
        _wcon
            .notify_one(); // 先检查写就绪队列，如果写队列中还有线程，则先唤醒它->TODO: 例如：时间线为"写1(执行)，读1(等待)，写2(等待)，写1完成，"，那么此时会先唤醒"写2"线程，而不是"读1"线程，违反了FIFO规则，导致如果写操作执行过程中，不断有写和读线程进入等待，那之前的"读1"线程就一直无法运行了。
      else if (_reader > 0)
        _rcon.notify_all(); // 唤醒读就绪队列上的所有线程
    }
  }
  rwlock() : _writer(0), _reader(0), _active(0) {}
};

// 测试
void fun1(rwlock *lock)
{
  //while (1) {
  lock->write_lock();
  cout << "Write 1" << endl;
  g_order = 1;
  this_thread::sleep_for(chrono::seconds(2));
  lock->unlock();
  //}
}

void fun2(rwlock *lock)
{ // 不能用左值引用，为什么？
  while (g_order != 1)
    ;
  cout << "Read 1" << endl;
  lock->read_lock();
  //g_order = 2;
  cout << "Reading 1 ... " << endl;
  this_thread::sleep_for(chrono::seconds(3));
  cout << "Read 1 done." << endl;
  lock->unlock();
}

void fun3(rwlock *lock, int id)
{
  while (g_order != 2)
    ;
  cout << "Write " << id << endl;
  lock->write_lock();
  cout << "Writing " << id << " ... " << endl;
  this_thread::sleep_for(chrono::seconds(1));
  cout << "Write " << id << " done." << endl;
  lock->unlock();
}

void fun4(rwlock *lock)
{
  while (g_order != 2)
    ;
  cout << "Write 3" << endl;
  lock->write_lock();
  cout << "Writing 3 ... " << endl;
  this_thread::sleep_for(chrono::seconds(1));
  cout << "Write 3 done." << endl;
  lock->unlock();
}

int main()
{
  rwlock lock;
  thread th1(fun1, &lock);
  //fun1(lock);
  thread th2(fun2, &lock); // 报错：fun2不能用左值引用，为什么？
  thread th4(fun3, &lock, 4);
  thread th5(fun3, &lock, 5);
  thread th6(fun3, &lock, 6);
  thread th7(fun3, &lock, 7);
  thread th8(fun3, &lock, 8);
  thread th9(fun3, &lock, 9);
  thread th10(fun3, &lock, 10);

  fun3(&lock, 3);

  th1.join(); // 必须join，不然fun1中的cout与main的控制台是不一样的？
  th2.join();
  th4.join();
  th5.join();
  th6.join();
  th7.join();
  th8.join();
  th9.join();
  th10.join();

  return 0;
}