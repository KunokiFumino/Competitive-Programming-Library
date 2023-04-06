/*
* Miller Rabin test has a failure probability of 1/4, but it can be acceptable if n passes multiple tests.
*/
long long miller_rabin_tester[10] = { 2,3,5,7,11,13,17,19,23,29 };
template <typename T> bool is_prime(T n, bool Miller_Rabin = false) {
    if (n < 2) return false;
    if (n < 4) return true;
    if ((n & 1) == 0) return false;
    if (Miller_Rabin) {
        T s = 0, t = n - 1;
        while (!(t & 1)) s++, t >>= 1;
        for (int i = 0; i < 10 && miller_rabin_tester[i] < n; i++) {
            T a = miller_rabin_tester[i], b = power(a, t, n), k;
            for (int j = 1; j <= s; j++) {
                k = b * b % n;
                if (k == 1 && b != 1 && b != n - 1) return false;
                b = k;
            }
            if (b != 1) return false;
        }
        return true;
    }
    else {
        T u = sqrt(n);
        for (T i = 3; i <= u; i += 2) {
            if (n % i == 0) return false;
        }
    }
    return true;
}
