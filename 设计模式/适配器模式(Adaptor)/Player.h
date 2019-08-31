#pragma once
#include <iostream>
#include <string>

// Target抽象类
class Player{
public:
	Player(std::string name): name(name){}
	virtual void Attack() = 0; // 进攻
	virtual void Defense() = 0; // 防守

protected:
	std::string name;
};

// 前锋
class Forwards : public Player{
public:
	Forwards(std::string name)
		: Player(name)
	{

	}	

	void Attack() override{
		printf("前锋 %s 进攻\n", name.c_str());
	}

	void Defense() override{
		printf("前锋 %s 防守\n", name.c_str());
	}
};

// 中锋
class Center : public Player{
public:
	Center(std::string name)
		: Player(name)
	{

	}	

	void Attack() override{
		printf("中锋 %s 进攻\n", name.c_str());
	}

	void Defense() override{
		printf("中锋 %s 防守\n", name.c_str());
	}
};

// 后卫
class Guards : public Player{
public:
	Guards(std::string name)
		: Player(name)
	{

	}	

	void Attack() override{
		printf("中锋 %s 进攻\n", name.c_str());
	}

	void Defense() override{
		printf("中锋 %s 防守\n", name.c_str());
	}
};


// 被适配者
// 该类可以与Player的行为不同
// 外籍中锋
class ForeignCenter{
public:
	void AttackForeign(){
		std::cout<<"外籍中锋 "<<name<<" 进攻"<<std::endl;
	}
	void DefenseForeign(){
		std::cout<<"外籍中锋 "<<name<<" 防守"<<std::endl;
	}

	std::string name;
};

// 适配器
// 翻译者类
class Translator : public Player{
public:
	Translator(std::string name) // 输入的是被翻译的外籍中锋名字
		:Player(name)
	{
		foreignCenter=new ForeignCenter;
		foreignCenter->name=name;
	}

	void Attack() override{
		foreignCenter->AttackForeign(); // 调用被适配者的方法，在外部看来，与一般的Player子类没有两样
	}

	void Defense() override{
		foreignCenter->DefenseForeign();
	}

private:
	ForeignCenter* 	foreignCenter;
};