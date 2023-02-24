class Trie {
public:
    int n, bias;
    vector<vector<int> > t;
    vector<int> id, fail, last, sz;

    Trie(int n = 26, int bias = 'a') : n(n), bias(bias), t(1, vector<int>(n, 0)), id(1, -1), fail(1, 0), last(1, 0), sz(1, 0) {}
    template<typename T> void insert(const T& p, int sid = 0) {
        int u = 0;
        for (int i = 0; i < p.size(); i++) {
            sz[u]++;
            int& v = t[u][p[i] - bias];
            if (!v) {
                v = t.size();
                t.push_back(vector<int>(n, 0));
                id.push_back(-1);
                fail.push_back(0);
                last.push_back(0);
                sz.push_back(0);
            }
            u = v;
        }
        id[u] = sid;
        sz[u]++;
    }
    template<typename T> void erase(const T& p) {
        int u = 0;
        for (int i = 0; i < p.size(); i++) {
            int& v = t[u][p[i] - bias];
            if (!v) return;
            u = v;
        }
        u = 0;
        for (int i = 0; i < p.size(); i++) {
            sz[u]--;
            int v = t[u][p[i] - bias];
            if (sz[v] == 1) t[u][p[i] - bias] = 0;
            u = v;
        }
        id[u] = -1;
        sz[u]--;
    }
    template<typename T> int find(const T& p) {
        int u = 0;
        for (int i = 0; i < p.size(); i++) {
            int& v = t[u][p[i] - bias];
            if (!v) return -1;
            u = v;
        }
        return u;
    }
    void reset() {
        t.assign(1, vector<int>(n, 0));
        id.assign(1, -1);
        fail.assign(1, 0);
        last.assign(1, 0);
        sz.assign(1, 0);
    }
};