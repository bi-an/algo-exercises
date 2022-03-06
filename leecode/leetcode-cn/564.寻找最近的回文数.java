class Solution {
  public String nearestPalindromic(String n) {
    long selfNumber = Long.parseLong(n), ans = -1l;
    System.out.println(selfNumber);
    for (long candidate : getCandidates(n)) {
        // 注意：这里会判断数值相等，所以 candidate 和 selfNumber 不能使用对象类型 Long
        // 否则两个对象即使数值相等，比较结果也是不等（因为属于不同的对象）
      if (candidate != selfNumber) {
        if (ans == -1 ||
            Math.abs(selfNumber - candidate) < Math.abs(selfNumber - ans) ||
            Math.abs(selfNumber - candidate) == Math.abs(selfNumber - ans) && candidate < ans) {
          ans = candidate;
        }
      }
    }
    return String.valueOf(ans);
  }

  public List<Long> getCandidates(String n) {
    int len = n.length();
    List<Long> candidates = new ArrayList<>() {
      {
        add((long) Math.pow(10, len - 1) - 1);
        add((long) Math.pow(10, len) + 1);
      }
    };
    long prefix = Long.parseLong(n.substring(0, (len - 1) / 2 + 1)); // (len + 1) / 2
    for (long i = prefix - 1; i <= prefix + 1; i++) {
      StringBuffer sb = new StringBuffer(String.valueOf(i));
      // 细节：len & 1
      // 如果 prefix 长度为奇数，从下标1开始续接字符串；
      // 如果为偶数，从下标0开始续接字符串
      sb.append(new StringBuffer(sb).reverse().substring(len & 1));
      candidates.add(Long.parseLong(sb.toString()));
    }

    return candidates;
  }
}