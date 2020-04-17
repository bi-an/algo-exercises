#pragma once
#include <iostream>
#include <string>

// 原型接口类：声明一个自我复制的接口
class ICloneable
{
 public:
  virtual void *Clone() = 0; // 如果有指针，仅复制指针(浅拷贝)
};

// 工作经历类
class WorkExperience : public ICloneable
{
 public:
  std::string timeArea;
  std::string company;

  void *Clone() override
  {
    return new WorkExperience(*this);
  }
};

// 简历类
class Resume : public ICloneable
{
 public:
  Resume(std::string name) : name(name), work(nullptr) {}
  //Resume(const Resume& rhs):Resume(rhs.work) { // 注意：默认的复制构造函数进行浅拷贝
  //	// 其他的成员复制，或者放在初始化列表中

  //}
  ~Resume()
  {
    delete work;
  }

  // 设置个人信息
  void SetPersonalInfo(std::string sex, std::string age)
  {
    this->sex = sex;
    this->age = age;
  }
  // 设置工作经历
  void SetWorkExperience(std::string timeArea, std::string company)
  {
    if (work == nullptr)
      work = new WorkExperience();
    work->timeArea = timeArea;
    work->company = company;
  }
  // 浅拷贝
  void *Clone() override
  {
    Resume *result = new Resume(*this); // 默认的复制构造函数进行浅拷贝
    return result;
  }
  // 深拷贝
  void *Copy()
  {
    Resume *result = new Resume(*this);
    result->work = (WorkExperience *)work->Clone();
    return result;
  }
  void Display()
  {
    std::cout << name << std::endl;
    std::cout << sex << std::endl;
    std::cout << age << std::endl;
    std::cout << work->timeArea << " " << work->company << std::endl;
  }

 private:
  std::string name;
  std::string sex;
  std::string age;
  WorkExperience *work;

  // 私有构造函数，实现work的深拷贝
  Resume(WorkExperience *work)
  {
    this->work = (WorkExperience *)work->Clone();
    // 复制其他成员
  }
};
