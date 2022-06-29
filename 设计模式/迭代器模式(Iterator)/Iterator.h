/*
 * @Author: bi_an:desktop 2608120872@qq.com
 * @Date: 2020-04-26 20:30:38
 * @LastEditors: bi_an:desktop 2608120872@qq.com
 * @LastEditTime: 2022-06-17 17:49:39
 * @FilePath: \practice\设计模式\迭代器模式(Iterator)\Iterator.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#pragma once

#include <vector>
using namespace std;

// Iterator迭代器抽象类
class Iterator
{
 public:
  virtual void First() = 0;
  virtual void Next() = 0;
  virtual bool IsDone() = 0;
  virtual void CurrentItem() = 0;
};

// Aggregate聚集（集合）抽象类
class Aggregate
{
 public:
  virtual Iterator* CreateIterator() = 0;
};

// ConcreteIterator具体迭代器类
class ConcreteIterator : public Iterator
{
 public:
  ConcreteIterator(ConcreteAggregate *aggregate) : aggregate(aggregate) {}

  void First() override {

  }
  void Next() override {

  }
  bool IsDone() override {

  }
  void CurrentItem() override {
    
  }

 private:
  ConcreteAggregate *aggregate;
  int current = 0;
};

// 具体聚合（集合）类
class ConcreteAggregate : public Aggregate {
  vector<int> items;
  
public:
  Iterator* CreateIterator() override {
    return &ConcreteIterator(this); // TODO
  }
};