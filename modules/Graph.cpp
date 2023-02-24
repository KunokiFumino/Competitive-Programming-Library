template <typename Twv = int, typename Twe = int> class Graph {
public:
    int n;
    vector<Twv> w;
    vector<Edge<Twe> > edge_pool;
    vector<vector<int> > edges;
    vector<int> f, d, sz;

public:
    void reset(int n) {
        this->n = n;
        edge_pool.clear();
        edges.assign(n, vector<int>());
        w.assign(n, Twv());
        f.assign(n, -1);
        d.assign(n, 0);
        sz.assign(n, 1);
    }
    void add_edge(int x, int y, Twe w, bool f = true) {
        Edge<Twe> e(x, y, w);
        edge_pool.push_back(e);
        int eid = edge_pool.size() - 1;
        edges[x].push_back(eid);
        if (!f) {
            Edge<Twe> ie(y, x, w);
            edge_pool.push_back(ie);
            int ieid = edge_pool.size() - 1;
            edges[y].push_back(ieid);
            edge_pool[eid].inv = ieid;
            edge_pool[ieid].inv = eid;
        }
    }
    Edge<Twe>& get_edge(int u, int i) {
        return edge_pool[edges[u][i]];
    }
    //q is a vector of size n, if q[u] != 0, u will be ignored during dfs process.
    void root(int u, int v = -1, vector<int>* q = NULL) {
        f[u] = v;
        d[u] = v == -1 ? 0 : d[v] + 1;
        sz[u] = 1;
        for (int i = 0; i < edges[u].size(); i++) {
            auto& e = edge_pool[edges[u][i]];
            if (e.z == v) continue;
            if (q != NULL && (*q)[e.z]) continue;
            root(e.z, u, q);
            sz[u] += sz[e.z];
        }
    }

private:
    int centroid, sz_inf, temp_sz;
    vector<int> max_sub_sz;
    void dfs(int u, int v, vector<int>* q = NULL) {
        max_sub_sz[u] = 0;
        for (int i = 0; i < edges[u].size(); i++) {
            auto& e = edge_pool[edges[u][i]];
            if (e.z == v) continue;
            if (q != NULL && (*q)[e.z]) continue;
            max_sub_sz[u] = max(max_sub_sz[u], sz[e.z]);
            dfs(e.z, u, q);
        }
        max_sub_sz[u] = max(max_sub_sz[u], temp_sz - sz[u]);
        if (max_sub_sz[u] < sz_inf) {
            centroid = u;
            sz_inf = max_sub_sz[u];
        }
    }
public:
    /*
    * q is a vector of size n, if q[u] != 0, u will be ignored during dfs process, in here they are usually previous centroids.
    * Divide and conquer on tree is usually used to deal with mess of paths on tree.
    * Centroid of a tree is a vertex of tree whose maximum size of subtree is minimum over all vertexes if consider it is the root of the tree.
    * Then paths can be divide into two categories: pass the centroid or completely belong to its subtrees. This can be solved recursively.
    * There would be O(log2(n)) levels of centroids, and each level takes O(n) to find them out.
    */
    int get_centroid(int u, vector<int>* q = NULL) {
        root(u, -1, q);
        if (max_sub_sz.size() < n) max_sub_sz.resize(n);
        sz_inf = 0x3FFFFFFF;
        centroid = u;
        temp_sz = sz[u];
        dfs(u, -1, q);
        return centroid;
    }
};