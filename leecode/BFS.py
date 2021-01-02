#     B ——  D 
#   / |   / | \
# A   |  /  |   F
#   \ | /   |
#     C ——  E


# s 图的第一个节点
def BFS(graph, s):
    queue = []
    seen = set()
    queue.append(s)
    seen.add(s)

    while (len(queue)!=0):
        vertex = queue.pop(0)
        print(vertex)
        nodes = graph[vertex]
        for w in nodes:
            if w not in seen:
                queue.append(w)
                seen.add(w)

# BFS的应用:最短路径
def shortestPath(graph, s):
    queue = []
    seen = []
    # parent保存当前节点的上一个节点，它记录最小生成树的信息
    parent = {s: None}
    queue.append(s)
    seen.append(s)

    while(len(queue)!=0):
        vertex = queue.pop(0)
        # print(vertex)
        nodes = graph[vertex]
        for w in nodes:
            if w not in seen:
                queue.append(w)
                seen.append(w)
                parent[w] = vertex
    return parent
        

if __name__ == "__main__":
    graph = {
        "A": ["B", "C"],
        "B": ["A", "C", "D"],
        "C": ["A", "B", "D"],
        "D": ["B", "C", "E", "F"],
        "E": ["C", "D"], 
        "F": ["D"]
    }
    # BFS(graph, "E")
    parent = shortestPath(graph, "E")
    # for (k,v) in parent.items():
    #     print(k, v)

    # 寻找从v到图的起始点的最短路径
    v = 'B'
    while(v!=None):
        print(v)
        v = parent[v]