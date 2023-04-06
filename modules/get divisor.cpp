/*
* Pollard Rho Algorithm.
* need to initialize random seed.
*/
template <typename T = long long> T get_divisor(T x) {
    T s = 0, t = 0, c = (T)1 * rand() % (x - 1) + 1;
    int stp = 0, goal = 1;
    T val = 1;
    for (goal = 1;; goal <<= 1, s = t, val = 1) {
        for (stp = 1; stp <= goal; ++stp) {
            t = (t * t + c) % x;
            val = val * (s < t ? (t - s) : (s - t)) % x;
            if ((stp % 127) == 0) {
                T d = euclid(val, x);
                if (1 < d) return d;
            }
        }
        T d = euclid(val, x);
        if (1 < d) return d;
    }
}
