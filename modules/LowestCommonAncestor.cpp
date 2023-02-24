template <typename Twv = int, typename Twe = int> class LowestCommonAncestor {
private:
    vector<vector<int> > ancestor;
    bool initialized;
    Graph<Twv, Twe>* t_;
    int n, R;
public:
    void bind(Graph<Twv, Twe>* t, int r = 0) {
        t_ = t;
        R = r;
        t_->root(R);
        initialized = false;
    }
    int query(int u, int v) {
        if (!initialized) initialize();
        if (t_->d[u] > t_->d[v]) swap(u, v);
        int d = 0;
        while (t_->d[u] != t_->d[v]) {
            if ((t_->d[v] - t_->d[u]) & (1 << d)) v = ancestor[v][d];
            d++;
        }
        if (u == v) return u;
        for (int i = ancestor[0].size() - 1; i >= 0; i--) {
            if (ancestor[u][i] != ancestor[v][i]) {
                u = ancestor[u][i];
                v = ancestor[v][i];
            }
        }
        return ancestor[u][0];
    }
private:
    void initialize() {
        check_memory(ancestor, n);
        int sz = n, p = 1;
        while (sz) {
            sz >>= 1;
            p++;
        }
        for (int i = 0; i < n; i++) check_memory(ancestor[i], p);
        for (int i = 0; i < n; i++) ancestor[i][0] = t_->f[i];
        for (int i = 0; i < p; i++) ancestor[R][i] = -1;
        for (int i = 1; i < p; i++) {
            for (int j = 0; j < n; j++) {
                if (ancestor[j][i - 1] == -1) ancestor[j][i] = -1;
                else ancestor[j][i] = ancestor[ancestor[j][i - 1]][i - 1];
            }
        }
        initialized = true;
    }
};