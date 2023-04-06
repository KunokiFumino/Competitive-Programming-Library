class DisjointSetUnion {
private:
    /*
    * f : current father
    * w : the relationship FROM f TO this node
    * rank : the depth under this node
    */
    struct Node {
        int f, w, rank;
    };
    /*
    * N : size of disjoint set union
    * t : the real index of original node
    */
    int N;
    vector<int> t;
    vector<Node> nodes;
    void internal_merge(int u, int v, int d = 0, bool by_rank = true) {
        int fu = internal_get_father(u), fv = internal_get_father(v);
        if (fu == fv) return;
        if (nodes[fu].rank < nodes[fv].rank && by_rank) {
            nodes[fu].f = v;
            nodes[fu].w = nodes[v].w - nodes[u].w - d;
        }
        else {
            nodes[fv].f = fu;
            nodes[fv].w = nodes[u].w - nodes[v].w + d;
            if (nodes[fu].rank == nodes[fv].rank) nodes[fu].rank++;
        }
    }
    int internal_get_father(int u) {
        if (nodes[u].f == u) return u;
        int fu = nodes[u].f;
        nodes[u].f = internal_get_father(fu);
        nodes[u].w += nodes[fu].w;
        return nodes[u].f;
    }
public:
    void reset(int N) {
        this->N = N;
        nodes.resize(N);
        t.resize(N);
        for (int i = 0; i < N; i++) {
            t[i] = i;
            nodes[i].f = i;
            nodes[i].w = 0;
            nodes[i].rank = 0;
        }
    }
    int get_father(int u) {
        return internal_get_father(t[u]);
    }
    /*
    * When d != 0, it is not only merge set(u) and set(v), but rather create a relationship between u and v, which is described by an integer d.
    */
    void merge(int u, int v, int d = 0, bool by_rank = true) {
        internal_merge(t[u], t[v], d, by_rank);
    }
    void isolate(int u) {
        int n = nodes.size();
        Node v;
        v.f = n;
        v.w = 0;
        v.rank = 0;
        nodes.push_back(v);
        t[u] = n;
    }
    Node get_node(int u) {
        return nodes[t[u]];
    }
};