// 方法一：分治法
// 先将链表转换成数组，然后就可以利用108题的解法。
// 时间复杂度：O(n)
// 空间复杂度：O(n)，数组的大小为 n.
class Solution
{
 public:
  TreeNode *sortedListToBST(ListNode *head)
  {
    vector<int> nums; // 为了迅速找到有序链表的中点。
    while (head)
    {
      nums.push_back(head->val);
      head = head->next;
    }
    return sortedArrayToBST(nums, 0, (int)nums.size() - 1);
  }

  TreeNode *sortedArrayToBST(const vector<int> &nums, int start, int end)
  {
    if (start > end)
      return nullptr;
    int mid = (start + end) / 2;
    TreeNode *root = new TreeNode(nums[mid]);
    root->left = sortedArrayToBST(nums, start, mid - 1);
    root->right = sortedArrayToBST(nums, mid + 1, end);
    return root;
  }
};

// 方法二：分治法，不使用额外数组保存链表
// 时间复杂度：O(nlogn)。证明方法见图解。TODO
// 空间复杂度：O(1)。
class Solution
{
 public:
  // 每次都使用双指针找到链表中点。
  ListNode *getMedian(ListNode *left, ListNode *right)
  {
    ListNode *fast = left;
    ListNode *slow = left;
    while (fast != right && fast->next != right)
    {
      fast = fast->next;
      fast = fast->next;
      slow = slow->next;
    }
    return slow;
  }

  TreeNode *buildTree(ListNode *left, ListNode *right)
  {
    if (left == right)
    {
      return nullptr;
    }
    ListNode *mid = getMedian(left, right);
    TreeNode *root = new TreeNode(mid->val);
    root->left = buildTree(left, mid);
    root->right = buildTree(mid->next, right);
    return root;
  }

  TreeNode *sortedListToBST(ListNode *head)
  {
    return buildTree(head, nullptr);
  }
};

// 方法三：分治法 + 中序遍历优化
// 把有序链表看成完全右倾的二叉搜索树，中序遍历时，上一次遍历到的节点就是本次
// 时间复杂度：O(n)，一次遍历。
// 空间复杂度：O(logn)，栈深度取决于二叉树的高度。
class Solution
{
  ListNode *next_; // 记录中序遍历的下一个节点
 public:
  TreeNode *sortedListToBST(ListNode *head)
  {
    int len = getLength(head);
    next_ = head; // 初始值
    return sortedListToBST(0, len - 1);
  }

  // 每次调用，更新 next_ 为链表的下一个节点。
  TreeNode *sortedListToBST(int left, int right)
  {
    if (left > right)
      return nullptr;
    int mid = (left + right) / 2;

    // 写法一：先用 root 占位，再更新 root 的值。
    TreeNode *root = new TreeNode(); // 先占位
    root->left = sortedListToBST(left, mid - 1);
    root->val = next_->val; // 更新 root 的值
    // // 写法二
    // TreeNode* leftTree = sortedListToBST(left, mid - 1);
    // TreeNode* root = new TreeNode(next_->val);
    // root->left = leftTree;

    // 中序遍历完成，更新到下一个节点。
    //（假装访问了当前的节点，准备访问下一个节点。）
    next_ = next_->next;
    root->right = sortedListToBST(mid + 1, right);
    return root;
  }

  int getLength(ListNode *head)
  {
    int len = 0;
    while (head)
    {
      ++len;
      head = head->next;
    }
    return len;
  }
};

// 方法三的递归函数的第二种写法，函数参数使用引用。
class Solution
{
 public:
  TreeNode *sortedListToBST(ListNode *head)
  {
    int len = getLength(head);
    return sortedListToBST(head, 0, len - 1);
  }

  // 每次调用，更新 next_ 为当前子树的下一个节点。
  // head 为引用参数，是函数的返回值。保存的是链表的下一个节点。
  TreeNode *sortedListToBST(ListNode *&head, int left, int right)
  {
    if (left > right)
      return nullptr;
    int mid = (left + right) / 2;
    TreeNode *root = new TreeNode(); // 占位节点
    // 创建 root 的左子树并更新 head 为链表的下一个节点。
    root->left = sortedListToBST(head, left, mid - 1);
    // 更新根节点值
    root->val = head->val;
    // 创建右子树
    // 必须更新 head 为下一个节点，仅仅通过将 head->next 传入本递归函数是不够的。
    // 因为这意味着 head 在整个函数中都没有更新，还是传入时的值，
    // 那么 head 指向的节点就不是向链表左边部分的下一个节点。于是上面更新 root->val 的操作就是错误的。
    head = head->next; // 必须更新 head 为下一个节点
    root->right = sortedListToBST(head, mid + 1, right);

    return root;
  }

  int getLength(ListNode *head)
  {
    int len = 0;
    while (head)
    {
      ++len;
      head = head->next;
    }
    return len;
  }
};
