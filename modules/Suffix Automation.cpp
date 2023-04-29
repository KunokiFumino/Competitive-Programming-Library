/*
*
* n : size of alphabet
* bias : bias
* last : the last state (the initial state is 0)
* sz : number of states
* t[x][y] : the next state from state x plus letter y
* v[x][y] : the total number of substrings you can possiblely get if you from state x plus letter y (same substring will be count separately at each appearance)
* f[x] : the father state of state x in state tree
* m[x] : the maximum length of state x
* c[x] : the size of endpos set of state x
*
*/
class SuffixAutomation {
private:
    int N, bias, last, sz, status;
    vector<int> path;
    struct Node {
        vector<int> t;
        vector<long long> v;
        long long sumv;
        int f, m, c;
        Node(int n) : sumv(-1), f(0), m(0), c(0) {
            t.assign(n, 0);
            v.assign(n, -1);
        }
    };
    vector<Node> nodes;
    void dfs(int x) {
        nodes[x].sumv = 0;
        for (int i = 0; i < N; i++) {
            if (nodes[x].t[i] && nodes[x].v[i] == -1) {
                int y = nodes[x].t[i];
                if (nodes[y].sumv == -1) dfs(y);
                nodes[x].v[i] = nodes[y].c + nodes[y].sumv;
                nodes[x].sumv += nodes[x].v[i];
            }
        }
    }
public:
    SuffixAutomation(int n, int bias) : N(n), bias(bias), last(0) {}
    template<typename T> void build(const T& s) {
        sz = 1;
        path.reserve(s.size());
        nodes.assign(s.size() << 1, Node(N));
        nodes[0].f = -1;
        for (int i = 0; i < s.size(); i++) {
            int x = s[i] - bias;
            int np = sz++, p = last;
            nodes[np].m = nodes[p].m + 1;
            nodes[np].c = 1;
            for (; p != -1 && !nodes[p].t[x]; p = nodes[p].f) nodes[p].t[x] = np;
            if (p == -1) nodes[np].f = 0;
            else {
                int q = nodes[p].t[x];
                if (nodes[q].m == nodes[p].m + 1) nodes[np].f = q;
                else {
                    int nq = sz++;
                    nodes[nq].t = nodes[q].t;
                    nodes[nq].f = nodes[q].f;
                    nodes[nq].m = nodes[p].m + 1;
                    nodes[np].f = nodes[q].f = nq;
                    for (; p != -1 && nodes[p].t[x] == q; p = nodes[p].f) nodes[p].t[x] = nq;
                }
            }
            last = np;
        }
        queue<int> q;
        vector<int> d(sz, 0);
        for (int i = 1; i < sz; i++) d[nodes[i].f]++;
        for (int i = 1; i < sz; i++) {
            if (d[i] == 0) q.push(i);
        }
        while (!q.empty()) {
            int x = q.front();
            q.pop();
            nodes[nodes[x].f].c += nodes[x].c;
            d[nodes[x].f]--;
            if (!d[nodes[x].f] && nodes[x].f) q.push(nodes[x].f);
        }
        dfs(0);
    }
    void reset() {
        status = 0;
        path.clear();
    }
    int end() { return last; }
    const vector<int>& get_cuttent_path() { return path; }
    void transform(int p) { 
        status = nodes[status].t[p - bias];
        if (status) path.push_back(p);
        else path.clear();
    }
    int peek_transform(int p) { return nodes[status].t[p - bias]; }
    int peek_transform(int x, int p) { return nodes[x].t[p - bias]; }
    long long count_appearances(int p) { return nodes[status].v[p - bias]; }
    long long count_appearances(int x, int p) { return nodes[x].v[p - bias]; }
    int get_maximum_length() { return nodes[status].m; }
    int get_maximum_length(int x) { return nodes[x].m; }
    int get_endpos_set_size() { return nodes[status].c; }
    int get_endpos_set_size(int x) { return nodes[x].c; }
};