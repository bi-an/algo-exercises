#include "GiveGift.h"
#include <iostream>
using namespace std;

int main()
{
  SchoolGirl mm("小红");
  Proxy proxy(&mm);

  proxy.GiveDolls();
  proxy.GiveChocolate();
  proxy.GiveFlowers();

  return 0;
}