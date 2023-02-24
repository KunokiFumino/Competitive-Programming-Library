template <typename Twv = int, typename Twe = int> class Toposort {
public:
    int n;
    Graph<Twv, Twe>* g_;
    vector<int> v;
private:
    vector<int> d;
public:
    void bind(Graph<Twv, Twe>* g) {
        g_ = g;
        n = g_->n;
    }
    void run() {
        check_memory(d, n);
        for (int i = 0; i < n; i++) d[i] = 0;
        for (int i = 0; i < g_->edge_pool.size(); i++) {
            auto& e = g_->edge_pool[i];
            d[e.z]++;
        }
        for (int i = 0; i < n; i++) {
            if (d[i] == 0) v.push_back(i);
        }
        for (int i = 0; i < v.size(); i++) {
            int u = v[i];
            for (int i = 0; i < g_->edges[u].size(); i++) {
                auto& e = g_->edge_pool[g_->edges[u][i]];
                d[e.z]--;
                if (d[e.z] == 0) v.push_back(e.z);
            }
        }
    }
};