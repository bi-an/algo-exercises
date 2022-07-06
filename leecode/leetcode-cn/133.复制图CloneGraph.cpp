/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;

    Node() {}

    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};
*/

// BFS
class Solution
{
 public:
  Node *cloneGraph(Node *node)
  {
    if (node == nullptr)
      return nullptr;
    queue<Node *> vertexQueue;
    unordered_map<Node *, Node *> hash; //key is old node, value is new node

    vertexQueue.push(node);
    Node *copy = new Node(node->val, {});
    hash[node] = copy;

    while (!vertexQueue.empty())
    {
      Node *frontVertex = vertexQueue.front();
      vertexQueue.pop();
      for (Node *nextNeighbor : frontVertex->neighbors)
      {
        if (hash.find(nextNeighbor) == hash.end())
        { //如果这个顶点没有访问过，那么它也没有被复制过
          hash[nextNeighbor] = new Node(nextNeighbor->val, {});
          vertexQueue.push(nextNeighbor);
        }
        hash[frontVertex]->neighbors.push_back(hash[nextNeighbor]);
      }
    }

    return copy;
  }
};

// DFS
class Solution
{
 public:
  Node *cloneGraph(Node *node)
  {
    if (node == nullptr)
      return nullptr;

    if (hash.find(node) == hash.end())
    {
      hash[node] = new Node(node->val, {});
      for (Node *nextNeighbor : node->neighbors)
      {
        hash[node]->neighbors.push_back(cloneGraph(nextNeighbor));
      }
    }
    return hash[node];
  }

 private:
  map<Node *, Node *> hash;
};

// DFS iteratively
class Solution
{
 public:
  Node *cloneGraph(Node *node)
  {
    if (node == nullptr)
      return nullptr;

    stack<Node *> vertexStack;
    unordered_map<Node *> hash;
    stack<int> idx; //记录当前顶点邻居的iterator

    Node *copy = new Node(node->val, {});
    vertexStack.push(node);
    hash[node] = copy;
    idx.push(0);

    while (!vertexStack.empty())
    {
      Node *topStack = vertexStack.top();
      for (Node *nextNeighbor : topStack->neighbors)
      {
        if (hash.find(nextNeighbor) == hash.end())
        {
          hash[topStack]->neighbors.push_back(new Node(nextNeighbor, {}));
          vertexStack.push(nextNeighbor);
          idx.push(0);
        }
        else
        {
          hash[topStack]->nextNeighbor.push_back(hash[nextNeighbor]);
          idx.top()++;
        }
      }
      if (idx.top() == topStack->neighbors.size())
      {
        vertexStack.pop();
        idx.pop();
      }
    }

    return copy;
  }
};