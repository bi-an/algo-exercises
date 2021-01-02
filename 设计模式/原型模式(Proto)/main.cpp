#include "ICloneable.h"

int main()
{
  Resume resume1("小明");
  resume1.SetPersonalInfo("男", "18");
  resume1.SetWorkExperience("2010-2012", "微软");

  resume1.Display();

  std::cout << "\n";

  Resume *resume2 = (Resume *)resume1.Copy(); // 深拷贝
  resume2->SetPersonalInfo("男", "25");
  resume2->SetWorkExperience("2018-2019", "谷歌");

  resume1.Display();
  std::cout << "\n";

  resume2->Display();
  std::cout << "\n";

  return 0;
}