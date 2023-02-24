vector<pair<int, int> > prime_factors_decomposition(int x) {
    vector<pair<int, int> > f;
    for (int i = 2; i <= x / i; i++) {
        pair<long long, int> p = { i,0 };
        while (x % i == 0) {
            x /= i;
            p.second++;
        }
        if (p.second) f.push_back(p);
    }
    if (x > 1) f.push_back({ x,1 });
    return f;
}