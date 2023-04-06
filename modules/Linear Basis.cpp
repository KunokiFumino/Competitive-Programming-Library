/*
* linear basis is a data structure that can do following:
*     1. insert a integer
* it can answer following  queries:
*     1. can a integer be represented by integers inserted.
*     2. the maximum, minimum, k-th maximum, kth-minimum integer that can be represented by integers inserted.
*/
template <typename T = long long> class LinearBasis {
private:
    vector<T> x;
    vector<int> y;
    bool canonised;
public:
    LinearBasis() : canonised(false) { reset(); }
    T operator [] (int h) { return x[h]; }
    void reset() {
        x.assign((sizeof(T) << 3), 0);
    }
    int insert(T v) {
        for (int i = x.size() - 1; i >= 0; i--) {
            if (v & ((T)1 << i)) {
                if (!x[i]) {
                    x[i] = v;
                    canonised = false;
                    return i;
                }
                v ^= x[i];
            }
        }
        return -1;
    }
    bool find(T v) {
        for (int i = x.size() - 1; i >= 0; i--) {
            if ((v & ((T)1 << i)) && x[i]) v ^= x[i];
            if (!v) return true;
        }
        return false;
    }
    T maximum() {
        T res = 0;
        for (int i = x.size() - 1; i >= 0; i--) {
            if ((res ^ x[i]) > res) res ^= x[i];
        }
        return res;
    }
    T minimum() {
        for (int i = 0; i < x.size(); i++) if (x[i]) return x[i];
        return 0;
    }
private:
    /*
    * the number of integers that can be represented is (1 << y.size())
    */
    void canonise() {
        for (int i = sz - 1; i > 0; i--) {
            for (int j = i - 1; j >= 0; j--) {
                if (x[i] & ((T)1 << j)) {
                    x[i] ^= x[j];
                }
            }
        }
        y.clear();
        for (int i = 0; i < x.size(); i++) {
            if (x[i]) y.push_back(i);
        }
        canonise = true;
    }
public:
    T kth_maximum(T k) {
        if (!canonised) canonise();
        T res = 0;
        for (int i = y.size() - 1; i >= 0; i--) {
            if (k & ((T)1 << i)) res ^= x[y[i]];
        }
        return res;
    }
    T kth_minimum(T k) {
        if (!canonised) canonise();
        T res = 0;
        for (int i = 0; i < y.size(); i++) {
            if (k & ((T)1 << i)) res ^= x[y[i]];
        }
        return res;
    }
};