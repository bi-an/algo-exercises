#pragma once
#include <iostream>
#include <string>

class Person {
public:
	Person(){}
	Person(std::string name) : m_name(name) {}
	virtual void Show() { // ���������װ�Σ�����ʾ
		std::cout << "Basic Show" << std::endl;
	}
private:
	std::string m_name;
};