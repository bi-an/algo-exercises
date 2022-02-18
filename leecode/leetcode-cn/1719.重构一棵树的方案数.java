// 参见官方题解
// 时间：O(m+n^2)，其中 m = pairs.length, n = nodes.length
class Solution {
    public int checkWays(int[][] pairs) {
        Map<Integer, Set<Integer>> adj = new HashMap<>();
        for(int[] p : pairs) {
            adj.putIfAbsent(p[0], new HashSet<>());
            adj.putIfAbsent(p[1], new HashSet<>());
            adj.get(p[0]).add(p[1]);
            adj.get(p[1]).add(p[0]);
        }
        Set<Map.Entry<Integer, Set<Integer>>> entries = adj.entrySet();

        // 寻找 root
        int root = -1;
        for(Map.Entry<Integer, Set<Integer>> entry : entries) {
            Set<Integer> neighbors = entry.getValue();
            if(neighbors.size() == adj.size() - 1) { // 注意：节点总数不是 pairs.length，而是 adj.size()
                root = entry.getKey();
                break;
            }
        }
        if(root == -1)
            return 0;

        int res = 1;
        // 逐个寻找父节点
        for(Map.Entry<Integer, Set<Integer>> entry : entries) {
            int node = entry.getKey();
            Set<Integer> neighbors = entry.getValue();
            // root 没有父节点
            if (node == root)
                continue;
            int currDegree = neighbors.size();
            // 寻找当前节点 node 的父节点（严格父节点，不是祖先）
            int parent = -1;
            int parentDegree = Integer.MAX_VALUE;
            for(int neighbor : neighbors) {
                int degree = adj.get(neighbor).size();
                if(degree < parentDegree && degree >= currDegree) {
                    parent = neighbor;
                    parentDegree = degree;
                }
            }
            if(parent == -1)
                return 0;
            Set<Integer> children = adj.get(parent);
            // 判断找到的 parent 是否是真正的父节点
            for(int neighbor : neighbors) {
                if(neighbor == parent)
                    continue;
                if(!children.contains(neighbor))
                    return 0;
            }
            if(parentDegree == currDegree)
                res = 2;
        }
        return res;
    }
}