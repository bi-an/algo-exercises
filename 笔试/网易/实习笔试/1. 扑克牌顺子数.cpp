#define _CRT_SECURE_NO_WARNINGS

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<int> card2num(vector<string> cards)
{
  vector<int> res;

  for (int i = 0; i < cards.size(); i++)
  {
    string card = cards[i];
    if (card == "A")
      res.push_back(1);
    else if (card == "J")
      res.push_back(11);
    else if (card == "Q")
      res.push_back(12);
    else if (card == "K")
      res.push_back(13);
    else
      res.push_back(atoi(card.c_str()));
  }
  sort(res.begin(), res.end());
  return res;
}

vector<vector<int>> getSequence(int hash[13])
{
  int begin = 0, end = 0, count = 0;
  vector<vector<int>> sequence; // 每一个元素保存顺子的开始、结束位置
  for (int i = 0; i < 13; i++)
  {
    if (hash[i] > 0)
    {
      count++;
      end = i;
    }
    else if (count < 5)
    {
      begin = i + 1;
    }
    else
    {
      end = i - 1;
      vector<int> tmp = { begin, end };
      sequence.push_back(tmp);
      begin = i + 1;
      //end = i;
      count = 0;
    }
  }

  if (count >= 5)
  {
    vector<int> tmp = { begin, end };
    sequence.push_back(tmp);
  }

  return sequence;
}

int numbersOfSequence(vector<int> cards)
{
  int res = 0;
  int hash[13] = {};

  for (int i = 0; i < cards.size(); i++)
  {
    hash[cards[i] - 1]++;
  }

  vector<vector<int>> sequence = getSequence(hash);

  for (int i = 0; i < sequence.size(); i++)
  {
    int times = 1;
    int begin = sequence[i][0], end = sequence[i][1];
    for (int j = begin; j <= end; j++)
    {
      times = times * hash[j]; // 每当有一种牌有n张重复，则需要扩大n倍
    }
    int num = end + 1 - begin;                    // 有num张连对
    int addition = (num - 4 + 1) * (num - 4) / 2; // 例如6,7,8,9,10,11,12, 则5连对(窗口大小为5)有3种，6连对有2种, 7连对有1种，即(1+2+3).
    res += times * addition;
  }

  return res;
}

int numbersOfSequence(vector<string> cards)
{
  vector<int> numbers = card2num(cards);
  int num = numbersOfSequence(numbers);
  return num;
}

int main()
{

  vector<string> cards;
  //cards.push_back("A");
  //cards.push_back("K");
  //cards.push_back("3");
  //cards.push_back("10");
  //cards.push_back("J");
  //cards.push_back("Q");
  cards.push_back("3");
  for (int i = 1; i <= 5; i++)
  {
    string tmp = to_string(i);
    cards.push_back(tmp);
  }
  for (int i = 7; i <= 12; i++)
  {
    string tmp = to_string(i);
    cards.push_back(tmp);
  }

  int num = numbersOfSequence(cards);

  return 0;
}