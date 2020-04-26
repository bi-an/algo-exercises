#pragma once
#include "Investment.h"

// 基金类(外观Facade)
class Fund
{
 public:
  // 基金类需要了解所有的股票或其他投资方式的方法或属性
  // 进行组合，以备外界调用
  Fund()
  {
    stock1 = new Stock1;
    stock2 = new Stock2;
    stock3 = new Stock3;
    nd1 = new NationalDebt1;
    rt1 = new Realty1;
  }
  ~Fund()
  { // 如果不是用来作为基类，不应该使用虚析构函数
    delete stock1;
    delete stock2;
    delete stock3;
    delete nd1;
    delete rt1;
  }

  void BuyFund()
  {
    stock1->Buy();
    stock2->Buy();
    stock3->Buy();
    nd1->Buy();
    rt1->Buy();
  }

  void SellFund()
  {
    stock1->Sell();
    stock2->Sell();
    stock3->Sell();
    nd1->Sell();
    rt1->Sell();
  }

 private:
  Stock1 *stock1;
  Stock2 *stock2;
  Stock3 *stock3;
  NationalDebt1 *nd1;
  Realty1 *rt1;
};