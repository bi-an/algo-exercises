#pragma once
#include <iostream>

class InvestBase
{
 public:
  virtual void Sell() = 0;
  virtual void Buy() = 0;
};

// 具体投资种类
class Stock1 : public InvestBase
{
 public:
  void Sell() override
  {
    std::cout << "Sell Stock1" << std::endl;
  }
  void Buy() override
  {
    std::cout << "Buy Stock1" << std::endl;
  }
};

class Stock2 : public InvestBase
{
 public:
  void Sell() override
  {
    std::cout << "Sell Stock2" << std::endl;
  }
  void Buy() override
  {
    std::cout << "Buy Stock2" << std::endl;
  }
};

class Stock3 : public InvestBase
{
 public:
  void Sell() override
  {
    std::cout << "Sell Stock3" << std::endl;
  }
  void Buy() override
  {
    std::cout << "Buy Stock3" << std::endl;
  }
};

class NationalDebt1 : public InvestBase
{
 public:
  void Sell() override
  {
    std::cout << "Sell NationalDebt1" << std::endl;
  }
  void Buy() override
  {
    std::cout << "Buy NationalDebt1" << std::endl;
  }
};

class NationalDebt2 : public InvestBase
{
 public:
  void Sell() override
  {
    std::cout << "Sell NationalDebt2" << std::endl;
  }
  void Buy() override
  {
    std::cout << "Buy NationalDebt2" << std::endl;
  }
};

class Realty1 : public InvestBase
{
 public:
  void Sell() override
  {
    std::cout << "Sell Realty1" << std::endl;
  }
  void Buy() override
  {
    std::cout << "Buy Realty1" << std::endl;
  }
};