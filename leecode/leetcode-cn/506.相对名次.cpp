class Solution {
public:
    vector<string> findRelativeRanks(vector<int>& score) {
        int n = score.size();
        vector<string> ans(n);
        vector<pair<int,int>> vec(n);

        for(int i=0;i<n;i++) {
            vec[i].first = i;
            vec[i].second = score[i];
        }

        sort(vec.begin(), vec.end(), [&](pair<int,int>& a, pair<int,int>& b){
            return a.second > b.second;
        });

        vector<string> tmp = {
            "Gold Medal","Silver Medal","Bronze Medal"
        };

        for(int i=0;i<n;i++) {
            if(i >= 3)
                ans[vec[i].first] = to_string(i+1);
            else
                ans[vec[i].first] = tmp[i];
        }

        return ans;
    }
};