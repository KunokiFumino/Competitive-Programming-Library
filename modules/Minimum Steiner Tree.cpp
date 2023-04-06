/*
* complexity : O(V * 3^K + VE * 2^K)
* undirected graph
* the solution will be restored in vector pick, if pick[i] == 1, then vertex i is in minimum steiner tree.
*/
template <typename Twv = int, typename Twe = int> class MinimumSteinerTree {
private:
    Graph<Twv, Twe>* g_;
    vector<vector<Twv> > dpv;
    vector<vector<Twe> > dpe;
    vector<vector<Twe> > dp;
    struct Node {
        int z, S;
    };
    vector<vector<Node> > pre;
    queue<int> q;
    vector<int> inq;
    Twv Inf_Twv;
    Twe Inf_Twe;
public:
    vector<int> pick;
private:
    void bfs_v(int S) {
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            inq[u] = 0;
            for (int i = 0; i < g_->get_fanout(u); i++) {
                auto& e = g_->get_o_edge(u, i);
                if (dpv[e.z][S] > dpv[u][S] + g_->vp[u].w) {
                    dpv[e.z][S] = dpv[u][S] + g_->vp[u].w;
                    pre[e.z][S] = { u,S };
                    if (!inq[e.z]) {
                        q.push(e.z);
                        inq[e.z] = 1;
                    }
                }
            }
        }
    }
    void bfs_e(int S) {
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            inq[u] = 0;
            for (int i = 0; i < g_->get_fanout(u); i++) {
                auto& e = g_->get_o_edge(u, i);
                if (dpe[e.z][S] > dpe[u][S] + e.w) {
                    dpe[e.z][S] = dpe[u][S] + e.w;
                    pre[e.z][S] = { u,S };
                    if (!inq[e.z]) {
                        q.push(e.z);
                        inq[e.z] = 1;
                    }
                }
            }
        }
    }
    void dfs(int u, int S) {
        pick[u] = 1;
        Node n = pre[u][S];
        if (!n.S) return;
        if (n.z == u) dfs(u, S ^ (n.S));
        dfs(n.z, n.S);
    }
public:
    MinimumSteinerTree() : Inf_Twv(0x3FFFFFFF), Inf_Twe(0x3FFFFFFF) {}
    void bind(Graph<Twv, Twe>* g_) {
        this->g_ = g_;
        inq.assign(g_->V, 0);
    }
    void run_on_vertex(const vector<int>& p) {
        int K = p.size();
        if (!K) return;
        dpv.assign(g_->V, vector<Twe>((1 << K), Inf_Twv));
        pre.assign(g_->V, vector<Node>((1 << K), { 0,0 }));
        for (int i = 0; i < K; i++) dpv[p[i]][1 << i] = 0;
        for (int S1 = 1; S1 < (1 << K); S1++) {
            for (int i = 0; i < g_->V; i++) {
                for (int S2 = S1 & (S1 - 1); S2; S2 = S1 & (S2 - 1)) {
                    if (dpv[i][S1] > dpv[i][S2] + dpv[i][S1 ^ S2] - g_->vp[i].w) {
                        dpv[i][S1] = dpv[i][S2] + dpv[i][S1 ^ S2] - g_->vp[i].w;
                        pre[i][S1] = { i,S2 };
                    }
                }
                if (dpv[i][S1] < Inf_Twv) {
                    q.push(i);
                    inq[i] = 1;
                }
            }
            bfs_v(S1);
        }
        pick.assign(g_->V, 0);
        dfs(p[0], (1 << K) - 1);
    }
    void run_on_edge(const vector<int>& p) {
        int K = p.size();
        if (!K) return;
        dpe.assign(g_->V, vector<Twe>((1 << K), Inf_Twe));
        pre.assign(g_->V, vector<Node>((1 << K), { 0,0 }));
        for (int i = 0; i < K; i++) dpe[p[i]][1 << i] = 0;
        for (int S1 = 1; S1 < (1 << K); S1++) {
            for (int i = 0; i < g_->V; i++) {
                for (int S2 = S1 & (S1 - 1); S2; S2 = S1 & (S2 - 1)) {
                    if (dpe[i][S1] > dpe[i][S2] + dpe[i][S1 ^ S2]) {
                        dpe[i][S1] = dpe[i][S2] + dpe[i][S1 ^ S2];
                        pre[i][S1] = { i,S2 };
                    }
                }
                if (dpe[i][S1] < Inf_Twe) {
                    q.push(i);
                    inq[i] = 1;
                }
            }
            bfs_e(S1);
        }
        pick.assign(g_->V, 0);
        dfs(p[0], (1 << K) - 1);
    }
};