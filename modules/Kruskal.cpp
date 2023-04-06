/*
* The minimum spanning tree will be restored in mst.
*/
template <typename Twv = int, typename Twe = int> class Kruskal {
private:
    Graph<Twv, Twe>* g_;
    vector<int> f;
    DisjointSetUnion dsu;
public:
    Graph<Twv, Twe> mst;
    void bind(Graph<Twv, Twe>* g_) {
        this->g_ = g_;
        dsu.reset(g_->V);
    }
    /*
    * set vector q to generate minimum spanning tree for only limitted vertices.
    */
    void run(vector<int>* q = NULL) {
        mst.reset(g_->V);
        if (q != NULL) {
            f.assign(g_->V, 0);
            for (int i = 0; i < (*q).size(); i++) f[(*q)[i]] = 1;
        }
        else f.assign(g_->V, 1);
        auto ep = g_->ep;
        sort(ep.begin(), ep.end());
        for (int i = 0; i < ep.size(); i++) {
            auto& e = ep[i];
            if (!f[e.a] || !f[e.z]) continue;
            int u = dsu.get_father(e.a), v = dsu.get_father(e.z);
            if (u != v) {
                dsu.merge(u, v);
                mst.add_edge(e.a, e.z, e.w, false);
            }
        }
    }
};