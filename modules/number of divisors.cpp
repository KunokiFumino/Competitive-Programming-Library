int number_of_divisors(int x) {
    auto f = factorize(x);
    int ans = 1;
    for (int i = 0; i < f.size(); i++) ans *= (f[i].second + 1);
    return ans;
}