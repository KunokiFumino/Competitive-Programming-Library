/*
* euclid algorithm
*/
template <typename T = long long> T greatest_common_divisor(T a, T b) {
    if (!b) return a;
    else return greatest_common_divisor(b, a % b);
}