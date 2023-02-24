/*
* Twv must allow { +, *, Twv(0), < }
*/
template <typename Twv = int, typename Twe = int> class HeavyLightDecomposition {
private:
    int top_index, n, R;
    vector<int> heavy_son, heavy_path_top, subtree_last_index, vertex_to_index, index_to_vertex;
    vector<Twv> feed;
    SegmentTree<Twv> st;
    Graph<Twv, Twe>* t_;
public:
    void bind(Graph<Twv, Twe>* t, int r = 0) {
        t_ = t;
        R = r;
        t_->root(R);
    }
    void decomposition() {
        check_memory(heavy_son, n);
        check_memory(heavy_path_top, n);
        check_memory(subtree_last_index, n);
        check_memory(vertex_to_index, n);
        check_memory(index_to_vertex, n);
        check_memory(feed, n);
        top_index = 1;
        dfs1(R);
        dfs2(R, R);
        for (int i = 0; i < n; i++) feed[i] = t_->wV[index_to_vertex[i]];
        st.build(0, n, feed);
    }
    void update_col(int u, int v, Twv k) {
        while (heavy_path_top[u] != heavy_path_top[v]) {
            if (t_->d[heavy_path_top[u]] < t_->d[heavy_path_top[v]]) swap(u, v);
            st.update_col(vertex_to_index[heavy_path_top[u]], vertex_to_index[u] + 1, k);
            u = t_->f[heavy_path_top[u]];
        }
        if (vertex_to_index[u] > vertex_to_index[v]) swap(u, v);
        st.update_col(vertex_to_index[u], vertex_to_index[v] + 1, k);
    }
    void update_mul(int u, int v, Twv k) {
        while (heavy_path_top[u] != heavy_path_top[v]) {
            if (t_->d[heavy_path_top[u]] < t_->d[heavy_path_top[v]]) swap(u, v);
            st.update_mul(vertex_to_index[heavy_path_top[u]], vertex_to_index[u] + 1, k);
            u = t_->f[heavy_path_top[u]];
        }
        if (vertex_to_index[u] > vertex_to_index[v]) swap(u, v);
        st.update_mul(vertex_to_index[u], vertex_to_index[v] + 1, k);
    }
    void update_add(int u, int v, Twv k) {
        while (heavy_path_top[u] != heavy_path_top[v]) {
            if (t_->d[heavy_path_top[u]] < t_->d[heavy_path_top[v]]) swap(u, v);
            st.update_add(vertex_to_index[heavy_path_top[u]], vertex_to_index[u] + 1, k);
            u = t_->f[heavy_path_top[u]];
        }
        if (vertex_to_index[u] > vertex_to_index[v]) swap(u, v);
        st.update_add(vertex_to_index[u], vertex_to_index[v] + 1, k);
    }
    void update_col(int u, Twv k) {
        st.update_col(vertex_to_index[u], subtree_last_index[u], k);
    }
    void update_mul(int u, Twv k) {
        st.update_mul(vertex_to_index[u], subtree_last_index[u], k);
    }
    void update_add(int u, Twv k) {
        st.update_add(vertex_to_index[u], subtree_last_index[u], k);
    }
    Twv query_sum(int u, int v) {
        Twv ret = 0;
        while (heavy_path_top[u] != heavy_path_top[v]) {
            if (t_->d[heavy_path_top[u]] < t_->d[heavy_path_top[v]]) swap(u, v);
            Twv tmp = st.query_sum(vertex_to_index[heavy_path_top[u]], vertex_to_index[u] + 1);
            ret += tmp;
            u = t_->f[heavy_path_top[u]];
        }
        if (vertex_to_index[u] > vertex_to_index[v]) swap(u, v);
        ret += st.query_sum(vertex_to_index[u], vertex_to_index[v] + 1);
        return ret;
    }
    pair<Twv, int> query_max(int u, int v) {
        pair<Twv, int> ret = { st.query_max(vertex_to_index[u],vertex_to_index[u] + 1),u };
        while (heavy_path_top[u] != heavy_path_top[v]) {
            if (t_->d[heavy_path_top[u]] < t_->d[heavy_path_top[v]]) swap(u, v);
            pair<Twv, int> tmp = st.query_max(vertex_to_index[heavy_path_top[u]], vertex_to_index[u] + 1);
            tmp.second = index_to_vertex[tmp.second];
            if (ret < tmp) ret = tmp;
            u = t_->f[heavy_path_top[u]];
        }
        if (vertex_to_index[u] > vertex_to_index[v]) swap(u, v);
        pair<Twv, int> tmp = st.query_max(vertex_to_index[u], vertex_to_index[v] + 1);
        tmp.second = index_to_vertex[tmp.second];
        if (ret < tmp) ret = tmp;
        return ret;
    }
    pair<Twv, int> query_min(int u, int v) {
        pair<Twv, int> ret = { st.query_min(vertex_to_index[u],vertex_to_index[u] + 1),u };
        while (heavy_path_top[u] != heavy_path_top[v]) {
            if (t_->d[heavy_path_top[u]] < t_->d[heavy_path_top[v]]) swap(u, v);
            pair<Twv, int> tmp = st.query_min(vertex_to_index[heavy_path_top[u]], vertex_to_index[u] + 1);
            tmp.second = index_to_vertex[tmp.second];
            if (ret > tmp) ret = tmp;
            u = t_->f[heavy_path_top[u]];
        }
        if (vertex_to_index[u] > vertex_to_index[v]) swap(u, v);
        pair<Twv, int> tmp = st.query_min(vertex_to_index[u], vertex_to_index[v] + 1);
        tmp.second = index_to_vertex[tmp.second];
        if (ret > tmp) ret = tmp;
        return ret;
    }
    Twv query_sum(int u) {
        return st.query_sum(vertex_to_index[u], subtree_last_index[u]);
    }
    pair<Twv, int> query_max(int u) {
        pair<Twv, int> ret = st.query_max(vertex_to_index[u], subtree_last_index[u]);
        ret.second = index_to_vertex[ret.second];
        return ret;
    }
    pair<Twv, int> query_min(int u) {
        pair<Twv, int> ret = st.query_min(vertex_to_index[u], subtree_last_index[u]);
        ret.second = index_to_vertex[ret.second];
        return ret;
    }
private:
    void dfs1(int u) {
        heavy_son[u] = -1;
        for (int i = 0; i < t_->adjacent[u].size(); i++) {
            auto& v = t_->adjacent[u][i];
            if (v == t_->f[u]) continue;
            dfs1(v);
            if (heavy_son[u] == -1) heavy_son[u] = v;
            else if (t_->subtree_sz[v] > t_->subtree_sz[heavy_son[u]]) heavy_son[u] = v;
        }
    }
    void dfs2(int u, int top_vertex) {
        heavy_path_top[u] = top_vertex;
        vertex_to_index[u] = top_index++;
        index_to_vertex[vertex_to_index[u]] = u;
        if (heavy_son[u] == -1) return;
        dfs2(heavy_son[u], top_vertex);
        for (int i = 0; i < t_->adjacent[u].size(); i++) {
            auto& v = t_->adjacent[u][i];
            if (v == t_->f[u]) continue;
            if (v != heavy_son[u]) dfs2(v, v);
        }
        subtree_last_index[u] = top_index;
    }
};