vector<int> generate_euler(int n) {
    vector<int> e(n + 1);
    vector<int> v(n + 1, 0), p;
    for (int i = 2; i <= n; i++) {
        if (v[i] == 0) {
            v[i] = i;
            p.push_back(i);
            e[i] = i - 1;
        }
        for (int j = 0; j < p.size(); j++) {
            int x = p[j];
            if (x > v[i] || x > n / i) break;
            v[i * x] = x;
            e[i * x] = e[i] * (i % x ? x - 1 : x);
            if (i % x == 0) break;
        }
    }
    return e;
}