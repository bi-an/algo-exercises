/*
 * @Author: your name
 * @Date: 2021-07-29 00:50:32
 * @LastEditTime: 2021-07-29 01:04:12
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \practice\剑指offer\二叉树\BinaryTree.java
 */

import java.util.Scanner;

// Definition for a binary tree node.
class TreeNode {
    int val;
    TreeNode left;
    TreeNode right;
    TreeNode(int x) { val = x; }
}

public class BinaryTree {
    private TreeNode root;

    public void reconstruct(String string) {
        String[] nodes = string.split(",");
        
    }

    // @Test
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        String str = null;
        while((str = scanner.next()) != null && !str.equals("exit")) {
            System.out.println(str);
        }
    }
}