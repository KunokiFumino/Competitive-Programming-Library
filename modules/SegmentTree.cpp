/*
*
* T MUST ALLOW : { +, *, T(0), < }
*
* Memory cost : about 25MB when T = int, sz = 200000
*
*/
template <typename T = int> class SegmentTree {
public:
    vector<T> lazy_col, lazy_mul, lazy_add;
    vector<T> sum, maxi, mini;
    vector<int> maxi_id, mini_id;
    vector<bool> col;
    //will return e when query on an illegal segment
    T e;
private:
    int L, R;

public:
    //[)
    template<typename V> void build(int l, int r, const V& src) {
        int sz = (r - l) << 2;
        L = l, R = r;
        check_memory(col, sz);
        check_memory(lazy_col, sz);
        check_memory(lazy_mul, sz);
        check_memory(lazy_add, sz);
        check_memory(sum, sz);
        check_memory(maxi, sz);
        check_memory(mini, sz);
        check_memory(maxi_id, sz);
        check_memory(mini_id, sz);
        do_build(1, l, r, src);
    }
    void update_col(int l, int r, T u) {
        do_update_col(1, L, R, l, r, u);
    }
    void update_mul(int l, int r, T u) {
        do_update_mul(1, L, R, l, r, u);
    }
    void update_add(int l, int r, T u) {
        do_update_add(1, L, R, l, r, u);
    }
    T query_sum(int l, int r) {
        return do_query_sum(1, L, R, l, r);
    }
    pair<T, int> query_max(int l, int r) {
        return do_query_max(1, L, R, l, r);
    }
    pair<T, int> query_min(int l, int r) {
        return do_query_min(1, L, R, l, r);
    }

private:
    template<typename V> void do_build(int rt, int l, int r, const V& src) {
        if (l + 1 == r) {
            sum[rt] = maxi[rt] = mini[rt] = src[l];
            maxi_id[rt] = mini_id[rt] = l;
            return;
        }
        int mid = (l + r) >> 1;
        do_build(rt << 1, l, mid, src);
        do_build(rt << 1 | 1, mid, r, src);
        push_up(rt);
        col[rt] = false;
        lazy_mul[rt] = 1;
        lazy_add[rt] = 0;
    }
    void do_update_col(int rt, int L, int R, int l, int r, T u) {
        if (l >= r) return;
        if (l < L) l = L;
        if (R < r) r = R;
        if (l == L && r == R) {
            col[rt] = true;
            lazy_col[rt] = u;
            lazy_mul[rt] = 1;
            lazy_add[rt] = 0;
            sum[rt] = u * (r - l);
            maxi[rt] = mini[rt] = u;
            maxi_id[rt] = mini_id[rt] = l;
            return;
        }
        push_down(rt, L, R);
        int mid = (L + R) >> 1;
        if (l < mid) do_update_col(rt << 1, L, mid, l, r, u);
        if (mid < r) do_update_col(rt << 1 | 1, mid, R, l, r, u);
        push_up(rt);
    }
    void do_update_mul(int rt, int L, int R, int l, int r, T u) {
        if (l >= r) return;
        if (l < L) l = L;
        if (R < r) r = R;
        if (l == L && r == R) {
            lazy_mul[rt] *= u;
            lazy_add[rt] *= u;
            sum[rt] *= u;
            maxi[rt] *= u;
            mini[rt] *= u;
            if (u < 0) {
                swap(maxi[rt], mini[rt]);
                swap(maxi_id[rt], mini_id[rt]);
            }
            return;
        }
        push_down(rt, L, R);
        int mid = (L + R) >> 1;
        if (l < mid) do_update_mul(rt << 1, L, mid, l, r, u);
        if (mid < r) do_update_mul(rt << 1 | 1, mid, R, l, r, u);
        push_up(rt);
    }
    void do_update_add(int rt, int L, int R, int l, int r, T u) {
        if (l >= r) return;
        if (l < L) l = L;
        if (R < r) r = R;
        if (l == L && r == R) {
            lazy_add[rt] += u;
            sum[rt] += u * (r - l);
            maxi[rt] += u;
            mini[rt] += u;
            return;
        }
        push_down(rt, L, R);
        int mid = (L + R) >> 1;
        if (l < mid) do_update_add(rt << 1, L, mid, l, r, u);
        if (mid < r) do_update_add(rt << 1 | 1, mid, R, l, r, u);
        push_up(rt);
    }
    T do_query_sum(int rt, int L, int R, int l, int r) {
        if (l >= r) return e;
        if (l < L) l = L;
        if (R < r) r = R;
        if (l == L && r == R) return sum[rt];
        push_down(rt, L, R);
        int mid = (L + R) >> 1;
        T ans = 0;
        if (l < mid) ans += do_query_sum(rt << 1, L, mid, l, r);
        if (mid < r) ans += do_query_sum(rt << 1 | 1, mid, R, l, r);
        return ans;
    }
    pair<T, int> do_query_max(int rt, int L, int R, int l, int r) {
        if (l >= r) return e;
        if (l < L) l = L;
        if (R < r) r = R;
        if (l == L && r == R) return { maxi[rt],maxi_id[rt] };
        push_down(rt, L, R);
        int mid = (L + R) >> 1;
        if (r <= mid) return do_query_max(rt << 1, L, mid, l, r);
        if (mid <= l) return do_query_max(rt << 1 | 1, mid, R, l, r);
        pair<T, int> al = do_query_max(rt << 1, L, mid, l, r), ar = do_query_max(rt << 1 | 1, mid, R, l, r);
        return al < ar ? ar : al;
    }
    pair<T, int> do_query_min(int rt, int L, int R, int l, int r) {
        if (l >= r) return e;
        if (l < L) l = L;
        if (R < r) r = R;
        if (l == L && r == R) return { mini[rt],mini_id[rt] };
        push_down(rt, L, R);
        int mid = (L + R) >> 1;
        if (r <= mid) return do_query_min(rt << 1, L, mid, l, r);
        if (mid <= l) return do_query_min(rt << 1 | 1, mid, R, l, r);
        pair<T, int> al = do_query_min(rt << 1, L, mid, l, r), ar = do_query_min(rt << 1 | 1, mid, R, l, r);
        return ar < al ? ar : al;
    }
    void push_up(int rt) {
        sum[rt] = sum[rt << 1] + sum[rt << 1 | 1];
        maxi[rt] = maxi[rt << 1] < maxi[rt << 1 | 1] ? maxi[rt << 1 | 1] : maxi[rt << 1];
        mini[rt] = mini[rt << 1] < mini[rt << 1 | 1] ? mini[rt << 1] : mini[rt << 1 | 1];
        maxi_id[rt] = maxi[rt << 1] < maxi[rt << 1 | 1] ? maxi_id[rt << 1 | 1] : maxi_id[rt << 1];
        mini_id[rt] = mini[rt << 1] > mini[rt << 1 | 1] ? mini_id[rt << 1 | 1] : mini_id[rt << 1];
    }
    void push_down(int rt, int l, int r) {
        int mid = (l + r) >> 1;
        if (col[rt]) {
            col[rt << 1] = true;
            col[rt << 1 | 1] = true;
            lazy_col[rt << 1] = lazy_col[rt << 1 | 1] = lazy_col[rt];
            col[rt] = false;
            lazy_mul[rt << 1] = lazy_mul[rt << 1 | 1] = 1;
            lazy_add[rt << 1] = lazy_add[rt << 1 | 1] = 0;
            sum[rt << 1] = lazy_col[rt] * (mid - l);
            sum[rt << 1 | 1] = lazy_col[rt] * (r - mid);
            maxi[rt << 1] = maxi[rt << 1 | 1] = lazy_col[rt];
            mini[rt << 1] = mini[rt << 1 | 1] = lazy_col[rt];
            maxi_id[rt << 1] = mini_id[rt << 1] = l;
            maxi_id[rt << 1 | 1] = mini_id[rt << 1 | 1] = mid;
        }
        if (lazy_mul[rt] != 1) {
            T u = lazy_mul[rt];
            lazy_mul[rt] = 1;
            lazy_mul[rt << 1] *= u;
            lazy_mul[rt << 1 | 1] *= u;
            lazy_add[rt << 1] *= u;
            lazy_add[rt << 1 | 1] *= u;
            sum[rt << 1] *= u;
            sum[rt << 1 | 1] *= u;
            maxi[rt << 1] *= u;
            maxi[rt << 1 | 1] *= u;
            mini[rt << 1] *= u;
            mini[rt << 1 | 1] *= u;
            if (u < 0) {
                swap(maxi[rt << 1], mini[rt << 1]);
                swap(maxi[rt << 1 | 1], mini[rt << 1 | 1]);
                swap(maxi_id[rt << 1], mini_id[rt << 1]);
                swap(maxi_id[rt << 1 | 1], mini_id[rt << 1 | 1]);
            }
        }
        if (lazy_add[rt]) {
            T u = lazy_add[rt];
            lazy_add[rt] = 0;
            lazy_add[rt << 1] += u;
            lazy_add[rt << 1 | 1] += u;
            sum[rt << 1] += u * (mid - l);
            sum[rt << 1 | 1] += u * (r - mid);
            maxi[rt << 1] += u;
            maxi[rt << 1 | 1] += u;
            mini[rt << 1] += u;
            mini[rt << 1 | 1] += u;
        }
    }
};