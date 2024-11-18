class Solution {
public:
    bool isRectangleCover(vector<vector<int>>& rectangles) {
        map<std::pair<int, int>, int> counts;

        for(vector<int>& rectangle : rectangles) {
            int x = rectangle[0], y = rectangle[1],
                a = rectangle[2], b = rectangle[3];
            // 画图可知，比如矩形A的右上角和矩形B的某个顶点重合，并且A与B不重合，
            // 那么该顶点一定不是B的右上角
            // 内部顶点最终一定会全部抵消掉
            if(++counts[make_pair(x,y)] == 0) counts.erase(make_pair(x,y));
            if(++counts[make_pair(a,b)] == 0) counts.erase(make_pair(a,b));
            if(--counts[make_pair(x,b)] == 0) counts.erase(make_pair(x,b));
            if(--counts[make_pair(a,y)] == 0) counts.erase(make_pair(a,y));
        }
        // 如果出现两个完全重合的矩形，那么虽然最终也会留下4个点，但是计数不为1
        return counts.size() == 4 && counts.begin()->second == 1;
    }
};