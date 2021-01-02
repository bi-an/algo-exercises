// 仿LISP运算：括号匹配

#include <bits/stdc++.h>
using namespace std;

string calc(string oper, int num1, int num2)
{
  int res;
  if (oper == "add")
  {
    res = num1 + num2;
  }
  else if (oper == "sub")
  {
    res = num1 - num2;
  }
  else if (oper == "mul")
  {
    res = num1 * num2;
  }
  else if (oper == "div")
  {
    if (num2 == 0)
      return "error";
    res = num1 / num2;
  }
  return to_string(res);
}

int main()
{
  string str;
  stack<string> operStack;
  stack<int> numStack;

  cin >> str;

  int mark = 0; // 子串的开始处
  for (int i = 0; i < str.size(); i++)
  {
    if (str[i] == '(')
    {
      operStack.push(str.substr(i, 3));
      mark++;
    }
    else if (str[i] == ')')
    {
      if (mark < i)
      { // 说明前面有非括号字符没有压栈
        numStack.push(atoi(str.substr(mark, i - mark).c_str()));
        mark = i + 1;
      }
    }
    else if(str[i]==' '){
      if(mark<i){
        
      }
    }
  }

  return 0;
}