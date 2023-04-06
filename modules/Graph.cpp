/*
* w : weight
* f : father
* d : depth
* sz : size of subtree rooted in this vertex.
* iep : indices of edges that ended in this vertex.
* oep : indices of edges that started from this vertex.
*/
template <typename Twv> class Vertex {
public:
    Twv w;
    int f, d, sz;
    vector<int> iep;
    vector<int> oep;
    Vertex() {}
    Vertex(Twv w) : w(w) {}
    bool operator < (const Vertex& rhs) const {
        return w < rhs.w;
    }
};
/*
* w : weight
* a : starting vertex
* z : ending vertex
* inv : the index of the reverse edge if this edge is undirected, otherwise equals -1.
*/
template <typename Twe> class Edge {
public:
    Twe w;
    int a, z, inv;
    Edge() : inv(-1) {}
    Edge(int a, int z, Twe w) : a(a), z(z), w(w), inv(-1) {}
    bool operator < (const Edge& rhs) const {
        return w < rhs.w;
    }
};
/*
* V : number of vertices.
* E : number of edges.
* vp : vertices.
* ep : edges.
* the graph is 0-indexed.
*/
template <typename Twv = int, typename Twe = int> class Graph {
public:
    int V, E;
    vector<Vertex<Twv> > vp;
    vector<Edge<Twe> > ep;

public:
    void reset(int n) {
        V = n;
        E = 0;
        vp.assign(V, Vertex<Twv>());
        ep.clear();
    }
    void add_edge(int x, int y, Twe w, bool f = true) {
        Edge<Twe> e(x, y, w);
        ep.push_back(e);
        int eid = E++;
        vp[x].oep.push_back(eid);
        vp[y].iep.push_back(eid);
        if (!f) {
            Edge<Twe> ie(y, x, w);
            ep.push_back(ie);
            int ieid = E++;
            vp[y].oep.push_back(ieid);
            vp[x].iep.push_back(ieid);
            ep[eid].inv = ieid;
            ep[ieid].inv = eid;
        }
    }
    int get_fanin(int u) {
        return vp[u].iep.size();
    }
    int get_fanout(int u) {
        return vp[u].oep.size();
    }
    Edge<Twe>& get_i_edge(int u, int i) {
        return ep[vp[u].iep[i]];
    }
    Edge<Twe>& get_o_edge(int u, int i) {
        return ep[vp[u].oep[i]];
    }
    /*
    * q is a vector of size n, if q[u] != 0, vertex u will be ignored during the process, that is, the rooting process will be applied only on a limitted area.
    */
    void root(int u, int v = -1, vector<int>* q = NULL) {
        vp[u].f = v;
        vp[u].d = v == -1 ? 0 : vp[v].d + 1;
        vp[u].sz = 1;
        for (int i = 0; i < get_fanout(u); i++) {
            auto& e = get_o_edge(u, i);
            if (e.z == v) continue;
            if (q != NULL && (*q)[e.z]) continue;
            root(e.z, u, q);
            vp[u].sz += vp[e.z].sz;
        }
    }

private:
    int centroid, sz_inf, temp_sz;
    vector<int> max_sub_sz;
    void get_max_sub_sz(int u, int v, vector<int>* q = NULL) {
        max_sub_sz[u] = 0;
        for (int i = 0; i < get_fanout(u); i++) {
            auto& e = get_o_edge(u, i);
            if (e.z == v) continue;
            if (q != NULL && (*q)[e.z]) continue;
            max_sub_sz[u] = max(max_sub_sz[u], vp[e.z].sz);
            get_max_sub_sz(e.z, u, q);
        }
        max_sub_sz[u] = max(max_sub_sz[u], temp_sz - vp[u].sz);
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
        if (max_sub_sz.size() < V) max_sub_sz.resize(V);
        sz_inf = 0x3FFFFFFF;
        centroid = u;
        temp_sz = vp[u].sz;
        get_max_sub_sz(u, -1, q);
        return centroid;
    }
};