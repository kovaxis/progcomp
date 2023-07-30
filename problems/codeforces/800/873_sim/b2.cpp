#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

#define cerr \
    if (0) cerr

template <class T>
struct Stl3 {
    // immediate, lazy
    vector<pair<T, T>> a;

    T qneutral() { return 0; }
    T merge(T l, T r) { return l + r; }
    T uneutral() { return INT64_MIN; }
    void update(pair<T, T> &u, T val, int l, int r) {
        if (val != INT64_MIN) {
            u.first = val * (r - l), u.second = val;
        }
    }

    Stl3() {}
    Stl3(int N) : a(4 * N, {qneutral(), uneutral()}) {} // node neutral

    void push(int v, int vl, int vm, int vr) {
        update(a[2 * v], a[v].second, vl, vm);     // node update
        update(a[2 * v + 1], a[v].second, vm, vr); // node update
        a[v].second = uneutral();                  // update neutral
    }

    // query for range [l, r)
    T query(int l, int r, int v = 1, int vl = 0, int vr = -1) {
        if (vr == -1) vr = a.size() / 4;
        if (l <= vl && r >= vr) return a[v].first; // query op
        if (l >= vr || r <= vl) return qneutral(); // query neutral
        int vm = (vl + vr) / 2;
        push(v, vl, vm, vr);
        return merge(query(l, r, 2 * v, vl, vm), query(l, r, 2 * v + 1, vm, vr)); // item merge
    }

    // update range [l, r) using val
    void update(int l, int r, T val, int v = 1, int vl = 0, int vr = -1) {
        if (vr == -1) vr = a.size() / 4;
        if (l >= vr || r <= vl || r <= l) return;
        if (l <= vl && r >= vr) update(a[v], val, vl, vr); // node update
        else {
            int vm = (vl + vr) / 2;
            push(v, vl, vm, vr);
            update(l, r, val, 2 * v, vl, vm);
            update(l, r, val, 2 * v + 1, vm, vr);
            a[v].first = merge(a[2 * v].first, a[2 * v + 1].first); // node merge
        }
    }
};

int N;
vector<int> A;
Stl3<ll> ok;
vector<ll> mx;
vector<int> mn;

const ll INF = 1e18;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    while (TC--) {
        cin >> N;
        A.resize(N);
        rep(i, N) cin >> A[i];

        ll ans = 0;
        rep(l, N) {
            ans += (N - l) * (N - l + 1) / 2;
        }
        cerr << ans << " lengths of subarrays" << endl;

        mx.assign(N, INF);
        mn.clear();

        rep(i, N) {
            mx[i] = i == 0 ? A[i] : max(A[i - 1], A[i]);
            if (i > 0) {
                while (!mn.empty() && A[mn.back()] > A[i]) mn.pop_back();
                mn.push_back(i);
            }
            int j = lower_bound(mx.begin(), mx.end(), A[i]) - mx.begin();
            ok.update(j, N, 0);
        }

        rep(i, N + 1) {
            int r = i;
            rep(l, i) {
                int lmax = mx.query(l, i);
                while (r < N && mn.query(i, r + 1) > lmax) r++;
                cerr << r - i + 1 << " subarrays contains split-point " << i << " starting at " << l << endl;
                ans -= r - i + 1;
            }
        }

        cout << ans << "\n";
    }
}
