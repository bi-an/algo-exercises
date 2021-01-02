class Solution
{
 public:
  // 前序遍历序列化
  char *Serialize(TreeNode *root)
  {
    if (root == nullptr)
      return nullptr;

    char *str = new char[101]; //在外部delete[]
                               //假定序列化长度不会超过100

    SerializeCore(root, str, 0);

    return str;
  }

  int SerializeCore(TreeNode *root, char *str, int pos)
  {
    //if(str[pos]=='\0') return;
    int len = 0;
    if (root == nullptr)
    {
      len = sprintf(str + pos, "$,");
      return len;
    }
    len = sprintf(str + pos, "%d,", root->val);
    len += SerializeCore(root->left, str, pos + len);
    len += SerializeCore(root->right, str, pos + len);
    return len;
  }

  TreeNode *Deserialize(char *str)
  {
    if (str == nullptr)
      return nullptr;
    int pos = 0;
    TreeNode *root = DeserializeCore(str, pos);
    return root;
  }

  TreeNode *DeserializeCore(char *str, int &pos)
  {
    if (str[pos] == '\0')
      return nullptr;
    if (str[pos] == '$')
    {
      pos += 2;
      return nullptr;
    }
    int i = pos;
    while (str[i] != ',')
      i++;
    string ch(str + pos, i - pos);
    int val = atoi(ch.c_str());
    TreeNode *root = new TreeNode(val);
    pos = i + 1;
    root->left = DeserializeCore(str, pos);
    root->right = DeserializeCore(str, pos);
    return root;
  }
};