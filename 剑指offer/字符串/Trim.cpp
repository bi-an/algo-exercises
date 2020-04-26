#include <fstream>
#include <string>
#include <vector>

void Trim(std::string &str)
{
  if (str.empty())
    return;
  int pos = 0;
  while (pos < str.size() && str[pos] == ' ')
    pos++;
  if (str.size() == pos)
  {
    str.clear();
    return;
  }
  str = str.substr(pos, str.size() - pos);
  pos = (int)str.size() - 1;
  while (pos >= 0 && str[pos] == ' ')
    pos--;
  if (pos == -1)
  {
    str.clear();
    return;
  }
  str = str.substr(0, pos + 1);
}