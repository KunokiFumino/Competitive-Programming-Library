/*
* extended baby step giant step algorithm.
* solving the equation of a ** x % p = b
* return -1 if there's no solution.
*/
template <typename T = long long> T discrete_logarithm(T a, T b, T p) {
    map<T, T> mp;
    if (b == 1) return 0;
    T k = 0, tmp = 1, d;
    while (true) {
        d = greatest_common_divisor(a, p);
        if (d == 1) break;
        if (b % d) return -1;
        b /= d;
        p /= d;
        (tmp *= (a / d)) %= p;
        k++;
        if (tmp == b) return k;
    }
    mp.clear();
    T mul = b;
    mp[b] = 0;
    T m = ceil(sqrt((double)p));
    for (T i = 1; i <= m; i++) {
        (mul *= a) %= p;
        mp[mul] = i;
    }
    T am = power(a, m, p);
    mul = tmp;
    for (T i = 1; i <= m; i++) {
        (mul *= am) %= p;
        if (mp.find(mul) != mp.end()) return i * m - mp[mul] + k;
    }
    return -1;
}
