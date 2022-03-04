// 方法一：滑动窗口 + 两次遍历
// 时间复杂度：O(n^2)
// 空间复杂度：O(1)
class Solution {
    public long subArrayRanges(int[] nums) {
        long ans = 0, n = nums.length;
        // i 为窗口左边界，j 为窗口右边界
        for (int i = 0; i < n; i++) {
            int minVal = nums[i], maxVal = nums[i];
            for (int j = i + 1; j < n; j++) {
                minVal = Math.min(minVal, nums[j]);
                maxVal = Math.max(maxVal, nums[j]);
                ans += maxVal - minVal;
            }
        }
        return ans;
    }
}

// 预处理 + 单调栈
// 单调栈：以单调递增栈为例，只有比栈顶小的元素能够入栈，否则就将栈顶弹出再入栈，这样最终栈中的元素就是自顶而下单增的。
// 单调递增栈适用于寻找第一个比当前数大的元素。
// 思路：
//  1. 由“范围和”的定义，所有子数组的范围和等价于所有子数组的最大值减去所有子数组的最小值。
//  2. 设 nums[i] 左边比其小的最近元素为 nums[j]，右边比其小的最近元素为 nums[k]，
//  换言之，nums[j+1,...,i-1], nums[i+1,...,k-1] 都比 nums[i] 大。
//  那么，以 nums[i] 为最小值的子数组个数为 (i-j) * (k-i) 个，这些子数组的最小值就是 nums[i]，
//  这些子数组的最小值之和则等于 (i-j) * (k-i) * nums[i].
//  同理，可以找出所有子数组的最大值。
//  3. 为了快速找出所有子数组的最大值，我们使用单调栈，leftStack 的栈顶为 nums[i] 左边次小元素下标，rightStack 的栈
//  顶为右边次小元素下标，这两个下标之间所有子数组的最小值就找出来了，就是 nums[i]，可以将 leftStack 和 rightStack
//  的栈顶分别存放在两个数组中，记作 minLeft[i] 和 minRight[i]，那么
//      sumMin = \sum_i { (i - minLeft[i]) * (minRight[i] - i) * nums[i]}。
//  同理可以求出 sumMax，那么 answer = sumMax - sumMin.
//  4. 细节：当数组中有相同元素时，这样分开统计的方式，会造成重复统计。例如：(1,3,3)
//    (1) 寻找以第二个 3 为最大值的子数组时，左边次大下标为 -1，右边次大下标为 3，那么子数组个数为 (1-(-1))*(3-1) = 4，
//      这些子数组（以下标表示）分别是 [1], [0,1], [1,2], [0,1,2]。
//    (2) 寻找以第三个 3 为最大值的子数组时，左边次大下标为 -1，右边次大下标为 3，那么子数组个数为 (2-(-1))*(3-2) = 3，
//      这些子数组（以下标表示）分别是 [2], [1,2], [0,1,2]。
//    可以看到，其中子数组被重复统计。
//  发生重复统计的原因是：3 作为最大数被统计了两次。如果我们将这两个相同的 3 定义出相对大小，则可以避免重复。
//  可以定义：当 nums[i] == nums[j] 时，如果 i < j，那么 nums[i] < nums[j].
//  第二种去重的方法：从左往右统计时，栈中不压入相同的数；从右往左统计时，栈中相同的数都压入。
// 时间复杂度：O(n)
// 空间复杂度：O(n)
class Solution {
    public long subArrayRanges(int[] nums) {
        int n = nums.length;
        int[] minLeft = new int[n], minRight = new int[n],
                maxLeft = new int[n], maxRight = new int[n];
        Stack<Integer> minLeftStack = new Stack<>(), minRightStack = new Stack<>(),
                maxLeftStack = new Stack<>(), maxRightStack = new Stack<>();

        for (int i = 0; i < n; i++) {
            // 左边第一个比当前数小的数的下标
            while (!minLeftStack.empty() && nums[minLeftStack.peek()] > nums[i])
                minLeftStack.pop();
            minLeft[i] = minLeftStack.empty() ? -1 : minLeftStack.peek();
            minLeftStack.push(i);
            // 左边第一个比当前数大的数的下标
            while (!maxLeftStack.empty() && nums[maxLeftStack.peek()] <= nums[i]) // Attention
                maxLeftStack.pop();
            maxLeft[i] = maxLeftStack.empty() ? -1 : maxLeftStack.peek();
            maxLeftStack.push(i);

            /// 从右到左
            int j = n - 1 - i;
            while (!minRightStack.empty() && nums[minRightStack.peek()] >= nums[j]) // Attention
                minRightStack.pop();
            minRight[j] = minRightStack.empty() ? n : minRightStack.peek();
            minRightStack.push(j);
            while (!maxRightStack.empty() && nums[maxRightStack.peek()] < nums[j])
                maxRightStack.pop();
            maxRight[j] = maxRightStack.empty() ? n : maxRightStack.peek();
            maxRightStack.push(j);
        }

        long ans = 0;
        for (int i = 0; i < n; i++) {
            ans += (((long)i - maxLeft[i]) * (maxRight[i] - i) - (i - minLeft[i]) * (minRight[i] - i)) * nums[i];
        }
        
        return ans;
    }
}

// 写法二
class Solution {
    public long subArrayRanges(int[] nums) {
        int n = nums.length;
        int[] minLeft = new int[n], minRight = new int[n],
                maxLeft = new int[n], maxRight = new int[n];
        Stack<Integer> minLeftStack = new Stack<>(), minRightStack = new Stack<>(),
                maxLeftStack = new Stack<>(), maxRightStack = new Stack<>();

        for (int i = 0; i < n; i++) {
            // 左边第一个比当前数小的数的下标
            while (!minLeftStack.empty() && nums[minLeftStack.peek()] >= nums[i]) // Attention
                minLeftStack.pop();
            minLeft[i] = minLeftStack.empty() ? -1 : minLeftStack.peek();
            minLeftStack.push(i);
            // 左边第一个比当前数大的数的下标
            while (!maxLeftStack.empty() && nums[maxLeftStack.peek()] <= nums[i]) // Attention
                maxLeftStack.pop();
            maxLeft[i] = maxLeftStack.empty() ? -1 : maxLeftStack.peek();
            maxLeftStack.push(i);

            /// 从右到左
            int j = n - 1 - i;
            while (!minRightStack.empty() && nums[minRightStack.peek()] > nums[j])
                minRightStack.pop();
            minRight[j] = minRightStack.empty() ? n : minRightStack.peek();
            minRightStack.push(j);
            while (!maxRightStack.empty() && nums[maxRightStack.peek()] < nums[j])
                maxRightStack.pop();
            maxRight[j] = maxRightStack.empty() ? n : maxRightStack.peek();
            maxRightStack.push(j);
        }

        long ans = 0;
        for (int i = 0; i < n; i++) {
            ans += (((long)i - maxLeft[i]) * (maxRight[i] - i) - (i - minLeft[i]) * (minRight[i] - i)) * nums[i];
        }

        return ans;
    }
}