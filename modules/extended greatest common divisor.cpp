/*
* get the minimum positive integer x that ax + by = gcd(a, b).
* return gcd(a, b).
*/
template <typename T = long long> T extended_greatest_common_divisor(T a, T b, T& x, T& y) {
    if (!b) {
        x = 1;
        y = 0;
        return a;
    }
    T d = extended_euclid(b, a % b, y, x);
    y -= (a / b) * x;
    return d;
}
