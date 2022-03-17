// 哈希集合
// 时间复杂度：O(nL*logn)，其中 nL表示所有字符串的长度之和，因为排序时间为 O(nL*logn)
// 空间复杂度：O(nL)
class Solution {
  public String longestWord(String[] words) {
      String ans = "";
      Set<String> occurs = new HashSet<>();
      occurs.add(""); // Attention
      Arrays.sort(words, (a, b) -> a.length() == b.length() ? b.compareTo(a) : a.length() - b.length());
      for (String s : words) {
          if (occurs.contains(s.substring(0, s.length() - 1))) {
              ans = s;
              occurs.add(s);
          }
      }
      return ans;
  }
}


// 时间复杂度：O(nL)，其中 nL 为所有字符串的总长度
// 空间复杂度：O(nL)，字典树最坏空间复杂度为所有字符串长度之和
class Solution {
  public String longestWord(String[] words) {
      Trie trie = new Trie();
      // 时间 O(nL)，其中 nL 为所有字符串的总长度
      for (String s : words) {
          trie.insert(s);
      }
      trie.insert(""); // 注意
      String longest = "";
      // 时间 O(nL)，其中 nL 为所有字符串的总长度
      for (String s : words) {
          if (trie.search(s)) {
              if (s.length() > longest.length() ||
                      s.length() == longest.length() && s.compareTo(longest) < 0) {
                  longest = s;
              }
          }
      }
      return longest;
  }
}

class Trie {
  static final int N = 26;
  Trie[] children;
  boolean end;

  public Trie() {
      // children 永不为 null
      children = new Trie[N];
      end = false;
  }

  public boolean search(String s) {
      Trie node = this;
      for (int i = 0; i < s.length(); ++i) {
          if (node == null || !node.end) // 注意：每个字符都要判断 end 是否为 true
              return false;
          node = node.children[s.charAt(i) - 'a'];
      }
      return true;
  }

  public void insert(String s) {
      Trie node = this;
      for (int i = 0; i < s.length(); ++i) {
          int pos = s.charAt(i) - 'a';
          if (node.children[pos] == null)
              node.children[pos] = new Trie();
          node = node.children[pos];
      }
      node.end = true;
  }
}
