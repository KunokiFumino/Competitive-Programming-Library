class CombinatorialNumber {
private:
    vector<Z> fac, inv, f;
    int N;
public:
    CombinatorialNumber() : N(0) {}
    void preprocess(int n) {
        N = n;
        fac.resize(n);
        inv.resize(n);
        f.resize(n);
        fac[0] = fac[1] = inv[0] = inv[1] = f[0] = f[1] = 1;
        for (int i = 2; i < n; i++) {
            fac[i] = fac[i - 1] * i;
            f[i] = (Z::get_modulo() - Z::get_modulo() / i) * f[Z::get_modulo() % i];
            inv[i] = inv[i - 1] * f[i];
        }
    }
    Z P(long long a, long long b) {
        if (a < 0 || b < 0 || a < b) return 0;
        if (N <= a) {
            Z res = 1, t = a;
            for (long long i = 0; i < b; i++) {
                res *= t;
                t.inc(-1);
            }
            return res;
        }
        return fac[a] * inv[a - b];
    }
    Z C(long long a, long long b, bool lucas = false) {
        if (a < 0 || b < 0 || a < b) return 0;
        if (!lucas) {
            if (N <= a) {
                Z res = 1, p = a, q = 1;
                for (long long i = 0; i < b; i++) {
                    res *= p;
                    res /= q;
                    p.inc(-1);
                    q.inc(1);
                }
                return res;
            }
            return fac[a] * inv[b] * inv[a - b];
        }
        else return C(a % Z::get_modulo(), b % Z::get_modulo()) * C(a / Z::get_modulo(), b / Z::get_modulo(), true);
    }
    /*
    * C(n, 0) + C(n, 1) + ... + C(n, k)
    */
    Z S(long long n, long long k, bool lucas = false) {
        return C(n + k + 1, n + 1, lucas);
    }
    /*
    * the number of ways to place n 0 and n 1 in a row, so that in any prefix, the number of 0 is not less than the number of 1.
    * both formula are ok.
    */
    Z Catalan(long long n, bool lucas = false) {
        return C(2 * n, n, lucas) / (n + 1);
        return C(2 * n, n, lucas) - C(2 * n, n + 1, lucas);
    }
};