// 层序遍历
public class Codec {

    // Encodes a tree to a single string.
    public String serialize(TreeNode root) {
        if (root == null) return "[]";
        StringBuffer sb = new StringBuffer();
        sb.append('[');
        int count = 1; // 记录队列中非空节点的个数
        Queue<TreeNode> q = new LinkedList<>();
        q.add(root);
        while (count > 0) {
            TreeNode cur = q.poll();

            // 分割符
            if (cur != root) sb.append(",");

            // 记录当前节点
            if (cur == null) sb.append("null");
            else sb.append(cur.val);

            //更新count
            if (cur == null) continue;
            else count--;

            // 记录子节点并更新count
            q.add(cur.left);
            q.add(cur.right);
            if (cur.left != null) count++;
            if (cur.right != null) count++;
        }
        sb.append(']');
        return sb.toString();
    }

    // Decodes your encoded data to tree.
    public TreeNode deserialize(String data) {
        if (data == null || data.length() <= 2) return null;
        String[] nums = data.substring(data.indexOf('[') + 1, data.indexOf(']')).split(",");
        TreeNode root = new TreeNode(Integer.valueOf(nums[0].trim()));
        Queue<TreeNode> q = new ArrayDeque<>();
        q.add(root);
        int i = 0, n = nums.length;
        while (!q.isEmpty()) {
            TreeNode cur = q.poll();
            if (++i < n && !nums[i].trim().equals("null")) {
                cur.left = new TreeNode(Integer.valueOf(nums[i].trim()));
                q.add(cur.left);
            }
            if (++i < n && !nums[i].trim().equals("null")) {
                cur.right = new TreeNode(Integer.valueOf(nums[i].trim()));
                q.add(cur.right);
            }
        }
        return root;
    }
}