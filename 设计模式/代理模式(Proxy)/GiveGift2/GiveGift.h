#pragma once
#include <iostream>
#include <string>

class GiveGift
{
 public:
  virtual void GiveDolls() = 0;
  virtual void GiveFlowers() = 0;
  virtual void GiveChocolate() = 0;
};

// ��׷����
class SchoolGirl
{
 public:
  SchoolGirl(std::string name) : name(name) {}

  std::string name;
};

// ׷������
class Pursuit : public GiveGift
{
 public:
  Pursuit(SchoolGirl *girl) : mm(girl) {}

  void GiveDolls() override
  {
    std::cout << mm->name << ", ����������" << std::endl;
  }
  void GiveFlowers() override
  {
    std::cout << mm->name << ", �����ʻ�" << std::endl;
  }
  void GiveChocolate() override
  {
    std::cout << mm->name << ", �����ɿ���" << std::endl;
  }

  SchoolGirl *mm;
};

// ������
class Proxy : public GiveGift
{
 public:
  Proxy(Pursuit *boy) : gg(boy) {}
  void GiveDolls() override
  {
    gg->GiveDolls();
  }
  void GiveFlowers() override
  {
    gg->GiveFlowers();
  }
  void GiveChocolate() override
  {
    gg->GiveChocolate();
  }

 private:
  Pursuit *gg;
};