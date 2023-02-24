/*
*
* z[i] = k means k is the maximum index that holds:
*     in string s = [0 ... k ... i ... ] s[0, k) = s[i, i + k)
* specially z[0] = 0
*
*/
template<typename T> vector<int> z_function(const T& p) {
    vector<int> z(p.size());
    for (int i = 1, l = 0, r = 0; i < p.size(); ++i) {
        if (i <= r && z[i - l] < r - i + 1) z[i] = z[i - l];
        else {
            z[i] = (r - i + 1 > 0 ? r - i + 1 : 0);
            while (i + z[i] < p.size() && p[z[i]] == p[i + z[i]]) ++z[i];
        }
        if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
    }
    return z;
}