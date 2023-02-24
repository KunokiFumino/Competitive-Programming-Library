template <typename T> T euclid(T a, T b) {
    if (b == 0) return a;
    else return euclid(b, a % b);
}