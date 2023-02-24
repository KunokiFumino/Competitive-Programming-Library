/*
*
* Convex hull trick is usually used to optimize dynamic programming.
* If your dp code looks like:
*     for y in range_y:
*         for x in range_x:
*           dp[y] = min{f1(x) * y + f2(x) + f3(y)}
* Let:
*     z = f1(x) * y + f2(x)
* Imagine here y is the independent variable, and z is the dependent variable.
* So we got a series of lines when enumerating x, and they stay the same when enumerating y.
* Now the problem becomes:
*     What is the minimum/maximum value of a series of lines on a specific value?
* After the process(O(range_x)) of convex hull trick, it only keeps the minimum/maximum parts of those lines.
* Now your dp code becomes:
*     process()
*     for y in range_y:
*         dp[y] = query(y) + f3(y)
* Each query can be processed in  O(log2(range_x)).
*
*/
template <typename T> class ConvexHull {
private:
    vector<pair<T, T> > lines;
    map<T, T> slope2intercept;
    vector<pair<pair<T, T>, double> > extremum;
public:
    void clear() {
        lines.clear();
        slope2intercept.clear();
        extremum.clear();
    }
    void add_line(T k, T b) {
        lines.push_back({ k,b });
    }

    void minimize() {
        slope2intercept.clear();
        for (int i = 0; i < lines.size(); i++) {
            auto& line = lines[i];
            if (slope2intercept.find(line.first) != slope2intercept.end()) slope2intercept[line.first] = slope2intercept[line.first] < line.second ? slope2intercept[line.first] : line.second;
            else slope2intercept[line.first] = line.second;
        }
        extremum.clear();
        for (auto i = slope2intercept.rbegin(); i != slope2intercept.rend(); i++) {
            while (extremum.size() > 1) {
                auto ex = extremum[extremum.size() - 2];
                if ((double)(ex.first.second - i->second) / (double)(i->first - ex.first.first) <= ex.second) extremum.pop_back();
                else break;
            }
            if (!extremum.empty()) {
                auto& ex = extremum.back();
                ex.second = (double)(ex.first.second - i->second) / (double)(i->first - ex.first.first);
            }
            extremum.push_back({ {i->first,i->second}, 1e18 });
        }
    }
    void maximize() {
        slope2intercept.clear();
        for (int i = 0; i < lines.size(); i++) {
            auto& line = lines[i];
            if (slope2intercept.find(line.first) != slope2intercept.end()) slope2intercept[line.first] = slope2intercept[line.first] > line.second ? slope2intercept[line.first] : line.second;
            else slope2intercept[line.first] = line.second;
        }
        extremum.clear();
        for (auto i = slope2intercept.begin(); i != slope2intercept.end(); i++) {
            while (extremum.size() > 1) {
                auto ex = extremum[extremum.size() - 2];
                if ((double)(ex.first.second - i->second) / (double)(i->first - ex.first.first) <= ex.second) extremum.pop_back();
                else break;
            }
            if (!extremum.empty()) {
                auto& ex = extremum.back();
                ex.second = (double)(ex.first.second - i->second) / (double)(i->first - ex.first.first);
            }
            extremum.push_back({ {i->first,i->second}, 1e18 });
        }
    }
    T query(T x) {
        if (extremum.empty()) return 0;
        int l = -1, r = extremum.size() - 1;
        while (l + 1 < r) {
            int mid = (l + r) >> 1;
            if (extremum[mid].second < x) l = mid;
            else r = mid;
        }
        return extremum[r].first.first * x + extremum[r].first.second;
    }
};