#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

template <class T>
struct Stl {
    int n;
    vector<T> a, b;

    T qneut() { return {0, 0}; }
    T uneut() { return {0, 0}; }
    T merge(T x, T y) { return max(x, y); }
    void upd(int v, T x, int l, int r) {
        a[v].first += x.first;
        a[v].second += x.second;
        b[v].first += x.first;
        b[v].second += x.second;
    }

    Stl() {}
    Stl(int n) : n(n), a(4 * n, qneut()), b(4 * n, uneut()) {}

    void push(int v, int vl, int vm, int vr) {
        upd(2 * v, b[v], vl, vm);
        upd(2 * v + 1, b[v], vm, vr);
        b[v] = uneut();
    }

    // compute the query operation for the range [l, r)
    T query(int l, int r, int v = 1, int vl = 0, int vr = 1e9) {
        vr = min(vr, n);
        if (l <= vl && r >= vr) return a[v];
        if (l >= vr || r <= vl) return qneut();
        int vm = (vl + vr) / 2;
        push(v, vl, vm, vr);
        return merge(query(l, r, 2 * v, vl, vm), query(l, r, 2 * v + 1, vm, vr));
    }

    // apply update operation to range [l, r)
    void update(int l, int r, T x, int v = 1, int vl = 0, int vr = 1e9) {
        vr = min(vr, n);
        if (l >= vr || r <= vl || r <= l) return;
        if (l <= vl && r >= vr) upd(v, x, vl, vr);
        else {
            int vm = (vl + vr) / 2;
            push(v, vl, vm, vr);
            update(l, r, x, 2 * v, vl, vm);
            update(l, r, x, 2 * v + 1, vm, vr);
            a[v] = merge(a[2 * v], a[2 * v + 1]);
        }
    }
};

int N;
vector<ll> A;
vector<pair<ll, ll>> B;
Stl<pair<ll, ll>> C;
vector<bool> erased;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    while (TC--) {
        cin >> N;
        A.resize(N);
        rep(i, N) cin >> A[i];

        B.resize(N);
        rep(i, N) B[i] = {A[i] + (i + 1) - i, A[i] + (i + 1)};

        sort(B.begin(), B.end(), [](auto a, auto b) {
            return a.second < b.second;
        });

        C = {N};
        rep(i, N) C.update(i, i + 1, {B[i].first, i});

        erased.assign(N, false);
        int right = N - 1;
        ll nxt_val = 1e18;
        vector<ll> ans;
        rep(iter, N) {
            while (erased[right]) right -= 1;
            nxt_val = min(nxt_val, B[right].second);

            int left;
            {
                int l = 0, r = N - 1;
                while (l != r) {
                    int m = (l + r) / 2;
                    if (B[m].second >= nxt_val) r = m;
                    else l = m + 1;
                }
                left = l;
            }

            int to_erase = C.query(left, N).second;
            erased[to_erase] = true;
            C.update(to_erase, to_erase + 1, {-1e9, 0});
            if (B[to_erase].first <= nxt_val) {
                ans.push_back(nxt_val);
                nxt_val -= 1;
            }
        }

        for (int x : ans) cout << x << " ";
        cout << "\n";
    }
}
