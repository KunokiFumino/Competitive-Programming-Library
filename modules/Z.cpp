/*
* Note that:
*     set_modulo will call function euler, which has a time cost of O(sqrt(P)).
*     inv will call function power, which has a time cost of O(log2(phi)).
* Both of them include modulo operation, abuse of them may lead to TLE.
*/
class Z {
private:
    long long x;
    static long long P;
    static long long phi;
    static long long norm(long long x) {
        if (x < 0) x += P;
        if (x >= P) x -= P;
        return x;
    }
public:
    Z(long long x = 0) : x(norm(x% P)) {}
    static void set_modulo(long long np) {
        P = np;
        phi = euler(P);
    }
    static long long get_modulo() {
        return P;
    }
    long long val() const {
        return x;
    }
    Z inv() const {
        return power(*this, phi - 1);
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