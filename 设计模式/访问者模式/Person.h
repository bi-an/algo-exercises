#pragma once
#include <iostream>
#include <string>
#include <set>
#include <typeinfo> // type_id   也可以使用__func__宏

class Action; // 访问者抽象类

// 元素抽象类(Element)
class Person{
public:
	virtual void Accept(Action *visitor)=0; // 没有使用Action, 所以这里只需要Action的前置声明
};

class Man;
class Woman;

// 访问者抽象类(Visitor)
// 状态、面对情况时的反应
class Action{
public:
	virtual void GetManConclusion(Man *concreteElementA)=0; // 这里没有使用Man, 所以只需要有Man的前置声明即可
	virtual void GetWomanConclusion(Woman *concreteElementB)=0;
};

// 如果元素不止“男人”和“女人”, 还需要添加其他元素，那么就需要修改Person以及Action和Action的实现者，不符合“开放-封闭”原则
// 访问者模式适用于数据结构相对稳定的系统
// 如果有相对稳定的数据结构(Element)，又有易于变化的算法(Visitor)，那么应该使用访问者模式
// 元素具体类
class Man : public Person {
public:
	void Accept(Action *visitor) override {
		visitor->GetManConclusion(this); // 使用了Action, 这里已经在Action的定义之后
	}
};

class Woman : public Person {
public:
	void Accept(Action *visitor) override {
		visitor->GetWomanConclusion(this);
	}
};

// 访问者具体类
class Success : public Action {
public:
	void GetManConclusion(Man *concreteElementA) {
		// typeid(*concreteElementA).name()使用了Man的对象(*concreteElement), 必须在Man的定义式之后
		// 即使只有typeid(Man)，也被认为是使用了Man，必须要有Man的定义式
		std::cout << const_cast<char*>(typeid(*concreteElementA).name()) + 6 << " " << const_cast<char*>(typeid(*this).name()) + 6 << "时，背后总有一个伟大的女人" << std::endl;
	}
	void GetWomanConclusion(Woman *conreteElementB) {
		std::cout << const_cast<char*>(typeid(*conreteElementB).name()) + 6 << " " << const_cast<char*>(typeid(*this).name()) + 6 << "时，背后总有一个不成功的男人" << std::endl;
	}
};

class Failing : public Action {
public:
	// 类似
};

// 添加访问者(例如结婚，谈恋爱等状态时，男人和女人的反应)时，直接定义访问者即可，其他不需要改动


// 对象结构类
// “男人”与“女人”在不同状态的对比
class ObjectStructure{
public:
	void Attach(Person *element){
		elements.insert(element); // 插入效率：指数
	}

	void Detach(Person *element){
		elements.erase(element); // 删除效率：指数
	}

	// 遍历方法
	void Display(Action *visitor){
		for(Person *e : elements)
			e->Accept(visitor);
	}

private:
	std::set<Person*> elements;
};

