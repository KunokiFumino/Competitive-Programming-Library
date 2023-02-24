template <typename Twv = int, typename Twe = int> class Tarjan {
public:
    int n;
    Graph<Twv, Twe>* g_, * dag_;
    vector<int> sid, bridges, aps;
private:
    int dep, m;
    vector<int> dfn, low, ins;
    stack<int> s;
    vector<tuple<int, int, Twe> > edges;

    void dfs(int x, int r) {
        dfn[x] = low[x] = ++dep;
        s.push(x);
        ins[x] = 1;
        int child = 0, is_ap = 0;
        for (int i = 0; i < g_->edges[x].size(); i++) {
            auto& e = g_->edge_pool[g_->edges[x][i]];
            if (!dfn[e.z]) {
                dfs(e.z, r);
                child++;
                low[x] = min(low[x], low[e.z]);
                if (dfn[x] < low[e.z]) bridges.push_back(g_->edges[x][i]);
                if (dfn[x] <= low[e.z] && x != r) is_ap = true;
            }
            else if (ins[e.z]) low[x] = min(low[x], dfn[e.z]);
        }
        if (x == r && child > 1) is_ap = true;
        if (is_ap) aps.push_back(x);
        if (low[x] == dfn[x]) {
            while (!s.empty()) {
                int y = s.top();
                s.pop();
                ins[y] = 0;
                sid[y] = m;
                if (y == x) break;
            }
            m++;
        }
    }
public:
    void bind(Graph<Twv, Twe>* g) {
        g_ = g;
        n = g_->n;
    }
    void run() {
        check_memory(dfn, n);
        check_memory(low, n);
        check_memory(ins, n);
        check_memory(sid, n);
        bridges.clear();
        aps.clear();
        while (!s.empty()) s.pop();
        for (int i = 0; i < n; i++) dfn[i] = low[i] = ins[i] = sid[i] = 0;
        dep = m = 0;
        for (int i = 0; i < n; i++) {
            if (!dfn[i]) dfs(i, i);
        }
    }
    void generate_dag(bool f = false) {
        if (dag_ == NULL) dag_ = new Graph<Twv, Twe>;
        dag_->reset(m);
        edges.clear();
        for (int i = 0; i < g_->edge_pool.size(); i++) {
            auto& e = g_->edge_pool[i];
            if (sid[e.a] != sid[e.z]) edges.push_back({ sid[e.a],sid[e.z],e.w });
        }
        if (edges.empty()) return;
        sort(edges.begin(), edges.end());
        int lu = get<0>(edges[0]), lv = get<1>(edges[0]), lw = get<2>(edges[0]);
        dag_->add_edge(lu, lv, lw);
        for (int i = 1; i < edges.size(); i++) {
            int u = get<0>(edges[i]), v = get<1>(edges[i]), w = get<2>(edges[i]);
            if (lu == u && lv == v && !f) continue;
            dag_->add_edge(u, v, w);
            lu = u;
            lv = v;
            lw = w;
        }
    }
};
