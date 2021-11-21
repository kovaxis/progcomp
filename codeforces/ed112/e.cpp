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

typedef int T;

int N;
// immediate, lazy
pair<T, T> st[4 * 2000002];

const T ZERO = INT32_MAX;
T opquery(const T& a, const T& b) { return min(a, b); }

void st_push(int v) {
    st[2 * v].first += st[v].second;
    st[2 * v].second += st[v].second;
    st[2 * v + 1].first += st[v].second;
    st[2 * v + 1].second += st[v].second;
    st[v].second = 0;
}

void st_update(int l, int r, int val, int v = 1, int vl = 0, int vr = N - 1) {
    if (l == vl && r == vr) {
        st[v].first += val;
        st[v].second += val;
        return;
    }
    st_push(v);
    int vm = (vl + vr) / 2;
    if (l <= vm) st_update(l, min(r, vm), val, 2 * v, vl, vm);
    if (r >= vm + 1) st_update(max(l, vm + 1), r, val, 2 * v + 1, vm + 1, vr);
    st[v].first = opquery(st[2 * v].first, st[2 * v + 1].first);
}

T st_query(int l, int r, int v = 1, int vl = 0, int vr = N - 1) {
    if (l <= vl && r >= vr) {
        return st[v].first;
    }
    st_push(v);
    int vm = (vl + vr) / 2;
    T val = ZERO;
    if (l <= vm) val = opquery(val, st_query(l, min(r, vm), 2 * v, vl, vm));
    if (r >= vm + 1)
        val = opquery(val, st_query(max(l, vm + 1), r, 2 * v + 1, vm + 1, vr));
    return val;
}

pair<int, pair<int, int>> segs[300001];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n >> N;
    N = N * 2 - 1;
    rep(i, n) {
        int l, r, w;
        cin >> l >> r >> w;
        segs[i] = {w, {(l - 1) * 2, (r - 1) * 2}};
    }
    sort(segs, segs + n);
    int top = 0;
    int mincost = INT32_MAX;
    rep(bot, n) {
        while (top < n && st_query(0, N - 1) == 0) {
            st_update(segs[top].second.first, segs[top].second.second, 1);
            top += 1;
        }
        if (st_query(0, N - 1) != 0) {
            int cost = segs[top - 1].first - segs[bot].first;
            mincost = min(mincost, cost);
        }
        st_update(segs[bot].second.first, segs[bot].second.second, -1);
    }
    cout << mincost << '\n';
}
