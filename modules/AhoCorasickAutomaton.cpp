class AhoCorasickAutomaton {
public:
    int n, bias;
    vector<vector<int> > res;
private:
    int m;
    Trie trie;
public:
    AhoCorasickAutomaton(int n = 26, int bias = 'a') : n(n), bias(bias), m(0), trie(n, bias) {}
    template<typename T> void insert(const T& p, int id = 0) {
        trie.insert(p, id);
        m = max(m, id);
    }
    void build() {
        queue<int> q;
        for (int i = 0; i < n; i++) {
            int v = trie.t[0][i];
            if (v) {
                trie.fail[v] = 0;
                q.push(v);
            }
        }
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int i = 0; i < n; i++) {
                int& v = trie.t[u][i];
                if (v) {
                    q.push(v);
                    trie.fail[v] = trie.t[trie.fail[u]][i];
                    trie.last[v] = trie.id[trie.fail[v]] == -1 ? trie.last[trie.fail[v]] : trie.fail[v];
                }
                else v = trie.t[trie.fail[u]][i];
            }
        }
        res.assign(m + 1, vector<int>());
    }
    template<typename T> void match(const T& p) {
        for (int i = 0; i < res.size(); i++) res[i].clear();
        int u = 0;
        for (int i = 0; i < p.size(); i++) {
            u = trie.t[u][p[i] - bias];
            int v = trie.id[u] == -1 ? trie.last[u] : u;
            while (v) {
                res[trie.id[v]].push_back(i);
                v = trie.last[v];
            }
        }
    }
};