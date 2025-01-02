/*
 * @lc app=leetcode.cn id=911 lang=cpp
 *
 * [911] 在线选举
 */

// @lc code=start
class TopVotedCandidate {
    vector<pair<int, int>> tops;  // timepoint -> person (who gets the most votes)
public:
    TopVotedCandidate(vector<int>& persons, vector<int>& times) {
        int n = persons.size();
        tops.resize(n);
        pair<int, int> top;  // vote -> person
        unordered_map<int, int> votes;
        for (int i = 0; i < n; ++i) {
            int p = persons[i], t = times[i];
            int vote = ++votes[p];
            if (vote >= top.first)
                top = make_pair(vote, p);
            tops[i] = make_pair(t, top.second);
        }
    }

    int q(int t) {
        // {t, INT_MAX} 不可能达到的上界
        auto i = ranges::upper_bound(tops, make_pair(t, INT_MAX));
        // 由题意，一定可以找到，故不需要判断边界条件
        return (i - 1)->second;
    }
};

/**
 * Your TopVotedCandidate object will be instantiated and called as such:
 * TopVotedCandidate* obj = new TopVotedCandidate(persons, times);
 * int param_1 = obj->q(t);
 */
// @lc code=end
