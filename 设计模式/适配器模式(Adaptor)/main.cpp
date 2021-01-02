#include "Player.h"

int main()
{
  Forwards b("巴蒂尔");
  Guards m("麦克格雷迪");

  Translator ym("姚明"); // 在外部调用者看来，无论是实例化，还是调用过程，都与其他类型对象没有区别

  b.Attack();
  m.Defense();

  ym.Attack();
  ym.Defense();

  return 0;
}