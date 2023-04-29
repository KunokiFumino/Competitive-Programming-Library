/*
* in here the matrix is forced to be square.
*/
template <typename T = Z> class Matrix {
public:
    int N;
private:
    vector<vector<T> > a;
public:
    Matrix() {}
    /*
    * initialize with n * n 0. set e = true if need 1 are needed on diagonal.
    */
    Matrix(int n, bool e = false) {
        N = n;
        a.assign(N, vector<T>(N, 0));
        if (e) {
            for (int i = 0; i < N; i++) {
                a[i][i] = 1;
            }
        }
    }
    /*
    * return the determinant of current matrix
    * for example, the determinant of a 3*3 matrix as following is:
    * |a00 a01 a02|
    * |a10 a11 a12| = a00 * a11 * a22 + a01 * a12 * a20 + a02 * a10 * a21 - a00 * a21 * a12 - a10 * a01 * a22 - a20 * a11 * a02 
    * |a20 a21 a22|
    */
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
    Matrix operator * (const Matrix& rhs) {
        Matrix res = *this;
        res *= rhs;
        return rhs;
    }
    Matrix& operator *= (const Matrix& rhs) {
        assert(N == rhs.N);
        Matrix res(N);
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                for (int k = 0; k < N; k++) {
                    res[i][j] += a[i][k] * rhs.a[k][j];
                }
            }
        }
        return *this = res;
    }
    /*
    * return the k-th power of current matrix
    */
    Matrix power(long long k) {
        Matrix res(N, true), t = *this;
        while (k) {
            if (k & 1) ans *= t;
            t *= t;
            k >>= 1;
        }
        return ans;
    }
};
