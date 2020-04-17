// input : 1 5 22 0 0 14 0 31 0 0 9 8 0 98 0 0 7 0 0

//#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <queue>
using namespace std;

struct Node
{
  Node *leftChild;
  Node *rightChild;
  int key;
};

Node *initTree()
{
  int n = 0;
  std::cin >> n;
  if (n == 0)
    return nullptr;
  Node *p = new Node();
  p->key = n;
  p->leftChild = initTree();
  p->rightChild = initTree();
  return p;
}

int getResult(Node *pTree)
{
  if (pTree == nullptr)
    return 0;
  std::queue<Node *> Q;
  Q.push(pTree);
  int res = 0;
  bool flag = true;
  //int factor = 0;
  while (flag && !Q.empty())
  {
    //res++; //层数加1
    int width = Q.size();
    for (int i = 0; i < width; i++)
    {
      Node *p = Q.front();
      Q.pop();
      if (p->leftChild == nullptr && p->rightChild == nullptr)
      {
        //factor++;	//TODO
        res += p->key;
        flag = false;
      }
      else
      {
        if (p->leftChild)
          Q.push(p->leftChild);
        if (p->rightChild)
          Q.push(p->rightChild);
      }
    }
  }
  return res; //factor*res;
}

int main(int argc, const char *argv[])
{
  Node *rootNode = nullptr;
  rootNode = initTree();

  int res = getResult(rootNode);

  cout << res;

  return 0;
}
