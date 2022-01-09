// 以"/"为分割符分割：
//  "///"：出现空字符串
//  "."：不需要管
//  ".."：弹栈
//  其他字符串：入栈
class Solution {
    public String simplifyPath(String path) {
        String[] sequence = path.split("/");
        Deque<String> stack = new ArrayDeque<>();
        for (String s : sequence) {
            if (s.isEmpty() || s.equals(".")) {
                continue;
            } else if (s.equals("..")) {
                if (!stack.isEmpty())
                    stack.pollLast();
            } else {
                stack.offerLast(s);
            }
        }
        StringBuffer ans = new StringBuffer();
        if (stack.isEmpty()) {
            ans.append("/");
        } else {
            while (!stack.isEmpty()) {
                ans.append("/" + stack.pollFirst());
            }
        }
        return ans.toString();
    }
}