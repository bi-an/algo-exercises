// 官方题解
class Solution {
public:
    bool circularArrayLoop(vector<int>& nums) {
        int n = nums.size();
        auto next = [&](int cur) {
            return ((cur + nums[cur]) % n + n) % n; // 保证返回值在 [0,n) 中
        };

        for (int i = 0; i < n; i++) {
            if (!nums[i]) {
                continue;
            }
            int slow = i, fast = next(i);
            // 判断非零且方向相同
            while (nums[slow] * nums[fast] > 0 && nums[slow] * nums[next(fast)] > 0) { // 每一步都要判断方向
                if (slow == fast) {
                    if (slow != next(slow)) {
                        return true;
                    }
                    else {
                        break;
                    }
                }
                slow = next(slow);
                // 因为这里走了两步，每一步都必须判断方向是否相同，所以在循环条件上要先判断nums[slow] * nums[next(fast)] > 0
                fast = next(next(fast));
            }
            // 把走过的位置全部置0（因为题目中nums不可能有0），防止重复遍历，降低时间复杂度
            int add = i;
            while (nums[add] * nums[next(add)] > 0) {
                int tmp = add;
                add = next(add);
                nums[tmp] = 0;
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