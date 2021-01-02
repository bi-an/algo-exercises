#pragma once
#include <iostream>
#include <list>
#include <string>

// 组件抽象类
class Component
{
 public:
  Component(std::string name) : name(name) {}
  virtual ~Component()
  { // 虚析构函数是为了保证能对base指针正确析构
    //std::cout << name << ": ~Component()" << std::endl;
    std::cout << name << " 析构完成" << std::endl;
  }

  virtual void Add(std::shared_ptr<Component> c) = 0; // 不要用引用，因为要允许非左值：如果能够成功添加，那么就会转移指针的管理者，这是允许的
  virtual void Remove(std::shared_ptr<Component> c) = 0;
  virtual void Display(int depth) = 0;

 protected:
  std::string name;
};

// 叶子
class Leaf : public Component
{
 public:
  Leaf(std::string name) : Component(name) {}
  ~Leaf()
  {
    //std::cout << std::endl;
    //std::cout << name << " 开始析构: " << std::endl;
    //std::cout << name << ": " << "~Leaf()" << std::endl;
  }

  void Add(std::shared_ptr<Component> c) override
  {
    std::cout << "Cannot add to a leaf" << std::endl;
  }
  void Remove(std::shared_ptr<Component> c) override
  {
    std::cout << "Cannot remove from a leaf" << std::endl;
  }
  void Display(int depth)
  {
    std::cout << std::string(depth, '-') << name << std::endl; // 叶节点的显示：名称 级别
  }
};

// 非叶子节点(子树)
class Composite : public Component
{
 public:
  Composite(std::string name) : Component(name) {}
  ~Composite()
  {
    //std::cout << std::endl;
    //std::cout << name << " 开始析构: " << std::endl;
    //std::cout << name << ": ~Composite()"<<std::endl;
  }

  // 所添加的组件必须在堆上
  void Add(std::shared_ptr<Component> c) override
  {
    for (auto o : children) // 不允许对同一个对象添加多次
      if (o.get() == c.get())
        return;
    children.push_back(c);
  }
  void Remove(std::shared_ptr<Component> c) override
  {
    children.remove(c);
  }
  void Display(int depth) override
  {
    std::cout << std::string(depth, '-') << name << std::endl;
    for (std::shared_ptr<Component> c : children)
    {
      c->Display(depth + 2);
    }
  }

 private:
  std::list<std::shared_ptr<Component>> children;
};
