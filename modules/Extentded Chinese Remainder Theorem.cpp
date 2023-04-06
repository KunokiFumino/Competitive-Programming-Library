template <typename T = long long> class ExtentedChineseRemainerTheorem {
private:
    vector<T> M, A;
public:
    T diff;
    void clear() {
        M.clear();
        A.clear();
    }
    /*
    * x % m = a
    */
    void add_equation(T m, T a) {
        assert(0 < m);
        assert(a < m);
        M.push_back(m);
        A.push_back(a);
    }
    /*
    * return -1 if there's no solution
    */
    T solve() {
        T at = A[0], mt = M[0], ap, mp, x = A[0], y, z;
        for (int i = 1; i < A.size(); i++) {
            ap = A[i];
            mp = M[i];
            if ((at - ap) % euclid(mt, mp) != 0) return -1;
            /* * * * * * * * * * * * *
             *  x=mt*y+at            *
             *  x=mp*z+ap            *
             *    => at-ap=mp*z-mt*y *
             * * * * * * * * * * * * */
            extended_euclid(mp, -mt, z, y);
            //  => mp*z-mt*y=gcd(mp,-mt)
            z = z * (at - ap) / euclid(mp, -mt);
            x = mp * z + ap;
            mt = mt * mp / euclid(mt, mp);
            at = x;
        }
        diff = mt;
        if (x < 0) x += (-x / diff + 1) * diff;
        return x;
    }
};