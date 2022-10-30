struct Hld {
    vector<int> parent, heavy, depth, pos, top;

    Hld() {}
    void init(vector<vector<int>>& G) {
        int N = G.size();
        parent.resize(N), heavy.resize(N), depth.resize(N), pos.resize(N),
            top.resize(N);
        depth[0] = -1, dfs(G, 0);
        int t = 0;
        rep(i, N) if (heavy[parent[i]] != i) {
            int j = i;
            while (j != -1) {
                top[j] = i, pos[j] = t++;
                j = heavy[j];
            }
        }
    }

    int dfs(vector<vector<int>>& G, int i) {
        int w = 1, mw = 0;
        depth[i] = depth[parent[i]] + 1, heavy[i] = -1;
        for (int c : G[i]) {
            if (c == parent[i]) continue;
            parent[c] = i;
            int sw = dfs(G, c);
            if (sw > mw) heavy[i] = c, mw = sw;
            w += sw;
        }
        return w;
    }

    template <class OP>
    void path(int u, int v, OP op) {
        while (top[u] != top[v]) {
            if (depth[top[u]] > depth[top[v]]) swap(u, v);
            op(pos[top[v]], pos[v]);
            v = parent[top[v]];
        }
        if (depth[u] > depth[v]) swap(u, v);
        op(pos[u], pos[v]);  // value on vertex
        // op(pos[u]+1, pos[v]); // value on path
    }

    // segment tree
    template <class T, class S>
    void update(S& seg, int i, T val) {
        seg.update(pos[i], val);
    }

    // segment tree lazy
    template <class T, class S>
    void update(S& seg, int u, int v, T val) {
        path(u, v, [&](int l, int r) { seg.update(l, r, val); });
    }

    template <class T, class S>
    T query(S& seg, int u, int v) {
        T ans = 0;
        path(u, v, [&](int l, int r) { ans += seg.query(l, r); });  // query op
        return ans;
    }
};