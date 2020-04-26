#pragma once
#include <iostream>
#include <string>

// 选择题试卷
class TestPaper
{
 public:
  void TestQuestion1()
  {
    std::cout << "Question1: 天龙八部" << std::endl;
    std::cout << "Answer1: " << Answer1() << std::endl;
  }
  void TestQuestion2()
  {
    std::cout << "Question2: 倚天屠龙记" << std::endl;
    std::cout << "Answer2: " << Answer2() << std::endl;
  }
  void TestQuestion3()
  {
    std::cout << "Question3: 还珠格格" << std::endl;
    std::cout << "Answer1: " << Answer3() << std::endl;
  }
  void TestQuestion4()
  {
    std::cout << "Question4: 天上人间" << std::endl;
    std::cout << "Answer2: " << Answer4() << std::endl;
  }

  void Display()
  {
    TestQuestion1();
    TestQuestion2();
    TestQuestion3();
    TestQuestion4();
  }

  virtual std::string Answer1()
  {
    return "";
  }
  virtual std::string Answer2()
  {
    return "";
  }
  virtual std::string Answer3()
  {
    return "";
  }
  virtual std::string Answer4()
  {
    return "";
  }
};

// 学生A的答卷
class StudentA : public TestPaper
{
 public:
  std::string Answer1() override
  {
    return "b";
  }
  std::string Answer2() override
  {
    return "c";
  }
  std::string Answer3() override
  {
    return "a";
  }
  std::string Answer4() override
  {
    return "d";
  }
};

// 学生B的答卷
class StudentB : public TestPaper
{
 public:
  std::string Answer1() override
  {
    return "a";
  }
  std::string Answer2() override
  {
    return "b";
  }
  std::string Answer3() override
  {
    return "c";
  }
  std::string Answer4() override
  {
    return "d";
  }
};
