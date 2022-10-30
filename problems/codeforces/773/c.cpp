#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define REPGET(_1, _2, _3, NAME, ...) NAME
#define rep3(i, b, n) for (int i = (int)(b); i < (int)(n); i++)
#define rep2(i, n) rep3(i, 0, (n))
#define rep(...) REPGET(__VA_ARGS__, rep3, rep2)(__VA_ARGS__)
#define invrep3(i, b, n) for (int i = (int)(n)-1; i >= (int)(b); i--)
#define invrep2(i, n) invrep3(i, 0, (n))
#define invrep(...) REPGET(__VA_ARGS__, invrep3, invrep2)(__VA_ARGS__)

template <class T>
struct Stl {
    // immediate (result of querying in the segment)
    // lazy (value that has not been pushed to the children)
    vector<pair<T, bool>> node;

    Stl() {}
    void build(int n, int v = 1, int vl = 0, int vr = -1) {
        node.resize(4 * n);
        if (vr == -1) vr = node.size() / 4 - 1;
        if (vl == vr) {
            node[v].first = 1;  // construction
            return;
        }
        int vm = (vl + vr) / 2;
        build(n, 2 * v, vl, vm);
        build(n, 2 * v + 1, vm + 1, vr);
        node[v].first = node[2 * v].first + node[2 * v + 1].first;  // query op
    }

    // helper: propagate lazy values in vertex `v` to both of its children
    void push(int v, int vl, int vr) {
        int vm = (vl + vr) / 2;
        bool& lazy = node[v].second;
        if (lazy) {
            node[2 * v].first = 0;          // update-op & query-op mix
            node[2 * v].second = true;      // update-op
            node[2 * v + 1].first = 0;      // update-op & query-op mix
            node[2 * v + 1].second = true;  // update-op
        }
        lazy = false;  // update-zero
    }

    // apply the update operation to the range [l, r] (inclusive) in O(log N)
    void update(int l, int r, int v = 1, int vl = 0, int vr = -1) {
        if (vr == -1) vr = node.size() / 4 - 1;
        if (l == vl && r == vr) {
            node[v].first = 0;      // update-op & query-op mix
            node[v].second = true;  // update-op
            return;
        }
        push(v, vl, vr);
        int vm = (vl + vr) / 2;
        if (l <= vm) update(l, min(r, vm), 2 * v, vl, vm);
        if (r >= vm + 1) update(max(l, vm + 1), r, 2 * v + 1, vm + 1, vr);
        node[v].first = node[2 * v].first + node[2 * v + 1].first;  // query-op
    }

    // apply the query operation to the range [l, r] (inclusive) in O(log N)
    T query(int l, int r, int v = 1, int vl = 0, int vr = -1) {
        if (vr == -1) vr = node.size() / 4 - 1;
        if (l <= vl && r >= vr) {
            return node[v].first;
        }
        push(v, vl, vr);
        int vm = (vl + vr) / 2;
        T val = 0;                                                // query-zero
        if (l <= vm) val += query(l, min(r, vm), 2 * v, vl, vm);  // query-op
        if (r >= vm + 1)
            val += query(max(l, vm + 1), r, 2 * v + 1, vm + 1, vr);  // query-op
        return val;
    }
};

const int INF = 1e9;

template <class T>
struct St {
    vector<pair<T, T>> node;

    St() {}

    void build(const vector<T>& a, int v = 1, int vl = 0, int vr = -1) {
        node.resize(4 * a.size());
        if (vr == -1) vr = node.size() / 4 - 1;
        if (vl == vr) {
            node[v] = {a[vl], INF};  // construction
            return;
        }
        int vm = (vl + vr) / 2;
        build(a, 2 * v, vl, vm);
        build(a, 2 * v + 1, vm + 1, vr);
        node[v].second =
            min(node[2 * v].second, node[2 * v + 1].second);  // query op
    }

    T query(int l, int r, int v = 1, int vl = 0, int vr = -1) {
        if (vr == -1) vr = node.size() / 4 - 1;
        if (l == vl && r == vr) return node[v].second;
        int vm = (vl + vr) / 2;
        T val = INF;  // neutral element
        if (r < l) return val;
        if (l <= vm)
            val = min(val, query(l, min(r, vm), 2 * v, vl, vm));  // query op
        if (r >= vm + 1)
            val = min(val, query(max(l, vm + 1), r, 2 * v + 1, vm + 1,
                                 vr));  // query op
        return val;
    }

    void update(int i, T val, int v = 1, int vl = 0, int vr = -1) {
        if (vr == -1) vr = node.size() / 4 - 1;
        if (vl == vr) {
            node[v].second = val;
            return;
        }
        int vm = (vl + vr) / 2;
        if (i <= vm) {
            update(i, val, 2 * v, vl, vm);
        } else {
            update(i, val, 2 * v + 1, vm + 1, vr);
        }
        node[v].second =
            min(node[2 * v].second, node[2 * v + 1].second);  // query op
    }
};

int N, Q;
Stl<int> sus;
St<int> ranges;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N, Q;
    cin >> N >> Q;
    vector<pair<int, pair<int, int>>> queries(Q);
    vector<pair<int, int>> range_sort;
    vector<int> range_idx;
    vector<int> range_l;
    rep(i, Q) {
        int t;
        cin >> t;
        if (t == 0) {
            // report
            int l, r, x;
            cin >> l >> r >> x;
            queries[i] = {x, {l - 1, r - 1}};
            if (x == 1) {
                int idx = range_sort.size();
                range_sort.push_back({l - 1, idx});
            }
        } else {
            // question
            int j;
            cin >> j;
            queries[i] = {2, {j - 1, 0}};
        }
    }
    sort(range_sort.begin(), range_sort.end());
    range_idx.resize(range_sort.size());
    range_l.resize(range_sort.size());
    rep(i, range_sort.size()) {
        range_idx[range_sort[i].second] = i;
        range_l[i] = range_sort[i].first;
    }
    sus.build(N);
    ranges.build(range_l);
    // cerr << "got here with " << queries.size() << endl;
    int si = 0;
    for (auto q : queries) {
        int t = q.first;
        int l = q.second.first;
        int r = q.second.second;
        if (t == 0) {
            // clear sus
            // cerr << "cleared " << l << ".." << r << " of sus" << endl;
            sus.update(l, r);
        } else if (t == 1) {
            // add sus range
            // cerr << "added " << l << ".." << r << " as sus range" << endl;
            int i = range_idx[si];
            assert(range_l[i] == l);
            ranges.update(i, r);
            si += 1;
        } else {
            // person query
            int j = l;
            // cerr << "querying person " << j << endl;

            if (sus.query(j, j) == 0) {
                // person is clear
                cout << "NO\n";
                continue;
            }

            int l, r;
            l = 0;
            r = j;
            while (l != r) {
                int m = l + (r - l) / 2;
                if (sus.query(m, j) == 1) {
                    r = m;
                } else {
                    l = m + 1;
                }
            }
            int r_l = l;

            l = j;
            r = N - 1;
            while (l != r) {
                int m = (l + r + 1) / 2;
                if (sus.query(j, m) == 1) {
                    l = m;
                } else {
                    r = m - 1;
                }
            }
            int r_r = r;

            // cerr << "person range: " << r_l << " .. " << r_r << endl;

            // get ranges with r_l <= l <= j
            int m_l = lower_bound(range_l.begin(), range_l.end(), r_l) -
                      range_l.begin();
            int m_r = lower_bound(range_l.begin(), range_l.end(), j + 1) -
                      range_l.begin();
            // cerr << "checking if ranges " << m_l << " to " << m_r - 1
            //     << " lie before " << r_r << endl;
            int mn = ranges.query(m_l, m_r - 1);
            if (mn <= r_r) {
                cout << "YES\n";
            } else {
                cout << "N/A\n";
            }
        }

        // cerr << "sus:" << endl;
        // rep(i, N) { cerr << sus.query(i, i) << " "; }
        // cerr << endl;
        // cerr << "ranges:" << endl;
        // rep(i, range_l.size()) { cerr << range_l[i] << " "; }
        // cerr << endl;
        // rep(i, range_l.size()) { cerr << ranges.query(i, i) << " "; }
        // cerr << endl;
        // cerr << endl;
    }
}
