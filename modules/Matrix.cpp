template <typename T = Z> class Matrix {
public:
    int N;
    vector<vector<T> > a;
    void reset(int n) {
        N = n;
        a.assign(N, vector<T>(N));
    }
    T determinant() {
        vector<T> p(N), m(N);
        for (int i = 0; i < N; i++) {
            p[i] = a[0][i];
            for (int j = 1, k = i + 1; j < N; j++, k++) {
                if (k == N) k = 0;
                p[i] *= a[j][k];
            }
            m[i] = a[0][i];
            for (int j = 1, k = i - 1; j < N; j++, k--) {
                if (k < 0) k = N - 1;
                m[i] *= a[j][k];
            }
        }
        T ret = p[0];
        for (int i = 1; i < N; i++) ret += p[i];
        for (int i = 0; i < N; i++) ret -= m[i];
        return ret;
    }
};
