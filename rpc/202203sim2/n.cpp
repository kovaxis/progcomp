
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define rep(i, n) for (int i = 0; i < n; i++)

template <class T>
struct St {
    vector<T> node;

    void resize(int N) { node.resize(4 * N); }

    T query(int l, int r, int v = 1, int vl = 0, int vr = -1) {
        if (vr == -1) vr = node.size() / 4;
        if (l == vl && r == vr) return node[v];
        int vm = (vl + vr) / 2;
        T val = 0;
        if (l >= vr || r <= vl) return val;
        val += query(l, min(r, vm), 2 * v, vl, vm);
        val += query(max(l, vm), r, 2 * v + 1, vm, vr);
        return val;
    }

    void update(int i, T val, int v = 1, int vl = 0, int vr = -1) {
        if (vr == -1) vr = node.size() / 4;
        if (vr - vl == 1) {
            node[v] = val;
            return;
        }
        int vm = (vl + vr) / 2;
        if (i < vm) {
            update(i, val, 2 * v, vl, vm);
        } else {
            update(i, val, 2 * v + 1, vm, vr);
        }
        node[v] = node[2 * v] + node[2 * v + 1];
    }
};

ll Y, N;
vector<ll> a, p, f, x, q;
St<ll> b;
vector<pair<ll, pair<int, int>>> evs;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> Y >> N;
    x.resize(Y);
    rep(i, Y) cin >> x[i];
    a.resize(N), p.resize(N), f.resize(N);
    rep(i, N) cin >> a[i] >> p[i] >> f[i];
    q.resize(N);
    b.resize(Y);

    rep(i, Y) evs.push_back({-x[i], {0, i}});
    rep(i, N) if (p[i] > x[a[i] - 1]) evs.push_back({-p[i], {1, i}});
    sort(evs.begin(), evs.end());

    for (auto ev : evs) {
        int t = ev.second.first;
        int i = ev.second.second;
        if (t == 0) {
            // add point
            b.update(i, 1);
            // cerr << "added x = " << x[i] << " at year " << i << endl;
        } else if (t == 1) {
            // query
            q[i] = b.query(a[i], a[i] + f[i]);
            // cerr << "doing query " << i << " in range [" << a[i] << ", "
            //     << a[i] + f[i] << ")" << endl;
        }
    }

    rep(i, N) cout << q[i] << "\n";
}