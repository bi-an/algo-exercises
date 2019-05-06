#pragma once
#include <iostream>
#include <list>

class Subject; // 发布者

// 观察者/订阅者接口
class Observer{
public:
	Observer(std::string name, Subject *sub) : name(name), sub(sub){}
	virtual void Update()=0; // 订阅者状态更新

protected:
	std::string name;
	Subject* sub;
};

// 具体订阅者
// 玩游戏的同事
class GameObserver : public Observer{
public:
	GameObserver(std::string name, Subject *sub) // 抽象发布者
		: Observer(name, sub)
	{}

	void Update() override{
		std::cout << name.c_str() << "关闭了游戏" << std::endl;
	}

};

// 看股票的同事
class StockObserver : public Observer{
public:
	StockObserver(std::string name, Subject *sub) 
		: Observer(name, sub)
	{

	}

	void Update() override {
		std::cout << name.c_str() << "关闭了股票行情" << std::endl;
	}
};


// 通知者/发布者接口
class Subject {
public:
	virtual void Attach(Observer *observer) = 0; // 增加订阅者
	virtual void Detach(Observer *observer) = 0; // 减少订阅者
	virtual void Notify() = 0;
};

// 具体发布者/通知者： 前台秘书、老板等
class Publisher : public Subject {
public:
	void Attach(Observer *observer) override { // 抽象观察者
		for (Observer* o : observers) { // 防止同一观察者添加多次 TODO: 效率低下
			if (o == observer)
				return;
		}
		observers.push_back(observer);
	}
	void Detach(Observer *observer) override {
		observers.remove(observer);
	}
	void Notify() override {
		for (Observer* o : observers)
			o->Update(); // 调用必须在Observer的定义式之后
	}

private:
	std::list<Observer*> observers; // 改用set是不是更好
};
