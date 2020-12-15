// 回溯：n限制回溯树的宽度，k限制回溯树的深度
// 组合问题：使用start来排除重复
// 排列问题：使用contains来排除重复
class Solution {
public:
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> result;
        vector<int> track;
        backtrack(n, k, 0, track, result);
        return result;
    }

    void backtrack(int n, int k, int start, vector<int>& track, vector<vector<int>>& result){
        // if(track.length() > k) return;
        // result.push_back(track);
        if(track.size() == k) {
            result.push_back(track);
            return;
        }
        for(int i=start;i<n;i++){
            track.push_back(i+1);
            backtrack(n, k, i+1, track, result);
            track.pop_back();
        }
    }
};