#pragma once
#include <iostream>
#include <string>

class Person {
public:
	Person(){}
	Person(std::string name) : m_name(name) {}
	virtual void Show() { // 先完成所有装饰，才显示
		std::cout << "Basic Show" << std::endl;
	}
private:
	std::string m_name;
};