class _2_SAT {
public:
    int n;
    vector<int> solution;
private:
    Graph<int, int> g;
    Tarjan<int, int> tj;
public:
    void reset(int n) {
        this->n = n;
        g.reset(n << 1);
        tj.bind(&g);
    }
    void add_constraint_must_choose(int u) {
        g.add_edge(u << 1, u << 1 | 1, 1, true);
    }
    void add_constraint_must_not_choose(int u) {
        g.add_edge(u << 1 | 1, u << 1, 1, true);
    }
    void add_constraint_must_on_same_side(int u, int v) {
        g.add_edge(u << 1, v << 1, 1, true);
        g.add_edge(u << 1 | 1, v << 1 | 1, 1, true);
        g.add_edge(v << 1, u << 1, 1, true);
        g.add_edge(v << 1 | 1, u << 1 | 1, 1, true);
    }
    void add_constraint_must_on_different_side(int u, int v) {
        g.add_edge(u << 1, v << 1 | 1, 1, true);
        g.add_edge(u << 1 | 1, v << 1, 1, true);
        g.add_edge(v << 1, u << 1 | 1, 1, true);
        g.add_edge(v << 1 | 1, u << 1, 1, true);
    }
    void add_constraint_choose_at_least_one(int u, int v) {
        g.add_edge(u << 1, v << 1 | 1, 1, true);
        g.add_edge(v << 1, u << 1 | 1, 1, true);
    }
    bool generate_solution() {
        tj.run();
        tj.generate_dag();
        check_memory(solution, n);
        for (int i = 0; i < n; i++) {
            if (tj.sid[i << 1] == tj.sid[i << 1 | 1]) return false;
        }
        for (int i = 0; i < n; i++) solution[i] = tj.sid[i << 1] < tj.sid[i << 1 | 1] ? 0 : 1;
        return true;
    }
};