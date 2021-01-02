#pragma once
#include "Person.h"

// ������(Decorator)
class Finery : public Person
{
 public:
  // ���
  void Decorate(Person *person)
  { // ��̬�ԣ����봫��ָ��������ã����Զ��󴫵ݣ�������������ƹ�����һ����ʱ������󣬵�Ȼ�麯����Ҳ��һ����
    this->m_person = person;
  }

  void Show() override
  {
    if (m_person != nullptr)
      m_person->Show();
  }

 protected: // ���ݳ�Ա���ݸ�����
  Person *m_person = nullptr;
};

// ���������(ConcreteDecorator)
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