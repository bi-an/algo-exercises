/*
3 打乱字符串树 
 
题目描述 
给定一个字符串 s ，可以将它表示成二叉树结构，比如下面就是 order 的一种二叉树形式。 
    order 
   /     \ 
  or     der 
 /  \   /   \ 
o    r d    er 
           /  \ 
          e    r 
针对这个二叉树，我们可以任意交换一个节点的子节点来重新变化字符串的形式，将 order 变为
roder 。 
    roder 
   /     \ 
  ro     der 
 /  \   /   \ 
r    o d    er 
           /  \ 
          e    r 
如果再继续交换，可以得到 rored 。 
    rored 
   /     \ 
  ro     red 
 /  \   /   \ 
r    o re    d 
      /  \  
     r    e 
给定两个字符串 s1 和 s2 ，判断 s1 能否通过上面提到的交换子节点的方式得到 s2 。 

输入格式 
共2行输入 
第一行为字符串s1， 
第二行为字符串s2。 
 
输出格式 
共1行输出，整数，1表示可以，0表示不可以。 
 
示例 1 
输入
order 
rored 

输出
1 

示例 2 
输入 
order 
darre 

输出
0 
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int fun(string tree1, string tree2) {

}

int main() {


}