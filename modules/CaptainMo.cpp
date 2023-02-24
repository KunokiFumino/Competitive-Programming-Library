/*
*
* Captain Mo's algorithm is an OFFLINE algorithm that can be used to deal with queries on range, it is basically a optimization of brute force.
* When you can calculate the answer of query (l - 1, r) (l + 1, r) (l, r - 1) (l, r + 1) base on the answer of (l, r) in a short time (O(1) usually), you
* can apply this. Mo's algorithm can optimize the complexity from O(nq)(pure brute force) to O(sqrt(n)(n + q)).
*
* status = 0 : normal range query
*          1 : query on subtree
*          2 : query on path
*
* When status == 0, run reset(n) before adding queries. n is the square root of length of the total range.
* And don't forget to implement function insert, erase and solve.
*
* More details:
* This trick is based on the fact that you can solve(l_, r_) from (l, r) simply by moving the pointer l to l_ and r to r_. So a proper order of processing can
* save loads of effort. How?
* First, split the range into sqrt(n) blocks, each has a length of sqrt(n).
* Second, sort queries by :
*     1. which block its l pointer is in.
*     2. its r pointer.
* In each block, the l pointer moves at most sqrt(n) times in each query, and r pointer moves at most n times over all queries whose l pointers are in this
* block. So the over all complexity is O(sqrt(n)(n + q)). To be more greedy, you can sort block 0's r pointer ascendingly and block 1's r pointer descendingly,
* and so on.
*
* When the problem is about tree, you can map the verteies of tree into its dfs order and become a range.
*
*/
template <typename Twv = int, typename Twe = int> class CaptainMo {
private:
    int block_sz, status, m;
    LowestCommonAncestor<Twv, Twe> lca;
    Graph<Twv, Twe>* t_;
    struct Query {
        int l, r, z, qid, e;
        Query(int l, int r, int z, int qid, int e = -1) : l(l), r(r), z(z), qid(qid), e(e) {}
        bool operator < (const Query rhs) const {
            if (z == rhs.z) return (z & 1) ? (r > rhs.r) : (r < rhs.r);
            return z < rhs.z;
        }
    };
    vector<Query> queries;
    vector<int> p, in, out, c;
    void generate(int u, int f) {
        in[u] = m;
        p[m++] = u;
        for (int i = 0; i < t_->edges[u].size(); i++) {
            auto& e = t_->get_edge(u, i);
            if (e.z == f) continue;
            generate(e.z, u);
        }
        if (status == 1) out[u] = m - 1;
        else if (status == 2) {
            out[u] = m;
            p[m++] = u;
        }
    }
public:
    CaptainMo(int status) : status(status) {}
    void (*insert)(int), (*erase)(int), (*solve)(int);
    void reset(int block_sz) {
        this->block_sz = block_sz;
        queries.clear();
    }
    void bind(Graph<Twv, Twe>* t, int r = 0) {
        t_ = t;
        lca.bind(t_, r);
        p.resize((t_->n) << 1);
        in.resize(t_->n);
        out.resize(t_->n);
        c.assign(t_->n, 0);
        reset(sqrt((t_->n) << 1));
        m = 0;
        generate(r, -1);
    }
    void addQuery(int l, int r, int qid = -1) {
        if (qid == -1) qid = queries.size();
        Query q(l, r, l / block_sz, qid);
        queries.push_back(q);
    }
    void addQueryOnTree(int u, int qid = -1) {
        if (qid == -1) qid = queries.size();
        Query q(in[u], out[u], in[u] / block_sz, qid);
        queries.push_back(q);
    }
    void addQueryOnTree(int u, int v, int qid = -1) {
        if (qid == -1) qid = queries.size();
        int e = lca.query(u, v);
        if (e == u || e == v) e = -1;
        if (out[u] < in[v]) {
            Query q(out[u], in[v], out[u] / block_sz, qid, e);
            queries.push(q);
        }
        else {
            Query q(out[v], in[u], out[v] / block_sz, qid, e);
            queries.push(q);
        }
    }
    void process() {
        sort(queries.begin(), queries.end());
        int l = 0, r = -1;
        for (int i = 0; i < queries.size(); i++) {
            auto& q = queries[i];
            while (r < q.r) {
                r++;
                if (status == 1 || status == 2) {
                    if (c[p[r]] == 1) erase(p[r]);
                    else insert(p[r]);
                    c[p[r]]++;
                }
                else insert(r);
            }
            while (q.l < l) {
                l--;
                if (status == 1 || status == 2) {
                    if (c[p[l]] == 1) erase(p[l]);
                    else insert(p[l]);
                    c[p[l]]++;
                }
                else insert(l);
            }
            while (q.r < r) {
                if (status == 1 || status == 2) {
                    if (c[p[r]] == 2) insert(p[r]);
                    else erase(p[r]);
                    c[p[r]]--;
                }
                else erase(r);
                r--;
            }
            while (l < q.l) {
                if (status == 1 || status == 2) {
                    if (c[p[l]] == 2) insert(p[l]);
                    else erase(p[l]);
                    c[p[l]]--;
                }
                else erase(l);
                l++;
            }
            if (status == 2 && q.e != -1) insert(q.e);
            solve(q.qid);
            if (status == 2 && q.e != -1) erase(q.e);
        }
    }
};