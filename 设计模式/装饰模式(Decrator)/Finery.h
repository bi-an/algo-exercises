#pragma once
#include "Person.h"

// 服饰类(Decorator)
class Finery : public Person
{
 public:
  // 打扮
  void Decorate(Person *person)
  { // 多态性：必须传递指针或者引用；若以对象传递，则用子类对象复制构造了一个临时父类对象，当然虚函数表也不一样了
    this->m_person = person;
  }

  void Show() override
  {
    if (m_person != nullptr)
      m_person->Show();
  }

 protected: // 数据成员传递给子类
  Person *m_person = nullptr;
};

// 具体服饰类(ConcreteDecorator)
class TShirts : public Finery
{
 public:
  void Show() override
  {
    std::cout << "TShirts" << std::endl;
    doSomething();
    Finery::Show();
  }
  void doSomething() {}
};

class BigTrouser : public Finery
{
 public:
  void Show() override
  {
    std::cout << "BigTrouser" << std::endl;
    Finery::Show();
  }

 private:
  std::string something;
};

class Sneaker : public Finery
{
 public:
  void Show() override
  {
    std::cout << "Sneaker" << std::endl;
    Finery::Show();
  }
};

class Tie : public Finery
{
 public:
  void Show() override
  {
    std::cout << "Tie" << std::endl;
    Finery::Show();
  }
};

class Suit : public Finery
{
 public:
  void Show() override
  {
    std::cout << "Suit" << std::endl;
    Finery::Show();
  }
};