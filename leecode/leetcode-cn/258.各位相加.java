class Solution {
    public int addDigits(int num) {
        int ans = num % 9;
        if(num == 0)
            return 0;
        else if(ans == 0)
            return 9;
        else
            return num % 9;
    }
}