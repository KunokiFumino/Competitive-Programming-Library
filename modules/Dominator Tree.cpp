/*
* Lengauer-Tarjan Algorithm
* complexity : O(VlogV)
* directed graph
* idom : nearest dominator vertex. if vertex v is the starting vertex or unreachable from the starting vertex, idom[v] = -1.
* domin : dominator tree/forest
*/
template <typename Twv = int, typename Twe = int> class DominatorTree {
private:
    Graph<Twv, Twe>* g_;
    Graph<Twv, Twe> semi;
    vector<int> dfn, ord, fa, sdom, uni, mn;
    int C;
public:
    vector<int> idom;
    Graph<Twv, Twe> domin;
private:
    void dfs(int u) {
        ord[dfn[u] = C++] = u;
        for (int i = 0; i < g_->get_fanout(u); i++) {
            int v = g_->get_o_edge(u, i).z;
            if (dfn[v] == -1) {
                fa[v] = u;
                dfs(v);
            }
        }
    }
    int find(int u) {
        if (u == uni[u]) return u;
        int res = find(uni[u]);
        if (dfn[sdom[mn[uni[u]]]] < dfn[sdom[mn[u]]]) mn[u] = mn[uni[u]];
        return uni[u] = res;
    }

public:
    void bind(Graph<Twv, Twe>* g_) {
        this->g_ = g_;
    }
    void run(int u) {
        dfn.assign(g_->V, -1);
        ord.resize(g_->V);
        fa.assign(g_->V, -1);
        idom.resize(g_->V, -1);
        sdom.resize(g_->V);
        uni.resize(g_->V);
        mn.resize(g_->V);
        semi.reset(g_->V);
        domin.reset(g_->V);
        C = 0;
        dfs(u);
        for (int i = 0; i <g_->V; ++i) sdom[i] = uni[i] = mn[i] = i;
        for (int i = C-1; i > 0; i--) {
            int t = ord[i];
            for (int i = 0; i < g_->get_fanin(t);i++) {
                int y = g_->get_i_edge(t,i).a;
                if (dfn[y] == -1) continue;
                find(y);
                if (dfn[sdom[mn[y]]] < dfn[sdom[t]]) sdom[t] = sdom[mn[y]];
            }
            uni[t] = fa[t];
            semi.add_edge(sdom[t], t, Twe(), true);
            for (int i = 0; i < semi.get_fanout(fa[t]); i++) {
                int y = semi.get_o_edge(fa[t],i).z;
                find(y);
                idom[y] = fa[t] == sdom[mn[y]] ? fa[t] : mn[y];
            }
            semi.vp[fa[t]].oep.clear();
        }
        for (int i = 1; i < C; ++i) {
            int t = ord[i];
            if (idom[t] ^ sdom[t]) idom[t] = idom[idom[t]];
        }
        for (int i = 0; i < g_->V; i++) {
            if (idom[i] == -1) continue;
            domin.add_edge(idom[i], i, Twe(), true);
        }
    }
};