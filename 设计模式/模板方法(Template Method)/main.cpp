#include "TestPaper.h"

int main()
{
  std::cout << "StudentA's Answer Paper: " << std::endl;
  TestPaper *studentA = new StudentA;
  studentA->Display();

  std::cout << "\n";

  std::cout << "StudentB's Answer Paper: " << std::endl;
  TestPaper *studentB = new StudentB;
  studentB->Display();

  return 0;
}