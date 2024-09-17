#pragma once
#include "common.h"

// 基于邻接矩阵的实现
// https://www.hello-algo.com/chapter_graph/graph_operations/
class GraphAjdMat {
    vector<int> vertices_;        // 顶点
    vector<vector<int>> adjMax_;  // 邻接矩阵

public:
    GraphAjdMat(const vector<int>& vertices, const vector<vector<int>> edges) {
    }

    // 获取顶点数量
    int size() const {
    }

    // 添加顶点
    void addVertex(int val) {

    }

    // 删除顶点
    void removeVertex(int index) {

    }

    // 添加边
    // i, j 对应 vertices 元素索引，即 vertices[i][j]
    void addEdge(int i, int j) {

    }

    // 删除边
    void removeEdge(int i, int j) {

    }

    // 打印邻接矩阵
    void print() {
        std::cout << "顶点列表 = ";
        printContainer(vertices_);
        
    }
};