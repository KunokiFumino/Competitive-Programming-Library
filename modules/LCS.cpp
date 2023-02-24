vector<int> LCS(const vector<int>& a, const vector<int>& b) {
    vector<vector<int> > f(a.size(), vector<int>(b.size(), 0));
    for (int i = 0; i < a.size(); i++) {
        for (int j = 0; j < b.size(); j++) {
            if (a[i] == b[j]) f[i][j] = i && j ? f[i - 1][j - 1] + 1 : 1;
            else f[i][j] = max(i ? f[i - 1][j] : 0, j ? f[i][j - 1] : 0);
        }
    }
    vector<int> res;
    for (int i = a.size() - 1, j = b.size() - 1, k = f[a.size() - 1][b.size() - 1]; k >= 1; k--) {
        while (i > 0 && f[i - 1][j] >= k) i--;
        while (j > 0 && f[i][j - 1] >= k) j--;
        res.push_back(a[i]);
        i--;
        j--;
    }
    reverse(res.begin(), res.end());
    return res;
}
