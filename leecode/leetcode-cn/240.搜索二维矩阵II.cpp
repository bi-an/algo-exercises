// Z字型搜索
// 时间复杂度：O(m+n)
// 空间复杂度：O(1)
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = matrix.size(), n = matrix[0].size();
        int x = 0, y = n - 1;
        while(x < m && y >= 0) {
            if(matrix[x][y] == target)
                return true;
            if(matrix[x][y] > target)
                y--;
            if(y >= 0 && matrix[x][y] < target)
                x++;
        }
        return false;
    }
};

// 每行二分查找
// 时间复杂度：O(mlogn)
// 空间复杂度：O(1)