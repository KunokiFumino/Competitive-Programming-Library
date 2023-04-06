/*
* min heap
*/
template <typename T = int> class LeftistTree {
private:
    struct Node {
        T d;
        int f, z, t[2];
    };
    vector<Node> nodes;
    int ptr;

    int rs(int u) {
        return nodes[nodes[u].t[0]].z < nodes[nodes[u].t[1]].z ? 0 : 1;
    }
    void push_up(int u) {
        if (!u) return;
        int r = rs(u);
        if (nodes[u].z != nodes[nodes[u].t[r]].z + 1) {
            nodes[u].z = nodes[nodes[u].t[r]].z + 1;
            push_up(nodes[u].f);
        }
    }
public:
    void reset(int n) {
        ptr = 0;
        nodes.resize(n);
        nodes[0].f = nodes[0].z = nodes[0].t[0] = nodes[0].t[1] = 0;
    }
    int merge(int u, int v) {
        if (!u || !v) return u | v;
        if (nodes[v].d < nodes[u].d) swap(u, v);
        int r = rs(u);
        nodes[u].t[r] = merge(nodes[u].t[r], v);
        nodes[nodes[u].t[r]].f = u;
        push_up(u);
        return u;
    }
    int create(T x) {
        ptr++;
        nodes[ptr].d = x;
        nodes[ptr].f = 0;
        nodes[ptr].z = 1;
        nodes[ptr].t[0] = nodes[ptr].t[1] = 0;
        return ptr;
    }
    void insert(int u, T x) {
        merge(u, create(x));
    }
    int isolate(int u) {
        int v = merge(nodes[u].t[0], nodes[u].t[1]);
        if (v) {
            int f = nodes[u].f;
            nodes[v].f = f;
            if (f) {
                if (nodes[f].t[0] == u) nodes[f].t[0] = v;
                else nodes[f].t[1] = v;
                push_up(f);
            }
        }
        return v;
    }
    Node get_node(int u) {
        return nodes[u];
    }
    int get_top(int u) {
        while (nodes[u].f) u = nodes[u].f;
        return u;
    }
};