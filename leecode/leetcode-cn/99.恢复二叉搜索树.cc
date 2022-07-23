// 方法一：显式中序遍历
// 时间复杂度：O(n)，两次遍历树。
// 空间复杂度：O(n)，保存树的中序遍历结果。
//
// (1) 先中序遍历并将结果序列保存在一个数组中；
// (2) 然后遍历该数组的所以逆序对，设为 {a[i], a[i+1]} 和 {a[j], a[j+1]}，
// 交换 a[i] 和 a[j+1]，得到有序的正确数组。
// 因为逆序对最多有两个，所以找到两个之后就可以终止寻找。
// (3) 最后重新中序遍历，用有序数组去依次替换原来的二叉树的值。



// 方法二：隐式中序遍历
// 递归写法一
// 时间复杂度：O(n)
// 空间复杂度：O(h)，递归栈的深度取决于树的高度 h.
//
// 注意，如果不相邻的两个节点的数被交换，则非递增的数对有两对：
// 例如 [1,2,3,4,5,6,7]
// (1) 如果不相邻的两个数交换，如 2 和 6，则新数组有两个错序对（连续的两个数字构成一对），
// 分别是 {6,3} 和 {5,2}。
// (2) 如果相邻的两个数交换，如 2 和 3，则新数组只有一个错序对，即 {2,3}.
class Solution {
    TreeNode* last = nullptr;
    TreeNode* x = nullptr, *y = nullptr; // 用来记录两个被错误交换的节点
public:
    void recoverTree(TreeNode* root) {
        recur(root);
        if (x != nullptr && y != nullptr) {
            swap(x->val, y->val);
        }
    }

    // 不要在递归过程中交换两个节点，而应该把这两个节点记录下来，在递归外交换。
    // 这样避免了很多难以把握的递归过程。
    void recur(TreeNode* root) {
        if (root == nullptr)
            return;
        recur(root->left);
        if (last != nullptr && last->val >= root->val) {
            if (x == nullptr) {
                x = last;
            }
            y = root;
        }
        last = root;
        recur(root->right);
    }
};

// 方法二：隐式中序遍历
// 递归写法二
class Solution {
    TreeNode* x = nullptr, *y = nullptr; // 用来记录两个被错误交换的节点
public:
    void recoverTree(TreeNode* root) {
        recur(root, nullptr);
        if (x != nullptr && y != nullptr) {
            swap(x->val, y->val);
        }
    }

    TreeNode* recur(TreeNode* root, TreeNode* last) {
        if (root == nullptr)
            return last;
        // 注意：调用 recur 将会更新 last，所以函数必须有返回值，或者传入一个引用。
        last = recur(root->left, last);
        // 此时的 last 经过递归访问左子树，已经被更新。
        if (last != nullptr && last->val >= root->val) {
            if (x == nullptr) {
                x = last;
            }
            y = root;
        }
        return recur(root->right, root);
    }
};

// 方法三：Morris 中序遍历
// 时间复杂度：O(n)
// 空间复杂度：O(1)
// TODO 参见官方题解
