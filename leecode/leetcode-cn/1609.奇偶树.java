class Solution {
    public boolean isEvenOddTree(TreeNode root) {
        if (root == null)
            return false; // TODO
        Queue<TreeNode> Q = new LinkedList<>();
        Q.add(root);
        boolean isEven = true;

        while (!Q.isEmpty()) {
            int width = Q.size();
            int lastVal = isEven ? Integer.MIN_VALUE : Integer.MAX_VALUE;
            for (int i = 0; i < width; i++) {
                TreeNode node = Q.poll();
                if (node.left != null)
                    Q.add(node.left);
                if (node.right != null)
                    Q.add(node.right);
                if (isEven && (node.val % 2 == 0 || node.val <= lastVal)
                        || (!isEven && (node.val % 2 != 0 || node.val >= lastVal)))
                    return false;
                lastVal = node.val;
            }
            isEven = !isEven;
        }

        return true;
    }
}