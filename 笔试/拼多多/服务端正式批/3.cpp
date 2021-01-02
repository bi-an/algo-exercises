// 思路：本题与leetcode440（字典序的第K小数）有相似之处，
// (1)建立字典树，按照先序遍历的顺序遍历，就是字典序的顺序
// 参考：https://blog.csdn.net/qq_36946274/article/details/81638367
// (2)用动态规划来求第k大的数

// 大概意思是建一个二叉树，二叉树的每个节点是一个[i,j]，根节点是[n,m]，然后连接左子节点代表走了一步a，
// 连接右子节点代表走了一步b，每个节点的num代表的是以该节点为根节点的子树（包含根本身）一共含有多少个节点，
// 整个二叉树除了根节点的每个节点都代表一个字典序的排列，这个排列就是从根节点走到该节点的字典路径
// 参考：https://www.nowcoder.com/discuss/281866?type=post&order=time&pos=&page=1

// num[i,j]表示含有i个a和j个b时，该树的节点总数

int n, m;
long long int k, num[55][55];
void dfs(int na, int nb, string s, long long int kk)
{
  if (kk == 1)
  {
    cout << s << endl;
    return;
  }

  if (na > 0 && num[na - 1][nb] >= kk - 1)
  {
    s = s + "a";
    dfs(na - 1, nb, s, kk - 1);
  }
  else if (nb > 0)
  {
    kk -= num[na - 1][nb];
    s = s + "b";
    dfs(na, nb - 1, s, kk - 1);
  }
  return;
}
int main()
{
  cin >> n >> m >> k;
  k++;
  num[0][0] = 1;

  for (int i = 0; i <= n; i++)
    for (int j = 0; j <= m; j++)
    {
      num[i][j] = 1;
      if (i > 0)
        num[i][j] += num[i - 1][j];
      if (j > 0)
        num[i][j] += num[i][j - 1];
    }
  num[n][m] -= 1;
  string ss = "";
  dfs(n, m, ss, k);

  return 0;
}