// 字典树
class WordDictionary {
private:
    static const int N = 26;
    WordDictionary* child[N] = { 0 };
    bool ended = false;

public:
    WordDictionary() {
    }

    void addWord(string word) {
        WordDictionary* node = this;
        for (char c : word) {
            if (node->child[c - 'a'] == nullptr)
                node->child[c - 'a'] = new WordDictionary();
            node = node->child[c - 'a'];
        }
        node->ended = true;
    }

    bool search(string word) {
        if (word.empty()) return false;
        return dfs(this, word, 0);
    }

    bool dfs(WordDictionary* root, const string& word, int index) {
        assert(root != nullptr); // TODO
        if (index == word.size())
            return root->ended;
        char c = word[index];
        if (c == '.') {
            for (WordDictionary* node : root->child) {
                if (node && dfs(node, word, index + 1))
                    return true;
            }
        }
        else if (c >= 'a' && c <= 'z') {
            if (root->child[c - 'a'] && dfs(root->child[c - 'a'], word, index + 1))
                return true;
        }
        return false;
    }
};

/**
 * Your WordDictionary object will be instantiated and called as such:
 * WordDictionary* obj = new WordDictionary();
 * obj->addWord(word);
 * bool param_2 = obj->search(word);
 */