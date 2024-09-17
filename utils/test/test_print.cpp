#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <bits/stdc++.h>

#include "doctest.h"
#include "print_utils.hpp"
using namespace std;

// TEST_CASE("printContainer") {
//     vector<int> vec = {1, 2, 3, 4, 5};
//     cout << "Vector elements: ";
//     printContainer(vec);

//     list<int> lst = {6, 7, 8, 9, 10};
//     cout << "List elements: ";
//     printContainer(lst);

//     // 单向链表
//     forward_list<int> flst = {11, 12, 13, 14, 15};
//     cout << "Forward_list elements: ";
//     printContainer(flst);

//     set<int> st = {16, 17, 18, 19, 20};
//     cout << "Set elements: ";
//     printContainer(st);
// }

TEST_CASE("printContainer") {
    // 一维容器
    std::vector<int> vec = {1, 2, 3, 4, 5};
    // printContainer1L(vec);  // 输出: [1, 2, 3, 4, 5]
    // std::cout << std::endl;
    // 多行
    // printContainer(vec);

    // 二维容器
    std::vector<std::vector<int>> vec2D = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    // printContainer1L(vec2D);  // 输出: [[1, 2, 3], [4, 5, 6], [7, 8, 9]]
    // std::cout << std::endl;
    // // 多行
    printContainer(vec2D);

    // // 多维容器
    // std::vector<std::vector<std::vector<int>>> vec3D = {
    //     {{1, 2}, {3, 4}},
    //     {{5, 6}, {7, 8}}};
    // printContainer1L(vec3D);  // 输出: [[[1, 2], [3, 4]], [[5, 6], [7, 8]]]
    // std::cout << std::endl;
    // // 多行
    // printContainer(vec3D);
}
