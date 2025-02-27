// 题目保证甲板上放置的战舰符合要求，所以只需要根据要求统计战舰数量即可。
// 连续放在一起的'X'共同组成一艘战舰
class Solution {
public:
    int countBattleships(vector<vector<char>>& board) {
        int ans = 0;
        for(int i=0;i<board.size();i++) {
            for(int j=0;j<board[0].size();j++) {
                if(board[i][j] == 'X') {
                    if(i > 0 && board[i-1][j] == 'X' || j > 0 && board[i][j-1] == 'X')
                        continue;
                    else
                        ans++;
                }
            }
        }
        return ans;
    }
};