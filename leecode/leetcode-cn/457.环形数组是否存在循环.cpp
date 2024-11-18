// 官方题解
class Solution {
public:
    bool circularArrayLoop(vector<int>& nums) {
        int n = nums.size();
        // 因为 (cur+nums[cur])%n 可能为负，所以需要加上n再取一次余
        auto next = [&](int cur) {return ((cur + nums[cur]) % n + n) % n;}; // 保证index在 [0,n) 范围

        for(int i=0;i<nums.size();i++) {
            int slow = i, fast = next(slow);
            // 非零并且方向相同，每一步都要判断
            // 判断fast的方向就行，因为slow必定在走fast走过的路
            // 因为fast会每次移动两次，所以要额外判断一次方向
            while(nums[slow] * nums[fast] > 0 && nums[slow] * nums[next(fast)] > 0) {
                if(slow == fast) {
                    if(slow != next(slow)) // 说明循环长度大于1
                        return true;
                    else
                        break; // 说明循环长度为1
                }
                slow = next(slow);
                fast = next(next(fast));
            }
            // 把快慢指针走过的地方标记为0（因为nums不存在0），可以降低时间复杂度
            int add = i;
            while(nums[add] * nums[next(add)] > 0) {
                nums[add] = 0;
                add = next(add);
            }
        }

        return false;
    }
};

// @author zzg
class Solution {
public:
    bool circularArrayLoop(vector<int>& nums) {
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            if (hasCircle(nums, i)) return true;
        }
        return false;
    }
    bool hasCircle(vector<int>& nums, int begin) {
        int n = nums.size(), dir = nums[begin];
        auto next = [&](int cur) {
            if (cur < 0 || nums[cur] * dir < 0) return -1;
            else if (dir < 0)
                return (cur - abs(nums[cur]) % n + n) % n;
            else
                return (cur + (nums[cur] % n)) % n;
        };
        // 1.首先找到环
        int slow = begin, fast = next(begin);
        // 由于该数组是个环形数组，所以朝着某个方向，最终一定会回到起点，也就是快慢指针不可能死循环
        while (slow != fast) {
            slow = next(slow);
            fast = next(next(fast));
            if (slow == -1 || fast == -1) return false;
        }
        // 2.计算环的长度
        int len = 1; // 环的长度至少为1
        for (int i = next(slow); i != slow; i = next(i)) {
            len++;
        }

        return len > 1;
    }
};