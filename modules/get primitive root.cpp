template <typename T = long long> T get_primitive_root(T m) {
    assert(m > 1);
    T phi = euler(m);
    auto fm = factorize(m);
    if (!(m == 2 || m == 4 || (fm.size() == 1 && fm[0].first != 2) || (fm.size() == 2 && fm[0].first == 2 && fm[0].second == 1))) return -1;
    auto fphi = factorize(phi);
    auto ok = [&](T g) {
        if (greatest_common_divisor(g, m) != 1) return false;
        for (int i = 0; i < fphi.size(); i++) {
            if (power(g, phi / fphi[i].first, m) == 1) return false;
        }
        return true;
    };
    for (T g = 1; g < m; g++) {
        if (ok(g)) return g;
    }
    return -1;
}