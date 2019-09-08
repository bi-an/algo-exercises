/*
在由若干 0 和 1  组成的数组 A 中，有多少个和为 S 的非空子数组。

示例：

输入：A = [1,0,1,0,1], S = 2
输出：4
解释：
如下面黑体所示，有 4 个满足题目要求的子数组：
[1,0,1,0,1]
[1,0,1,0,1]
[1,0,1,0,1]
[1,0,1,0,1]

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/binary-subarrays-with-sum
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

// 本题与“560.和为K的子数组”类似，但是因为数组中只有0和1
// 所以可以对hashmap优化，数组下标表示sum（因为sum不会超过n），作为hasmap的key；
// hashmap的value为前缀和出现的次数

class Solution {
public:
    int numSubarraysWithSum(vector<int>& A, int S) {
        if(A.empty()) return 0;
        int preSum=0;
        int *sum2times=new int[A.size()+1]();
        int ans=0;
        for(int i=0;i<A.size();i++){
            preSum+=A[i];
            int sum_j=preSum-S;
            if(sum_j>=0)
                ans+=sum2times[sum_j];
            if(sum_j==0) ans++;
            sum2times[preSum]++;
        }
        return ans;
    }
};

// 初始化技巧
// 注意到我们要判断sum_j为0（即A[i]本身等于S）的情况
// 这可以通过将sum2times[0]初始为1来避免
class Solution {
public:
    int numSubarraysWithSum(vector<int>& A, int S) {
        if(A.empty()) return 0;
        int preSum=0;
        int *sum2times=new int[A.size()+1]();
        sum2times[0]=1; // 初始化为1，而不是0
        int ans=0;
        for(int i=0;i<A.size();i++){
            preSum+=A[i];
            int sum_j=preSum-S;
            if(sum_j>=0)
                ans+=sum2times[sum_j];
           // if(sum_j==0) ans++;
            sum2times[preSum]++;
        }
        return ans;
    }
};