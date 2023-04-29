class Z {
private:
    long long x;
    static long long P;
    static long long phi;
    static bool phi_outdated;
    static long long norm(long long x) {
        if (x < 0) x += P;
        if (x >= P) x -= P;
        return x;
    }
public:
    Z(long long x = 0) : x(norm(x% P)) {}
    /*
    * set the modulo number to np
    */
    static void set_modulo(long long np) {
        P = np;
        phi_outdated = true;
    }
    /*
    * return current modulo number
    */
    static long long get_modulo() {
        return P;
    }
    long long val() const {
        return x;
    }
    /*
    * return the inverse element of current, i.e. a/b=a*b.inv()
    */
    Z inv() const {
        if (phi_outdated) {
            phi = euler(P);
            phi_outdated = false;
        }
        return *this ^ (phi - 1);
    }
    /*
    * increase by d, but avoid modulo operation
    */
    void inc(long long d) {
        x = norm(x + d);
    }
    /*
    * return the b-th power of current number
    */
    Z power(long long b) {
        if (b < 0) return Z(1) * ((*this) ^ (-b)).inv();
        Z res = 1, a = *this;
        for (; b; b >>= 1, a *= a) {
            if (b & 1) res *= a;
        }
        return res;
    }
    bool operator < (const Z& rhs) const {
        return x < rhs.x;
    }
    Z operator - () const {
        return Z(norm(P - x));
    }
    Z& operator *= (const Z& rhs) {
        x = x * rhs.x % P;
        return *this;
    }
    Z& operator += (const Z& rhs) {
        x = norm(x + rhs.x);
        return *this;
    }
    Z& operator -= (const Z& rhs) {
        x = norm(x - rhs.x);
        return *this;
    }
    Z& operator /= (const Z& rhs) {
        return *this *= rhs.inv();
    }
    friend Z operator * (const Z& lhs, const Z& rhs) {
        Z res = lhs;
        res *= rhs;
        return res;
    }
    friend Z operator + (const Z& lhs, const Z& rhs) {
        Z res = lhs;
        res += rhs;
        return res;
    }
    friend Z operator - (const Z& lhs, const Z& rhs) {
        Z res = lhs;
        res -= rhs;
        return res;
    }
    friend Z operator / (const Z& lhs, const Z& rhs) {
        Z res = lhs;
        res *= rhs.inv();
        return res;
    }
    friend Z operator ^ (const Z& lhs, long long b) {
        if (b < 0) return Z(1) * ((lhs) ^ (-b)).inv();
        Z res = 1, a = lhs;
        for (; b; b >>= 1, a *= a) {
            if (b & 1) res *= a;
        }
        return res;
    }
    friend std::istream& operator >> (std::istream& is, Z& a) {
        long long v;
        is >> v;
        a = Z(v);
        return is;
    }
    friend std::ostream& operator << (std::ostream& os, const Z& a) {
        return os << a.val();
    }
};
long long Z::P = 1e9 + 7;
long long Z::phi = 1e9 + 6;
bool Z::phi_outdated = false;