template <class T>
struct StlSumSum {
    // immediate (result of querying in the segment)
    // lazy (value that has not been pushed to the children)
    vector<pair<T, T>> node;

    void reset(int N) { node.assign(4 * N, {0, 0}); }

    void build(const vector<T> &a, int v = 1, int vl = 0, int vr = -1) {
        node.resize(4 * a.size());
        if (vr == -1) vr = node.size() / 4;
        if (vr - vl == 1) {
            node[v].first = a[vl]; // construction
            return;
        }
        int vm = (vl + vr) / 2;
        build(a, 2 * v, vl, vm);
        build(a, 2 * v + 1, vm, vr);
        node[v].first = node[2 * v].first + node[2 * v + 1].first; // query op
        node[v].second = 0;                                        // update-zero
    }

    // helper: propagate lazy values in vertex `v` to both of its children
    void push(int v, int vl, int vr) {
        int vm = (vl + vr) / 2;
        T &lazy = node[v].second;
        node[2 * v].first += lazy * (vm - vl);     // update-op & query-op mix
        node[2 * v].second += lazy;                // update-op
        node[2 * v + 1].first += lazy * (vr - vm); // update-op & query-op mix
        node[2 * v + 1].second += lazy;            // update-op
        lazy = 0;                                  // update-zero
    }

    // update range [l, r) using val
    void update(int l, int r, T val, int v = 1, int vl = 0, int vr = -1) {
        if (vr == -1) vr = node.size() / 4;
        if (l >= vr || r <= vl || r <= l) return;
        if (l == vl && r == vr) {
            node[v].first += val * (vr - vl); // update-op & query-op mix
            node[v].second += val;            // update-op
            return;
        }
        push(v, vl, vr);
        int vm = (vl + vr) / 2;
        update(l, min(r, vm), val, 2 * v, vl, vm);
        update(max(l, vm), r, val, 2 * v + 1, vm, vr);
        node[v].first = node[2 * v].first + node[2 * v + 1].first; // query-op
    }

    // query range [l, r)
    T query(int l, int r, int v = 1, int vl = 0, int vr = -1) {
        if (vr == -1) vr = node.size() / 4;
        if (l <= vl && r >= vr) return node[v].first;
        int vm = (vl + vr) / 2;
        T val = 0; // query-zero
        if (l >= vr || r <= vl || r <= l) return val;
        push(v, vl, vr);
        val += query(l, min(r, vm), 2 * v, vl, vm);     // query-op
        val += query(max(l, vm), r, 2 * v + 1, vm, vr); // query-op
        return val;
    }
};

const ll INF = 1e18;

template <class T>
struct StlSetSum {
    // immediate (result of querying in the segment)
    // lazy (value that has not been pushed to the children)
    vector<pair<T, T>> node;

    void reset(int N) { node.assign(4 * N, {0, INF}); }

    void build(const vector<T> &a, int v = 1, int vl = 0, int vr = -1) {
        node.resize(4 * a.size());
        if (vr == -1) vr = node.size() / 4;
        if (vr - vl == 1) {
            node[v] = {a[vl], INF}; // construction
            return;
        }
        int vm = (vl + vr) / 2;
        build(a, 2 * v, vl, vm);
        build(a, 2 * v + 1, vm, vr);
        node[v].first = node[2 * v].first + node[2 * v + 1].first; // query op
        node[v].second = INF;                                      // update-zero
    }

    // helper: propagate lazy values in vertex `v` to both of its children
    void push(int v, int vl, int vr) {
        int vm = (vl + vr) / 2;
        T &lazy = node[v].second;
        if (lazy != INF) {
            node[2 * v].first = lazy * (vm - vl); // update-op & query-op mix
            node[2 * v].second = lazy;            // update-op
            node[2 * v + 1].first =
                lazy * (vr - vm);          // update-op & query-op mix
            node[2 * v + 1].second = lazy; // update-op
        }
        lazy = INF; // update-zero
    }

    // update range [l, r) using val
    void update(int l, int r, T val, int v = 1, int vl = 0, int vr = -1) {
        if (vr == -1) vr = node.size() / 4;
        if (l >= vr || r <= vl || r <= l) return;
        if (l == vl && r == vr) {
            node[v].first = val * (vr - vl); // update-op & query-op mix
            node[v].second = val;            // update-op
            return;
        }
        push(v, vl, vr);
        int vm = (vl + vr) / 2;
        update(l, min(r, vm), val, 2 * v, vl, vm);
        update(max(l, vm), r, val, 2 * v + 1, vm, vr);
        node[v].first = node[2 * v].first + node[2 * v + 1].first; // query-op
    }

    // query range [l, r)
    T query(int l, int r, int v = 1, int vl = 0, int vr = -1) {
        if (vr == -1) vr = node.size() / 4;
        if (l <= vl && r >= vr) return node[v].first;
        int vm = (vl + vr) / 2;
        T val = 0; // query-zero
        if (l >= vr || r <= vl || r <= l) return val;
        push(v, vl, vr);
        val += query(l, min(r, vm), 2 * v, vl, vm);     // query-op
        val += query(max(l, vm), r, 2 * v + 1, vm, vr); // query-op
        return val;
    }
};

template <class T>
struct StlSumMin {
    // immediate (result of querying in the segment)
    // lazy (value that has not been pushed to the children)
    vector<pair<T, T>> node;

    void reset(int N) { node.assign(4 * N, {0, 0}); }

    void build(const vector<T> &a, int v = 1, int vl = 0, int vr = -1) {
        node.resize(4 * a.size());
        if (vr == -1) vr = node.size() / 4;
        if (vr - vl == 1) {
            node[v] = {a[vl], 0}; // construction
            return;
        }
        int vm = (vl + vr) / 2;
        build(a, 2 * v, vl, vm);
        build(a, 2 * v + 1, vm, vr);
        node[v].first =
            min(node[2 * v].first, node[2 * v + 1].first); // query op
        node[v].second = 0;                                // update-zero
    }

    // helper: propagate lazy values in vertex `v` to both of its children
    void push(int v, int vl, int vr) {
        int vm = (vl + vr) / 2;
        T &lazy = node[v].second;
        node[2 * v].first += lazy;      // update-op & query-op mix
        node[2 * v].second += lazy;     // update-op
        node[2 * v + 1].first += lazy;  // update-op & query-op mix
        node[2 * v + 1].second += lazy; // update-op
        lazy = 0;                       // update-zero
    }

    // update range [l, r) using val
    void update(int l, int r, T val, int v = 1, int vl = 0, int vr = -1) {
        if (vr == -1) vr = node.size() / 4;
        if (l >= vr || r <= vl || r <= l) return;
        if (l == vl && r == vr) {
            node[v].first += val;  // update-op & query-op mix
            node[v].second += val; // update-op
            return;
        }
        push(v, vl, vr);
        int vm = (vl + vr) / 2;
        update(l, min(r, vm), val, 2 * v, vl, vm);
        update(max(l, vm), r, val, 2 * v + 1, vm, vr);
        node[v].first =
            min(node[2 * v].first, node[2 * v + 1].first); // query-op
    }

    // query range [l, r)
    T query(int l, int r, int v = 1, int vl = 0, int vr = -1) {
        if (vr == -1) vr = node.size() / 4;
        if (l <= vl && r >= vr) return node[v].first;
        int vm = (vl + vr) / 2;
        T val = INF; // query-zero
        if (l >= vr || r <= vl || r <= l) return val;
        push(v, vl, vr);
        val = min(val, query(l, min(r, vm), 2 * v, vl, vm));     // query-op
        val = min(val, query(max(l, vm), r, 2 * v + 1, vm, vr)); // query-op
        return val;
    }
};