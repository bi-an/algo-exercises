#include <iostream>
#include <iterator>
#include <string>
#include <type_traits>
#include <vector>
using namespace std;

// Data structure to store a binary tree node
struct Node {
    int data;
    Node *left, *right;

    Node(int data) {
        this->data = data;
        this->left = this->right = nullptr;
    }
};

struct Trunk {
    Trunk* prev;
    std::string str;

    Trunk(Trunk* prev, std::string str) {
        this->prev = prev;
        this->str = str;
    }
};

// Helper function to print branches of the binary tree
void showTrunks(Trunk* p) {
    if (p == nullptr) {
        return;
    }

    showTrunks(p->prev);
    cout << p->str;
}

/**
 * 打印二叉树
 * https://www.techiedelight.com/c-program-print-binary-tree/
 *
 * 格式形如：
 *             .——— 15
 *         .——— 7
 *        |    `——— 14
 *     .——— 3
 *    |   |        .——— 17
 *    |   |    .——— 13
 *    |   |   |    `——— 16
 *    |    `——— 6
 *    |        `——— 12
 * ——— 1
 *    |        .——— 11
 *    |    .——— 5
 *    |   |    `——— 10
 *     `——— 2
 *        |    .——— 9
 *         `——— 4
 *             `——— 8
 */
// 右序遍历，即：右-中-左。因为这是按行打印的顺序。
// root为父级Node；prev为父级Trunk；isLeft表明是否为左子树
// prev以行为单位。每一个节点值占据一行，两个节点不会同时出现在同一行。
void printTree(Node* root, Trunk* prev, bool isLeft) {
    if (root == nullptr) {
        return;
    }

    // 只有当“自己是右子树，父亲是左子树”或“自己是左子树，父亲是右子树”时，
    // 才需要在本行前添加"   |"，所以我们进入右子树时让prev->str总是"    "，
    // 进入左子树时让prev->str总是"   |"，这样能构造出这种左右交叉情况。
    // 反过来则不行，因为左子树是在下一行立即打印的，右子树则需要递归到最深层。
    // 所以，左子树的打印前准备是立即生效的。

    std::string prev_str = "    ";
    // 用 prev_str 初始化是为了打印右子树
    // 进入右子树时，prev_str 总是"    "
    Trunk* trunk = new Trunk(prev, prev_str);

    // 先打印右子树，因为右子树在屏幕最上方
    printTree(root->right, trunk, false);

    // 打印本级节点
    // 打印前准备
    // 到达root
    if (!prev) {
        trunk->str = "———";
    }
    // 是左子树
    else if (isLeft) {
        trunk->str = "`———";
        // 打印时，本级trunk的前面应该总是"    "，也就是"    `——— value"
        prev->str = "    ";  // 将父级trunk改成"    "
    }
    // 是右子树
    else {
        trunk->str = ".———";
        prev->str = "    ";  // 这一步可以省略，因为进入右子树时，prev->str总是"    "
    }

    showTrunks(trunk);                  // 打印一行
    cout << " " << root->data << endl;  // 一行的末尾打印节点值

    // 接下来为左子树做准备
    // 设置爷爷
    if (prev) {  // 防止crash，也确保了爷爷一定存在
        if (isLeft)
            prev->str = "    ";  // 这一步也是多余的，因为prev->str之前已经修改过了。
        else
            prev->str = "   |";  // 是右子树，但是接下来将打印左子树，这是交叉情况，所以需要将爷爷改成"   |"
    }

    // 设置父亲
    // 进入左子树时，prev->str总是"   |"，所以打印前需要将其修正为"    "
    trunk->str = "   |";

    printTree(root->left, trunk, true);
}

#if 0
int main()
{
    // Construct above tree
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    root->right->left = new Node(6);
    root->right->right = new Node(7);
    root->left->left->left = new Node(8);
    root->left->left->right = new Node(9);
    root->left->right->left = new Node(10);
    root->left->right->right = new Node(11);
    root->right->left->left = new Node(12);
    root->right->left->right = new Node(13);
    root->right->right->left = new Node(14);
    root->right->right->right = new Node(15);
    root->right->left->right->left = new Node(16);
    root->right->left->right->right = new Node(17);
 
    // print constructed binary tree
    printTree(root, nullptr, false);
 
    return 0;
}
#endif /* 0 */

/// 打印任意维度容器

// 基础模板，打印非容器类型（也就是基础类型）
template <typename T>
void printElement1L(const T& element, std::true_type) {
    std::cout << element;
}

// 特化模板，用于递归打印容器类型
template <typename ForwardIterable>
void printElement1L(const ForwardIterable& container, std::false_type) {
    std::cout << "[";
    auto it = container.begin();
    if (it != container.end()) {
        printElement1L(*it, std::is_fundamental<typename ForwardIterable::value_type>());
        ++it;
    }
    while (it != container.end()) {
        std::cout << ", ";
        printElement1L(*it, std::is_fundamental<typename ForwardIterable::value_type>());
        ++it;
    }
    std::cout << "]";
}

// 辅助函数模板，自动判断容器类型
// 迭代器必须是前向迭代器，比如std::queue就无法在不改变其元素的前提下获取其所有内部元素
// 打印成一行，不包含任何换行符
template <typename ForwardIterable>
void printContainer1L(const ForwardIterable& container) {
    printElement1L(container, std::is_fundamental<ForwardIterable>());
}
