template<typename T = int> class SizeBalancedTree {
public:
    int R, ptr;
    vector<T> d;
    vector<int> t[2], sz;
    void reset(int n) {
        R = 0;
        ptr = 1;
        d.resize(n);
        t[0].assign(n, 0);
        t[1].assign(n, 0);
        sz.assign(n, 1);
        sz[0] = 0;
    }
    void push_up(int R) {
        sz[R] = 1 + sz[t[0][R]] + sz[t[1][R]];
    }
    void rotate(int& R, int p) {
        int y = t[p ^ 1][R];
        t[p ^ 1][R] = t[p][y];
        t[p][y] = R;
        push_up(R);
        push_up(y);
        R = y;
    }
    void adjust(int& R, int p) {
        if (sz[t[p][t[p][R]]] > sz[t[p ^ 1][R]]) rotate(R, p ^ 1);
        else if (sz[t[p ^ 1][t[p][R]]] > sz[t[p ^ 1][R]]) {
            rotate(t[p][R], p);
            rotate(R, p ^ 1);
        }
        else return;
        adjust(t[0][R], 0);
        adjust(t[1][R], 1);
        adjust(R, 0);
        adjust(R, 1);
    }
    int prev(int R) {
        R = t[0][R];
        if (!R) return 0;
        while (t[1][R]) R = t[1][R];
        return R;
    }
    int succ(int R) {
        R = t[1][R];
        if (!R) return 0;
        while (t[0][R]) R = t[0][R];
        return R;
    }
    void insert(int& R, T x) {
        if (!R) {
            R = ptr++;
            d[R] = x;
        }
        else {
            sz[R]++;
            int p = x < d[R] ? 0 : 1;
            insert(t[p][R], x);
            adjust(R, p);
        }
    }
    void insert(T x) {
        insert(R, x);
    }
    bool erase(int& R, T x) {
        if (!R) return false;
        if (d[R] == x) {
            if (!t[0][R]) {
                R = t[1][R];
                return true;
            }
            if (!t[1][R]) {
                R = t[0][R];
                return true;
            }
            int u = prev(R);
            swap(d[R], d[u]);
            sz[R]--;
            return erase(t[0][R], x);
        }
        else {
            int p = x < d[R] ? 0 : 1;
            if (erase(t[p][R], x)) {
                sz[R]--;
                return true;
            }
            else return false;
        }
    }
    bool erase(T x) {
        return erase(R, x);
    }
    int kth(int R, int k) {
        if (!R) return 0;
        if (t[0][R]) {
            if (k <= sz[t[0][R]]) return kth(t[0][R], k);
            else k -= sz[t[0][R]];
        }
        if (k == 1) return R;
        else k--;
        return kth(t[1][R], k);
    }
    int kth(int k) {
        return kth(R, k);
    }
    int rank(int R, T x) {
        if (!R) return 0;
        if (x <= d[R]) return rank(t[0][R], x);
        return sz[t[0][R]] + 1 + rank(t[1][R], x);
    }
    int rank(T x) {
        return rank(R, x);
    }
    int lower_bound(int R, T x) {
        if (!R) return 0;
        if (x <= d[R]) return lower_bound(t[0][R], x);
        int z = lower_bound(t[1][R], x);
        if (z == 0) return R;
        return z;
    }
    int lower_bound(T x) {
        return lower_bound(R, x);
    }
    int upper_bound(int R, T x) {
        if (!R) return 0;
        if (d[R] <= x) return upper_bound(t[1][R], x);;
        int z = upper_bound(t[0][R], x);
        if (z == 0) return R;
        return z;
    }
    int upper_bound(T x) {
        return upper_bound(R, x);
    }
    int find(int R, T x) {
        if (!R) return 0;
        if (d[R] == x) return R;
        int p = x < d[R] ? 0 : 1;
        return find(t[p][R], x);
    }
    int find(T x) {
        return find(R, x);
    }
};
