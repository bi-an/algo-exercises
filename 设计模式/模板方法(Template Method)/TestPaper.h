#pragma once
#include <iostream>
#include <string>

// ѡ�����Ծ�
class TestPaper
{
 public:
  void TestQuestion1()
  {
    std::cout << "Question1: �����˲�" << std::endl;
    std::cout << "Answer1: " << Answer1() << std::endl;
  }
  void TestQuestion2()
  {
    std::cout << "Question2: ����������" << std::endl;
    std::cout << "Answer2: " << Answer2() << std::endl;
  }
  void TestQuestion3()
  {
    std::cout << "Question3: ������" << std::endl;
    std::cout << "Answer1: " << Answer3() << std::endl;
  }
  void TestQuestion4()
  {
    std::cout << "Question4: �����˼�" << std::endl;
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

// ѧ��A�Ĵ��
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

// ѧ��B�Ĵ��
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
