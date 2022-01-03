class Solution {
    private Trie trie = new Trie();

    public List<String> findAllConcatenatedWordsInADict(String[] words) {
        List<String> ans = new ArrayList<>();
        // 由短到长排序
        Arrays.sort(words, (a, b) -> a.length() - b.length());

        for (String word : words) {
            if (word.isEmpty())
                continue;
            if (dfs(word, 0))
                ans.add(word);
            else
                insert(word);
        }

        return ans;
    }

    void insert(String word) {
        Trie node = trie;
        for (char c : word.toCharArray()) {
            int index = c - 'a';
            if (node.children[index] == null)
                node.children[index] = new Trie();
            node = node.children[index];
        }
        node.end = true;
    }

    boolean dfs(String word, int start) {
        if (word.length() == start)
            return true; // 第三次调用dfs时，应该返回true

        Trie node = trie;
        for (int i = start; i < word.length(); i++) {
            char ch = word.charAt(i);
            int index = ch - 'a';
            node = node.children[index];
            if (node == null)
                return false;
            if (node.end)
                if (dfs(word, i + 1))
                    return true;
            // 继续循环
        }

        return false;
    }
}

class Trie {
    Trie[] children;
    boolean end;

    Trie() {
        children = new Trie[26];
        end = false;
    }
}
