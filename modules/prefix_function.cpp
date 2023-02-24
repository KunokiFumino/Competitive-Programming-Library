/*
*
* prefix[i] = k means k is the maximum index that holds:
*     in string s = [0 ... k ... i ... ] s[0, k) = s[i - k, i)
*
*/
template<typename T> vector<int> prefix_function(const T& p) {
    vector<int> prefix(p.size());
    prefix[0] = -1;
    int k = -1;
    for (int i = 0; i < p.size(); i++) {
        while (k != -1 && p[k] != p[i]) k = prefix[k];
        prefix[i] = ++k;
    }
    return prefix;
}