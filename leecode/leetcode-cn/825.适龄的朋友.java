// 方法一：排序 + 双指针
// age[y] <= 0.5 * age[x] + 7
// age[y] > age[x]
// age[y] > 100 && age[x] < 100
// 第2个条件包含第3个条件，只要同时不满足第1个和第2个条件，x就会向y发送好友请求。
// 也就是说，只要 0.5*ages[x]+7 < ages[y] <= ages[x]，那么x就会向y发送好友请求。
// 可以看到，左右边界随着ages[x]增加是单调递增的，所以可以升序排列之后，移动左右边界。
// 同时注意到，如果x=y，那么一定满足条件，[left,right]区间包含y的个数应该-1.
class Solution {
    public int numFriendRequests(int[] ages) {
        int ans = 0, left = 0, right = 0, n = ages.length;
        Arrays.sort(ages); // 升序排列
        for (int age : ages) { // x, 对于每个x，边界是固定的，我们要找出这个范围的所有y.
            if(age < 15) // 如果不判断这一步，就必须判断 left<=right
                continue;
            while (left < n && ages[left] <= 0.5 * age + 7)
                left++; // 包含
            while (right < n && ages[right] <= age)
                right++; // 不包含
            ans += right - left - 1;
        }
        return ans;
    }
}


// 对计数排序 + 前缀和
//
// 本题无非就是要对每个x，计算满足条件
//      ages[x]*0.5+7 < ages[y] <= ages[x]
// 的y的个数。
// 注意：ages[i]可以相同。
// 难点在于，如果对每个age重新计算一遍条件，并且进行计数，时间复杂度为O(n^2)，过高。
// 发现规律：左右边界是递增函数，所以如果先对ages排序，然后：
// 解决方法一：因为左右边界递增，可以使用双指针寻找窗口边界，因为指针也将是递增的，其他age的个数就是窗口长度-1。
//      -1表示去掉本身。
// 解决方法二：（1）排序时间复杂度过高，但我们可以发现ages的取值范围 [1,120]，于是可以直接对ages计数，放在哈希表中，
// 哈希表的顺序就是已经排序好的。
//      （2）我们依然需要解决第二个问题：怎么在O(1)时间内计算出筛选条件？现在的筛选条件发生了一些变化：因为我们已经计
// 算出每个age的计数了，所以现在累加所有满足条件的age的计数即可：
//      对每个age，sum{ cnt[i] | floor(age * 0.5 + 8) <= i <= age} - 1
// 累加问题的时间优化可以使用前缀和。
//
// 时间复杂度：O(n + C)，其中 C 是用户年龄的范围，本题中 C = 120。计数排序需要 O(n) 的时间，计算前缀和以及统计答案需要 O(C) 的时间。
// 空间复杂度：O(C)，即为计数排序以及前缀和数组需要使用的空间。
class Solution {
    public int numFriendRequests(int[] ages) {
        int n = ages.length, ans = 0;
        int[] cnt = new int[121];
        for (int age : ages)
            ++cnt[age];

        int[] pre = new int[121];
        for (int i = 1; i <= 120; i++)
            pre[i] = pre[i - 1] + cnt[i]; // 左开右闭

        for (int i = 15; i <= 120; i++) {
            int bound = (int) (0.5 * i + 8);
            ans += cnt[i] * (pre[i] - pre[bound - 1] - 1);
        }

        return ans;
    }
}
