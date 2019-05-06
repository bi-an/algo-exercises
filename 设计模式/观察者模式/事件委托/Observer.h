#pragma once
#include <functional>
#include <list>
#include <iostream>

// 方法一：函数对象
// 缺点：函数形式必须一样
// 这样，除了方法名称可以不一样，其他跟经典观察者模式没有什么两样
typedef std::function<void()> UpdateCallback;

// 方法二：可变参数模板
// 好像行不通

class Subject; // 发布者/通知者

// 订阅者/观察者接口
class Observer {
public:
	Observer(std::string name, Subject *sub)
		: name(name), sub(sub)
	{}

	virtual void RegisterUpdateCallback(UpdateCallback f) final {
		fCallback = f;
	}

	void Update() {
		fCallback();
	}

protected:
	UpdateCallback fCallback;
	std::string name;
	Subject *sub;
};

// 具体订阅者
// 玩游戏的同事
class GameObserver : public Observer{
public:
	GameObserver(std::string name, Subject *sub)
		: Observer(name, sub)
	{
		RegisterUpdateCallback(std::bind(&GameObserver::CloseGame, this));
	}

private:
	void CloseGame(){
		std::cout<<name.c_str()<<"关闭了游戏"<<std::endl;
	}
};

// 看股票的同事
class StockObserver : public Observer{
public:
	StockObserver(std::string name, Subject *sub) 
		: Observer(name, sub)
	{
		RegisterUpdateCallback(std::bind(&StockObserver::CloseStock, this));
	}

private:
	void CloseStock() {
		std::cout << name.c_str() << "关闭了股票行情" << std::endl;
	}
};


// 发布者接口
class Subject{
public:
	virtual void Attach(Observer *observer)=0;
	virtual void Detach(Observer *observer)=0;
	virtual void Notify()=0;
};

// 具体发布者
class Publisher : public Subject{
public:
	void Attach(Observer *observer) override{
		for(Observer* o : observers){
			if(o==observer)
				return;
		}
		observers.push_back(observer);
	}
	void Detach(Observer *observer) override{
		observers.remove(observer);
	}
	void Notify(){
		for(Observer* o : observers)
			o->Observer::Update(); // 只调用抽象订阅者的方法，防止具体订阅者也定义了Update同名方法
	}

private:
	std::list<Observer*> observers; // 好像可以放到基类中去
};