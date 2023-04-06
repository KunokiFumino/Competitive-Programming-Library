/*
*
* when adding a directed path (u, v, w), execute this:
*     int e = add_edge(u, v, w);
*     int ie = add_edge(v, u, 0);
*     edge_pool[e].inv = ie;
*     edge_pool[ie].inv = e;
* r[i] : the max flow that vertex i can receive.
* To get the real flow on each edge, use the w on original edge minus its correspondance in f.
*
*/
template <typename Twv = int, typename Twe = int> class HighLevelPreflowPush {
private:
    int inf;
    vector<int> h, gap;
public:
    int n;
    Graph<Twv, Twe>* g_;
    vector<Twe> r;
    vector<Edge<Twe> > f;
    HighLevelPreflowPush() : inf(0x3FFFFFFF) {}
    void bind(Graph<Twv, Twe>* g) {
        g_ = g;
        n = g_->n;
        f = g_->edge_pool;
    }
private:
    void bfs(int t) {
        queue<int> q;
        check_memory(h, n);
        for (int i = 0; i < n; i++) h[i] = inf;
        h[t] = 0;
        q.push(t);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int i = 0; i < g_->edges[u].size(); i++) {
                auto& e = f[g_->edges[u][i]];
                if (f[e.inv].w && h[e.z] > h[u] + 1) {
                    h[e.z] = h[u] + 1;
                    q.push(e.z);
                }
            }
        }
    }
public:
    void run(int s, int t) {
        bfs(t);
        h[s] = n - 1;
        check_memory(gap, n << 1);
        for (int i = 0; i < (n << 1); i++) gap[i] = 0;
        for (int i = 0; i < n; i++) {
            if (h[i] < inf) gap[h[i]]++;
        }
        vector<bool> inq(n, false);
        vector<int> q(1);
        check_memory(r, n);
        for (int i = 0; i < g_->edges[s].size(); i++) {
            auto& e = f[g_->edges[s][i]];
            if (e.w) {
                Twe d = e.w;
                e.w -= d;
                f[e.inv].w += d;
                r[s] -= d;
                r[e.z] += d;
                if (e.z != s && e.z != t && !inq[e.z]) {
                    q.push_back(e.z);
                    for (int j = q.size() - 1; j > 1; j >>= 1) {
                        if (h[q[j]] < h[q[j >> 1]]) break;
                        else swap(q[j], q[j >> 1]);
                    }
                    inq[e.z] = true;
                }
            }
        }
        while (q.size() > 1) {
            int u = q[1];
            q[1] = q.back();
            q.pop_back();
            for (int i = 1;;) {
                int j = i;
                if ((i << 1) < q.size() && h[q[j]] < h[q[i << 1]]) j = i << 1;
                if ((i << 1 | 1) < q.size() && h[q[j]] < h[q[i << 1 | 1]]) j = i << 1 | 1;
                if (i != j) {
                    swap(q[i], q[j]);
                    i = j;
                }
                else break;
            }
            inq[u] = false;
            for (int i = 0; i < g_->edges[u].size(); i++) {
                auto& e = f[g_->edges[u][i]];
                if (e.w && h[u] == h[e.z] + 1) {
                    Twe d = min(r[u], e.w);
                    e.w -= d;
                    f[e.inv].w += d;
                    r[u] -= d;
                    r[e.z] += d;
                    if (e.z != s && e.z != t && !inq[e.z]) {
                        q.push_back(e.z);
                        for (int j = q.size() - 1; j > 1; j >>= 1) {
                            if (h[q[j]] < h[q[j >> 1]]) break;
                            else swap(q[j], q[j >> 1]);
                        }
                        inq[e.z] = true;
                    }
                    if (!r[u]) break;
                }
            }
            if (r[u]) {
                --gap[h[u]];
                if (!gap[h[u]]) {
                    for (int i = 0; i < n; i++) {
                        if (i != s && i != t && h[i] > h[u] && h[i] < n) h[i] = n;
                    }
                }
                h[u] = inf;
                for (int i = 0; i < g_->edges[u].size(); i++) {
                    auto& e = f[g_->edges[u][i]];
                    if (e.w && h[u] > h[e.z] + 1) h[u] = h[e.z] + 1;
                }
                ++gap[h[u]];
                q.push_back(u);
                for (int i = q.size() - 1; i > 1; i >>= 1) {
                    if (h[q[i]] < h[q[i >> 1]]) break;
                    else swap(q[i], q[i >> 1]);
                }
                inq[u] = true;
            }
        }
    }
};
