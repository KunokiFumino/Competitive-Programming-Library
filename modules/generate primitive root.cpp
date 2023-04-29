template <typename T = long long> vector<T> generate_primitive_root(T m) {
    assert(m > 1);
    T phi = euler(m);
    auto fm = factorize(m);    
    vector<T> res;
    if (!(m == 2 || m == 4 || (fm.size() == 1 && fm[0].first != 2) || (fm.size() == 2 && fm[0].first == 2 && fm[0].second == 1))) return res;
    auto fphi = factorize(phi);
    auto ok = [&](T g) {
        if (greatest_common_divisor(g, m) != 1) return false;
        for (int i = 0; i < fphi.size(); i++) {
            if (power(g, phi / fphi[i].first, m) == 1) return false;
        }
        return true;
    };
    T g = 1;
    for (; g < m; g++) { if (ok(g)) break; }
    for (T i = 1, p = g; i <= phi; i++) {
        if (greatest_common_divisor(i, phi) == 1) res.push_back(p);
        (p *= g) %= m;
    }
    return res;
}
