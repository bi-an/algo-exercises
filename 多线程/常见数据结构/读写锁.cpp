#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
using namespace std;

class rwlock {
private:
	condition_variable _rcon, _wcon; // 因为读队列可以同时唤醒（允许同时读），但是永远只能有一个写线程，故要读写队列分开（故用两个条件变量）
	mutex _lock;
	unsigned _reader, _writer; // 就绪/等待队列
	int	_active; // 运行态，活动线程池，其绝对值表示活动线程数（大于0，当前线程都为读；小于0，当前线程为写（由于活动写线程只能有一个，所以小于0时只可能等于-1）；等于0，没有活动线程）
public:
	void read_lock() {
		unique_lock<mutex> lk(_lock); // 如果不能获得锁，则阻塞
		++_reader; // 插入到读就绪队列中
		while (_active < 0 || _writer > 0) // 如果正在写或有写就绪线程，则进入就绪队列（FIFO，先就绪的先运行）
			_rcon.wait(lk); // 阻塞等待（依然在就绪队列中，或者说条件变量是就绪队列的维护者）并释放锁，要由其他线程通知才能结束等待并往下执行
		--_reader; // 从读就绪队列中删除，
		++_active; // 并进入活动线程池中运行
	}
	void write_lock() {
		unique_lock<mutex> lk(_lock);
		++_writer; // 进入就绪队列
		while (_active != 0) // 如果正在读写，则等待
			_wcon.wait(lk); // 就绪等待并释放锁
		--_writer; // 从就绪队列中删除
		_active = -1; // 进入运行态
	}
	void unlock() {
		unique_lock<mutex> lk(_lock);
		if (_active > 0) { // 释放读锁：当前的线程都为读，那么应该先全部读完再写
			--_active;
			if (_active == 0) _wcon.notify_one(); // 因为可以同时读，所以不需要通知读等待线程（此时如果存在读等待线程，它一定比写等待线程来得晚，应该写完再去唤醒）
		}
		else { // 释放写锁：活动线程为写或没有活动线程
			_active = 0;
			if (_writer > 0) _wcon.notify_one(); // 先检查写就绪队列，如果写队列中还有线程，则先唤醒它->TODO: 例如：时间线为"写1(执行)，读1(等待)，写2(等待)，写1完成，"，那么此时会先唤醒"写2"线程，而不是"读1"线程，违反了FIFO规则，导致如果写操作执行过程中，不断有写和读线程进入等待，那之前的"读1"线程就一直无法运行了。
			else if (_reader > 0) _rcon.notify_all(); // 唤醒读就绪队列上的所有线程
		}
	}
	rwlock() :_writer(0), _reader(0), _active(0) {}
};

int main() {


	return 0;
}