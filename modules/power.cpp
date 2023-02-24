template<typename T> T power(T a, long long b) {
    T res = 1;
    for (; b; b >>= 1, a *= a) {
        if (b & 1) res *= a;
    }
    return res;
}