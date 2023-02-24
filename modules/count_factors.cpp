int count_factors(int x) {
    auto f = prime_factors_decomposition(x);
    int ans = 1;
    for (int i = 0; i < f.size(); i++) ans *= (f[i].second + 1);
    return ans;
}