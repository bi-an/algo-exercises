#include "Player.h"

int main()
{
  Forwards b("�͵ٶ�");
  Guards m("��˸��׵�");

  Translator ym("Ҧ��"); // ���ⲿ�����߿�����������ʵ���������ǵ��ù��̣������������Ͷ���û������

  b.Attack();
  m.Defense();

  ym.Attack();
  ym.Defense();

  return 0;
}