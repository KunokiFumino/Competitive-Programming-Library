vector<int> LIS(const vector<int>& p) {
    vector<int> f(p.size()), g(p.size() + 1);
    f[0] = 1;
    g[1] = p[0];
    int n = 1;
    for (int i = 1; i < p.size(); i++) {
        if (g[n] < p[i]) g[++n] = p[i];
        else {
            int l = 0, r = n, mid;
            while (l + 1 < r) {
                mid = (l + r) >> 1;
                if (g[mid] < p[i]) l = mid;
                else r = mid;
            }
            g[r] = p[i];
        }
        f[i] = n;
    }
    vector<int> res;
    for (int i = n, j = p.size() - 1; i >= 1; i--) {
        for (; j >= 0; j--) {
            if (f[j] == i) {
                res.push_back(p[j]);
                break;
            }
        }
    }
    reverse(res.begin(), res.end());
    return res;
}