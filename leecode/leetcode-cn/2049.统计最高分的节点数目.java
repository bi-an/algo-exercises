// @ref 官方题解
class Solution {
  List<Integer>[] children;
  long maxScore = 0; // 注意：score 定义为 long，因为乘法可能溢出
  int cnt = 0;
  int n;

  public int countHighestScoreNodes(int[] parents) {
      n = parents.length;
      children = new List[n];
      for (int i = 0; i < n; i++) {
          children[i] = new ArrayList<>();
      }
      // 0 一定为根，不是所有的节点的孩子；并且 parents[0] = -1
      for (int i = 1; i < n; i++) {
          children[parents[i]].add(i);
      }
      dfs(0);
      return cnt;
  }

  // @ret 当前子树的大小
  public int dfs(int node) {
      // size 表示剪掉当前子树之后，剩余子树的大小
      // 初始时，假设当前子树为叶子（也包括根树只有一个节点的情况），剪去叶子，剩余的子树大小则为 n-1
      int size = n - 1;
      long score = 1;
      for (Integer c : children[node]) {
          int t = dfs(c);
          score *= t;
          size -= t; // 如果当前子树不是叶子，其余子树大小还需要减去其孩子树的大小
      }
      // 去掉当前节点 node 之后，根树被分成三部分：node 的左子树、node 的右子树、剪去 node树之后的树（如果 node 是 root，则这部分没有）
      if (node != 0) {
          score *= size; // 剪去当前树之后的其余部分构成的树
      }
      if (score == maxScore) {
          cnt++;
      } else if (score > maxScore) {
          maxScore = score;
          cnt = 1;
      }
      return n - size; // size 表示剪去当前树的树的大小，那么，n-size 则表示当前树的大小
  }
}

// 初始解法，比较繁琐
class Solution {
  public int countHighestScoreNodes(int[] parents) {
      int n = parents.length;
      Map<Integer, List<Integer>> tree = new HashMap<>();
      for (int i = 0; i < n; i++) {
          if (!tree.containsKey(parents[i]))
              tree.put(parents[i], new ArrayList<>());
          tree.get(parents[i]).add(i); // -1:[0] 是多余的，不需要利用
      }
      int[] sizes = new int[n];
      long[] scores = new long[n]; // Attention: 定义为 long，防止 int 乘法溢出
      countSizes(0, tree, sizes);
      long maxScore = 0;
      for (int i = 0; i < n; i++) {
          scores[i] = 1;
          if (tree.containsKey(i)) {
              for (Integer child : tree.get(i)) {
                  scores[i] *= sizes[child];
              }
              // 如果不是 root
              if (parents[i] != -1) {
                  scores[i] *= sizes[0] - sizes[i];
              }
          } else {
              scores[i] = n - 1;
          }
          if (scores[i] > maxScore) {
              maxScore = scores[i];
          }
      }
      int cnt = 0;
      for (long score : scores) {
          if (score == maxScore)
              cnt++;
      }
      return cnt;
  }

  public void countSizes(int parent, Map<Integer, List<Integer>> tree, int[] sizes) {
      sizes[parent] = 1;
      if (!tree.containsKey(parent))
          return;
      for (Integer child : tree.get(parent)) {
          countSizes(child, tree, sizes);
          sizes[parent] += sizes[child];
      }
  }
}