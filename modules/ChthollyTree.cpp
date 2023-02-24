template <typename T> class ChthollyTree {
private:
    static constexpr int inf = 0x3FFFFFFF;
public:
    struct ChthollyTreeNode {
        int l, r;
        mutable T t;
        bool operator <(const ChthollyTreeNode& rhs) const {
            return l < rhs.l;
        }
    };
    set<ChthollyTreeNode> chtholly;
    auto split(int x) {
        auto it = --chtholly.upper_bound({ x,inf,0 });
        int l = it->l, r = it->r;
        T t = it->t;
        if (l == x) return it;
        chtholly.erase(it);
        chtholly.insert({ l,x,t });
        return chtholly.insert({ x,r,t }).first;
    }
    void assign(int l, int r, T t) {
        auto itr = split(r), itl = split(l);
        chtholly.erase(itl, itr);
        chtholly.insert({ l,r,t });
    }
};