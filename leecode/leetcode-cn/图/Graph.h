#pragma once
#include <iostream>
#include <queue>
#include <set>
#include <vector>

class Node
{
 public:
  int val;
  std::vector<Node *> neighbors;

  Node() {}
  Node(int _val, vector<Node *> _neighbors) : val(_val), neighbors(_neighbors) {}
};

// 广度优先搜索BFS
// 访问一个顶点，接下来访问其所有邻居。
void printBroadFirstTraversal(Node *originVertex)
{
  if (originVertex == nullptr)
    return;

  std::queue<Node *> vertexQueue;
  std::set<Node *> visited;

  vertexQueue.push(originVertex);
  visited.emplace(originVertex);

  printf("%d\t", originVertex->val);
  // std::queue<Node*> traversalOrder;

  while (!vertexQueue.empty())
  {
    Node *frontVertex = vertexQueue.front();
    vertexQueue.pop();

    for (Node *nextNeighbor : frontVertex->neighbors)
    {
      if (visited.find(nextNeighbor) == visited.end())
      {
        printf("%d\t", nextNeighbor->val);
        visited.emplace(nextNeighbor);
        vertexQueue.push(nextNeighbor);
      }
    }
  }
}

std::queue<Node *> getBroadFirstTraversal(Node *originVertex)
{
  std::queue<Node *> traversalOrder;
  if (originVertex == nullptr)
    return traversalOrder;

  std::unordered_set<Node *> visited;
  visited.emplace(originVertex); // 标记originVertex已被访问
  std::queue<Node *> vertexQueue;
  vertexQueue.push(originVertex);
  traversalOrder.push(originVertex);

  while (!vertexQueue.empty())
  {
    Node *frontVertex = vertexQueue.front();
    vertexQueue.pop();
    for (Node *nextNeighbor : frontVertex->neighbors)
    {
      if (visited.find(nextNeighbor) == visited.end())
      {
        // 标记nextNeighbor已被访问
        visited.emplace(nextNeighbor);
        traversalOrder.push(nextNeighbor);
        vertexQueue.push(nextNeighbor);
      }
    }
  }

  return traversalOrder;
}

void printGraphInQueue(std::queue<Node *> graph)
{
  while (!graph.empty())
  {
    Node *p = graph.front();
    printf("%d\t", p->val);
    graph.pop();
  }
  printf("\n");
}

// 深度优先搜索DFS
// 访问一个顶点，接下来访问其中一个邻居，再访问邻居的邻居，知道没有邻居，然后后退，访问上一个顶点的另一个邻居。递归、栈。
std::queue<Node *> getDepthFirstTraversal(Node *originVertex)
{
  std::queue<Node *> traversalOrder;
  if (originVertex == nullptr)
    return traversalOrder;

  std::stack<Node *> vertexStack;
  std::set<Node *> visited;

  visited.emplace(originVertex);
  vertexStack.push(originVertex);
  traversalOrder.push(originVertex);

  while (!vertexStack.empty())
  {
    Node *topVertex = vertexStack.top();
    Node *nextNeighbor = nullptr;

    for (int i = 0; i < topVertex->neighbors.size(); i++)
    {
      if (visited.find(topVertex->neighbors[i]) == visited.end())
      {
        nextNeighbor = topVertex->neighbors[i];
        break;
      }
    }

    if (nextNeighbor != nullptr)
    { //如果存在没有被访问的节点
      visited.emplace(nextNeighbor);
      traversalOrder.push(nextNeighbor);
      vertexStack.push(nextNeighbor);
    }
    else
      vertexStack.pop();
  }

  return traversalOrder;
}
