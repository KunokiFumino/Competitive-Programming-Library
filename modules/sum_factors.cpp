int sum_factors(int x) {
    auto f = prime_factors_decomposition(x);
    int ans = 1;
    for (int i = 0; i < f.size(); i++) ans *= (power(f[i].first, f[i].second + 1) - 1) / (f[i].first - 1);
    return ans;
}
