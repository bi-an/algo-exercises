// 参考官方题解
// 每次找到当前最大的数，先将其翻转到最前面，然后整个翻转，这样能把其放置在末尾；
// 以此类推，翻转其余的。
// 时间复杂度：O(n^2)。
//      每个数都需要翻转2次，每次翻转的时间分别为 n, n-1, ..., 1 => n(n+1)/2
// 空间复杂度：O(1)
class Solution {
    public List<Integer> pancakeSort(int[] arr) {
        List<Integer> res = new ArrayList<>();
        for(int n = arr.length; n > 0; n--) {
            int index = 0;
            for(int i = 0; i < n; i++) {
                if(arr[i] > arr[index])
                    index = i;
            }
            if(index == n - 1)
                continue;
            res.add(index + 1);
            res.add(n);
            flip(arr, 0, index);
            flip(arr, 0, n-1);
        }
        return res;
    }

    public void flip(int[] arr, int start, int end) {
        while(start < end) {
            int temp = arr[start];
            arr[start] = arr[end];
            arr[end] = temp;
            start++;
            end--;
        }
    }
}