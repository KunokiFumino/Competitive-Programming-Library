template <typename Twe> class Edge {
public:
    int a, z, inv;
    Twe w;
    Edge() : inv(-1) {}
    Edge(int a, int z, Twe w) : a(a), z(z), w(w), inv(-1) {}
};