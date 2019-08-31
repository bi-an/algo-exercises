#pragma once
#include <iostream>

// 画小人

// 绘图工具
class Graphics{
public:

};

class Pen{
public:

};

// 建造者接口
class PersonBuilder{
public:
	virtual void BuildHead()=0;
	virtual void BuildBody()=0;
	virtual void BuildArmLeft()=0;
	virtual void BuildArmRight()=0;
	virtual void BuildLegLeft()=0;
	virtual void BuildLegRight()=0;

protected:
	Graphics g;
	Pen p;
};

// 具体建造类(这里把具体建造和产品放到一起了)
// 瘦小人
class PersonThinBuilder : public PersonBuilder{
public:
	void BuildHead() override{
		std::cout << "Thin Header" << std::endl;
	}

	void BuildBody() override {
		std::cout << "Thin Body" << std::endl;
	}
	
	void BuildArmLeft() override {

	}

	void BuildArmRight() override {

	}

	void BuildLegLeft() override {

	}

	void BuildLegRight() override {

	}
};

// 胖小人
class PersonFatBuilder : public PersonBuilder {
public:
	void BuildHead() override {
		std::cout << "Fat Header" << std::endl;
	}

	void BuildBody() override {
		std::cout << "Fat Body" << std::endl;
	}

	void BuildArmLeft() override {

	}

	void BuildArmRight() override {

	}

	void BuildLegLeft() override {

	}

	void BuildLegRight() override {

	}
};

// 指挥者
class PersonDirector {
public:
	PersonDirector(PersonBuilder *pb) :pb(pb) {} // 用户告诉指挥者，需要什么样的小人
	void CreatePerson() {
		pb->BuildHead();
		pb->BuildBody();
		pb->BuildArmLeft();
		pb->BuildArmRight();
		pb->BuildLegLeft();
		pb->BuildLegRight();
	}

private:
	PersonBuilder *pb;
};