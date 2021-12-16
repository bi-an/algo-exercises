// 方法一：排序 + 二分查找
class Solution {
    public int visiblePoints(List<List<Integer>> points, int angle, List<Integer> location) {
        int sameCnt = 0;
        int maxCnt = 0;

        List<Double> polarRadians = new ArrayList<>();
        for (List<Integer> point : points) {
            int y = point.get(1) - location.get(1);
            int x = point.get(0) - location.get(0);
            if (y == 0 && x == 0) {
                sameCnt++;
                continue;
            }
            // tip1: atan2值域范围[-pi,pi]
            polarRadians.add(Math.atan2(y, x)); 
        }

        // 排序
        Collections.sort(polarRadians);

        int m = polarRadians.size();
        // tip2: 环形处理，将原有数组加上2*pi放在后面，防止
        for (int i = 0; i < m; i++) {
            polarRadians.add(polarRadians.get(i) + 2 * Math.PI);
        }

        // tip3: 二分查找，找出 [di,di+angle] 内的点
        double toRadian = angle * Math.PI / 180;

        for (int i = 0; i < m; i++) {
            int right = binarySearch(polarRadians, polarRadians.get(i) +  toRadian, false);
            maxCnt = Math.max(maxCnt, right - i);
        }

        return sameCnt + maxCnt;
    }

    // 如果lower为false，与C++ upper_bound()函数相同；
    // 反之与C++ lower_bound()相同
    public int binarySearch(List<Double> nums, Double target, boolean lower) {
        int left = 0, right = nums.size() - 1;
        int ans = nums.size(); // 注意
        while(left <= right) {
          int mid = (left + right) / 2;
          if(nums.get(mid) > target || (lower && nums.get(mid) >= target)) {
            right = mid - 1;
            ans = mid;
          } else {
            left = mid + 1;
          }
        }
        return ans;
    }
}


// 方法二：排序 + 滑动窗口
// 该方法与上面的方法基本相同，唯一不同的是使用滑动窗口使得区间查找的时间优化为O(2n+2n)
// 时间复杂度：O(nlogn + 2n+2n)
class Solution {
    public int visiblePoints(List<List<Integer>> points, int angle, List<Integer> location) {
        int sameCnt = 0;
        int maxCnt = 0;

        List<Double> polarRadians = new ArrayList<>();
        for (List<Integer> point : points) {
            int y = point.get(1) - location.get(1);
            int x = point.get(0) - location.get(0);
            if (y == 0 && x == 0) {
                sameCnt++;
                continue;
            }
            // tip1: atan2值域范围[-pi,pi]
            polarRadians.add(Math.atan2(y, x)); 
        }

        // 排序
        Collections.sort(polarRadians);

        int m = polarRadians.size();
        // tip2: 环形处理，将原有数组加上2*pi放在后面，防止
        for (int i = 0; i < m; i++) {
            polarRadians.add(polarRadians.get(i) + 2 * Math.PI);
        }

        // tip3: 滑动窗口进行区间查找，找出 [di,di+angle] 内的点
        int right = 0;
        double toRadian = angle * Math.PI / 180;

        for (int i = 0; i < m; i++) {
            double curr = polarRadians.get(i);
            while (right < polarRadians.size() && polarRadians.get(right) - curr <= toRadian) {
                right++;
            }
            maxCnt = Math.max(maxCnt, right - i);
        }

        return sameCnt + maxCnt;
    }
}
