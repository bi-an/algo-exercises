#pragma once
#include <iostream>
#include <queue>

template <typename T>
class BinarySearchTree
{
 public:
  BinarySearchTree() {}
  BinarySearchTree(const BinarySearchTree &rhs) {}
  ~BinarySearchTree()
  {
    makeEmpty();
  }

  const T &findMin() const; // 什么情况下不能返回引用？
  const T &findMax() const;
  bool contains(const T &x) const;
  bool isEmpty() const;
  void printTree() const;

  void makeEmpty();
  void insert(const T &x);
  void remove(const T &x);

  const BinarySearchTree &operator=(const BinarySearchTree &rhs);

 private:
  struct BinaryNode
  {
    T val;
    BinaryNode *left;
    BinaryNode *right;
    BinaryNode() {}
    BinaryNode(T x) : val(x), left(nullptr), right(nullptr) {}
    BinaryNode(T x, BinaryNode *l, BinaryNode *r) : val(x), left(l), right(r) {}
  };

  BinaryNode *root;
  void insert(const T &x, BinaryNode *&t) const; // 用引用参数可以修改root
  void remove(const T &x, BinaryNode *&t) const;
  BinaryNode *findMin(BinaryNode *t) const
  { // 似乎不能把定义写在类外,不然找不到返回值类型BinaryNode的定义
    if (t == nullptr)
      return nullptr;
    else if (t->left == nullptr)
      return t;
    else
      return findMin(t->left);
  }
  BinaryNode *findMax(BinaryNode *t) const
  {
    if (t != nullptr)
      while (t->right != nullptr)
        t = t->right;
    return t;
  }
  bool contains(const T &x, BinaryNode *t) const;
  void makeEmpty(BinaryNode *&t) const;
  void printTree(BinaryNode *t) const;
  // Deep copy
  BinaryNode *clone(BinaryNode *t) const
  {
    if (t == nullptr)
      return nullptr;
    return new BinaryNode(t->val, clone(t->left), clone(t->right));
  }
};

template <typename T>
const T &BinarySearchTree<T>::findMin() const
{
  return findMin(root);
}
template <typename T>
const T &BinarySearchTree<T>::findMax() const
{
  return findMax(root);
}
template <typename T>
bool BinarySearchTree<T>::contains(const T &x) const
{
  return contains(x, root);
}
template <typename T>
bool BinarySearchTree<T>::isEmpty() const
{
  return root == nullptr;
}
template <typename T>
void BinarySearchTree<T>::printTree() const
{
  printTree(root);
}
template <typename T>
void BinarySearchTree<T>::makeEmpty()
{
  makeEmpty(root);
}
template <typename T>
void BinarySearchTree<T>::insert(const T &x)
{
  insert(x, root);
}
template <typename T>
void BinarySearchTree<T>::remove(const T &x)
{
  remove(x, root);
}
template <typename T>
const BinarySearchTree<T> &BinarySearchTree<T>::operator=(const BinarySearchTree &rhs)
{
  if (this != &rhs)
  { // 自我复制检测
    makeEmpty();
    root = clone(rhs.root);
  }
  return *this;
}

// 保证永远不会插入重复项
// 如果要允许重复项，则需要修改bst树的定义，例如：左子树所有节点值小于根，右子树的所有节点大于或等于根。
// 但是getEntry和remove会有歧义，需要类的定义者来指明。
template <typename T>
void BinarySearchTree<T>::insert(const T &x, BinaryNode *&t) const
{
  if (t == nullptr)
    t = new BinaryNode(x);
  else if (x < t->val)
    insert(x, t->left);
  else if (x > t->val)
    insert(x, t->right);
  else
    ; // Duplicate; do nothing
}
// 要删除节点N：
// 找到节点左子树的最右孩子R
// 用R的值替换N的值
// 删除节点R
// 同理：也可以删除右子树的最左节点
template <typename T>
void BinarySearchTree<T>::remove(const T &x, BinaryNode *&t) const
{
  if (t == nullptr)
    return;
  else if (x < t->val)
    remove(x, t->left);
  else if (x > t->val)
    remove(x, t->right);
  else if (t->left != nullptr || t->right != nullptr)
  { // x==t->val and the node has two children
    t->val = findMin(x, t->right)
                 ->val; // 把当前节点的值用右子树的最小值来替换，并且从右子树的根开始往下寻找并删除右子树的这个最小值节点，对右子树进行了两次查找，所以效率不高
    remove(
        t->val,
        t->right); // 第二次查找并删除，因为右子树的最小节点不可能有左孩子，所以第二次删除等于删除只有一个孩子节点的情况；效率不高，应该用removeMin() / removeFromRoot()来代替
  }
  else
  { // x==t->val and the node only has one children
    BinaryNode *oldNode = t;
    t = (t->left != nullptr) ? t->left : t->right;
    delete oldNode; // 如果删除的次数不多或者有重复项时，一般使用lazy deletion: 不删除节点，而是做一个删除记号.
                    // 在没有删除或者只是懒惰删除时，可以证明所有二叉查找树都是等可能出现的。
  }
}
//template<typename T> BinarySearchTree<T>::BinaryNode* BinarySearchTree<T>::findMin(BinaryNode *t) const {
//	if (t == nullptr)
//		return nullptr;
//	else if (t->left == nullptr)
//		return t;
//	else
//		return findMin(t->left);
//}
//template<typename T> BinarySearchTree<T>::BinaryNode* BinarySearchTree<T>::findMax(BinaryNode *t) const {
//	if (t != nullptr)
//		while (t->right != nullptr)
//			t = t->right;
//	return t;
//}
template <typename T>
bool BinarySearchTree<T>::contains(const T &x, BinaryNode *t) const
{
  if (t == nullptr)
    return false;
  else if (x < t->left)
    return contains(x, t->left);
  else if (x > t->right)
    return contains(x, t->right);
  else
    return true; // Match
}
template <typename T>
void BinarySearchTree<T>::makeEmpty(BinaryNode *&t) const
{
  if (t != nullptr)
  {
    makeEmpty(t->left);
    makeEmpty(t->right);
    delete t;
  }
  t = nullptr;
}
// 按层打印，空节点用#表示
template <typename T>
void BinarySearchTree<T>::printTree(BinaryNode *t) const
{
  if (t == nullptr)
    return;
  std::queue<BinaryNode *> Q;
  Q.push(t);
  int width = 1;
  while (!Q.empty())
  {
    for (int i = 0; i < width; i++)
    {
      if (!Q.empty())
      {
        BinaryNode *p = Q.front();
        Q.pop();
        if (p == nullptr)
        {
          std::cout << "# ";
          //Q.push_back(nullptr);
          //Q.push_back(nullptr);
        }
        else
        {
          std::cout << p->val << " ";
          if (p->left)
            Q.push(p->left);
          if (p->right)
            Q.push(p->right);
        }
      }
      else
      {
        std::cout << "# ";
      }
    }
    width *= 2;
    std::cout << std::endl;
  }
}
// Deep copy
//template<typename T> BinarySearchTree<T>::BinaryNode* BinarySearchTree<T>::clone(BinaryNode *t) const {
//	if (t == nullptr)
//		return nullptr;
//	return new BinaryNode(t->val, clone(t->left), clone(t->right));
//}
