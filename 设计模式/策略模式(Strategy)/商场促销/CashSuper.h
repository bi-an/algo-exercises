#pragma once

// 策略公共接口
class CashSuper
{
 public:
  virtual double acceptCash(double money) = 0;
};

// 具体策略/算法
// 正常收费
class CashNormal : public CashSuper
{
 public:
  double acceptCash(double money) override
  {
    return money;
  }
};

// 打折收费
class CashRebate : public CashSuper
{
 public:
  CashRebate(double rebate) : m_moneyRebate(rebate) {}

  double acceptCash(double money) override
  {
    return money * m_moneyRebate;
  }

 private:
  double m_moneyRebate = 1.0;
};

// 满减返利收费
class CashReturn : public CashSuper
{
 public:
  CashReturn(double moneyCondition, double monyReturn) : m_moneyCondition(moneyCondition), m_moneyReturn(monyReturn) {}

  double acceptCash(double money) override
  {
    double result = money;
    if (money >= m_moneyCondition)
      result -= m_moneyReturn;
    return result;
  }

 private:
  double m_moneyCondition = 0.0;
  double m_moneyReturn = 0.0;
};