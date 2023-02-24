vector<int> LCIS(const vector<int>& a, const vector<int>& b) {
    int ans = 0;
    vector<vector<int> > f(a.size(), vector<int>(b.size(), 0));
    for (int i = 0; i < a.size(); i++) {
        int z = 0;
        for (int j = 0; j < b.size(); j++) {
            if (i) f[i][j] = f[i - 1][j];
            if (a[i] == b[j]) f[i][j] = max(f[i][j], z + 1);
            if (a[i] > b[j] && i) z = max(z, f[i - 1][j]);
            ans = max(ans, f[i][j]);
        }
    }
    vector<int> res;
    int z = 0x7FFFFFFF;
    for (int i = ans, j = a.size() - 1, k = b.size() - 1; i >= 1; i--) {
        for (; k >= 0; k--) {
            if (f[j][k] == i && b[k] < z) {
                z = b[k];
                res.push_back(b[k]);
                while (a[j] != b[k]) j--;
                j--;
                k--;
                break;
            }
        }
    }
    reverse(res.begin(), res.end());
    return res;
}