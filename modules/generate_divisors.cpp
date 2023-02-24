vector<int> generate_divisors(int x) {
    vector<int> v;
    for (int i = 1; i <= x / i; i++) {
        if (x % i == 0) {
            v.push_back(i);
            if (i != x / i) v.push_back(x / i);
        }
    }
    return v;
}