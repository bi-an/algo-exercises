class Solution {
    public boolean checkPerfectNumber(int num) {
        if (num == 1)
            return false;

        int sum = 1, i = 2;

        while (i * i < num) {
            if (num % i == 0) {
                sum += i;
                sum += num / i;
            }
            i++;
        }
        if (i * i == num)
            sum += i;

        return sum == num;
    }
}
