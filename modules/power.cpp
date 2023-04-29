template <typename T> T power(T x, T k, T p) {
    assert(k >= 0);
    long long res = 1;
    while (k) {
        if (k & 1) (res *= x) %= p;
        (x *= x) %= p;
        k >>= 1;
    }
    return res;
}
