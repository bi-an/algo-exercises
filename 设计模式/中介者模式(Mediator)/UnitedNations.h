#pragma once
#include <iostream>
#include <string>

class Country; // 抽象同事类

// 中介接口
// 联合国类
class UnitedNations{
public:
	// 传递双方消息
	virtual void Declare(std::string message, Country* colleague)=0;
};

// 抽象同事类
// 国家类
class Country{
public:
	Country(UnitedNations* mediator)
		: mediator(mediator)
	{	}

protected:
	UnitedNations *mediator; // 中介
};

// 具体同事类
// 美国
class USA : public Country{
public:
	USA(UnitedNations *mediator)
		: Country(mediator) // 子类不能直接初始化基类成员，只能通过基类构造函数（原则：各自的构造函数初始化各自的成员）
	{	}

	// 发出声明
	void Declare(std::string message){
		mediator->Declare(message, this);
	}

	// 获得消息
	void GetMessage(std::string message){
		std::cout<<"美国获得对方消息: "<<message<<std::endl;
	}
};

class Iraq : public Country{
public:
	Iraq(UnitedNations *mediator)
		: Country(mediator)
	{	}

	// 发出声明
	void Declare(std::string message){
		mediator->Declare(message, this);
	}

	// 获得消息
	void GetMessage(std::string message){
		std::cout<<"伊拉克获得对方消息: "<<message<<std::endl;
	}
};

// 具体中介者类
// 联合国安理会
class UnitedNationsSecurityCouncil : public UnitedNations{
public:
	void Declare(std::string message, Country *colleague) override{
		if(colleague==colleague1)
			colleague2->GetMessage(message);
		else if(colleague==colleague2) // 该判断的作用是，如果都不相等，则不传话
			colleague1->GetMessage(message);
	}

	// 联合国安理会认识所有国家，所以可以直接设置
	// 其他国家之间相互不认识，但是都认识中介(联合国安理会)
	USA *colleague1=nullptr; // 可以直接设置
	Iraq *colleague2=nullptr;
};