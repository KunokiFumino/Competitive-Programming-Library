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
public:
    int n, bias, last, sz;
    vector<vector<int> > t;
    vector<vector<long long> > v;
    vector<int> f, m, c;
private:
    vector<long long> sumv;
    void dfs(int x) {
        sumv[x] = 0;
        for (int i = 0; i < n; i++) {
            if (t[x][i] && v[x][i] == -1) {
                int y = t[x][i];
                if (sumv[y] == -1) dfs(y);
                v[x][i] = c[y] + sumv[y];
                sumv[x] += v[x][i];
            }
        }
    }
public:
    SuffixAutomation(int n = 26, int bias = 'a') : n(n), bias(bias), last(0) {}
    template<typename T> void build(const T& s) {
        sz = 1;
        t.assign(s.size() << 1, vector<int>(n, 0));
        f.assign(s.size() << 1, 0);
        m.assign(s.size() << 1, 0);
        c.assign(s.size() << 1, 0);
        f[0] = -1;
        for (int i = 0; i < s.size(); i++) {
            int x = s[i] - bias;
            int np = sz++, p = last;
            m[np] = m[p] + 1;
            c[np] = 1;
            for (; p != -1 && !t[p][x]; p = f[p]) t[p][x] = np;
            if (p == -1) f[np] = 0;
            else {
                int q = t[p][x];
                if (m[q] == m[p] + 1) f[np] = q;
                else {
                    int nq = sz++;
                    t[nq] = t[q];
                    f[nq] = f[q];
                    m[nq] = m[p] + 1;
                    f[np] = f[q] = nq;
                    for (; p != -1 && t[p][x] == q; p = f[p]) t[p][x] = nq;
                }
            }
            last = np;
        }
        queue<int> q;
        vector<int> d(sz, 0);
        for (int i = 1; i < sz; i++) d[f[i]]++;
        for (int i = 1; i < sz; i++) {
            if (d[i] == 0) q.push(i);
        }
        while (!q.empty()) {
            int x = q.front();
            q.pop();
            c[f[x]] += c[x];
            d[f[x]]--;
            if (!d[f[x]] && f[x]) q.push(f[x]);
        }
        v.assign(s.size() << 1, vector<long long>(n, -1));
        sumv.assign(s.size() << 1, -1);
        dfs(0);
    }
};