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

// 被追求者
class SchoolGirl
{
 public:
  SchoolGirl(std::string name) : name(name) {}

  std::string name;
};

// 追求者类
class Pursuit : public GiveGift
{
 public:
  Pursuit(SchoolGirl *girl) : mm(girl) {}

  void GiveDolls() override
  {
    std::cout << mm->name << ", 送你洋娃娃" << std::endl;
  }
  void GiveFlowers() override
  {
    std::cout << mm->name << ", 送你鲜花" << std::endl;
  }
  void GiveChocolate() override
  {
    std::cout << mm->name << ", 送你巧克力" << std::endl;
  }

  SchoolGirl *mm;
};

// 代理类
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