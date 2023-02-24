vector<int> generate_prime(int n, bool f = false) {
    vector<int> p, st(n + 1, 1);
    st[0] = st[1] = 0;
    for (int i = 2; i <= n; i++) {
        if (st[i]) p.push_back(i);
        for (int j = 0; p[j] <= n / i; j++) {
            st[p[j] * i] = 0;
            if (i % p[j] == 0) break;
        }
    }
    if (f) return p;
    else return st;
}