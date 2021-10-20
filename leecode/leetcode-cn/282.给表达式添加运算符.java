// 回溯法
class Solution {
    private List<String> ans = new ArrayList<>();
    private String num;
    private int target;

    public List<String> addOperators(String num, int target) {
        this.num = num;
        this.target = target;
        StringBuffer expr = new StringBuffer();
        backtrace(expr, 0, 0, 0);
        return ans;
    }

    public void backtrace(StringBuffer expr, int i, long res, long mul) {
        if (num.length() == i) {
            if (res == target) {
                ans.add(expr.toString());
            }
            return;
        }
        int signIndex = expr.length(); // 保存状态
        if (i > 0)
            expr.append(0); // 占位
        long val = 0; // 可能溢出
        // 注意数字0只能有一个前置0
        for (int j = i; j < num.length() && (j == i || num.charAt(i) != '0'); ++j) {
            val = 10 * val + (num.charAt(j) - '0');
            expr.append(num.charAt(j));
            if (i == 0) { // 表达式开头不能添加符号
                backtrace(expr, j + 1, val, val);
            } else { // 添加符号
                expr.setCharAt(signIndex, '+');
                backtrace(expr, j + 1, res + val, val);
                expr.setCharAt(signIndex, '-');
                backtrace(expr, j + 1, res - val, -val);
                expr.setCharAt(signIndex, '*');
                backtrace(expr, j + 1, res - mul + val * mul, val * mul);
            }
        }
        expr.setLength(signIndex); // 还原状态
    }
}