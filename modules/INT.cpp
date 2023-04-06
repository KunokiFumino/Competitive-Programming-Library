template <int d> class INT {
private:
    bitset<d + 1> p;
public:
    INT() {}
    INT(long long x) {
        if (x < 0) {
            p[d] = 1;
            x = -x;
        }
        for (register int i = 0; i < d && x; i++) {
            p[i] = x & 1;
            x >>= 1;
        }
    }
    template<int q> INT(INT<q> x) {
        for (register int i = 0; i < d && i < q; i++) p[i] = x.p[i];
        p[d] = x.p[q];
    }
    explicit operator bool() const {
        return !(p.none());
    }
    friend bool operator < (const INT<d>& lhs, const INT<d>& rhs) {
        /*
        * a b
        * 0 1 f
        * 1 0 t
        */
        if (lhs.p[d] ^ rhs.p[d]) return lhs.p[d];
        /*
        * p[d] p[i]
        * 1    1    t
        * 1    0    f
        * 0    1    f
        * 0    0    t
        */
        for (register int i = d - 1; i >= 0; i--) {
            if (lhs.p[i] ^ rhs.p[i]) return !(lhs.p[d] ^ lhs.p[i]);
        }
        return false;
    }
    friend bool operator == (const INT<d>& lhs, const INT<d>& rhs) {
        return lhs.p == rhs.p;
    }
    friend bool operator != (const INT<d>& lhs, const INT<d>& rhs) {
        return lhs.p != rhs.p;
    }
    friend bool operator <= (const INT<d>& lhs, const INT<d>& rhs) {
        if (lhs.p[d] ^ rhs.p[d]) return lhs.p[d];
        for (register int i = d - 1; i >= 0; i--) {
            if (lhs.p[i] ^ rhs.p[i]) return !(lhs.p[d] ^ lhs.p[i]);
        }
        return true;
    }
    INT<d> operator - () const {
        INT<d> res = *this;
        res.p.flip(d);
        return res;
    }
    INT<d>& operator ++() {
        return (*this) += 1;
    }
    INT<d> operator ++(int) {
        INT<d> t = *this;
        ++(*this);
        return t;
    }
    INT<d>& operator --() {
        return (*this) += -1;
    }
    INT<d> operator --(int) {
        INT<d> t = *this;
        --(*this);
        return t;
    }
    INT<d> operator << (int x) {
        INT<d> res = (*this);
        return res <<= x;
    }
    INT<d>& operator <<= (int x) {
        int t = p[d];
        p[d] = 0;
        p <<= x;
        p[d] = t;
        return (*this);
    }
    INT<d> operator >> (int x) {
        INT<d> res = (*this);
        return res >>= x;
    }
    INT<d>& operator >>= (int x) {
        int t = p[d];
        p[d] = 0;
        p >>= x;
        p[d] = t;
        return (*this);
    }
    friend INT<d> operator | (const INT<d>& lhs, const INT<d>& rhs) {
        INT<d> res = lhs;
        res |= rhs;
        return res;
    }
    INT<d>& operator |= (const INT<d>& rhs) {
        for (register int i = 0; i <= d; i++) p[i] = p[i] | rhs.p[i];
        return (*this);
    }
    friend INT<d> operator & (const INT<d>& lhs, const INT<d>& rhs) {
        INT<d> res = lhs;
        res &= rhs;
        return res;
    }
    INT<d>& operator &= (const INT<d>& rhs) {
        for (register int i = 0; i <= d; i++) p[i] = p[i] & rhs.p[i];
        return (*this);
    }
    friend INT<d> operator ^ (const INT<d>& lhs, const INT<d>& rhs) {
        INT<d> res = lhs;
        res ^= rhs;
        return res;
    }
    INT<d>& operator ^= (const INT<d>& rhs) {
        for (register int i = 0; i <= d; i++) p[i] = p[i] ^ rhs.p[i];
        return (*this);
    }
    friend INT<d> operator + (const INT<d>& lhs, const INT<d>& rhs) {
        INT<d> res = lhs;
        res += rhs;
        return res;
    }
    INT<d>& operator += (INT<d> rhs) {
        if (p[d]) {
            for (register int i = 0; i < d; i++) p[i] = p[i] ^ 1;;
            for (register int i = 0, j = 1; j && i <= d; i++) {
                j = p[i];
                p[i] = p[i] ^ 1;
            }
        }
        if (rhs.p[d]) {
            for (register int i = 0; i < d; i++) rhs.p[i] = rhs.p[i] ^ 1;
            for (register int i = 0, j = 1; j && i <= d; i++) {
                j = rhs.p[i];
                rhs.p[i] = rhs.p[i] ^ 1;
            }
        }
        for (register int i = 0, j = 0; i <= d; i++) {
            /*
            * a b j c nj
            * 0 0 0 0 0
            * 0 0 1 1 0 *
            * 0 1 0 1 0
            * 0 1 1 0 1
            * 1 0 0 1 0
            * 1 0 1 0 1
            * 1 1 0 0 1 *
            * 1 1 1 1 1
            */
            p[i] = p[i] ^ rhs.p[i] ^ j;
            if (((rhs.p[i] ^ 1) && j && p[i]) || (rhs.p[i] && (j ^ 1) && (p[i] ^ 1))) j ^= 1;
        }
        if (p[d]) {
            for (register int i = 0; i < d; i++) p[i] = p[i] ^ 1;
            for (register int i = 0, j = 1; j && i <= d; i++) {
                j = p[i];
                p[i] = p[i] ^ 1;
            }
        }
        return *this;
    }
    friend INT<d> operator - (const INT<d>& lhs, const INT<d>& rhs) {
        INT<d> res = lhs;
        res += -rhs;
        return res;
    }
    INT<d>& operator -= (const INT<d>& rhs) {
        return (*this) += (-rhs);
    }
    friend INT<d> operator * (const INT<d>& lhs, const INT<d>& rhs) {
        INT<d> res = lhs;
        res *= rhs;
        return res;
    }
    INT<d>& operator *= (INT<d> rhs) {
        INT<d> res = 0, lhs = (*this);
        int sgn = lhs.p[d] ^ rhs.p[d];
        lhs.p[d] = 0;
        rhs.p[d] = 0;
        for (register int i = 0; i < d; i++) {
            if (rhs.p[i]) res += lhs;
            lhs <<= 1;
        }
        res.p[d] = sgn;
        return (*this) = res;
    }
    friend INT<d> operator / (const INT<d>& lhs, const INT<d>& rhs) {
        INT<d> res = lhs;
        res /= rhs;
        return res;
    }
    INT<d>& operator /= (INT<d> rhs) {
        INT<d> res = 0, lhs = (*this);
        int f = 0, sgn = lhs.p[d] ^ rhs.p[d];
        lhs.p[d] = 0;
        rhs.p[d] = 0;
        assert(!rhs.p.none());
        while (rhs <= lhs) {
            f = d - 1;
            for (register int i = 1; i < d; i++) {
                if (lhs < (rhs << i)) {
                    f = i - 1;
                    break;
                }
            }
            lhs -= (rhs << f);
            res.p[f] = 1;
        }
        res.p[d] = sgn;
        return (*this) = res;
    }
    friend INT<d> operator % (const INT<d>& lhs, const INT<d>& rhs) {
        INT<d> res = lhs;
        res %= rhs;
        return res;
    }
    INT<d>& operator %= (INT<d> rhs) {
        INT<d> lhs = (*this);
        int f = 0, sgn = lhs.p[d];
        lhs.p[d] = 0;
        rhs.p[d] = 0;
        assert(!rhs.p.none());
        while (rhs <= lhs) {
            f = d - 1;
            for (register int i = 1; i < d; i++) {
                if (lhs < (rhs << i)) {
                    f = i - 1;
                    break;
                }
            }
            lhs -= (rhs << f);
        }
        if (lhs != 0 && sgn) lhs = rhs - lhs;
        return (*this) = lhs;
    }
    INT<d> mod_div(INT<d> rhs) {
        INT<d> res = 0, lhs = (*this);
        int f = 0, sgn = lhs.p[d] ^ rhs.p[d];
        lhs.p[d] = 0;
        rhs.p[d] = 0;
        assert(!rhs.p.none());
        while (rhs <= lhs) {
            f = d - 1;
            for (register int i = 1; i < d; i++) {
                if (lhs < (rhs << i)) {
                    f = i - 1;
                    break;
                }
            }
            lhs -= (rhs << f);
            res.p[f] = 1;
        }
        res.p[d] = sgn;
        p = res.p;
        if (lhs != 0 && sgn) lhs = rhs - lhs;
        return lhs;
    }
    template <typename T = int> T value(int u = (sizeof(T) << 3) - 1) {
        T res = 0, t = 1;
        u = min(u, d);
        for (register int i = 0; i < u; i++) {
            if (p[i]) res += t;
            t <<= 1;
        }
        if (p[d]) res *= -1;
        return res;
    }
    string binary() {
        string res = "";
        if (p[d]) res += '-';
        for (register int i = d - 1; i >= 0; i--) {
            if (p[i]) {
                for (register int j = i; j >= 0; j--) res += p[i] ? '1' : '0';
                break;
            }
        }
        if (res == "" || res == "-") res = "0";
        return res;
    }
    string digital() {
        INT<d> lhs = (*this), rhs = 10, m;
        int sgn = lhs.p[d];
        lhs.p[d] = 0;
        if (lhs.p.none()) return "0";
        string res = "";
        while (lhs) {
            m = lhs.mod_div(rhs);
            res += '0' + m.value<int>(4);
        }
        if (sgn) res += '-';
        reverse(res.begin(), res.end());
        return res;
    }
    INT<d> abs() {
        if (!p[d]) return (*this);
        else return -(*this);
    }
};
template <int d> INT<d> sqrt(INT<d> n) {
    assert(0 < n);
    INT<d> l = 1, r = n + 1, mid;
    while (l + 1 < r) {
        mid = (l + r) >> 1;
        if (mid * mid <= n) l = mid;
        else r = mid;
    }
    return l;
}
template <int d> INT<d> abs(INT<d> n) {
    return n.abs();
}