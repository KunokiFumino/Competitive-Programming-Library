/*
*
* n : size of dsu
* p : length of the logical circle
* f[i] : i's father
* sz[i] : size of set i (when i is the root vertex)
* w[i] : the logical distance from f[i] to i (p - w[i] if from i to f[i])
* rank[i] : the depth of set i (when i is the root vertex)
*
*/
class DisjointSetUnion {
public:
    int n, p;
    vector<int> f, sz, w, rank;

    DisjointSetUnion(int n, int p = 1) : n(n), p(p) {
        check_memory(f, n);
        check_memory(sz, n);
        check_memory(w, n);
        check_memory(rank, n);
        for (int i = 0; i < n; i++) {
            f[i] = i;
            sz[i] = 1;
            w[i] = 0;
            rank[i] = 0;
        }
    }
    int getFather(int x) {
        if (f[x] == x) return x;
        int fx = f[x];
        f[x] = getFather(fx);
        w[x] += w[fx];
        return f[x];
    }
    //d(a -> b) = c
    void merge(int a, int b, int c = 0) {
        int wa = w[a], wb = w[b];
        a = getFather(a);
        b = getFather(b);
        if (rank[a] < rank[b]) {
            f[a] = b;
            sz[b] += sz[a];
            w[a] = p - c - wa + wb;
        }
        else {
            f[b] = a;
            sz[a] += sz[b];
            w[b] = c + wa - wb;
            if (rank[a] == rank[b]) rank[a]++;
        }
    }
};