/**
序列化是将一个数据结构或者对象转换为连续的比特位的操作，进而可以将转换后的数据存储在一个文件或者内存中，同时也可以通过网络传输到另一个计算机环境，采取相反方式重构得到原数据。

请设计一个算法来实现二叉树的序列化与反序列化。这里不限定你的序列 / 反序列化算法执行逻辑，你只需要保证一个二叉树可以被序列化为一个字符串并且将这个字符串反序列化为原始的树结构。

提示: 输入输出格式与 LeetCode 目前使用的方式一致，详情请参阅 LeetCode 序列化二叉树的格式。你并非必须采取这种方式，你也可以采用其他的方法解决这个问题。

 

示例 1：


输入：root = [1,2,3,null,null,4,5]
输出：[1,2,3,null,null,4,5]
示例 2：

输入：root = []
输出：[]
示例 3：

输入：root = [1]
输出：[1]
示例 4：

输入：root = [1,2]
输出：[1,2]
 

提示：

树中结点数在范围 [0, 104] 内
-1000 <= Node.val <= 1000

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/serialize-and-deserialize-binary-tree
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */

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

            // 更新count
            if (cur == null) continue;
            else count--; // 队列中取出了当前节点

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