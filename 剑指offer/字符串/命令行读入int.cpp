// 空格分隔 换行结束

// 1、scantf

#include <iostream>
using namespace std;

int main()
{
  int x;
  while (scanf("%d", &x) != EOF)
  {
    printf("%d ", x);
  }

  return 0;
}

// 2、stringstream

#include <iostream>
#include <sstream>
#include <string>
using namespace std;

int main()
{
  string str;
  getline(cin, str);

  stringstream ss(str);

  int x;
  while (ss >> x)
  {
    printf("%d ", x);
  }

  return 0;
}

// 3、推荐写法：getline

#include <iostream>
#include <string>
using namespace std;

int main()
{
  string str;
  while (getline(cin, str, ' '))
  { // geline指定分隔符
    if (!str.empty())
      printf("%s ", str.c_str());
  }

  return 0;
}
