#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
using namespace std;

void dfs_y(int i, int j, vector<string> &board)
{
  int n = board.size(), m = board[0].length();
  if (i >= 0 && i < n && j >= 0 && j < m && (board[i][j] == 'Y' || board[i][j] == 'G'))
  {
    if (board[i][j] == 'Y')
      board[i][j] = 'X'; // 如果要画的是'Y'，那么下一次不需要再画
    else if (board[i][j] == 'G')
      board[i][j] = 'B'; // 如果要画的是'G',那么下一次应该画'B'
                         // 连笔，因为Y是"\"，所以是左上和右下
    dfs_y(i - 1, j - 1, board);
    dfs_y(i + 1, j + 1, board);
  }
}

void dfs_b(int i, int j, vector<string> &board)
{
  int n = board.size(), m = board[0].length();
  if (i >= 0 && i < n && j >= 0 && j < m && (board[i][j] == 'B' || board[i][j] == 'G'))
  {
    if (board[i][j] == 'B')
      board[i][j] = 'X';
    else if (board[i][j] == 'G')
      board[i][j] = 'Y';
    // 连笔，因为B是"/"，所以是左下和右上
    dfs_b(i - 1, j + 1, board);
    dfs_b(i + 1, j - 1, board);
  }
}

void Trim(string &str)
{
  int left = 0;
  while (left < str.size() && str[left] == ' ')
    left++;
  str = str.substr(left, str.size() - left);
  int right = (int)str.size() - 1;
  while (right >= 0 && str[right] == ' ')
    right--;
  str = str.substr(0, right + 1);
}

int main()
{
  int N, M;
  scanf("%d%d", &N, &M);
  getchar();
  vector<string> board;
  for (int i = 0; i < N; i++)
  {
    string tmp;
    //char tmp[100];
    cin >> tmp;
    //scanf("%s", tmp);
    Trim(tmp);
    board.push_back(tmp);
  }

  int step = 0;
  for (int i = 0; i < N; i++)
  {
    for (int j = 0; j < M; j++)
    {
      if (board[i][j] == 'Y')
      {
        dfs_y(i, j, board);
        step++;
      }
      else if (board[i][j] == 'B')
      {
        dfs_b(i, j, board);
        step++;
      }
      else if (board[i][j] == 'G')
      {
        dfs_y(i, j, board);
        step++;
        dfs_b(i, j, board);
        step++;
      }
    }
  }

  printf("%d", step);

  return 0;
}