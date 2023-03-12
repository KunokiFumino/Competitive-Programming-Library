class Combination {
private:
    vector<Z> fac, inv, f;
public:
    void reset(int n) {
        int m = fac.size();
        if (m >= n) return;
        fac.resize(n);
        inv.resize(n);
        f.resize(n);
        fac[0] = fac[1] = inv[0] = inv[1] = f[0] = f[1] = 1;
        for (int i = max(2, m); i < n; i++) {
            fac[i] = fac[i - 1] * i;
            f[i] = (Z::get_modulo() - Z::get_modulo() / i) * f[Z::get_modulo() % i];
            inv[i] = inv[i - 1] * f[i];
        }
    }
    Z P(int a, int b) {
        return fac[a] * inv[a - b];
    }
    Z C(int a, int b) {
        return fac[a] * inv[b] * inv[a - b];
    }
    Z subsum_Cn0_Cnk(int n, int k) {
        return C(n + k + 1, n + 1);
    }
};