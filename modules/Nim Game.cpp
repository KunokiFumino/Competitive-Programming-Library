/*
* assume there are n(>=1) game(s) at the same time, and the i-th game's starting state is Si(in each NimGame instance).
* in a normal-play game(the player who can't move loses): 
*     if sg[S1] ^ sg[S2] ^ ... ^ sg[Sn] > 0
* then the first player can force a win.
* 
* in a misère-play game(the player who can't move wins):
*     if sg[S1] == sg[S2] == ... == sg[Sn] and n is even
*     if sg[S1] ^ sg[S2] ^ ... ^ sg[Sn] > 0 and exist i that sg[Si] > 1
* then the first player can force a win.
* 
* if the first player can't force a win, then the second player can force a win.
*/
class NimGame {
private:
    vector<int> visited;
    Graph<> g;
public:
    vector<int> sg;
private:
    bool get_sg(int u, int f) {
        visited[u] = f;
        set<int> s;
        for (int i = 0; i < g.get_fanout(u); i++) {
            int v = g.get_o_edge(u, i).z;
            if (visited[v] == f) return false;
            if (visited[v] == -1) get_sg(v, f);
            s.insert(sg[v]);
        }
        for (int i = 0;; i++) {
            if (s.find(i) == s.end()) {
                sg[u] = i;
                return true;
            }
        }
        return false;
    }
    
public:
    void reset(int n) {
        g.reset(n);
        visited.assign(n, -1);
        sg.assign(n, 0);
    }
    void add_transform(int u, int v) {
        g.add_edge(u, v, 1, true);
    }
    bool analyze() {
        for (int i = 0; i < g.V; i++) {
            if (visited[i] != -1) continue;
            if (!get_sg(i, i)) return false;
        }
        return true;
    }
};
