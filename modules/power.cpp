template<typename T> T power(T x, T k, T p = 1) {
    T s = 1;
    while (0 < k) {
        if (k & 1) {
            s *= x;
            if (1 < p) s %= p;
        }
        x *= x;
        if (1 < p) x %= p;
        k >>= 1;
    }
    return s;
}