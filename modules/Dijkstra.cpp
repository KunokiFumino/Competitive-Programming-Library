template <typename Twv = int, typename Twe = int> class Dijkstra {
public:
    int n;
    vector<Twe> shortest_path;
    Graph<Twv, Twe>* g_;
    Twe inf;
private:
    vector<int> st;
    vector<Twe> temp;
    void build(int x, int l, int r) {
        if (l + 1 == r) st[x] = l;
        else {
            int mid = (l + r) >> 1;
            build(x << 1, l, mid);
            build(x << 1 | 1, mid, r);
            st[x] = temp[st[x << 1]] < temp[st[x << 1 | 1]] ? st[x << 1] : st[x << 1 | 1];
        }
    }
    void update(int x, int l, int r, int p) {
        if (l + 1 == r) return;
        else {
            int mid = (l + r) >> 1;
            if (p < mid) update(x << 1, l, mid, p);
            else update(x << 1 | 1, mid, r, p);
            st[x] = temp[st[x << 1]] < temp[st[x << 1 | 1]] ? st[x << 1] : st[x << 1 | 1];
        }
    }
public:
    Dijkstra() : inf(0x3FFFFFFF) {}
    void bind(Graph<Twv, Twe>* g) {
        g_ = g;
        n = g_->n;
        shortest_path.assign(n, inf);
    }
    void run(int s) {
        temp = shortest_path;
        temp[s] = 0;
        check_memory(st, n << 2);
        build(1, 0, n);
        vector<bool> f(n, false);
        for (int i = 1; i < n; i++) {
            int u = st[1];
            shortest_path[u] = temp[u];
            for (int i = 0; i < g_->edges[u].size(); i++) {
                auto& e = g_->edge_pool[g_->edges[u][i]];
                if (f[e.z]) continue;
                if (temp[e.z] > temp[u] + e.w) {
                    temp[e.z] = temp[u] + e.w;
                    update(1, 0, n, e.z);
                }
            }
            f[u] = true;
            temp[u] = inf + 1;
            update(1, 0, n, u);
        }
        shortest_path[st[1]] = temp[st[1]];
    }
};